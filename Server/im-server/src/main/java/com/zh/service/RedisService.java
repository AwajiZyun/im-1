package com.zh.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.StringRedisTemplate;
import org.springframework.stereotype.Service;

import java.util.Collection;
import java.util.List;

/**
 * redis相关操作
 * @author zh2683
 */
@Service
public class RedisService {

    @Autowired
    private StringRedisTemplate redisTemplate;

    public String lpop(String key) {
        return redisTemplate.opsForList().leftPop(key);
    }

    public Long lpush(String key, String value) {
        return redisTemplate.opsForList().leftPush(key, value);
    }

    public Long rpush(String key, String value) {
        return redisTemplate.opsForList().rightPush(key, value);
    }

    public void set(String key, String value) {
        redisTemplate.opsForValue().set(key, value);
    }

    public String get(String key) {
        return redisTemplate.opsForValue().get(key);
    }

    public List<String> multiGet(Collection<String> keys) {
        return redisTemplate.opsForValue().multiGet(keys);
    }

    public Boolean delete(String key) {
        return redisTemplate.delete(key);
    }
}
