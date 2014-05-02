package japidviews.FrontendController;
import java.util.*;
import java.io.*;
import cn.bran.japid.tags.Each;
import java.util.List;
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
// NOTE: This file was generated from: japidviews/FrontendController/index.html
// Change to this file will be lost next time the template file is compiled.
//
@cn.bran.play.NoEnhance
public class index extends cn.bran.play.JapidTemplateBase
{
	public static final String sourceTemplate = "japidviews/FrontendController/index.html";
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


	public index() {
		super(null);
	}
	public index(StringBuilder out) {
		super(out);
	}
/* based on https://github.com/branaway/Japid/issues/12
 */
	public static final String[] argNames = new String[] {/* args of the template*/"list", "recoms",  };
	public static final String[] argTypes = new String[] {/* arg types of the template*/"List<TravelInfo>", "List<TravelInfo>",  };
	public static final Object[] argDefaults= new Object[] {null,null, };
	public static java.lang.reflect.Method renderMethod = getRenderMethod(japidviews.FrontendController.index.class);

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
	public cn.bran.japid.template.RenderResult render(List<TravelInfo> list,List<TravelInfo> recoms) {
		this.list = list;
		this.recoms = recoms;
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
"			<header>\n" + 
"				<logo>DEMO旅游网</logo>\n" + 
"				<column1>首页</column1>\n" + 
"				<column>攻略</column>\n" + 
"				<column>游记</column>\n" + 
"			</header>\n" + 
"			<show>\n" + 
"				<info_opt>\n" + 
"					<opt_font1>旅游景点：</opt_font1>\n" + 
"					<a href=\"http://localhost:9000/index?order=POINT\"><opt_font2>好评</opt_font2></a>\n" + 
"					<a href=\"http://localhost:9000/index?order=CLICK\"><opt_font2>热度</opt_font2></a>\n" + 
"					<a href=\"http://localhost:9000/index?order=TIME\"><opt_font2>时间</opt_font2></a>\n" + 
"				</info_opt>\n" + 
"				");// line 4
		for(int i = 0; i < list.size(); ++i) {// line 28
		p("					");// line 28
		if (list.get(i) != null) {// line 29
		p("					<info>\n" + 
"						<picture>\n" + 
"							<img class=\"info_img\" src=\"../image/background.png\"/>\n" + 
"						</picture>\n" + 
"						<content>\n" + 
"							<detail_head>");// line 29
		p(list.get(i).getShowName());// line 35
		p("</detail_head>\n" + 
"							<detail1>\n" + 
"								<detail_font1>作者：</detail_font1>\n" + 
"								<detail_font2>Aaron</detail_font2>\n" + 
"								<detail_font3>04-30 02:11</detail_font3>\n" + 
"								<detail_font4>");// line 35
		p(list.get(i).getClickNum());// line 40
		p("/");// line 40
		p(list.get(i).getLikeNum());// line 40
		p("</detail_font4>\n" + 
"							</detail1>\n" + 
"							<detail2>");// line 40
		p(list.get(i).getShowContent());// line 42
		p("</detail2>\n" + 
"						</content>\n" + 
"					</info>\n" + 
"					");// line 42
		}// line 45
		p("				");// line 45
		}// line 46
		p("				<page>\n" + 
"					<page_font>上一页</page_font>\n" + 
"					<page_font>下一页</page_font>\n" + 
"				</page>\n" + 
"			</show>\n" + 
"			<recommend>\n" + 
"				<recom_page>\n" + 
"					<recom_opt1>猜你喜欢：</recom_opt1>\n" + 
"					<recom_opt2>换一换</recom_opt2>\n" + 
"				</recom_page>\n" + 
"				<recom_info>\n" + 
"					<recom_image>\n" + 
"						<img class=\"info_img\" src=\"../image/background.png\"/>\n" + 
"					</recom_image>\n" + 
"					<recom_title>\n" + 
"						<recom_tittle_font>西藏</recom_tittle_font>\n" + 
"						<detail_font4>26/1</detail_font4>\n" + 
"					</recom_title>\n" + 
"					<recom_detail>\n" + 
"						<recom_content_font>总述: 天津 出发。 2008年，老爸乘火车去了一趟西藏...</recom_content_font>\n" + 
"					</recom_detail>\n" + 
"				</recom_info>\n" + 
"				<recom_info>\n" + 
"					<recom_image>\n" + 
"						<img class=\"info_img\" src=\"../image/background.png\"/>\n" + 
"					</recom_image>\n" + 
"					<recom_title>\n" + 
"						<recom_tittle_font>西藏</recom_tittle_font>\n" + 
"						<detail_font4>26/1</detail_font4>\n" + 
"					</recom_title>\n" + 
"					<recom_detail>\n" + 
"						<recom_content_font>总述: 天津 出发。 2008年，老爸乘火车去了一趟西藏...</recom_content_font>\n" + 
"					</recom_detail>\n" + 
"				</recom_info>\n" + 
"				<recom_info>\n" + 
"					<recom_image>\n" + 
"						<img class=\"info_img\" src=\"../image/background.png\"/>\n" + 
"					</recom_image>\n" + 
"					<recom_title>\n" + 
"						<recom_tittle_font>西藏</recom_tittle_font>\n" + 
"						<detail_font4>26/1</detail_font4>\n" + 
"					</recom_title>\n" + 
"					<recom_detail>\n" + 
"						<recom_content_font>总述: 天津 出发。 2008年，老爸乘火车去了一趟西藏...</recom_content_font>\n" + 
"					</recom_detail>\n" + 
"				</recom_info>\n" + 
"				<recom_info>\n" + 
"					<recom_image>\n" + 
"						<img class=\"info_img\" src=\"../image/background.png\"/>\n" + 
"					</recom_image>\n" + 
"					<recom_title>\n" + 
"						<recom_tittle_font>西藏</recom_tittle_font>\n" + 
"						<detail_font4>26/1</detail_font4>\n" + 
"					</recom_title>\n" + 
"					<recom_detail>\n" + 
"						<recom_content_font>总述: 天津 出发。 2008年，老爸乘火车去了一趟西藏...</recom_content_font>\n" + 
"					</recom_detail>\n" + 
"				</recom_info>\n" + 
"				<recom_info>\n" + 
"					<recom_image>\n" + 
"						<img class=\"info_img\" src=\"../image/background.png\"/>\n" + 
"					</recom_image>\n" + 
"					<recom_title>\n" + 
"						<recom_tittle_font>西藏</recom_tittle_font>\n" + 
"						<detail_font4>26/1</detail_font4>\n" + 
"					</recom_title>\n" + 
"					<recom_detail>\n" + 
"						<recom_content_font>总述: 天津 出发。 2008年，老爸乘火车去了一趟西藏...</recom_content_font>\n" + 
"					</recom_detail>\n" + 
"				</recom_info>\n" + 
"			</recommend>\n" + 
"		</main>\n" + 
"		<footer>Copyright © 2014-2014 Aaron_P</footer>\n" + 
"	</body>\n" + 
"</html>");// line 46
		
		endDoLayout(sourceTemplate);
	}

}