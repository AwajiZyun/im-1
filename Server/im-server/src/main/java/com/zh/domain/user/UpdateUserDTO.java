package com.zh.domain.user;

import com.zh.constant.SexEnum;
import lombok.Data;

import java.util.Date;

/**
 * @author zh2683
 */
@Data
public class UpdateUserDTO {
    // im号,唯一
    private String code;
    // 昵称
    private String nickname;
    //
    private String oldPassword;
    //
    private String newPassword;
    // 性别
    private SexEnum sex;

    private Date modifyTime;
}
