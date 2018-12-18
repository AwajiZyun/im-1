package com.zh.netty.handler;

import com.zh.constant.SystemConsts;
import io.netty.channel.ChannelHandlerContext;
import io.netty.handler.timeout.IdleStateEvent;
import io.netty.handler.timeout.IdleStateHandler;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

import java.util.concurrent.TimeUnit;

/**
 * 空闲检测
 * @author zh2683
 */
@Component
@Scope(ConfigurableBeanFactory.SCOPE_PROTOTYPE)
public class IdleHandler extends IdleStateHandler {

    public IdleHandler() {
        super(SystemConsts.CHANNEL_IDLE_TIME, 0, 0, TimeUnit.SECONDS);
    }

    protected void channelIdle(ChannelHandlerContext ctx, IdleStateEvent evt) throws Exception {
        System.out.println("空闲时间过长，关闭次此连接...");
        ctx.channel().close();
    }

    @Override
    public void handlerAdded(ChannelHandlerContext ctx) throws Exception {
        System.out.println("idleHandler被添加");
        super.handlerAdded(ctx);
    }

    @Override
    public void handlerRemoved(ChannelHandlerContext ctx) throws Exception {
        System.out.println("idleHandler被移除");
        super.handlerRemoved(ctx);
    }
}
