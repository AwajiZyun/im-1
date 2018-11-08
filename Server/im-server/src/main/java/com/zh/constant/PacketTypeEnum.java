package com.zh.constant;

/**
 * 协议类型
 * @author zh2683
 */
public enum PacketTypeEnum {
    LOGIN_REQUEST("登录请求"),
    LOGIN_RESPONSE("登录响应"),

    LOGOUT_REQUEST("登出请求"),
    LOGOUT_RESPONSE("登出响应")
    ;

    private String desc;

    PacketTypeEnum(String desc) {
        this.desc = desc;
    }
}
