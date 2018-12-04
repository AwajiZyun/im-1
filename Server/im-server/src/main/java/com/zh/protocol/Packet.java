package com.zh.protocol;

import com.zh.constant.PacketTypeEnum;
import lombok.Data;

/**
 * 数据包定义
 *
 * magic: 魔数,3byte
 * procotolVersion: 协议版本,1byte
 * totalLen:数据区长度,4byte
 * typeype: 包类型,2byte
 * blankRegion: 预留, 6字节
 * data: 数据区....
 * @author zh2683
 */
@Data
public abstract class Packet {

    /**协议版本*/
    private Byte version = 1;

    public abstract PacketTypeEnum getType();
}