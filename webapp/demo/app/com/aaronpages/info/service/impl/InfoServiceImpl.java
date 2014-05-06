package com.aaronpages.info.service.impl;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import com.aaronpages.aprs.IAprsClient;
import com.aaronpages.info.dao.IInfoDao;
import com.aaronpages.info.dto.TravelInfo;
import com.aaronpages.info.dto.TravelInfo.InfoOrder;
import com.aaronpages.info.service.IInfoService;
import com.aaronpages.recom.service.IRecomService;
import com.aaronpages.user.service.IUserService;
import com.google.inject.Inject;

public class InfoServiceImpl implements IInfoService {

	@Inject
	private IInfoDao infoDao;

	@Inject
	private IAprsClient aprsClient;

	@Inject
	private IUserService userService;

	@Inject
	private IRecomService recomService;

	/**
	 * 推荐系统生成推荐数
	 */
	private static final int _recomNum = 20;

	/**
	 * 前台显示推荐数
	 */
	private static final int _showNum = 5;

	/**
	 * 有id获取TravelInfo
	 * 
	 * @param idList
	 * @return
	 */
	private List<TravelInfo> packList(List<Integer> idList) {

		if (idList == null)
			return null;

		List<TravelInfo> list = new ArrayList<TravelInfo>();
		Iterator<Integer> iter = idList.iterator();
		while (iter.hasNext()) {
			Integer id = iter.next();
			TravelInfo e = infoDao.getOne(id);
			if (e != null)
				list.add(e);
		}
		return list;
	}

	@Override
	public List<TravelInfo> getRecoms(String sessionId) {

		List<Integer> idList = aprsClient.getRecoms(userService
				.getUserId(sessionId));
		
		/* supply the recommend number */
		if (idList != null && idList.size() < 20) {
			int need = _recomNum - idList.size();
			List<Integer> tmpList = infoDao.getList(InfoOrder.CLICK, 0, need);
			idList.addAll(tmpList);
		}

		/* select _showNum info by random */
		List<Integer> result = new ArrayList<Integer>();
		int i = 0;
		while (i < _showNum && i < idList.size()) {
			int n = (int) (Math.random() * idList.size());
			int id = idList.get(n);
			if (!result.contains(id)) {
				result.add(id);
				++i;
			}
		}

		return packList(result);
	}

	@Override
	public List<TravelInfo> getList(InfoOrder order, int page, int pageSize) {

		if (order == null)
			order = InfoOrder.CLICK;
		if (page < 1)
			page = 1;
		if (pageSize < 1)
			pageSize = 5;

		List<Integer> idList = infoDao.getList(order, (page - 1) * pageSize,
				pageSize);
		return packList(idList);
	}

	private void incrClick(int id) {

		infoDao.incrClick(id);
	}

	@Override
	public TravelInfo getInfo(int id, String sessionId) {

		int uId = userService.getUserId(sessionId);
		recomService.incrPoint(uId, id);
		incrClick(id);
		return infoDao.getOne(id);
	}

	@Override
	public void incrLike(int id) {

		infoDao.incrLike(id);
	}

}
