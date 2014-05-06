package com.aaronpages.recom.dao;

import com.aaronpages.recom.dto.RecomInfo;

public interface IRecomDao {

	/**
	 * 获取Recom记录
	 * 
	 * @param uId
	 * @param pId
	 * @return
	 */
	public RecomInfo getOne(int uId, int pId);

	/**
	 * 添加记录
	 * 
	 * @param e
	 */
	public void addOne(RecomInfo e);

	/**
	 * 修改Recom记录
	 * 
	 * @param info
	 * @return
	 */
	public void update(RecomInfo e);
}
