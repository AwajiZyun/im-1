package com.zh.netty.protocol;

import com.zh.netty.constant.PacketTypeEnum;
import com.zh.netty.protocol.login.LoginRequestPacket;
import com.zh.util.PacketCodec;
import org.junit.Assert;
import org.junit.Test;

/**
 * 数据包写入读取测试
 */
public class PacketCodecTest {

    private Integer code = 123;
    private String password = "测试密码";

    @Test
    public void testEncodeAndDecode() {
        LoginRequestPacket loginRequestPacket = new LoginRequestPacket();
        loginRequestPacket.setCode(code);
        loginRequestPacket.setPassword(password);
        Packet packet = PacketCodec.decode(PacketCodec.encode(loginRequestPacket));

        Assert.assertTrue(packet instanceof LoginRequestPacket);
        Assert.assertTrue(packet.getVersion() == 1);
        LoginRequestPacket loginRequest = (LoginRequestPacket) packet;
        Assert.assertEquals(loginRequest.getCode(), code);
        Assert.assertEquals(loginRequest.getPassword(), password);
        Assert.assertEquals(loginRequest.getType(), PacketTypeEnum.login_request);
    }
}
