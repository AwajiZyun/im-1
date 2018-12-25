package com.zh.exception;


/**
 * 不存在用户
 * @author zh2683
 */
public class UserNotFoundException extends ImException {

    public UserNotFoundException(String msg) {
        super(msg);
    }
}
