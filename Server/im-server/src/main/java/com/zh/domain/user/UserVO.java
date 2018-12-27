package com.zh.domain.user;

import com.alibaba.fastjson.annotation.JSONField;
import com.zh.constant.OnlineStateEnum;
import com.zh.constant.SexEnum;
import com.zh.util.OnlineStateEnumCodec;
import com.zh.util.SexEnumCodec;
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
    @JSONField(deserializeUsing = SexEnumCodec.class, serializeUsing = SexEnumCodec.class)
    private SexEnum sex;
    // 在线状态
    @JSONField(deserializeUsing = OnlineStateEnumCodec.class, serializeUsing = OnlineStateEnumCodec.class)
    private OnlineStateEnum online;
}
