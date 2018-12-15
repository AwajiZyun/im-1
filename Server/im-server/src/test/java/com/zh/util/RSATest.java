package com.zh.util;

import org.junit.Assert;
import org.junit.Test;

import java.util.Map;

/**
 * @author zh2683
 */
public class RSATest {

    @Test
    public void rsa() {
        Map<String, String> map = RSAUtil.generateKeyPair();
        String publicKey = map.get("publicKey");
        String privateKey = map.get("privateKey");

        System.out.println(publicKey);
        System.out.println("====================================");
        System.out.println(privateKey);

        System.out.println("公钥加密——私钥解密");
        String source = "噫吁嚱，危乎高哉， 蜀道之难难于上青天";
        System.out.println("\r加密前文字：\r\n" + source);
        String aData = RSAUtil.encrypt(publicKey, source);
        System.out.println("加密后文字：\r\n" + aData);
        String dData = RSAUtil.decrypt(privateKey, aData);
        System.out.println("解密后文字: \r\n" + dData);
        Assert.assertEquals(source, dData);
    }
}
