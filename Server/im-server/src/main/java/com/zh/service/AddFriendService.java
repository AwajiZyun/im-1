package com.zh.service;

import com.zh.domain.friend.FriendsPO;
import com.zh.mapper.FriendsMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

/**
 * @author zh2683
 */
@Service
public class AddFriendService {

    @Autowired
    private FriendsMapper friendsMapper;

    @Transactional
    public void addFriend(FriendsPO friendsPO) {
        // TODO 添加朋友逻辑
    }
}
