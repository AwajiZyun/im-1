package com.zh.util;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * @author zh2683
 */
public class JVMCloseUtil {

    private static final Logger log = LoggerFactory.getLogger(JVMCloseUtil.class);

    public static void close(Runnable runnable) {
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            try {
                runnable.run();
            } catch (Exception e) {
                log.error("", e);
            }
        }));
    }
}
