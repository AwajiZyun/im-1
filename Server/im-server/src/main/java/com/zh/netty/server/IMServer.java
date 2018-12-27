package com.zh.netty.server;

import com.zh.constant.ImConfig;
import io.netty.bootstrap.ServerBootstrap;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.nio.NioServerSocketChannel;
import lombok.extern.slf4j.Slf4j;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

/**
 * im服务器
 * @author zh2683
 */
@Slf4j
@Component
@Scope(ConfigurableBeanFactory.SCOPE_SINGLETON)
public class IMServer {

    private static NioEventLoopGroup boss = new NioEventLoopGroup();
    private static NioEventLoopGroup worker = new NioEventLoopGroup();
    private static ServerBootstrap serverBootstrap;

    @Autowired
    private ChannelInitializer channelInitializer;

    public synchronized void start() throws InterruptedException {
        if (serverBootstrap == null) {
            serverBootstrap = new ServerBootstrap();
            serverBootstrap
                    .group(boss, worker)
                    .channel(NioServerSocketChannel.class)
                    .childHandler(channelInitializer);
            bind(serverBootstrap, ImConfig.serverPort);
        }
    }

    private void bind(ServerBootstrap serverBootstrap, final Integer port) throws InterruptedException {
        serverBootstrap.bind(port).addListener(future -> {
           if (future.isSuccess()) {
               log.info("端口: [" + port + "]绑定成功");
           } else {
               log.error("端口:[" + port + "]绑定失败");
               close();
           }
        }).sync();
    }

    public static void close() {
        worker.shutdownGracefully();
        boss.shutdownGracefully();
    }
}
