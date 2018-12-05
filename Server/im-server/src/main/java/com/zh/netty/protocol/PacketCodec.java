package com.zh.netty.protocol;

import com.alibaba.fastjson.JSONObject;
import com.zh.constant.SystemConsts;
import com.zh.main.ImConfig;
import io.netty.buffer.ByteBuf;
import io.netty.buffer.ByteBufAllocator;

import java.nio.charset.Charset;

/**
 * 编解码
 * @author zh2683
 */
public class PacketCodec {

    /**
     * 编码
     * @param packet
     * @return
     */
    public static ByteBuf encode(Packet packet) {
        String data = JSONObject.toJSONString(packet);
        byte[] dataBytes = data.getBytes(Charset.forName(SystemConsts.ENCODING_UTF8));
        ByteBuf byteBuf = ByteBufAllocator.DEFAULT.buffer();
        // 魔数
        byteBuf.writeBytes(ImConfig.magicNumber);
        // 协议版本
        byteBuf.writeByte(packet.getVersion());
        // 总长度
        byteBuf.writeInt(dataBytes.length);
        // 消息类型
        byteBuf.writeShort(packet.getType().code());
        // 6字节保留
        byteBuf.writerIndex(byteBuf.writerIndex() + 6);
        // 数据区
        byteBuf.writeBytes(dataBytes);
        return byteBuf;
    }

    /**
     * 解码
     * @param byteBuf
     */
    public static Packet decode(ByteBuf byteBuf) {
        byteBuf.resetReaderIndex();
        byte[] magicNumber = new byte[3];
        byteBuf.readBytes(magicNumber);
        byte version = byteBuf.readByte();
        int dataLength = byteBuf.readInt();
        short packetType = byteBuf.readShort();
        byteBuf.skipBytes(6);
        Class<? extends Packet> packetClazz = ImConfig.packetTypeMap.get(packetType);
        byte[] data = new byte[dataLength];
        byteBuf.readBytes(data);
        Packet packet = JSONObject.parseObject(new String(data, Charset.forName("utf-8")), packetClazz);
        return packet;
    }

    /**
     * 编码响应
     * @param responsePacket
     * @return
     */
    public static ByteBuf encode(ResponsePacket responsePacket) {
        String data = JSONObject.toJSONString(responsePacket);
        byte[] dataBytes = data.getBytes(Charset.forName(SystemConsts.ENCODING_UTF8));
        ByteBuf byteBuf = ByteBufAllocator.DEFAULT.buffer();
        // 魔数
        byteBuf.writeBytes(ImConfig.magicNumber);
        // 协议版本
        byteBuf.writeByte(responsePacket.getVersion());
        // 总长度
        byteBuf.writeInt(dataBytes.length);
        // 消息类型
        byteBuf.writeShort(responsePacket.getType().code());
        // 6字节保留
        byteBuf.writerIndex(byteBuf.writerIndex() + 6);
        // 数据区
        byteBuf.writeBytes(dataBytes);
        return byteBuf;
    }

}
