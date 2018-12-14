package com.zh.netty.protocol.register;

import com.zh.domain.user.UserVO;
import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.ResponsePacket;

/**
 * 注册响应
 */
public class RegisterResponsePacket extends ResponsePacket<UserVO> {

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.register_response;
    }
}
