package com.zh.netty.protocol.friend;

import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.Packet;

public class UpdateFriendListRequestPacket extends Packet {
    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.updatefriendlist_request;
    }
}
