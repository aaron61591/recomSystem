package com.aaronpages.recom.service;

import com.aaronpages.recom.dto.RecomInfo;

public interface IRecomService {

	/**
	 * 浏览记录
	 * 
	 * @param sessionId
	 * @param travelId
	 */
	public void incrPoint(int uId, int pId);

	/**
	 * 喜欢景点
	 * 
	 * @param uId
	 * @param pId
	 */
	public void likeInfo(int uId, int pId);
}
