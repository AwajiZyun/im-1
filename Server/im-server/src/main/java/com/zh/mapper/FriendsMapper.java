package com.zh.mapper;

import com.zh.domain.friend.FriendsPO;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface FriendsMapper {

    void save(FriendsPO friendsPO);

    FriendsPO select(FriendsPO friendsPO);

    List<FriendsPO> selectByCode(String code);

    int delete(@Param("userCode") String userCode, @Param("friendCode") String friendCode);
}
