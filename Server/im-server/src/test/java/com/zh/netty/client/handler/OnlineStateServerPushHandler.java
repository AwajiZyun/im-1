package com.zh.netty.client.handler;

import com.alibaba.fastjson.JSONObject;
import com.zh.netty.protocol.onlinestate.OnlineStateServerPushPacket;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;

public class OnlineStateServerPushHandler extends SimpleChannelInboundHandler<OnlineStateServerPushPacket> {

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, OnlineStateServerPushPacket msg) throws Exception {
        switch (msg.getOnline()) {
            case offline:
                System.out.println(msg.getCode() + "下线了");
                break;
            case online:
                System.out.println(msg.getCode() + "上线了");
                break;
        }
    }
}
