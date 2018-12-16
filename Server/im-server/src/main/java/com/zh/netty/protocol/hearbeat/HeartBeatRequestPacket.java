package com.zh.netty.protocol.hearbeat;

import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.Packet;

/**
 * @author zh2683
 */
public class HeartBeatRequestPacket extends Packet {

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.heartbeat_request;
    }
}
