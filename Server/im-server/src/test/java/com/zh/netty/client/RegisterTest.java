package com.zh.netty.client;

import com.zh.constant.ImConfig;
import com.zh.constant.SexEnum;
import com.zh.constant.SystemConsts;
import com.zh.netty.protocol.register.RegisterRequestPacket;
import com.zh.netty.handler.PacketDecoder;
import com.zh.netty.handler.PacketEncoder;
import com.zh.util.RSAUtil;
import io.netty.bootstrap.Bootstrap;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.SocketChannel;
import io.netty.channel.socket.nio.NioSocketChannel;


/**
 * @author zh2683
 */
public class RegisterTest {


    public static void main(String[] args) {
        ChannelFuture channelFuture;
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
//                                .addLast(new TestHeartBeatHandler());
                                .addLast(new PacketEncoder());
                    }
                });
        bootstrap.connect("127.0.0.1", ImConfig.serverPort)
                .addListener(future -> {
                   if (future.isSuccess()) {
                       System.out.println("success");
                       RegisterRequestPacket registerRequestPacket = new RegisterRequestPacket();
                       registerRequestPacket.setPassword(RSAUtil.encrypt(SystemConsts.PUBLIC_KEY, "zh2683"));
                       registerRequestPacket.setEmail("zh2683@133.com");
                       registerRequestPacket.setSex(SexEnum.FEMALE);
                       registerRequestPacket.setNickname("zh2683");
                       ((ChannelFuture)future).channel().writeAndFlush(registerRequestPacket);
                   } else {
                       System.out.println("failure");
                   }
                });
    }
}
