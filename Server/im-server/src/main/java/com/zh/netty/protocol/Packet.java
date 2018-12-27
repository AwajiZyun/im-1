package com.zh.netty.protocol;

import com.alibaba.fastjson.annotation.JSONField;
import com.zh.netty.constant.PacketTypeEnum;
import lombok.Data;

/**
 * 数据包定义
 *
 * magic: 魔数,3byte
 * procotolVersion: 协议版本,1byte
 * dataLen:数据区长度,4byte
 * msgType: 包类型,2byte
 * blankRegion: 预留, 6byte
 * data: 数据区....
 * @author zh2683
 */
@Data
public abstract class Packet {

    /**协议版本*/
    @JSONField(serialize = false)
    private Byte version = 1;

    @JSONField(serialize = false)
    public abstract PacketTypeEnum getType();
}
