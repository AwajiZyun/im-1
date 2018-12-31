package com.zh.util;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * @author zh2683
 */
public class ThreadPoolUtil {

    private static ThreadPoolExecutor threadPoolExecutor;
    private static AtomicInteger atomicInteger = new AtomicInteger(0);
    private static Logger log = LoggerFactory.getLogger(ThreadPoolUtil.class);

    static {
        int cpuCount = Runtime.getRuntime().availableProcessors();
        ThreadFactory threadFactory = r -> new Thread(r,"IMPOOL_" + atomicInteger.getAndIncrement());
        threadPoolExecutor = new ScheduledThreadPoolExecutor(
                cpuCount * 2,
                threadFactory
                ) {
            @Override
            protected void afterExecute(Runnable r, Throwable t) {
                super.afterExecute(r, t);
                if (t != null) {
                    log.error("任务执行失败", t);
                }
            }

        };
        JVMCloseUtil.close(() -> {
            threadPoolExecutor.shutdown();
        });
    }

    public static void execute(Runnable task) {
        threadPoolExecutor.execute(task);
    }

    public static void main(String[] args) {
        ThreadPoolUtil.execute(() -> {
            System.out.println("asdfasdfasd");
        });
    }

}
