package com.zh.netty.protocol.hearbeat;

import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.ResponsePacket;

/**
 * @author zh2683
 */
public class HeartBeatResponsePacket extends ResponsePacket<String> {

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.heartbeat_response;
    }
}
