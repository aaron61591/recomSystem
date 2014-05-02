package com.aaronpages.info.service.impl;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import com.aaronpages.info.dao.IInfoDao;
import com.aaronpages.info.dto.TravelInfo;
import com.aaronpages.info.dto.TravelInfo.InfoOrder;
import com.aaronpages.info.service.IInfoService;
import com.google.inject.Inject;

public class InfoServiceImpl implements IInfoService {

	@Inject
	private IInfoDao infoDao;
	
	@Override
	public List<TravelInfo> getRecoms(String sessionId) {
		// TODO Auto-generated method stub
		return null;
	}
	
	@Override
	public List<TravelInfo> getList(InfoOrder order, int page, int pageSize) {
		
		if (order == null)
			order = InfoOrder.CLICK;
		if (page < 1)
			page = 1;
		if (pageSize < 1)
			pageSize = 5;

		List<TravelInfo> list = new ArrayList<TravelInfo>();
		List<Integer> idList = infoDao.getList(order, (page - 1) * pageSize, pageSize);
		
		Iterator<Integer> iter = idList.iterator();
		while(iter.hasNext()) {
			Integer id = iter.next();
			TravelInfo e = infoDao.getOne(id);
			if (e != null)
				list.add(e);
		}
		return list;
	}

	@Override
	public TravelInfo getInfo(int id, String userId) {
		// TODO Auto-generated method stub
		return null;
	}

}
