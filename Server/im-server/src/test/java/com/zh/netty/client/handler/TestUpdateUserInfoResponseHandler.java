package com.zh.netty.client.handler;

import com.alibaba.fastjson.JSONObject;
import com.zh.netty.protocol.register.UpdateRegisterInfoResponsePacket;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;

/**
 * @author zh2683
 */
public class TestUpdateUserInfoResponseHandler extends SimpleChannelInboundHandler<UpdateRegisterInfoResponsePacket> {


    @Override
    protected void channelRead0(ChannelHandlerContext ctx, UpdateRegisterInfoResponsePacket msg) throws Exception {
        System.out.println(JSONObject.toJSONString(msg));
    }
}
