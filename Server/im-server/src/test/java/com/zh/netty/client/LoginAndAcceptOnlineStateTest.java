package com.zh.netty.client;

import com.zh.constant.ImConfig;
import com.zh.constant.SystemConsts;
import com.zh.netty.client.handler.OnlineStateServerPushHandler;
import com.zh.netty.client.handler.TestHeartResponseHandler;
import com.zh.netty.client.handler.TestLoginResponseHandler;
import com.zh.netty.client.handler.TestUpdateFriendsResponseHandler;
import com.zh.netty.handler.PacketDecoder;
import com.zh.netty.handler.PacketEncoder;
import com.zh.netty.protocol.friend.UpdateFriendListRequestPacket;
import com.zh.netty.protocol.hearbeat.HeartBeatRequestPacket;
import com.zh.netty.protocol.login.LoginRequestPacket;
import com.zh.util.RSAUtil;
import io.netty.bootstrap.Bootstrap;
import io.netty.channel.Channel;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.SocketChannel;
import io.netty.channel.socket.nio.NioSocketChannel;

import java.util.concurrent.TimeUnit;


/**
 * @author zh2683
 */
public class LoginAndAcceptOnlineStateTest {


    public static void main(String[] args) {
        NioEventLoopGroup workerGroup = new NioEventLoopGroup();
        Bootstrap bootstrap = new Bootstrap();
        bootstrap
                .group(workerGroup)
                .channel(NioSocketChannel.class)
                .handler(new ChannelInitializer<SocketChannel>() {
                    @Override
                    protected void initChannel(SocketChannel socketChannel) {
                        socketChannel
                                .pipeline()
                                .addLast(new PacketDecoder())
                                .addLast(new TestHeartResponseHandler())
                                .addLast(new TestLoginResponseHandler())
                                .addLast(new OnlineStateServerPushHandler())
                                .addLast(new PacketEncoder());
                    }
                });
        bootstrap.connect("127.0.0.1", ImConfig.serverPort)
                .addListener(future -> {
                   if (future.isSuccess()) {
                       Channel channel = ((ChannelFuture)future).channel();
                       channel.eventLoop()
                               .scheduleWithFixedDelay(() -> {
                                   channel.writeAndFlush(new HeartBeatRequestPacket());
                               }, 5, 5, TimeUnit.SECONDS);
                       LoginRequestPacket loginRequestPacket = new LoginRequestPacket();
                       loginRequestPacket.setCode("500000");
                       loginRequestPacket.setPassword(RSAUtil.encrypt(SystemConsts.PUBLIC_KEY, "zh2683"));
                       ChannelFuture channelFuture = channel.writeAndFlush(loginRequestPacket);
                   } else {
                       System.out.println("failure");
                   }
                });
    }
}
