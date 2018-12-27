package com.zh.netty.client.handler;

import com.alibaba.fastjson.JSONObject;
import com.zh.netty.protocol.friend.UpdateFriendListResponsePacket;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;

/**
 * @author zh2683
 */
public class TestUpdateFriendsResponseHandler extends SimpleChannelInboundHandler<UpdateFriendListResponsePacket> {
    @Override
    protected void channelRead0(ChannelHandlerContext ctx, UpdateFriendListResponsePacket msg) throws Exception {
        System.out.println(JSONObject.toJSONString(msg));
    }
}
