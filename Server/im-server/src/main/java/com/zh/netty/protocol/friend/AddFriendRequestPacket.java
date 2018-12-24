package com.zh.netty.protocol.friend;

import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.Packet;

/**
 * 添加好友
 * @author zh2683
 */
public class AddFriendRequestPacket extends Packet {

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.addfriend_request;
    }
}
