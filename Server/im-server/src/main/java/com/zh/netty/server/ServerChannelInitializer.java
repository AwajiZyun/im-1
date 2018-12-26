package com.zh.netty.server;

import com.zh.netty.protocol.friend.AddFriendRequestPacket;
import com.zh.util.SpringContextUtils;
import com.zh.netty.handler.*;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.socket.nio.NioSocketChannel;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

/**
 * 初始化
 * @author zh2683
 */
@Component
@Scope(ConfigurableBeanFactory.SCOPE_SINGLETON)
public class ServerChannelInitializer extends ChannelInitializer<NioSocketChannel> {

    @Autowired
    private LoginRequestHandler loginRequestHandler;
    @Autowired
    private RegisterRequestHandler registerRequestHandler;
    @Autowired
    private HeartBeatHandler heartBeatHandler;
    @Autowired
    private CheckAuthHandler checkAuthHandler;
    @Autowired
    private AddFriendHandler addFriendHandler;
    @Autowired
    private UpdateFriendListRequestHandler updateFriendListRequestHandler;

    @Override
    protected void initChannel(NioSocketChannel nioSocketChannel) throws Exception {
        nioSocketChannel.pipeline()
                .addLast(SpringContextUtils.getBean(IdleHandler.class))
                .addLast(SpringContextUtils.getBean(LengthFieldDecoder.class))
                .addLast(SpringContextUtils.getBean(PacketDecoder.class))
                .addLast(heartBeatHandler)
                .addLast(registerRequestHandler)
                .addLast(loginRequestHandler)
                .addLast(checkAuthHandler)
                .addLast(addFriendHandler)
                .addLast(updateFriendListRequestHandler)
                .addLast(SpringContextUtils.getBean(PacketEncoder.class));
    }
}
