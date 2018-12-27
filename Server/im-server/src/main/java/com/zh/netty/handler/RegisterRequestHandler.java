package com.zh.netty.handler;

import com.zh.netty.constant.AttributeKeyConsts;
import com.zh.netty.protocol.register.RegisterRequestPacket;
import com.zh.service.RegisterService;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import lombok.extern.slf4j.Slf4j;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

import java.net.InetSocketAddress;

/**
 * 注册请求处理
 */
@Slf4j
@Component
@Scope(ConfigurableBeanFactory.SCOPE_SINGLETON)
@ChannelHandler.Sharable
public class RegisterRequestHandler extends SimpleChannelInboundHandler<RegisterRequestPacket> {

    private static final Logger logger = LoggerFactory.getLogger(RegisterRequestHandler.class);

    @Autowired
    private RegisterService registerService;

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, RegisterRequestPacket msg) throws Exception {
        ctx.channel().attr(AttributeKeyConsts.register).set(true);
        ctx.channel().writeAndFlush(registerService.register(msg));
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {
        InetSocketAddress socketAddress = (InetSocketAddress) ctx.channel().remoteAddress();
        log.error(String.format("%s,注册异常", socketAddress.getHostString()), cause);
        ctx.channel().close();
    }
}
