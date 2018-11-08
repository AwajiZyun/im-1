package com.zh.protocol.login;

import com.zh.constant.PacketTypeEnum;
import com.zh.protocol.Packet;

/**
 * @author zh2683
 */
public class LoginRequestPacketImpl extends Packet {

    private String code;

    private String password;

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.LOGIN_REQUEST;
    }
}
