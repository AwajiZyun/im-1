package com.zh.netty.handler;

import com.zh.domain.friend.AddFriendDTO;
import com.zh.domain.user.UserDTO;
import com.zh.domain.user.UserVO;
import com.zh.exception.UserNotFoundException;
import com.zh.netty.constant.AttributeKeyConsts;
import com.zh.netty.protocol.friend.AddFriendRequestPacket;
import com.zh.netty.protocol.friend.AddFriendResponsePacket;
import com.zh.service.FriendService;
import com.zh.service.OnlineStateService;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

/**
 * @author zh2683
 */
@Component
@Scope(ConfigurableBeanFactory.SCOPE_SINGLETON)
@Slf4j
@ChannelHandler.Sharable
public class AddFriendHandler extends SimpleChannelInboundHandler<AddFriendRequestPacket> {

    @Autowired
    private FriendService addFriendService;

    @Autowired
    private OnlineStateService onlineStateService;

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, AddFriendRequestPacket msg) throws Exception {
        AddFriendDTO addFriendDTO = new AddFriendDTO();
        addFriendDTO.setUserCode(ctx.channel().attr(AttributeKeyConsts.code).get());
        addFriendDTO.setSymbol(msg.getSymbol());
        AddFriendResponsePacket addFriendResponsePacket = new AddFriendResponsePacket();
        UserDTO userDTO = addFriendService.addFriend(addFriendDTO);
        UserVO userVO = new UserVO();
        BeanUtils.copyProperties(userDTO, userVO);
        userVO.setOnline(onlineStateService.getOnlineState(userVO.getCode()));
        addFriendResponsePacket.setData(userVO);
        addFriendResponsePacket.setSuccess(true);
        ctx.channel().writeAndFlush(addFriendResponsePacket);
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx,  Throwable throwable) {
        log.error("添加好友失败", throwable);
        AddFriendResponsePacket addFriendResponsePacket = new AddFriendResponsePacket();
        addFriendResponsePacket.setSuccess(false);
        if (throwable instanceof UserNotFoundException) {
            addFriendResponsePacket.setMsg("要添加的用户不存在");
        } else {
            addFriendResponsePacket.setMsg("添加好友失败");
        }
        ctx.channel().writeAndFlush(addFriendResponsePacket);
    }
}
