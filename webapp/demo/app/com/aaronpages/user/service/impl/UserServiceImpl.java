package com.aaronpages.user.service.impl;

import com.aaronpages.recom.service.IRecomService;
import com.aaronpages.user.dao.IUserDao;
import com.aaronpages.user.dto.UserInfo;
import com.aaronpages.user.service.IUserService;
import com.google.inject.Inject;

public class UserServiceImpl implements IUserService {

	@Inject
	private IUserDao userDao;

	@Override
	public int getUserId(String sessionId) {

		UserInfo u = userDao.getOne(sessionId);

		if (u != null)
			return u.getId();

		userDao.addOne(sessionId);
		return userDao.getOne(sessionId).getId();
	}

}
