package com.zh.netty.constant;

import io.netty.util.AttributeKey;

/**
 * @author zh2683
 */
public interface AttributeKeyConsts {

    /**
     * 注册
     */
    AttributeKey<String> register = AttributeKey.newInstance("register");
    /**
     * 登陆后channel标记属性
     */
    AttributeKey<String> login = AttributeKey.newInstance("login");
}
