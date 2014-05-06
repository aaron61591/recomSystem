package controllers;

import java.util.List;

import javax.inject.Inject;

import com.aaronpages.info.dto.TravelInfo;
import com.aaronpages.info.dto.TravelInfo.InfoOrder;
import com.aaronpages.info.service.IInfoService;
import com.aaronpages.user.dto.UserInfo;
import com.aaronpages.user.service.IUserService;

public class FrontendController extends BaseController {

	@Inject
	private static IInfoService infoService;

	public static void index(InfoOrder order, int page, int pageSize) {

		List<TravelInfo> list = infoService.getList(order, page, pageSize);
		String sessionId = session.getId();
		List<TravelInfo> recoms = infoService.getRecoms(sessionId);
		renderJapid(list, recoms, order, page, null);
	}

	public static void detail(int id) {

		String sessionId = session.getId();
		List<TravelInfo> recoms = infoService.getRecoms(sessionId);
		TravelInfo e = infoService.getInfo(id, sessionId);
		if (e == null)
			index(InfoOrder.CLICK, 1, 5);
		renderJapid(null, recoms, null, 0, e);
	}
}