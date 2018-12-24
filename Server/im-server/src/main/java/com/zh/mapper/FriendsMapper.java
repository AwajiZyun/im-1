package com.zh.mapper;

import com.zh.domain.friend.FriendsPO;

import java.util.List;

public interface FriendsMapper {

    void save(FriendsPO friendsPO);

    List<FriendsPO> selectByCode(String code);
}
