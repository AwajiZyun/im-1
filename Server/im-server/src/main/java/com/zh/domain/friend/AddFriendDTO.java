package com.zh.domain.friend;

import lombok.Data;

/**
 * @author zh2683
 */
@Data
public class AddFriendDTO {

    private String userCode;

    // 朋友的邮箱或者朋友的code
    private String symbol;
}
