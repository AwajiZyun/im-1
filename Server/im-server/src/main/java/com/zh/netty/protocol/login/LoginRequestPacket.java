package com.zh.netty.protocol.login;

import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.Packet;
import lombok.Data;

/**
 * @author zh2683
 */
@Data
public class LoginRequestPacket extends Packet {

    private Integer code;

    private String password;

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.login_request;
    }
}
