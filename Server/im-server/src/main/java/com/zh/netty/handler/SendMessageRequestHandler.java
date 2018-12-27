package com.zh.netty.handler;

import com.zh.exception.UserOfflineException;
import com.zh.netty.protocol.message.MessageRequestPacket;
import com.zh.netty.protocol.message.MessageResponsePacket;
import com.zh.util.SessionUtil;
import io.netty.channel.Channel;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

/**
 * 向客户端转发消息
 */
@Slf4j
@Component
@Scope(ConfigurableBeanFactory.SCOPE_SINGLETON)
@ChannelHandler.Sharable
public class SendMessageRequestHandler extends SimpleChannelInboundHandler<MessageRequestPacket> {

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, MessageRequestPacket msg) throws Exception {
        Channel userChannel = SessionUtil.get(msg.getToUser());
        if (userChannel == null) {
            throw new UserOfflineException();
        }
        userChannel.writeAndFlush(msg);
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable t) {
        log.error("消息发送失败", t);
        MessageResponsePacket messageResponsePacket = new MessageResponsePacket();
        messageResponsePacket.setSuccess(false);
        if (t instanceof UserOfflineException) {
            messageResponsePacket.setMsg("用户不在线");
        }
        ctx.channel().writeAndFlush(messageResponsePacket);
    }
}
