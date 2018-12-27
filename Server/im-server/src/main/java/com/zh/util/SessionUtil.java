package com.zh.util;

import com.zh.netty.constant.AttributeKeyConsts;
import io.netty.channel.Channel;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class SessionUtil {

    private static final Map<String, Channel> sessions = new ConcurrentHashMap<>(100);

    public static Channel get(String code) {
        return sessions.get(code);
    }

    public static boolean exist(String code) {
        return sessions.containsKey(code);
    }

    public static Channel bind(String code, Channel channel) {
        return sessions.put(code, channel);
    }

    public static Channel unbind(String code) {
        return sessions.remove(code);
    }

    public static Channel unbind(Channel channel) {
        if (channel.hasAttr(AttributeKeyConsts.code)) {
            return sessions.remove(channel.attr(AttributeKeyConsts.code).get());
        }
        return null;
    }
}
