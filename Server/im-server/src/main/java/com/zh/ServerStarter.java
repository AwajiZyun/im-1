package com.zh;

import com.zh.server.IMServer;
import com.zh.init.SpringContextUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * 服务启动入口
 * @author zh2683
 */
public class ServerStarter {

    private static final Logger logger = LoggerFactory.getLogger(ServerStarter.class);

    public static void main(String[] args) {
        // 初始化spring, mybatis
        SpringContextUtils.init();
        logger.info("spring初始化完成.");

        // 启动netty
        IMServer imServer = SpringContextUtils.getBean(IMServer.class);
        imServer.start();
    }
}
