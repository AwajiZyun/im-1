package com.zh.netty.handler;

import com.zh.constant.OnlineStateEnum;
import com.zh.constant.SystemConsts;
import com.zh.netty.constant.AttributeKeyConsts;
import com.zh.service.OnlineStateService;
import com.zh.util.SessionUtil;
import io.netty.channel.ChannelHandlerContext;
import io.netty.handler.timeout.IdleStateEvent;
import io.netty.handler.timeout.IdleStateHandler;
import io.netty.util.AttributeKey;
import lombok.extern.slf4j.Slf4j;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
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

    @Autowired
    private OnlineStateService onlineStateService;

    public IdleHandler() {
        super(SystemConsts.CHANNEL_IDLE_TIME, 0, 0, TimeUnit.SECONDS);
    }

    protected void channelIdle(ChannelHandlerContext ctx, IdleStateEvent evt) throws Exception {
        InetSocketAddress socketAddress = (InetSocketAddress) ctx.channel().remoteAddress();
        log.info(String.format("%s空闲时间过长，连接关闭", socketAddress.getHostString()));
        // 离线
        if (ctx.channel().hasAttr(AttributeKeyConsts.code)) {
            String code = ctx.channel().attr(AttributeKeyConsts.code).get();
            onlineStateService.offline(code);
        }
        SessionUtil.unbind(ctx.channel());
        ctx.channel().close();
    }

    @Override
    public void channelInactive(ChannelHandlerContext ctx) throws Exception {
        SessionUtil.unbind(ctx.channel());
        ctx.fireChannelInactive();
    }
}
