package com.zh.netty.protocol.register;

import com.zh.constant.SexEnum;
import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.Packet;
import lombok.Data;

/**
 * 注册请求
 */
@Data
public class RegisterRequestPacket extends Packet {

    private String email;

    private String nickname;

    private SexEnum sexEnum;

    private String password;

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.register_request;
    }
}
