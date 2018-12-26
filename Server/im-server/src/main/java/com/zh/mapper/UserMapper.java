package com.zh.mapper;

import com.zh.domain.user.UserPO;
import org.apache.ibatis.annotations.Param;

import java.util.Collection;
import java.util.List;

/**
 * @author zh2683
 */
public interface UserMapper {

    void save(UserPO userPO);

    List<UserPO> listAll();

    Integer count();

    List<UserPO> listByCode(List<String> codes);

    UserPO selectByCodeOrEmail(@Param("code") String code, @Param("email") String email);

    UserPO selectByCodeAndPassword(@Param("code") String code, @Param("password") String password);

    UserPO selectByEmail(String email);
}
