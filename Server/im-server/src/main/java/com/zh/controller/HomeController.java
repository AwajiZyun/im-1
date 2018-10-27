package com.zh.controller;

import com.alibaba.fastjson.JSONObject;
import com.zh.domain.user.UserDTO;
import com.zh.domain.user.UserPO;
import com.zh.service.UserService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import java.util.ArrayList;
import java.util.List;


/**
 * @Author zh2683
 */
@RestController
public class HomeController {

    private static final Logger logger = LoggerFactory.getLogger(HomeController.class);

    @Autowired
    private UserService userService;

    @RequestMapping(value = "/", method = RequestMethod.GET,
            produces = MediaType.APPLICATION_JSON_UTF8_VALUE)
    public JSONObject home() {

        List<UserDTO> userDTOList = userService.listAll();

        List<UserPO> userPOS = new ArrayList<>();
        if (userDTOList.size() > 0) {
            for (UserDTO userDTO : userDTOList) {
                UserPO userPO = new UserPO();
                BeanUtils.copyProperties(userDTO, userPO);
                userPOS.add(userPO);
            }
        }

        JSONObject result = new JSONObject();
        result.put("success", true);
        result.put("users", userPOS);
        result.put("totalCount", userPOS.size());
        return result;
    }
}
