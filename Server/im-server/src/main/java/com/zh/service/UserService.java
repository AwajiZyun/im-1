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
                userDTOS.add(getUserDTO(userPO));
            }
        }

        return userDTOS;
    }

    public Integer count() {
        return userMapper.count();
    }

    public UserDTO selectByCodeAndPassword(Integer code, String password) {
        UserPO userPO = userMapper.selectByCodeAndPassword(code, password);
        return getUserDTO(userPO);
    }

    public UserDTO selectByEmail(String email) {
        UserPO userPO = userMapper.selectByEmail(email);
        return getUserDTO(userPO);
    }

    public void save(UserPO userPO) {
        userMapper.save(userPO);
    }

    private UserDTO getUserDTO(UserPO userPO) {
        if (userPO == null) {
            return null;
        }
        UserDTO userDTO = new UserDTO();
        BeanUtils.copyProperties(userPO, userDTO);
        return userDTO;
    }
}
