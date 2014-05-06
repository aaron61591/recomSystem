package com.aaronpages.recom.service.impl;

import com.aaronpages.info.service.IInfoService;
import com.aaronpages.recom.dao.IRecomDao;
import com.aaronpages.recom.dto.RecomInfo;
import com.aaronpages.recom.service.IRecomService;
import com.google.inject.Inject;

public class RecomServiceImpl implements IRecomService {

	@Inject
	private IRecomDao recomDao;

	@Inject
	private IInfoService infoService;

	/**
	 * 获取推荐条目
	 * 
	 * @param uId
	 * @param pId
	 * @return
	 */
	private RecomInfo getRecom(int uId, int pId) {

		RecomInfo e = recomDao.getOne(uId, pId);
		if (e == null) {
			e = new RecomInfo(uId, pId, 0, 0);
			recomDao.addOne(e);
		}
		return e;
	}

	@Override
	public void incrPoint(int uId, int pId) {

		RecomInfo e = getRecom(uId, pId);
		if (e.getPoint1() <= 9)
			e.setPoint1(e.getPoint1() + 1);

		recomDao.update(e);
	}

	@Override
	public void likeInfo(int uId, int pId) {

		RecomInfo e = getRecom(uId, pId);
		// if (e.getPoint2() != 0)
		// e.setPoint2(0);
		// else
		// e.setPoint2(5);
		e.setPoint2(5);
		recomDao.update(e);

		infoService.incrLike(pId);
	}

}
