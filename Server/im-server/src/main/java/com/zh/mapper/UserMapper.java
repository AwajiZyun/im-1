package com.zh.mapper;

import com.zh.domain.user.UserPO;

import java.util.List;

/**
 * @author zh2683
 */
public interface UserMapper {

    List<UserPO> listAll();

    Integer count();
}
