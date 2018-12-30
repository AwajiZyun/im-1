package com.zh.netty.protocol.onlinestate;

import com.alibaba.fastjson.annotation.JSONField;
import com.zh.constant.OnlineStateEnum;
import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.Packet;
import com.zh.util.OnlineStateEnumCodec;
import lombok.Data;

/**
 * 服务端给客户端的状态推送请求
 */
@Data
public class OnlineStateServerPushPacket extends Packet {

    private String code;

    @JSONField(deserializeUsing = OnlineStateEnumCodec.class, serializeUsing = OnlineStateEnumCodec.class)
    private OnlineStateEnum online;

    @Override
    public PacketTypeEnum getType() {
        return PacketTypeEnum.onlinestatepush_request;
    }
}
