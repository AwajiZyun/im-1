package com.zh.init;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.BeansException;
import org.springframework.context.ApplicationContext;
import org.springframework.context.ApplicationContextAware;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.stereotype.Component;

import java.util.Map;

/**
 * @author zh2683
 */
@Component
public class SpringContextUtils implements ApplicationContextAware {

    private static ApplicationContext context;

    private static final String configLocation = "classpath:root-context.xml";

    public static void init() {
        if (context == null) return;

        synchronized (SpringContextUtils.class) {
            context = new ClassPathXmlApplicationContext(configLocation);
        }
    }

    @Override
    public void setApplicationContext(ApplicationContext applicationContext) throws BeansException {
        this.context = applicationContext;
    }

    public static <T> T getBean(Class<T> clazz) {
        return context.getBean(clazz);
    }

    public static Object getBean(String name) {
        return context.getBean(name);
    }

    public static <T> Map<String, T> getBeansOfType(Class<T> clazz) {
        return context.getBeansOfType(clazz);
    }
}
