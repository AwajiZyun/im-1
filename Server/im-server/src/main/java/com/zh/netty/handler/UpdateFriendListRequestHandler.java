package com.zh.netty.handler;

import com.zh.domain.user.UserDTO;
import com.zh.domain.user.UserVO;
import com.zh.netty.constant.AttributeKeyConsts;
import com.zh.netty.protocol.friend.UpdateFriendListRequestPacket;
import com.zh.netty.protocol.friend.UpdateFriendListResponsePacket;
import com.zh.service.FriendService;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import lombok.extern.slf4j.Slf4j;
import org.apache.ibatis.annotations.Update;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.List;

@Slf4j
@ChannelHandler.Sharable
@Component
public class UpdateFriendListRequestHandler extends SimpleChannelInboundHandler<UpdateFriendListRequestPacket> {

    @Autowired
    private FriendService friendService;

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, UpdateFriendListRequestPacket msg) throws Exception {
        String userCode = ctx.channel().attr(AttributeKeyConsts.code).get();
        List<UserDTO> userDTOList = friendService.listFriends(userCode);
        List<UserVO> userVOS = new ArrayList<>(userDTOList.size());
        userDTOList.stream().forEach(userDTO -> {
            UserVO userVO = new UserVO();
            BeanUtils.copyProperties(userDTO, userVO);
            userVOS.add(userVO);
        });
        UpdateFriendListResponsePacket updateFriendListResponsePacket = new UpdateFriendListResponsePacket();
        updateFriendListResponsePacket.setSuccess(true);
        updateFriendListResponsePacket.setData(userVOS);
        ctx.channel().writeAndFlush(updateFriendListResponsePacket);
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable throwable) {
        UpdateFriendListResponsePacket updateFriendListResponsePacket = new UpdateFriendListResponsePacket();
        updateFriendListResponsePacket.setSuccess(false);
        updateFriendListResponsePacket.setMsg("查询用户好友列表失败");
        ctx.channel().writeAndFlush(updateFriendListResponsePacket);
    }
}
