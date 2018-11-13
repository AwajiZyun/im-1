package com.zh.util;

import com.zh.init.ImConfig;
import com.zh.protocol.Packet;

/**
 * 对包进行处理
 * @see Packet
 *
 * @author zh2683
 */
public class PacketUtil {

    /**
     * 判断魔数
     * @param magicNumber
     * @return
     */
    public static boolean checkMagicNumber(byte[] magicNumber) {
        if (magicNumber.length < 3) return false;
        byte[] magicNumberDefault = ImConfig.magicNumber;
        return magicNumberDefault[0] == magicNumber[0]
                && magicNumberDefault[1] == magicNumber[1]
                && magicNumberDefault[2] == magicNumber[2];
    }
}
