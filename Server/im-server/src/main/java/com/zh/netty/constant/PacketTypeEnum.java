package com.zh.netty.constant;

import com.zh.netty.protocol.Packet;
import com.zh.netty.protocol.hearbeat.HeartBeatRequestPacket;
import com.zh.netty.protocol.hearbeat.HeartBeatResponsePacket;
import com.zh.netty.protocol.login.LoginRequestPacket;
import com.zh.netty.protocol.login.LoginResponsePacket;
import com.zh.netty.protocol.register.RegisterRequestPacket;
import com.zh.netty.protocol.register.RegisterResponsePacket;

/**
 * @author zh2683
 */
public enum  PacketTypeEnum {
    login_request((short)1, LoginRequestPacket.class),
    login_response((short)2, LoginResponsePacket.class),
    register_request((short)3, RegisterRequestPacket.class),
    register_response((short)4, RegisterResponsePacket.class),
    heartbeat_request((short)5, HeartBeatRequestPacket.class),
    heartbeat_response((short)6, HeartBeatResponsePacket.class),
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
