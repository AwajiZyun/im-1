package com.zh.netty.constant;

import io.netty.util.AttributeKey;

/**
 * @author zh2683
 */
public interface AttributeKeyConsts {

    /**
     * 注册
     */
    AttributeKey<Boolean> register = AttributeKey.newInstance("register");
    /**
     * 登陆后channel标记属性
     */
    AttributeKey<Boolean> login = AttributeKey.newInstance("login");
    /**
     * 登陆后channel标记code属性
     */
    AttributeKey<String> code = AttributeKey.newInstance("code");
}
