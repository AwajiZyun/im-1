package com.zh.netty.protocol.hearbeat;

import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.Packet;
import lombok.Data;

/**
 * @author zh2683
 */
@Data
public class HeartBeatRequestPacket extends Packet {

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.heartbeat_request;
    }
}
