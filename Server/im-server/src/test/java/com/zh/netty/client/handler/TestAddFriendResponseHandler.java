package com.zh.netty.client.handler;

import com.alibaba.fastjson.JSONObject;
import com.zh.netty.protocol.friend.AddFriendResponsePacket;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import lombok.extern.slf4j.Slf4j;

/**
 * @author zh2683
 */
@Slf4j
public class TestAddFriendResponseHandler extends SimpleChannelInboundHandler<AddFriendResponsePacket> {

    @Override
    public void channelActive(ChannelHandlerContext ctx) {
        log.info("添加好友响应处理器被添加");
    }


    @Override
    protected void channelRead0(ChannelHandlerContext ctx, AddFriendResponsePacket msg) throws Exception {
      log.info("添加好友回复:" + JSONObject.toJSONString(msg));
    }
}
