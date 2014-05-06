package com.aaronpages.aprs;

import java.util.List;

public interface IAprsClient {

	/**
	 * 获取推荐项目id
	 * 
	 * @param userId
	 * @return
	 */
	public List<Integer> getRecoms(int userId);
}
