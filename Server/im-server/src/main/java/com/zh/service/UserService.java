package com.zh.service;

import com.zh.domain.user.UserDTO;
import com.zh.domain.user.UserPO;
import com.zh.mapper.UserMapper;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

/**
 * @author zh2683
 */
@Service
public class UserService {

    @Autowired
    private UserMapper userMapper;

    public List<UserDTO> listAll() {
        List<UserPO> userPOS = userMapper.listAll();

        List<UserDTO> userDTOS = new ArrayList<>();
        if (userPOS != null && userPOS.size() > 0) {
            for (UserPO userPO : userPOS) {
                UserDTO userDTO = new UserDTO();
                BeanUtils.copyProperties(userPO, userDTO);
                userDTOS.add(userDTO);
            }
        }

        return userDTOS;
    }

    public Integer count() {
        return userMapper.count();
    }

    public UserDTO selectByCodeAndPassword(String code, String password) {
        UserPO userPO = userMapper.selectByCodeAndPassword(code, password);
        if (userPO == null) {
            return null;
        }
        UserDTO userDTO = new UserDTO();
        BeanUtils.copyProperties(userPO, userPO);
        return userDTO;
    }
}
