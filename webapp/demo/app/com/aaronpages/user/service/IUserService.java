package com.aaronpages.user.service;

public interface IUserService {

	/**
	 * 浏览记录
	 * 
	 * @param sessionId
	 * @param travelId
	 */
	public void incrPoint(String sessionId, int travelId);
	
	/**
	 * 喜欢景点
	 * 
	 * @param id
	 * @param userId
	 */
	public void likeInfo(int id, String sessionId);
}
