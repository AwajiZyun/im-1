package com.zh.service;

import com.zh.constant.SystemConsts;
import com.zh.domain.user.UserDTO;
import com.zh.domain.user.UserVO;
import com.zh.netty.protocol.login.LoginRequestPacket;
import com.zh.netty.protocol.login.LoginResponsePacket;
import com.zh.util.RSAUtil;
import org.apache.commons.codec.digest.DigestUtils;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

/**
 * 登录相关
 */
@Service
public class LoginService {

    @Autowired
    private UserService userService;

    @Transactional
    public LoginResponsePacket login(LoginRequestPacket requestPacket) {
        String password = DigestUtils.md5Hex(RSAUtil.decrypt(SystemConsts.PRIVATE_KEY, requestPacket.getPassword()));
        UserDTO userDTO = userService.selectByCodeAndPassword(requestPacket.getCode(), password);
        LoginResponsePacket loginResponsePacket = new LoginResponsePacket();
        if (userDTO == null) {
            loginResponsePacket.setSuccess(false);
            loginResponsePacket.setMsg("用户名或者密码错误");
        } else {
            loginResponsePacket.setSuccess(true);
            loginResponsePacket.setMsg("登录成功");
            UserVO userVO = new UserVO();
            BeanUtils.copyProperties(userDTO, userVO);
            loginResponsePacket.setData(userVO);
        }
        return loginResponsePacket;
    }
}
