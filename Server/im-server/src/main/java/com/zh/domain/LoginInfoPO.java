package com.zh.domain;

import lombok.Data;

import java.util.Date;

/**
 * 登录日志
 * @Author zh2683
 */
@Data
public class LoginInfoPO {

    private String id;

    private Integer code;

    private Date date;

    private String ip;
}
