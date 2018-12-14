package com.zh.mapper;

import com.zh.domain.user.UserPO;

import java.util.List;

/**
 * @author zh2683
 */
public interface UserMapper {

    void save(UserPO userPO);

    List<UserPO> listAll();

    Integer count();

    UserPO selectByCodeAndPassword(String code, String password);

    UserPO selectByEmail(String email);
}
