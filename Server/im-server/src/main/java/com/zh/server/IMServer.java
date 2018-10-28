package com.zh.server;

import io.netty.bootstrap.ServerBootstrap;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.nio.NioServerSocketChannel;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

/**
 * im服务器
 * @author zh2683
 */
@Component
@Scope(ConfigurableBeanFactory.SCOPE_SINGLETON)
public class IMServer {

    private static Logger logger = LoggerFactory.getLogger(IMServer.class);

    private static NioEventLoopGroup boss = new NioEventLoopGroup();
    private static NioEventLoopGroup worker = new NioEventLoopGroup();
    private static ServerBootstrap serverBootstrap;

    @Value("${im.port}")
    public Integer port;

    @Autowired
    private ChannelInitializer channelInitializer;

    public synchronized void start() {
        if (serverBootstrap == null) {
            serverBootstrap = new ServerBootstrap();
            serverBootstrap
                    .group(boss, worker)
                    .channel(NioServerSocketChannel.class)
                    .childHandler(channelInitializer);
            bind(serverBootstrap, port);
        }
    }

    private void bind(ServerBootstrap serverBootstrap, final Integer port) {
        serverBootstrap.bind(port).addListener(future -> {
           if (future.isSuccess()) {
               logger.info("端口: [" + port + "]绑定成功");
           } else {
               logger.error("端口:[" + port + "]绑定失败");
               close();
           }
        });
    }

    public static void close() {
        // TODO 优雅退出
        System.exit(1);
    }
}
