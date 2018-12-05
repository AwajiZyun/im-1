package com.zh.netty.constant;

import com.zh.netty.protocol.Packet;
import com.zh.netty.protocol.login.LoginRequestPacket;
import com.zh.netty.protocol.login.LoginResponsePacket;

/**
 * @author zh2683
 */
public enum  PacketTypeEnum {
    login_request((short)1, LoginRequestPacket.class),
    login_response((short)2, LoginResponsePacket.class)
    ;

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
