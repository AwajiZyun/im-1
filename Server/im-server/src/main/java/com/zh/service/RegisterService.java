package com.zh.service;

import com.zh.constant.SystemConsts;
import com.zh.domain.user.UserDTO;
import com.zh.domain.user.UserPO;
import com.zh.domain.user.UserVO;
import com.zh.netty.protocol.register.RegisterRequestPacket;
import com.zh.netty.protocol.register.RegisterResponsePacket;
import com.zh.util.RSAUtil;
import org.apache.commons.codec.digest.DigestUtils;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Date;
import java.util.UUID;

/**
 * TODO 注册处理
 */
@Service
public class RegisterService {

    @Autowired
    private UserService userService;

    @Autowired
    private RedisService redisService;

    @Transactional
    public RegisterResponsePacket register(RegisterRequestPacket registerRequestPacket) {
        RegisterResponsePacket registerResponsePacket = new RegisterResponsePacket();
        try {
            UserDTO userDTO = userService.selectByEmail(registerRequestPacket.getEmail());
            if (userDTO == null) {
                UserPO userPO = new UserPO();
                userPO.setId(UUID.randomUUID().toString().replaceAll("-", ""));
                userPO.setEmail(registerRequestPacket.getEmail());
                userPO.setNickname(registerRequestPacket.getNickname());
                userPO.setSex(registerRequestPacket.getSexEnum());
                String password = DigestUtils.md5Hex(RSAUtil.decrypt(SystemConsts.PRIVATE_KEY, registerRequestPacket.getPassword()));
                userPO.setPassword(password);
                userPO.setCreateTime(new Date());
                userPO.setDelete(false);
                // TODO 这里要检测队列长度,然后在号码短缺时自动增长
                Integer code = Integer.valueOf(redisService.lpop(SystemConsts.RAW_CODE_POOL));
                userPO.setCode(code);
                userService.save(userPO);
                registerResponsePacket.setMsg("注册成功");
                registerResponsePacket.setSuccess(true);
                UserVO userVO = new UserVO();
                BeanUtils.copyProperties(userPO, userVO);
                registerResponsePacket.setData(userVO);
            } else {
                registerResponsePacket.setMsg("此邮箱已被使用");
                registerResponsePacket.setSuccess(false);
            }
        } catch (Exception e) {
            registerResponsePacket.setMsg("系统错误");
            registerResponsePacket.setSuccess(false);
        }
        return registerResponsePacket;
    }
}
