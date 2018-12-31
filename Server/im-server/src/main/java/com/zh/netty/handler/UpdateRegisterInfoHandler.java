package com.zh.netty.handler;

import com.zh.constant.SystemConsts;
import com.zh.domain.user.UpdateUserDTO;
import com.zh.netty.constant.AttributeKeyConsts;
import com.zh.netty.protocol.register.UpdateRegisterInfoRequestPacket;
import com.zh.netty.protocol.register.UpdateRegisterInfoResponsePacket;
import com.zh.service.UserService;
import com.zh.util.RSAUtil;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import lombok.extern.slf4j.Slf4j;
import org.apache.commons.codec.digest.DigestUtils;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

import java.util.Date;

/**
 * @author zh2683
 */
@Slf4j
@Component
@Scope(ConfigurableBeanFactory.SCOPE_SINGLETON)
@ChannelHandler.Sharable
public class UpdateRegisterInfoHandler extends SimpleChannelInboundHandler<UpdateRegisterInfoRequestPacket> {

    @Autowired
    private UserService userService;

    @Override
    public void channelActive(ChannelHandlerContext ctx) {
        System.out.println("active");
    }

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, UpdateRegisterInfoRequestPacket msg) throws Exception {
        String currentUserCode = ctx.channel().attr(AttributeKeyConsts.code).get();
        if (!currentUserCode.equals(msg.getCode())) {
            throw new RuntimeException("不能更新其他人的信息");
        }
        UpdateUserDTO updateUserDTO = new UpdateUserDTO();
        BeanUtils.copyProperties(msg, updateUserDTO);
        updateUserDTO.setOldPassword(DigestUtils.md5Hex(RSAUtil.decrypt(SystemConsts.PRIVATE_KEY, msg.getOldPassword())));
        updateUserDTO.setNewPassword(DigestUtils.md5Hex(RSAUtil.decrypt(SystemConsts.PRIVATE_KEY, msg.getNewPassword())));
        updateUserDTO.setModifyTime(new Date());
        int count = userService.update(updateUserDTO);
        UpdateRegisterInfoResponsePacket updateRegisterInfoResponsePacket = new UpdateRegisterInfoResponsePacket();
        updateRegisterInfoResponsePacket.setSuccess(true);
        updateRegisterInfoResponsePacket.setData(String.valueOf(count));
        ctx.channel().writeAndFlush(updateRegisterInfoResponsePacket);
        // TODO 向好友推送此更新

    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable t) {
        log.error("", t);
        UpdateRegisterInfoResponsePacket updateRegisterInfoResponsePacket = new UpdateRegisterInfoResponsePacket();
        updateRegisterInfoResponsePacket.setSuccess(false);
        ctx.channel().writeAndFlush(updateRegisterInfoResponsePacket);
    }
}
