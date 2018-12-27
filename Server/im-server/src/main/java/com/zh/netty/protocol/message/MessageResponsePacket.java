package com.zh.netty.protocol.message;

import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.ResponsePacket;

public class MessageResponsePacket extends ResponsePacket<String> {

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.message_response;
    }
}
