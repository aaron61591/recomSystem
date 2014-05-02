package controllers;

import java.util.List;

import javax.inject.Inject;

import com.aaronpages.info.dto.TravelInfo;
import com.aaronpages.info.dto.TravelInfo.InfoOrder;
import com.aaronpages.info.service.IInfoService;

public class FrontendController extends BaseController {

	@Inject
	private static IInfoService infoService;

	public static void index(InfoOrder order, int page, int pageSize) {

		List<TravelInfo> list = infoService.getList(order, page, pageSize);
		String sessionId = null;
		List<TravelInfo> recoms = infoService.getRecoms(sessionId);
		renderJapid(list, recoms);
	}

}