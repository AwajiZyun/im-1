package com.zh.service;

import com.zh.domain.friend.AddFriendDTO;
import com.zh.domain.friend.FriendsPO;
import com.zh.domain.user.UserDTO;
import com.zh.domain.user.UserPO;
import com.zh.exception.UserNotFoundException;
import com.zh.mapper.FriendsMapper;
import com.zh.mapper.UserMapper;
import com.zh.util.IDUtil;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Date;
import java.util.Objects;

/**
 * @author zh2683
 */
@Service
public class AddFriendService {

    @Autowired
    private FriendsMapper friendsMapper;

    @Autowired
    private UserMapper userMapper;

    @Transactional
    public UserDTO addFriend(AddFriendDTO addFriendDTO) {
        Objects.requireNonNull(addFriendDTO.getUserCode(), "用户code不能为空");
        UserPO userPO = userMapper.selectByCodeOrEmail(addFriendDTO.getSymbol(), addFriendDTO.getSymbol());
        if (userPO == null) {
            throw new UserNotFoundException("用户不存在:" + addFriendDTO.getSymbol());
        }
        // 保证userCode < friendCode
        String userCode = addFriendDTO.getUserCode();
        String friendCode = userPO.getCode();
        FriendsPO friendsPO = new FriendsPO();
        friendsPO.setCreateTime(new Date());
        if (userCode.compareTo(friendCode) > 0) {
            friendsPO.setUserCode(friendCode);
            friendsPO.setFriendCode(userCode);
        } else {
            friendsPO.setUserCode(userCode);
            friendsPO.setFriendCode(friendCode);
        }
        FriendsPO existFriendPO = friendsMapper.select(friendsPO);
        if (existFriendPO == null) {
            friendsPO.setId(IDUtil.uuid());
            friendsMapper.save(friendsPO);
        }
        UserDTO userDTO = new UserDTO();
        BeanUtils.copyProperties(userPO, userDTO);
        return userDTO;
    }
}
