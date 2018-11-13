package com.zh.constant;

import com.zh.protocol.Packet;
import com.zh.protocol.login.LoginRequestPacketImpl;

/**
 * @author zh2683
 */
public enum  PacketTypeEnum {
    login_request((short)1, LoginRequestPacketImpl.class);

    private Short code;
    private Class<? extends Packet> packetType;

    PacketTypeEnum(Short code, Class<? extends Packet> packetType) {
        this.code = code;
        this.packetType = packetType;
    }

    public Short code() {
        return this.code;
    }

    public Class<? extends Packet> packetType() {
        return this.packetType;
    }
}
