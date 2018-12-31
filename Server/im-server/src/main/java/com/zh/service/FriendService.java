package com.zh.service;

import com.zh.domain.friend.AddFriendDTO;
import com.zh.domain.friend.DeleteFriendDTO;
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

import java.util.*;

/**
 * @author zh2683
 */
@Service
public class FriendService {

    @Autowired
    private FriendsMapper friendsMapper;

    @Autowired
    private UserMapper userMapper;

    @Transactional
    public UserDTO addFriend(AddFriendDTO addFriendDTO) throws Exception {
        Objects.requireNonNull(addFriendDTO.getUserCode(), "用户code不能为空");
        UserPO userPO = userMapper.selectByCodeOrEmail(addFriendDTO.getSymbol(), addFriendDTO.getSymbol());
        if (userPO == null) {
            throw new UserNotFoundException();
        }
        FriendsPO friendsPO = newFriendPO(addFriendDTO.getUserCode(), userPO.getCode());
        friendsPO.setCreateTime(new Date());
        FriendsPO existFriendPO = friendsMapper.select(friendsPO);
        if (existFriendPO == null) {
            friendsPO.setId(IDUtil.uuid());
            friendsMapper.save(friendsPO);
        }
        UserDTO userDTO = new UserDTO();
        BeanUtils.copyProperties(userPO, userDTO);
        return userDTO;
    }

    private FriendsPO newFriendPO(String code, String otherCode) {
        // 保证userCode < friendCode
        FriendsPO friendsPO = new FriendsPO();
        if (code.compareTo(otherCode) > 0) {
            friendsPO.setUserCode(otherCode);
            friendsPO.setFriendCode(code);
        } else {
            friendsPO.setUserCode(code);
            friendsPO.setFriendCode(otherCode);
        }
        return friendsPO;
    }

    public List<UserDTO> listFriends(String code) {
        List<FriendsPO> friendsPOS = friendsMapper.selectByCode(code);
        List<String> friendCodes = new ArrayList<>(friendsPOS.size());
        friendsPOS.stream().forEach(friendsPO -> {
            if (friendsPO.getUserCode().equals(code)) {
                friendCodes.add(friendsPO.getFriendCode());
            } else {
                friendCodes.add(friendsPO.getUserCode());
            }
        });
        if (friendCodes.size() > 0) {
            List<UserPO> userPOS = userMapper.listByCode(friendCodes);
            List<UserDTO> result = new ArrayList<>(userPOS.size());
            userPOS.stream().forEach(userPO -> {
                UserDTO userDTO = new UserDTO();
                BeanUtils.copyProperties(userPO, userDTO);
                result.add(userDTO);
            });
            return result;
        }
        return new ArrayList<>(0);
    }

    @Transactional
    public int delete(DeleteFriendDTO friendDTO) {
        FriendsPO friendsPO = newFriendPO(friendDTO.getUserCode(), friendDTO.getFriendCode());
        return friendsMapper.delete(friendsPO.getUserCode(), friendsPO.getFriendCode());
    }
}
