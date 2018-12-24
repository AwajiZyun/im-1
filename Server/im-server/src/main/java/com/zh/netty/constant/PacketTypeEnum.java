package com.zh.netty.constant;

import com.zh.netty.protocol.Packet;
import com.zh.netty.protocol.friend.AddFriendRequestPacket;
import com.zh.netty.protocol.friend.AddFriendResponsePacket;
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
    register_request((short)0x0000, RegisterRequestPacket.class),
    register_response((short)0x1000, RegisterResponsePacket.class),
    login_request((short)0x0001, LoginRequestPacket.class),
    login_response((short)0x1001, LoginResponsePacket.class),
    heartbeat_request((short)0x00f0, HeartBeatRequestPacket.class),
    heartbeat_response((short)0x10f0, HeartBeatResponsePacket.class),
    addfriend_request((short)0x0021, AddFriendRequestPacket.class),
    addfriend_response((short)0x1021, AddFriendResponsePacket.class)
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
