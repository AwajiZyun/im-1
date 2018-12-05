package com.zh.constant;

import java.util.HashMap;
import java.util.Map;

/**
 * 性别
 * @author zh2683
 */
public enum SexEnum {
    MALE(0, "男"),
    FEMALE(1, "女"),
    OTHER(2, "其他");

    private static final Map<Integer, SexEnum> sexMap = new HashMap<>();

    static {
        for (SexEnum sexEnum : SexEnum.values()) {
            sexMap.put(sexEnum.ordinal(), sexEnum);
        }
    }

    private Integer index;
    private String desc;

    SexEnum(Integer sex, String desc) {
        this.index = sex;
        this.desc = desc;
    }

    public static SexEnum getEnum(Integer index) {
        return sexMap.get(index);
    }

}
