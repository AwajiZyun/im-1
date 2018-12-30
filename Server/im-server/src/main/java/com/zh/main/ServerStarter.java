package com.zh.main;

import com.zh.netty.server.IMServer;
import com.zh.util.SpringContextUtils;
import lombok.extern.slf4j.Slf4j;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * 服务启动器
 * 初始化spring
 * 启动netty服务
 * @author zh2683
 */
@Slf4j
public class ServerStarter {

    public static void main(String[] args) {
        try {
            // 初始化spring, mybatis
            SpringContextUtils.init();
            // 启动netty
            IMServer imServer = SpringContextUtils.getBean(IMServer.class);
            imServer.start();
            log.info("启动完成");
        } catch (Exception e) {
            log.error("启动失败", e);
        }
    }
}
