package com.zh.netty.protocol.register;

import com.alibaba.fastjson.annotation.JSONField;
import com.zh.constant.SexEnum;
import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.Packet;
import com.zh.util.SexEnumCodec;
import lombok.Data;

/**
 * 注册请求
 */
@Data
public class RegisterRequestPacket extends Packet {

    private String email;

    private String nickname;

    @JSONField(serializeUsing = SexEnumCodec.class, deserializeUsing = SexEnumCodec.class)
    private SexEnum sex;

    private String password;

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.register_request;
    }
}
