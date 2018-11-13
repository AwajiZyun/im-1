package com.zh.protocol.login;

import com.zh.constant.PacketTypeEnum;
import com.zh.protocol.Packet;
import lombok.Data;

/**
 * @author zh2683
 */
@Data
public class LoginRequestPacketImpl extends Packet {

    private String code;

    private String password;

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.login_request;
    }
}
