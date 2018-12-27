package com.zh.constant;

import java.util.HashMap;

/**
 * 在线状态
 * @author zh2683
 */
public enum  OnlineStateEnum {
    offline, online, leave, busy, other;

    private static HashMap<Integer, OnlineStateEnum> map;

    static {
        map = new HashMap<>();
        for (OnlineStateEnum stateEnum : OnlineStateEnum.values()) {
            map.put(stateEnum.ordinal(), stateEnum);
        }
    }

    public static OnlineStateEnum getOnlineState(int oridinal) {
        return map.get(oridinal);
    }
}
