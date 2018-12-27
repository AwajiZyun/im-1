package com.zh.util;

import org.apache.commons.codec.digest.DigestUtils;

/**
 * @author zh2683
 */
public class MD5Test {

    public static void main(String[] args) {
        String md5str = DigestUtils.md5Hex("asdf");
        System.out.println(md5str);
    }
}
