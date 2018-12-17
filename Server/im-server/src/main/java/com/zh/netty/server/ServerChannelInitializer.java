package com.zh.netty.server;

import com.zh.main.SpringContextUtils;
import com.zh.netty.server.handler.*;
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
    private LoginRequestHandler loginRequestHandler;
    @Autowired
    private RegisterRequestHandler registerRequestHandler;
    @Autowired
    private IdleHandler idleHandler;
    @Autowired
    private HeartBeatHandler heartBeatHandler;
    @Autowired
    private CheckAuthHandler checkAuthHandler;

    @Override
    protected void initChannel(NioSocketChannel nioSocketChannel) throws Exception {
        nioSocketChannel.pipeline()
                .addLast(idleHandler)
                .addLast(SpringContextUtils.getBean(PacketDecoder.class))
                .addLast(checkAuthHandler)
                .addLast(heartBeatHandler)
                .addLast(registerRequestHandler)
                .addLast(loginRequestHandler)
                .addLast(SpringContextUtils.getBean(PacketEncoder.class));
    }
}
