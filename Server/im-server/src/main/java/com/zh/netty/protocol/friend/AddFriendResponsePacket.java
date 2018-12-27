package com.zh.netty.protocol.friend;

import com.zh.domain.user.UserVO;
import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.ResponsePacket;

/**
 * @author zh2683
 */
public class AddFriendResponsePacket extends ResponsePacket<UserVO> {

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.addfriend_response;
    }
}
