package com.zh.netty.client.handler;

import com.alibaba.fastjson.JSONObject;
import com.zh.netty.protocol.friend.DeleteFriendResponsePacket;
import com.zh.netty.protocol.register.UpdateRegisterInfoResponsePacket;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;

/**
 * @author zh2683
 */
public class TestDeleteFriendResponseHandler extends SimpleChannelInboundHandler<DeleteFriendResponsePacket> {


    @Override
    protected void channelRead0(ChannelHandlerContext ctx, DeleteFriendResponsePacket msg) throws Exception {
        System.out.println(JSONObject.toJSONString(msg));
    }
}
