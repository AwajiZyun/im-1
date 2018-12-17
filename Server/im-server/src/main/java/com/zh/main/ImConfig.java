package com.zh.main;


import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.Packet;

import java.util.HashMap;
import java.util.Map;

/**
 * im服务配置项
 * @author zh2683
 */
public class ImConfig {
    /**服务端口号*/
    public static final Integer serverPort = 8080;

    /**协议魔数*/
    public static final byte[] magicNumber = new byte[]{57, 48, 48};

    /**每种packetType的对应类型*/
    public static final Map<Short, Class<? extends Packet>> packetTypeMap;

    static {
        packetTypeMap = new HashMap<>();
        for (PacketTypeEnum packetTypeEnum : PacketTypeEnum.values()) {
            packetTypeMap.put(packetTypeEnum.code(), packetTypeEnum.packetType());
        }
    }

}
