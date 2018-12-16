package com.zh.constant;

/**
 * 系统公用变量
 */
public interface SystemConsts {

    String ENCODING_UTF8 = "UTF-8";

    /**
     * 公钥
     */
    String PUBLIC_KEY = "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQC2v3F2OIZWpbI05cc4pwGY/jnwlCZMdo5zMKSq" +
                        "1MxNoTh3hXhm5txkRt4ZQFqdS485zxissUz4ukAebOguolXUrtXEI1lxJEDd4CmidTdiK1zxE6vE" +
                        "N955uZQkSF7hBJ6EvoLzNom/Vcnn66zqS506e7wHKIDKDJb4K8yHbSqHKQIDAQAB";
    /**
     * 私钥
     */
    String PRIVATE_KEY = "MIICeAIBADANBgkqhkiG9w0BAQEFAASCAmIwggJeAgEAAoGBALa/cXY4hlalsjTlxzinAZj+OfCU" +
                         "Jkx2jnMwpKrUzE2hOHeFeGbm3GRG3hlAWp1LjznPGKyxTPi6QB5s6C6iVdSu1cQjWXEkQN3gKaJ1" +
                         "N2IrXPETq8Q33nm5lCRIXuEEnoS+gvM2ib9VyefrrOpLnTp7vAcogMoMlvgrzIdtKocpAgMBAAEC" +
                         "gYAsDKdXvLY86oGzGHPV5wOOkjD7GWrF4YnioCYA+3wndiX7QVPNUfZrwV1Frupooc7rO00SS0Zn" +
                         "adWMv+mTXBPd4BVjZE4o915ZJEJ+ePDkIRjVDfD461GbCTmD2m0Z+JUkEs9oKWA9qi1JiirR4/Kw" +
                         "NZoE8qMhw05sqKOxksm65QJBAPT+t+Bd6+1QxJLjP0XQ6n8uQmSO+TiRossrVn43h/PDTyGPrxso" +
                         "Nm2PbCeTnyH7DQDEWiWIy3m3Kkj1xNwLVI8CQQC+9OxfvQ8+0y4E26U7b2VHh6o3B0pWEptpLJUi" +
                         "xEbOp5FWbo8LkvHtzdAwmxEy7Rf4hlt4dUYEZDiIvwgUxXTHAkEAwkU5ibDwZD6nodKRWctQJ4mH" +
                         "HDZDaZgSfwjejTd7ltBI71QAhohcoIQaP0fP6CIrLXCGCz1uHBYicbhxYguaAQJBAKGE9fM9LYoM" +
                         "gp5lU2vkm5xXamjFZ+FKN95McZFIyEPAhTTAq4o0ryJgtjqGz5Nt7Jqwuuo2+BR62T8Bpso7Ar0C" +
                         "QQDvaOtb/vUOavRnXRkjltLidTwlJetRNT89JQH1s4c7suYuybIwMpqz+An9JMz7cynszOmW7Mi/" +
                         "R9NanljtIojo";

    /**
     * 未使用的code池
     */
    String RAW_CODE_POOL = "raw_code_pool";
    /**
     * 已被使用的code池
     */
    String USED_CODE_POOL = "used_code_pool";

    /**
     * 空闲时间
     */
    Integer CHANNEL_IDLE_TIME = 10;
}
