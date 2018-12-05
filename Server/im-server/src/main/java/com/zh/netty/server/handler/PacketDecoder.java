package com.zh.netty.server.handler;

import com.zh.netty.protocol.PacketCodec;
import com.zh.util.PacketUtil;
import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelHandlerContext;
import io.netty.handler.codec.ByteToMessageDecoder;
import org.springframework.stereotype.Component;

import java.util.List;

/**
 * 消息解码器
 * @author zh2683
 */
@Component
public class PacketDecoder extends ByteToMessageDecoder {

    @Override
    protected void decode(ChannelHandlerContext channelHandlerContext, ByteBuf byteBuf, List<Object> list) throws Exception {
        // 判断魔数
        byte[] magicNumber = new byte[3];
        if (!PacketUtil.checkMagicNumber(magicNumber)) {
            channelHandlerContext.channel().close();
        }
        list.add(PacketCodec.decode(byteBuf));
    }

}
