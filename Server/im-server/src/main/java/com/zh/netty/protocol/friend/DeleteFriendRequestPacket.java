package com.zh.netty.protocol.friend;

import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.Packet;
import lombok.Data;

/**
 * @author zh2683
 */
@Data
public class DeleteFriendRequestPacket extends Packet {

    private String code;

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.deletefriend_request;
    }
}
