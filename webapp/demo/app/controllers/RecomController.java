package controllers;

import java.util.List;

import javax.inject.Inject;

import com.aaronpages.info.dto.TravelInfo;
import com.aaronpages.info.dto.TravelInfo.InfoOrder;
import com.aaronpages.recom.service.IRecomService;
import com.aaronpages.user.service.IUserService;

public class RecomController extends BaseController {

	@Inject
	private static IRecomService recomService;

	@Inject
	private static IUserService userService;

	public static void like(int id) {

		String sessionId = session.getId();
		int uId = userService.getUserId(sessionId);
		recomService.likeInfo(uId, id);
		redirect("../detail?id=" + id);
	}

	public static void reRecom(InfoOrder order, int page, int id) {

		if (id == 0)
			redirect("../index?order" + order + "&page=" + page);
		else
			redirect("../detail?id=" + id);
	}
}