package com.zh.service;

import com.zh.constant.OnlineStateEnum;
import com.zh.constant.SystemConsts;
import com.zh.domain.user.UserDTO;
import com.zh.netty.protocol.onlinestate.OnlineStateServerPushPacket;
import com.zh.util.SessionUtil;
import io.netty.channel.Channel;
import lombok.extern.slf4j.Slf4j;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

/**
 * 在线状态相关
 * 状态存在redis
 * @author zh2683
 */
@Service
@Slf4j
public class OnlineStateService {

    @Autowired
    private RedisService redisService;

    @Autowired
    private FriendService friendService;

    public void online(String code) {
        changeOnlineState(code, OnlineStateEnum.online);
    }

    public void offline(String code) {
        changeOnlineState(code, OnlineStateEnum.offline);
    }

    public void leave(String code) {
        changeOnlineState(code, OnlineStateEnum.leave);
    }

    public void busy(String code) {
        changeOnlineState(code, OnlineStateEnum.busy);
    }

    public void other(String code) {
        changeOnlineState(code, OnlineStateEnum.other);
    }

    private void changeOnlineState(String code, OnlineStateEnum stateEnum) {
        // 1，改变状态
        String stateKey = SystemConsts.ONLINE_STATE_PREFIX + code;
        if (!stateEnum.equals(OnlineStateEnum.offline)) {
            redisService.set(stateKey, String.valueOf(stateEnum.ordinal()));
        } else {
            redisService.delete(stateKey);
        }
        // 2, 通知好友
        List<UserDTO> friends = friendService.listFriends(code);
        friends.parallelStream().forEach(friend -> {
            Channel channel = SessionUtil.get(friend.getCode());
            if (channel == null) {
                return;
            }
            try {
                OnlineStateServerPushPacket onlineStateServerPushPacket = new OnlineStateServerPushPacket();
                onlineStateServerPushPacket.setCode(code);
                onlineStateServerPushPacket.setOnline(stateEnum);
                channel.writeAndFlush(onlineStateServerPushPacket);
            } catch (Exception e) {
                log.error("推送好友在线状态失败: " + friend.getCode(), e);
            }
        });
    }

    public OnlineStateEnum getOnlineState(String code) {
        String onlineStateStr = redisService.get(SystemConsts.ONLINE_STATE_PREFIX + code);
        if (StringUtils.isBlank(onlineStateStr)) {
            return OnlineStateEnum.offline;
        } else {
            OnlineStateEnum onlineStateEnum = OnlineStateEnum.getOnlineState(Integer.valueOf(onlineStateStr));
            return onlineStateEnum == null ? OnlineStateEnum.other : onlineStateEnum;
        }
    }

    public List<OnlineStateEnum> multiGetOnlineState(List<String> codes) {
        List<String> keys = codes.stream().map(code -> SystemConsts.ONLINE_STATE_PREFIX + code).collect(Collectors.toList());
        List<String> onlineStateStrs = redisService.multiGet(keys);
        if (onlineStateStrs == null) {
            return new ArrayList<>(keys.size());
        } else {
            List<OnlineStateEnum> onlineStateEnums = new ArrayList<>(onlineStateStrs.size());
            onlineStateStrs.stream().forEach(onlineStateStr -> {
                onlineStateEnums.add(onlineStateStr == null ? OnlineStateEnum.offline : OnlineStateEnum.getOnlineState(Integer.valueOf(onlineStateStr)));
            });
            return onlineStateEnums;
        }
    }

}
