package com.zh.netty.handler;

import com.zh.netty.constant.AttributeKeyConsts;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;
import lombok.extern.slf4j.Slf4j;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

import java.net.InetSocketAddress;

/**
 * 抽出认证处理代码，不需要每个handler单独写了
 */
@Slf4j
@Component
@Scope(ConfigurableBeanFactory.SCOPE_SINGLETON)
@ChannelHandler.Sharable
public class CheckAuthHandler extends ChannelInboundHandlerAdapter {

    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
        if (!ctx.channel().hasAttr(AttributeKeyConsts.login) &&
                ctx.channel().hasAttr(AttributeKeyConsts.register)) {
            ctx.fireChannelRead(msg);
        } else {
            if (ctx.channel().hasAttr(AttributeKeyConsts.login)) {
                ctx.pipeline().remove(this);
                ctx.fireChannelRead(msg);
            } else {
                ctx.channel().close();
            }
        }
    }

    @Override
    public void handlerRemoved(ChannelHandlerContext ctx) throws Exception {
        InetSocketAddress socketAddress = (InetSocketAddress) ctx.channel().remoteAddress();
        if (ctx.channel().hasAttr(AttributeKeyConsts.login)) {
            log.info(String.format("%s已被认证，认证处理被移除", socketAddress.getHostString()));
        } else {
            log.info(String.format("%s未认证通过，连接关闭", socketAddress.getHostString()));
        }
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {
        InetSocketAddress socketAddress = (InetSocketAddress) ctx.channel().remoteAddress();
        log.error(String.format("%s认证检测异常", socketAddress.getHostString()), cause);
        ctx.channel().close();
    }
}
