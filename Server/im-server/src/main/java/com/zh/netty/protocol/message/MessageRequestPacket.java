package com.zh.netty.protocol.message;

import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.Packet;
import lombok.Data;

@Data
public class MessageRequestPacket extends Packet {

    /**发送人code*/
    private String fromUser;

    /**接收人code*/
    private String toUser;

    private String message;

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.message_request;
    }
}
