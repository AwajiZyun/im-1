package com.zh.constant;

import java.util.HashMap;
import java.util.Map;

/**
 * 性别
 * @author zh2683
 */
public enum SexEnum {
    male("男"),
    female("女"),
    other("其他");

    private static final Map<Integer, SexEnum> sexMap = new HashMap<>();

    static {
        for (SexEnum sexEnum : SexEnum.values()) {
            sexMap.put(sexEnum.ordinal(), sexEnum);
        }
    }

    private String desc;

    SexEnum(String desc) {
        this.desc = desc;
    }

    public static SexEnum getEnum(Integer index) {
        return sexMap.get(index);
    }
}
