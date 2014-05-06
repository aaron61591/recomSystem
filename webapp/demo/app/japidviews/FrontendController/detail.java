package japidviews.FrontendController;
import java.util.*;
import java.io.*;
import cn.bran.japid.tags.Each;
import com.aaronpages.info.dto.TravelInfo.InfoOrder;
import com.aaronpages.info.dto.TravelInfo;
import static cn.bran.play.JapidPlayAdapter.*;
import static play.templates.JavaExtensions.*;
import static play.data.validation.Validation.*;
import japidviews._layouts.*;
import play.i18n.Messages;
import play.data.validation.Validation;
import play.mvc.Scope.*;
import models.*;
import play.data.validation.Error;
import japidviews._tags.*;
import play.i18n.Lang;
import controllers.*;
import play.mvc.Http.*;
import japidviews._javatags.*;
//
// NOTE: This file was generated from: japidviews/FrontendController/detail.html
// Change to this file will be lost next time the template file is compiled.
//
@cn.bran.play.NoEnhance
public class detail extends cn.bran.play.JapidTemplateBase
{
	public static final String sourceTemplate = "japidviews/FrontendController/detail.html";
	{
		putHeader("Content-Type", "text/html; charset=utf-8");
		setContentType("text/html; charset=utf-8");
	}

// - add implicit fields with Play

	final Request request = Request.current(); 
	final Response response = Response.current(); 
	final Session session = Session.current();
	final RenderArgs renderArgs = RenderArgs.current();
	final Params params = Params.current();
	final Validation validation = Validation.current();
	final cn.bran.play.FieldErrors errors = new cn.bran.play.FieldErrors(validation);
	final play.Play _play = new play.Play(); 

// - end of implicit fields with Play 


	public detail() {
		super(null);
	}
	public detail(StringBuilder out) {
		super(out);
	}
/* based on https://github.com/branaway/Japid/issues/12
 */
	public static final String[] argNames = new String[] {/* args of the template*/"list", "recoms", "order", "page", "detail",  };
	public static final String[] argTypes = new String[] {/* arg types of the template*/"List<TravelInfo>", "List<TravelInfo>", "InfoOrder", "int", "TravelInfo",  };
	public static final Object[] argDefaults= new Object[] {null,null,null,null,null, };
	public static java.lang.reflect.Method renderMethod = getRenderMethod(japidviews.FrontendController.detail.class);

	{
		setRenderMethod(renderMethod);
		setArgNames(argNames);
		setArgTypes(argTypes);
		setArgDefaults(argDefaults);
		setSourceTemplate(sourceTemplate);
	}
////// end of named args stuff

	private List<TravelInfo> list; // line 4
	private List<TravelInfo> recoms; // line 4
	private InfoOrder order; // line 4
	private int page; // line 4
	private TravelInfo detail; // line 4
	public cn.bran.japid.template.RenderResult render(List<TravelInfo> list,List<TravelInfo> recoms,InfoOrder order,int page,TravelInfo detail) {
		this.list = list;
		this.recoms = recoms;
		this.order = order;
		this.page = page;
		this.detail = detail;
		long t = -1;
		try {super.layout();} catch (RuntimeException e) { super.handleException(e);} // line 4
		return new cn.bran.japid.template.RenderResultPartial(getHeaders(), getOut(), t, actionRunners, sourceTemplate);
	}
	@Override protected void doLayout() {
		beginDoLayout(sourceTemplate);
//------
;// line 1
p("<html>\n" + 
"	<head>\n" + 
"		<title>旅游网站demo</title>\n" + 
"	</head>\n" + 
"	<link href=\"css/init.css\" rel=\"stylesheet\" type=\"text/css\" />\n" + 
"	<link href=\"css/main.css\" rel=\"stylesheet\" type=\"text/css\" />\n" + 
"	<link href=\"css/font.css\" rel=\"stylesheet\" type=\"text/css\" />\n" + 
"	<body>\n" + 
"		<main>\n" + 
"			<head_decorate>test</head_decorate>\n" + 
"			<header>\n" + 
"				<logo>DEMO旅游网</logo>\n" + 
"				<a href=\"../index\"><column1>首页</column1></a>\n" + 
"				<column>攻略</column>\n" + 
"				<column>游记</column>\n" + 
"			</header>\n" + 
"			<decorate>\n" + 
"				<decorate1></decorate1>\n" + 
"				<decorate2></decorate2>\n" + 
"				<div style=\"clear: both;\"></div>\n" + 
"			</decorate>\n" + 
"			<show>\n" + 
"				");// line 4
		if (detail == null) {// line 28
		p("				<info_opt>\n" + 
"					<opt_font1>旅游景点：</opt_font1>\n" + 
"					<a href=\"http://localhost:9000/index?order=POINT\"><opt_font2>好评</opt_font2></a>\n" + 
"					<a href=\"http://localhost:9000/index?order=CLICK\"><opt_font2>热度</opt_font2></a>\n" + 
"					<a href=\"http://localhost:9000/index?order=TIME\"><opt_font2>时间</opt_font2></a>\n" + 
"				</info_opt>\n" + 
"				");// line 28
		if (list != null)// line 35
		p("				");// line 35
		for(int i = 0; i < list.size(); ++i) {// line 36
		p("					");// line 36
		if (list.get(i) != null) {// line 37
		p("					<info>\n" + 
"						<picture>\n" + 
"							<img class=\"info_img\" src=\"");// line 37
		p(list.get(i).getImagePath());// line 40
		p("\"/>\n" + 
"						</picture>\n" + 
"						<content>\n" + 
"							<a href=\"../detail?id=");// line 40
		p(list.get(i).getId());// line 43
		p("\"><detail_head>");// line 43
		p(list.get(i).getShowName());// line 43
		p("</detail_head></a>\n" + 
"							<detail1>\n" + 
"								<detail_font1>作者：</detail_font1>\n" + 
"								<detail_font2>Aaron</detail_font2>\n" + 
"								<detail_font3>04-30 02:11</detail_font3>\n" + 
"								<detail_font4>");// line 43
		p(list.get(i).getClickNum());// line 48
		p("/");// line 48
		p(list.get(i).getLikeNum());// line 48
		p("</detail_font4>\n" + 
"							</detail1>\n" + 
"							<detail2>");// line 48
		p(list.get(i).getShowContent());// line 50
		p("</detail2>\n" + 
"						</content>\n" + 
"					</info>\n" + 
"					");// line 50
		}// line 53
		p("				");// line 53
		}// line 54
		p("				<page>\n" + 
"					<a href=\"../index?page=");// line 54
		p(page - 1);// line 56
		p("&order=");// line 56
		p(order);// line 56
		p("\"><page_font>上一页</page_font></a>\n" + 
"					<a href=\"../index?page=");// line 56
		p(page + 1);// line 57
		p("&order=");// line 57
		p(order);// line 57
		p("\"><page_font>下一页</page_font></a>\n" + 
"				</page>\n" + 
"				");// line 57
		} else {// line 59
		p("					<detail_title>\n" + 
"						<detail_title_font>");// line 59
		p(detail.getName());// line 61
		p("</detail_title_font>\n" + 
"						<detail_font5>");// line 61
		p(detail.getClickNum());// line 62
		p("/");// line 62
		p(detail.getLikeNum());// line 62
		p("</detail_font5>\n" + 
"						<detail_font7 style=\"margin-left: 30px; font-size: 15px;\">作者：</detail_font1>\n" + 
"						<detail_font8 style=\"font-size: 15px;\">Aaron</detail_font2>\n" + 
"						<detail_font9 style=\"font-size: 15px;\">04-30 02:11</detail_font3>\n" + 
"						<a href=\"../like?id=");// line 62
		p(detail.getId());// line 66
		p("\">\n" + 
"							<img class=\"detail_like\" src=\"../image/like.jpg\"/>\n" + 
"							<detail_font6>喜欢</detail_font6>\n" + 
"						</a>\n" + 
"					</detail_title>\n" + 
"					<detail_img>\n" + 
"						<img style=\"height: 100%; width: 500px; margin-left: 30px;\" src=\"");// line 66
		p(detail.getImagePath());// line 72
		p("\"/>\n" + 
"					</detail_img>\n" + 
"					<detail_content>");// line 72
		p(detail.getContent());// line 74
		p("</detail_content>\n" + 
"				");// line 74
		}// line 75
		p("			</show>\n" + 
"			<recommend>\n" + 
"				<recom_page>\n" + 
"					<recom_opt1>猜你喜欢：</recom_opt1>\n" + 
"					");// line 75
		if (detail == null) {// line 80
		p("						<a href=\"../reRecom?order=");// line 80
		p(order);// line 81
		p("&page=");// line 81
		p(page);// line 81
		p("\"><recom_opt2>换一换</recom_opt2></a>\n" + 
"					");// line 81
		} else {// line 82
		p("						<a href=\"../reRecom?id=");// line 82
		p(detail.getId());// line 83
		p("\"><recom_opt2>换一换</recom_opt2></a>\n" + 
"					");// line 83
		}// line 84
		p("					\n" + 
"				</recom_page>\n" + 
"				");// line 84
		if (recoms != null) {// line 87
		p("				");// line 87
		for (int i = 0; i < recoms.size(); ++i) {// line 88
		p("					");// line 88
		if (recoms.get(i) != null) {// line 89
		p("					<recom_info>\n" + 
"						<recom_image>\n" + 
"							<img class=\"info_img\" src=\"");// line 89
		p(recoms.get(i).getImagePath());// line 92
		p("\"/>\n" + 
"						</recom_image>\n" + 
"						<recom_title>\n" + 
"							<a href=\"../detail?id=");// line 92
		p(recoms.get(i).getId());// line 95
		p("\">\n" + 
"								<recom_tittle_font>");// line 95
		p(recoms.get(i).getRemName());// line 96
		p("</recom_tittle_font>\n" + 
"							</a>\n" + 
"							<detail_font4>");// line 96
		p(recoms.get(i).getClickNum());// line 98
		p("/");// line 98
		p(recoms.get(i).getLikeNum());// line 98
		p("</detail_font4>\n" + 
"						</recom_title>\n" + 
"						<recom_detail>\n" + 
"							<recom_content_font>");// line 98
		p(recoms.get(i).getRemContent());// line 101
		p("</recom_content_font>\n" + 
"						</recom_detail>\n" + 
"					</recom_info>\n" + 
"					");// line 101
		}// line 104
		p("					");// line 104
		}// line 105
		p("				");// line 105
		}// line 106
		p("			</recommend>\n" + 
"			<div style=\"clear: both;\"></div>\n" + 
"		</main>\n" + 
"		<footer>Copyright © 2014-2014 Aaron_P</footer>\n" + 
"	</body>\n" + 
"</html>");// line 106
		
		endDoLayout(sourceTemplate);
	}

}