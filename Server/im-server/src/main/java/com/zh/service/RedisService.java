package com.zh.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.StringRedisTemplate;
import org.springframework.stereotype.Service;

/**
 * redis相关操作
 * @author zh2683
 */
@Service
public class RedisService {

    @Autowired
    private StringRedisTemplate redisTemplate;

    public String lpop(String key) {
        return redisTemplate.opsForList().leftPop("");
    }

    public Long rpush(String key, String value) {
        return redisTemplate.opsForList().rightPush(key, value);
    }
}
