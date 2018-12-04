package com.zh.protocol;

import com.zh.constant.PacketTypeEnum;
import com.zh.protocol.login.LoginRequestPacketImpl;
import org.junit.Assert;
import org.junit.Test;

/**
 * 数据包写入读取测试
 */
public class PacketCodecTest {

    private String code = "123";
    private String password = "测试密码";

    @Test
    public void testEncodeAndDecode() {
        LoginRequestPacketImpl loginRequestPacket = new LoginRequestPacketImpl();
        loginRequestPacket.setCode(code);
        loginRequestPacket.setPassword(password);
        Packet packet = PacketCodec.decode(PacketCodec.encode(loginRequestPacket));

        Assert.assertTrue(packet instanceof LoginRequestPacketImpl);
        Assert.assertTrue(packet.getVersion() == 1);
        LoginRequestPacketImpl loginRequest = (LoginRequestPacketImpl) packet;
        Assert.assertEquals(loginRequest.getCode(), code);
        Assert.assertEquals(loginRequest.getPassword(), password);
        Assert.assertEquals(loginRequest.getType(), PacketTypeEnum.login_request);
    }
}
