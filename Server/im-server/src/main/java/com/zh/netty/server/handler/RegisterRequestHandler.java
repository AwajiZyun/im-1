package com.zh.netty.server.handler;

import com.zh.netty.constant.AttributeKeyConsts;
import com.zh.netty.protocol.register.RegisterRequestPacket;
import com.zh.service.RegisterService;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

/**
 * 注册请求处理
 */
@Component
@Scope(ConfigurableBeanFactory.SCOPE_SINGLETON)
@ChannelHandler.Sharable
public class RegisterRequestHandler extends SimpleChannelInboundHandler<RegisterRequestPacket> {

    @Autowired
    private RegisterService registerService;

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, RegisterRequestPacket msg) throws Exception {
        ctx.channel().attr(AttributeKeyConsts.register);
        ctx.channel().writeAndFlush(registerService.register(msg));
    }
}
