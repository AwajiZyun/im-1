package com.zh.netty.client.handler;

import com.alibaba.fastjson.JSONObject;
import com.zh.netty.protocol.message.MessageRequestPacket;
import com.zh.netty.protocol.message.MessageResponsePacket;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;

public class TestMessageResquestHandler extends SimpleChannelInboundHandler<MessageRequestPacket> {

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, MessageRequestPacket msg) throws Exception {
        System.out.println(JSONObject.toJSONString(msg));
    }
}
