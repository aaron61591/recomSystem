package com.aaronpages.info.dao;

import java.util.List;

import com.aaronpages.info.dto.TravelInfo;
import com.aaronpages.info.dto.TravelInfo.InfoOrder;

public interface IInfoDao {

	/**
	 * 获取List
	 * 
	 * @param order
	 * @param start
	 * @param num
	 * @return
	 */
	public List<Integer> getList(InfoOrder order, int start, int num);

	/**
	 * 获取旅游详情
	 * 
	 * @param id
	 * @return
	 */
	public TravelInfo getOne(int id);

	/**
	 * 增加点击数
	 * 
	 * @param id
	 */
	public void incrClick(int id);

	/**
	 * 增加喜欢数
	 * 
	 * @param id
	 */
	public void incrLike(int id);
}
