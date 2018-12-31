package com.zh.netty.handler;

import com.zh.domain.friend.DeleteFriendDTO;
import com.zh.netty.constant.AttributeKeyConsts;
import com.zh.netty.protocol.friend.DeleteFriendRequestPacket;
import com.zh.netty.protocol.friend.DeleteFriendResponsePacket;
import com.zh.service.FriendService;
import com.zh.util.SessionUtil;
import com.zh.util.ThreadPoolUtil;
import io.netty.channel.Channel;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

/**
 * @author zh2683
 */
@Slf4j
@Component
@Scope(ConfigurableBeanFactory.SCOPE_SINGLETON)
@ChannelHandler.Sharable
public class DeleteFriendHandler extends SimpleChannelInboundHandler<DeleteFriendRequestPacket> {

    @Autowired
    private FriendService friendService;

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, DeleteFriendRequestPacket msg) throws Exception {
        DeleteFriendDTO friendDTO = new DeleteFriendDTO();
        String userCode = ctx.channel().attr(AttributeKeyConsts.code).get();
        String friendCode = msg.getCode();
        friendDTO.setUserCode(userCode);
        friendDTO.setFriendCode(friendCode);
        int count = friendService.delete(friendDTO);
        DeleteFriendResponsePacket deleteFriendResponsePacket = new DeleteFriendResponsePacket();
        if (count == 0) {
            deleteFriendResponsePacket.setSuccess(true);
            ctx.channel().writeAndFlush(deleteFriendResponsePacket);
            return;
        }
        deleteFriendResponsePacket.setSuccess(true);
        deleteFriendResponsePacket.setData(String.valueOf(count));
        ctx.channel().writeAndFlush(deleteFriendResponsePacket);
        // 异步通知被删除的好友
        ThreadPoolUtil.execute(() -> {
            Channel friendChannel = SessionUtil.get(friendCode);
            if (friendChannel != null) {
                try {
                    DeleteFriendRequestPacket deleteFriendRequestPacket = new DeleteFriendRequestPacket();
                    deleteFriendRequestPacket.setCode(userCode);
                    friendChannel.writeAndFlush(deleteFriendRequestPacket);
                } catch (Exception e) {
                    log.error("推送" + friendCode + "被" + userCode + "删除失败", e);
                }
            }
        });
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable t) {
        log.error("", t);
        DeleteFriendResponsePacket deleteFriendResponsePacket = new DeleteFriendResponsePacket();
        deleteFriendResponsePacket.setSuccess(false);
        ctx.channel().writeAndFlush(deleteFriendResponsePacket);
    }
}
