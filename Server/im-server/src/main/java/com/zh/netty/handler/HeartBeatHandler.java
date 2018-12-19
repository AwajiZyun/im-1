package com.zh.netty.handler;

import com.zh.netty.protocol.hearbeat.HeartBeatRequestPacket;
import com.zh.netty.protocol.hearbeat.HeartBeatResponsePacket;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

import java.net.InetSocketAddress;

/**
 * 心跳
 * @author zh2683
 */
@Component
@Scope(ConfigurableBeanFactory.SCOPE_SINGLETON)
@ChannelHandler.Sharable
public class HeartBeatHandler extends SimpleChannelInboundHandler<HeartBeatRequestPacket> {

    private static final Logger logger = LoggerFactory.getLogger(HeartBeatHandler.class);

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, HeartBeatRequestPacket msg) {
        InetSocketAddress socketAddress = (InetSocketAddress) ctx.channel().remoteAddress();
        logger.info(String.format("客户端%s心跳", socketAddress.getHostString()));
        ctx.channel().writeAndFlush(new HeartBeatResponsePacket());
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {
        InetSocketAddress socketAddress = (InetSocketAddress) ctx.channel().remoteAddress();
        logger.error(String.format("%s心跳失败", socketAddress.getHostString()), cause);
        ctx.channel().close();
    }
}
