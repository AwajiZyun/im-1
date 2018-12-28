package com.zh.util;

import io.netty.util.CharsetUtil;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.Base64;
import java.util.Objects;

/**
 * base64加解密
 */
public class Base64Util {

    /**
     * 加密后默认有\r\n分隔符，替换掉
     * @param source
     * @param charsetName
     * @return
     */
    private static String encrypt(String source, String charsetName) {
        Objects.requireNonNull(source, "源字符串不能为null");
        try {
            return Base64.getEncoder().encodeToString(source.getBytes(charsetName))
                    .replaceAll("[\\r\\n]", "");
        } catch (UnsupportedEncodingException e) {
            return null;
        }
    }

    public static String encrypt(String source) {
        return encrypt(source, CharsetUtil.UTF_8.name());
    }

    private static String decrypt(String base64_source, String charsetName) {
        Objects.requireNonNull(base64_source, "加密字符串不能为null");
        try {
            return new String(Base64.getDecoder().decode(base64_source), charsetName);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static String decrypt(String base64_source) {
        return decrypt(base64_source, CharsetUtil.UTF_8.name());
    }

}
