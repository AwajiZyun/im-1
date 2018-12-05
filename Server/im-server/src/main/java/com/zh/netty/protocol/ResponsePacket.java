package com.zh.netty.protocol;

import lombok.Data;

/**
 * 默认响应
 * @author zh2683
 */
@Data
public abstract class ResponsePacket<T> extends Packet {

    private Boolean success;

    private T data;

    private String msg;
}
