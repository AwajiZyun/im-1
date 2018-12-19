package com.zh.netty.handler;

import com.zh.netty.constant.AttributeKeyConsts;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

import java.net.InetSocketAddress;

/**
 * 抽出认证处理代码，不需要每个handler单独写了
 */
@Component
@Scope(ConfigurableBeanFactory.SCOPE_SINGLETON)
@ChannelHandler.Sharable
public class CheckAuthHandler extends ChannelInboundHandlerAdapter {

    private static final Logger logger = LoggerFactory.getLogger(CheckAuthHandler.class);

    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
        if (!ctx.channel().hasAttr(AttributeKeyConsts.login) &&
                ctx.channel().hasAttr(AttributeKeyConsts.register)) {
            super.channelRead(ctx, msg);
        }
        if (ctx.channel().hasAttr(AttributeKeyConsts.login)) {
            ctx.pipeline().remove(this);
        } else {
            ctx.channel().close();
        }
    }

    @Override
    public void handlerRemoved(ChannelHandlerContext ctx) throws Exception {
        InetSocketAddress socketAddress = (InetSocketAddress) ctx.channel().remoteAddress();
        if (ctx.channel().hasAttr(AttributeKeyConsts.login)) {
            logger.info(String.format("%s已被认证，认证处理被移除", socketAddress.getHostString()));
        } else {
            logger.info(String.format("%s未认证通过，连接关闭", socketAddress.getHostString()));
        }
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {
        InetSocketAddress socketAddress = (InetSocketAddress) ctx.channel().remoteAddress();
        logger.error(String.format("%s认证检测异常", socketAddress.getHostString()), cause);
    }
}
