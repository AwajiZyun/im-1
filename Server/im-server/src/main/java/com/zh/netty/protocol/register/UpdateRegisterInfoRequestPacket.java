package com.zh.netty.protocol.register;

import com.alibaba.fastjson.annotation.JSONField;
import com.zh.constant.SexEnum;
import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.Packet;
import com.zh.util.SexEnumCodec;
import lombok.Data;

/**
 * 更新注册信息
 * @author zh2683
 */
@Data
public class UpdateRegisterInfoRequestPacket extends Packet {

    private String code;

    private String nickname;

    @JSONField(serializeUsing = SexEnumCodec.class, deserializeUsing = SexEnumCodec.class)
    private SexEnum sex;

    private String oldPassword;

    private String newPassword;

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.updateinfo_request;
    }
}
