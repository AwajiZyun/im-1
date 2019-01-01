package com.zh.netty.protocol.friend;

import com.zh.domain.user.UserVO;
import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.Packet;

/**
 * @TODO 此协议需要沟通定义
 * @author zh2683
 */
public class UpdateFriendInfoRequestPacket extends Packet {

    private UserVO userVO;

    @Override
    public PacketTypeEnum getType() {
        return null;
    }
}
