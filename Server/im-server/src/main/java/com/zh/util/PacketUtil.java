package com.zh.util;

import com.zh.init.ImConfig;
import com.zh.protocol.Packet;
import io.netty.buffer.ByteBuf;

/**
 * 对包进行处理
 * @see Packet
 *
 * @author zh2683
 */
public class PacketUtil {

    public Packet decode(ByteBuf byteBuf) {
        return null;
    }

    /**
     * 判断魔数
     * @param magicNumber
     * @return
     */
    public static boolean checkMagicNumber(byte[] magicNumber) {
        if (magicNumber.length < 3) return false;
        return ImConfig.magicNumber == (magicNumber[0] << 16 | magicNumber[1] << 8 | magicNumber[0]);
    }
}
