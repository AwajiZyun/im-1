package com.zh.domain.user;

import com.zh.constant.SexEnum;
import lombok.Data;

/**
 * @author zh2683
 */
@Data
public class UserVO {
    // 主键
    private String id;
    // im号,唯一
    private String code;
    // 邮箱, 唯一
    private String email;
    // 昵称
    private String nickname;
    // 性别
    private SexEnum sex;
}
