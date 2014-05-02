package com.aaronpages.info.service;

import java.util.List;

import com.aaronpages.info.dto.TravelInfo;
import com.aaronpages.info.dto.TravelInfo.InfoOrder;

public interface IInfoService {

	/**
	 * 获取景点列表
	 * 
	 * @param order
	 * @param page
	 * @param pageSize
	 * @return
	 */
	public List<TravelInfo> getList(InfoOrder order, int page, int pageSize);
	
	/**
	 * 获取景点详情
	 * 
	 * @param id
	 * @param userId
	 * @return
	 */
	public TravelInfo getInfo(int id, String sessionId);

	/**
	 * 获取推荐景点
	 * 
	 * @param sessionId
	 * @return
	 */
	public List<TravelInfo> getRecoms(String sessionId);
}
