package com.zh.netty.protocol.friend;

import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.Packet;
import lombok.Data;

/**
 * 添加好友
 * @author zh2683
 */
@Data
public class AddFriendRequestPacket extends Packet {

    private String symbol;

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.addfriend_request;
    }
}
