package com.zh.init;

import com.zh.server.IMServer;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * 服务启动器
 * 初始化spring
 * 启动netty服务
 * @author zh2683
 */
public class ServerStarter {

    private static final Logger logger = LoggerFactory.getLogger(ServerStarter.class);

    public static void main(String[] args) {
        // 初始化spring, mybatis
        SpringContextUtils.init();
        // 启动netty
        IMServer imServer = SpringContextUtils.getBean(IMServer.class);
        imServer.start();
    }
}
