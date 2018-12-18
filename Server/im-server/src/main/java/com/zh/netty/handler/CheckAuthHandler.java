package com.zh.netty.handler;

import com.zh.netty.constant.AttributeKeyConsts;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

/**
 * 抽出认证处理代码，不需要每个handler单独写了
 */
@Component
@Scope(ConfigurableBeanFactory.SCOPE_SINGLETON)
@ChannelHandler.Sharable
public class CheckAuthHandler extends ChannelInboundHandlerAdapter {

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
        if (ctx.channel().hasAttr(AttributeKeyConsts.login)) {
            System.out.println("已被认证，认证处理被移除");
        } else {
            System.out.println("未认证通过，连接关闭");
        }
    }
}
