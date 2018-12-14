package com.zh.service;

import com.zh.domain.user.UserDTO;
import com.zh.domain.user.UserPO;
import com.zh.netty.protocol.register.RegisterRequestPacket;
import com.zh.netty.protocol.register.RegisterResponsePacket;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

/**
 * TODO 注册处理
 */
@Service
public class RegisterService {

    @Autowired
    private UserService userService;

    @Transactional
    public RegisterResponsePacket register(RegisterRequestPacket registerRequestPacket) {
        RegisterResponsePacket registerResponsePacket = new RegisterResponsePacket();
        UserDTO userDTO = userService.selectByEmail(registerRequestPacket.getEmail());
        if (userDTO == null) {
            UserPO userPO = new UserPO();
            // TODO userPO转UserDTO

        } else {
        }
        return null;
    }
}
