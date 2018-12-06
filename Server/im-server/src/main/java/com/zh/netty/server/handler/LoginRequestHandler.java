package com.zh.netty.server.handler;

import com.zh.constant.SystemConsts;
import com.zh.netty.constant.AttributeKeyConsts;
import com.zh.domain.user.UserDTO;
import com.zh.domain.user.UserVO;
import com.zh.netty.protocol.PacketCodec;
import com.zh.netty.protocol.login.LoginRequestPacket;
import com.zh.netty.protocol.login.LoginResponsePacket;
import com.zh.service.UserService;
import com.zh.util.RSAUtil;
import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import org.apache.commons.codec.digest.DigestUtils;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

/**
 * 登录请求处理
 * @author zh2683
 */
@Component
public class LoginRequestHandler extends SimpleChannelInboundHandler<LoginRequestPacket> {

    @Autowired
    private UserService userService;

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, LoginRequestPacket msg) throws Exception {
        String password = DigestUtils.md5Hex(RSAUtil.decrypt(SystemConsts.PRIVATE_KEY, msg.getPassword()));
        UserDTO userDTO = userService.selectByCodeAndPassword(msg.getCode(), password);
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
            ctx.channel().attr(AttributeKeyConsts.login);
        }
        ByteBuf byteBuf = PacketCodec.encode(loginResponsePacket);
        ctx.channel().writeAndFlush(byteBuf);
    }
}
