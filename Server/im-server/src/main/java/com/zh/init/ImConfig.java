package com.zh.init;


import com.zh.constant.PacketTypeEnum;
import com.zh.protocol.Packet;
import com.zh.protocol.login.LoginRequestPacketImpl;

import java.util.HashMap;
import java.util.Map;

/**
 * @author zh2683
 */
public class ImConfig {
    /**服务端口号*/
    public static final Integer serverPort = 59454;

    /**协议魔数*/
    public static final Integer magicNumber = 0x5A4848;

    /**每种packetType的对应类型*/
    public static final Map<PacketTypeEnum, Class<? extends Packet>> packetTypeMap;

    static {
        packetTypeMap = new HashMap<>();
        packetTypeMap.put(PacketTypeEnum.LOGIN_REQUEST, LoginRequestPacketImpl.class);
    }

}
