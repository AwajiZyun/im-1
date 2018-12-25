package com.zh.netty.client.handler;

import com.alibaba.fastjson.JSON;
import com.zh.netty.constant.AttributeKeyConsts;
import com.zh.netty.protocol.login.LoginResponsePacket;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;

/**
 * @author zh2683
 */
public class TestLoginResponseHandler extends SimpleChannelInboundHandler<LoginResponsePacket> {

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, LoginResponsePacket msg) throws Exception {
        System.out.println(JSON.toJSONString(msg));
        if (ctx.channel().hasAttr(AttributeKeyConsts.login)) {
            System.out.println(ctx.channel().attr(AttributeKeyConsts.login).get());
        }
    }
}
