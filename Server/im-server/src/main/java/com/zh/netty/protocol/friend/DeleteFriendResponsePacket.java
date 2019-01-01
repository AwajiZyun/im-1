package com.zh.netty.protocol.friend;

import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.ResponsePacket;

/**
 * @author zh2683
 */
public class DeleteFriendResponsePacket extends ResponsePacket<String> {
    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.deletefriend_response;
    }
}
