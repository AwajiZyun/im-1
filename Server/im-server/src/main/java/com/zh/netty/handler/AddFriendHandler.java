package com.zh.netty.handler;

import com.zh.netty.protocol.friend.AddFriendRequestPacket;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

/**
 * @author zh2683
 */
@Component
@Scope(ConfigurableBeanFactory.SCOPE_SINGLETON)
@Slf4j
public class AddFriendHandler extends SimpleChannelInboundHandler<AddFriendRequestPacket> {

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, AddFriendRequestPacket msg) throws Exception {
        // TODO 添加相关逻辑
    }
}
