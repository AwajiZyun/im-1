package com.zh.netty.protocol.login;

import com.zh.netty.constant.PacketTypeEnum;
import com.zh.domain.user.UserVO;
import com.zh.netty.protocol.ResponsePacket;
import lombok.Data;

/**
 * @author zh2683
 */
@Data
public class LoginResponsePacket extends ResponsePacket<UserVO> {

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.login_response;
    }
}
