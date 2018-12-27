package com.zh.netty.protocol.friend;

import com.zh.domain.user.UserVO;
import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.ResponsePacket;

import java.util.List;

public class UpdateFriendListResponsePacket extends ResponsePacket<List<UserVO>> {
    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.updateFriendlist_response;
    }
}
