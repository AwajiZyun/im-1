package com.zh.netty;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import com.zh.constant.SexEnum;
import com.zh.netty.protocol.register.RegisterRequestPacket;

public class SexEnumCodecTest {

    public static void main(String[] args) {
        RegisterRequestPacket packet = new RegisterRequestPacket();
        packet.setSex(SexEnum.other);
        String s = JSON.toJSONString(packet);
        System.out.println(s);
        packet = JSONObject.parseObject(s, packet.getClass());
        System.out.println(packet);
    }
}
