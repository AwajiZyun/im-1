package com.zh.netty.handler;

import com.zh.netty.constant.AttributeKeyConsts;
import com.zh.util.PacketCodec;
import com.zh.netty.protocol.login.LoginRequestPacket;
import com.zh.netty.protocol.login.LoginResponsePacket;
import com.zh.service.LoginService;
import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

import java.net.InetSocketAddress;

/**
 * 登录请求处理
 * @author zh2683
 */
@Component
@Scope(ConfigurableBeanFactory.SCOPE_SINGLETON)
@ChannelHandler.Sharable
public class LoginRequestHandler extends SimpleChannelInboundHandler<LoginRequestPacket> {

    private static final Logger logger = LoggerFactory.getLogger(LoginRequestHandler.class);

    @Autowired
    private LoginService loginService;

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, LoginRequestPacket msg) throws Exception {
        LoginResponsePacket loginResponsePacket = loginService.login(msg);
        if (loginResponsePacket.getSuccess()) {
            logger.info(String.format("%s登录成功", msg.getCode()));
            ctx.channel().attr(AttributeKeyConsts.login).set(true);
        }
        ByteBuf byteBuf = PacketCodec.encode(loginResponsePacket);
        ctx.channel().writeAndFlush(byteBuf);
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {
        InetSocketAddress socketAddress = (InetSocketAddress) ctx.channel().remoteAddress();
        logger.error(String.format("%s登录异常", socketAddress.getHostString()), cause);
        ctx.channel().close();
    }
}
