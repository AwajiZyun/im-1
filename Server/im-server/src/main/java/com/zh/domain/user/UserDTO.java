package com.zh.domain.user;

import com.zh.constant.SexEnum;
import lombok.Data;

import java.util.Date;

/**
 * @author zh2683
 */
@Data
public class UserDTO {
    // 主键
    private String id;
    // im号,唯一
    private String code;
    // 邮箱, 唯一
    private String email;
    // 昵称
    private String nickname;
    //
    private String password;
    // 性别
    private SexEnum sex;
    // 是否被删除
    private Boolean delete;
    // 创建时间
    private Date createTime;
    // 修改时间
    private Date modifyTime;
}
