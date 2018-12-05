package com.zh.netty.server;

import com.zh.netty.server.handler.LoginRequestHandler;
import com.zh.netty.server.handler.PacketDecoder;
import com.zh.netty.server.handler.PacketEncoder;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.socket.nio.NioSocketChannel;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

/**
 * 初始化
 * @author zh2683
 */
@Component
public class ServerChannelInitializer extends ChannelInitializer<NioSocketChannel> {

    @Autowired
    private PacketDecoder packetDecoder;
    @Autowired
    private PacketEncoder packetEncoder;
    @Autowired
    private LoginRequestHandler loginRequestHandler;

    @Override
    protected void initChannel(NioSocketChannel nioSocketChannel) throws Exception {
        nioSocketChannel.pipeline()
                .addLast(packetDecoder)
                .addLast(loginRequestHandler)
                .addLast(packetEncoder);
    }
}
