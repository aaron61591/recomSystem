package com.aaronpages.user.dao;

import com.aaronpages.user.dto.UserInfo;

public interface IUserDao {

	/**
	 * 获取用户
	 * 
	 * @param sessionId
	 * @return
	 */
	public UserInfo getOne(String sessionId);

	/**
	 * 添加用户
	 * 
	 * @param sessionId
	 * @return
	 */
	public void addOne(String sessionId);

}
