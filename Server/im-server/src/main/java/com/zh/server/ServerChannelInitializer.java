package com.zh.server;

import com.zh.server.handler.PacketDecoder;
import com.zh.server.handler.PacketEncoder;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.socket.nio.NioSocketChannel;
import org.springframework.stereotype.Component;

/**
 * 初始化
 * @author zh2683
 */
@Component
public class ServerChannelInitializer extends ChannelInitializer<NioSocketChannel> {

    private PacketDecoder packetDecoder;
    private PacketEncoder packetEncoder;

    @Override
    protected void initChannel(NioSocketChannel nioSocketChannel) throws Exception {
        nioSocketChannel.pipeline()
                .addLast(packetDecoder)
                .addLast(packetEncoder);
    }
}
