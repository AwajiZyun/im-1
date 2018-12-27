package com.zh.netty.client.handler;

import com.alibaba.fastjson.JSONObject;
import com.zh.netty.protocol.message.MessageResponsePacket;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;

public class TestMessageResponseHandler extends SimpleChannelInboundHandler<MessageResponsePacket> {

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, MessageResponsePacket msg) throws Exception {
        System.out.println(JSONObject.toJSONString(msg));
    }
}
