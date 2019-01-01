package com.zh.netty.constant;

import com.zh.netty.protocol.Packet;
import com.zh.netty.protocol.friend.*;
import com.zh.netty.protocol.hearbeat.HeartBeatRequestPacket;
import com.zh.netty.protocol.hearbeat.HeartBeatResponsePacket;
import com.zh.netty.protocol.login.LoginRequestPacket;
import com.zh.netty.protocol.login.LoginResponsePacket;
import com.zh.netty.protocol.message.MessageRequestPacket;
import com.zh.netty.protocol.message.MessageResponsePacket;
import com.zh.netty.protocol.onlinestate.OnlineStateServerPushPacket;
import com.zh.netty.protocol.register.RegisterRequestPacket;
import com.zh.netty.protocol.register.RegisterResponsePacket;
import com.zh.netty.protocol.register.UpdateRegisterInfoRequestPacket;
import com.zh.netty.protocol.register.UpdateRegisterInfoResponsePacket;

/**
 * @author zh2683
 */
public enum  PacketTypeEnum {
    register_request((short)0x0000, RegisterRequestPacket.class),
    register_response((short)0x1000, RegisterResponsePacket.class),
    login_request((short)0x0001, LoginRequestPacket.class),
    login_response((short)0x1001, LoginResponsePacket.class),
    updateinfo_request((short)0x0002, UpdateRegisterInfoRequestPacket.class),
    updateinfo_response((short)0x1002, UpdateRegisterInfoResponsePacket.class),
    heartbeat_request((short)0x00f0, HeartBeatRequestPacket.class),
    heartbeat_response((short)0x10f0, HeartBeatResponsePacket.class),
    addfriend_request((short)0x0021, AddFriendRequestPacket.class),
    addfriend_response((short)0x1021, AddFriendResponsePacket.class),
    updatefriendlist_request((short)0x0022, UpdateFriendListRequestPacket.class),
    updateFriendlist_response((short)0x1022, UpdateFriendListResponsePacket.class),
    message_request((short)0x0010, MessageRequestPacket.class),
    message_response((short)0x1010, MessageResponsePacket.class),
    onlinestatepush_request((short)0x1030, OnlineStateServerPushPacket.class),
    deletefriend_request((short)0x0024, DeleteFriendRequestPacket.class),
    deletefriend_response((short)0x1025, DeleteFriendResponsePacket.class),

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
