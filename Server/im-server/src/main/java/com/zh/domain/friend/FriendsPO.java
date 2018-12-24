package com.zh.domain.friend;

import lombok.Data;

import java.util.Date;

/**
 * 好友对象实体
 * userCode < friendCode
 * 保证{userCode, friendCode}唯一
 */
@Data
public class FriendsPO {

    private String id;

    private String userCode;

    private String friendCode;

    private Date createTime;
}
