package com.zh.exception;

/**
 * 用户不在线
 * @author zh2683
 */
public class UserOfflineException extends ImException {

    public UserOfflineException() {
        super("用户不在线");
    }
}
