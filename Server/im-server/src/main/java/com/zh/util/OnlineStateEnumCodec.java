package com.zh.util;

import com.alibaba.fastjson.parser.DefaultJSONParser;
import com.alibaba.fastjson.parser.deserializer.ObjectDeserializer;
import com.alibaba.fastjson.serializer.JSONSerializer;
import com.alibaba.fastjson.serializer.ObjectSerializer;
import com.zh.constant.OnlineStateEnum;
import com.zh.constant.SexEnum;

import java.io.IOException;
import java.lang.reflect.Type;

/**
 * 性别序列化和反序列化
 */
public class OnlineStateEnumCodec implements ObjectSerializer, ObjectDeserializer {
    @Override
    public <T> T deserialze(DefaultJSONParser parser, Type type, Object fieldName) {
        Object object = parser.parse();
        return (T) OnlineStateEnum.getOnlineState((int) object);
    }

    @Override
    public int getFastMatchToken() {
        return 0;
    }

    @Override
    public void write(JSONSerializer serializer, Object object, Object fieldName, Type fieldType, int features) throws IOException {
        serializer.write(((OnlineStateEnum)object).ordinal());
    }
}
