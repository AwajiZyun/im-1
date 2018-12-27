package com.zh.netty.handler;

import io.netty.channel.ChannelHandlerContext;
import io.netty.handler.codec.LengthFieldBasedFrameDecoder;
import lombok.extern.slf4j.Slf4j;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

/**
 * 基于长度域的包解码器
 * @see com.zh.netty.protocol.Packet
 */
@Slf4j
@Component
@Scope(ConfigurableBeanFactory.SCOPE_PROTOTYPE)
public class LengthFieldDecoder extends LengthFieldBasedFrameDecoder {

    private static final int MAXFRAMELENGTH = 500;
    private static final int LENGTHFIELDOFFSET =4;
    private static final int LENFTHFIELDLENGTH = 4;
    private static final int LENGTHADJUSTMENT = 8;
    private static final int INITIALBYTESTOSTRIP = 0;

    public LengthFieldDecoder() {
        super(MAXFRAMELENGTH, LENGTHFIELDOFFSET, LENFTHFIELDLENGTH, LENGTHADJUSTMENT, INITIALBYTESTOSTRIP);
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {
        log.error("包处理失败", cause);
        ctx.channel().close();
    }
}
