package com.zh.netty.protocol.register;

import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.ResponsePacket;
import lombok.Data;

/**
 * 更新注册信息
 * @author zh2683
 */
@Data
public class UpdateRegisterInfoResponsePacket extends ResponsePacket<String> {

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.updateinfo_response;
    }
}
