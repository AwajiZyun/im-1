package com.zh.service;

import com.zh.constant.OnlineStateEnum;
import com.zh.constant.SystemConsts;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

/**
 * 在线状态相关
 * @author zh2683
 */
@Service
public class OnlineStateService {

    @Autowired
    private RedisService redisService;

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
        String stateKey = SystemConsts.ONLINE_STATE_PREFIX + code;
        if (!stateEnum.equals(OnlineStateEnum.offline)) {
            redisService.set(stateKey, String.valueOf(stateEnum.ordinal()));
        } else {
            redisService.delete(stateKey);
        }
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

}
