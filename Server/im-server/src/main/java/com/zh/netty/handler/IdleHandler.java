package com.zh.netty.handler;

import com.zh.constant.SystemConsts;
import io.netty.channel.ChannelHandlerContext;
import io.netty.handler.timeout.IdleStateEvent;
import io.netty.handler.timeout.IdleStateHandler;
import lombok.extern.slf4j.Slf4j;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

import java.net.InetSocketAddress;
import java.util.concurrent.TimeUnit;

/**
 * 空闲检测
 * @author zh2683
 */
@Slf4j
@Component
@Scope(ConfigurableBeanFactory.SCOPE_PROTOTYPE)
public class IdleHandler extends IdleStateHandler {

    public IdleHandler() {
        super(SystemConsts.CHANNEL_IDLE_TIME, 0, 0, TimeUnit.SECONDS);
    }

    protected void channelIdle(ChannelHandlerContext ctx, IdleStateEvent evt) throws Exception {
        InetSocketAddress socketAddress = (InetSocketAddress) ctx.channel().remoteAddress();
        log.info(String.format("%s空闲时间过长，连接关闭", socketAddress.getHostString()));
        ctx.channel().close();
    }

    @Override
    public void handlerAdded(ChannelHandlerContext ctx) throws Exception {
        super.handlerAdded(ctx);
    }

    @Override
    public void handlerRemoved(ChannelHandlerContext ctx) throws Exception {
        super.handlerRemoved(ctx);
    }
}
