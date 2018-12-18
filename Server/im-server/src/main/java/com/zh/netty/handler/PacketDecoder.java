package com.zh.netty.handler;

import com.zh.util.PacketCodec;
import com.zh.util.PacketUtil;
import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelHandlerContext;
import io.netty.handler.codec.ByteToMessageDecoder;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

import java.util.List;

/**
 * 消息解码器
 * @author zh2683
 */
@Component
@Scope(ConfigurableBeanFactory.SCOPE_PROTOTYPE)
public class PacketDecoder extends ByteToMessageDecoder {

    @Override
    protected void decode(ChannelHandlerContext channelHandlerContext, ByteBuf byteBuf, List<Object> list) throws Exception {
        // 判断魔数
        byte[] magicNumber = new byte[3];
        byteBuf.readBytes(magicNumber);
        if (!PacketUtil.checkMagicNumber(magicNumber)) {
            // 非本服务支持的数据包，关闭连接
            channelHandlerContext.channel().close();
        } else {
            byteBuf.resetReaderIndex();
            list.add(PacketCodec.decode(byteBuf));
        }
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {
        cause.printStackTrace();
    }

}
