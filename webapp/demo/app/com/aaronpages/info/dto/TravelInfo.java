package com.aaronpages.info.dto;

import java.io.Serializable;

public class TravelInfo implements Serializable {

	private static final long serialVersionUID = 6650314398100775661L;
			
	/**
	 * 景点详情显示的字数
	 */
	private static final int contentNum = 100;

	/**
	 * 推荐景点详情显示的字数
	 */
	private static final int contentRemNum = 20;

	/**
	 * 景点名称显示字数
	 */
	private static final int nameNum = 10;


	/**
	 * 推荐景点名称显示字数
	 */
	private static final int nameRemNum = 4;

	/**
	 * 景点id
	 */
	private int id;

	/**
	 * 景点名称
	 */
	private String name;

	/**
	 * 景点描述
	 */
	private String content;

	/**
	 * 景点图片
	 */
	private String imagePath;

	/**
	 * 点击次数
	 */
	private int clickNum;

	/**
	 * 喜欢次数
	 */
	private int likeNum;

	/**
	 * 景点状态
	 */
	private int status;

	public TravelInfo(int id, String name, String content, String imagePath,
			int clickNum, int likeNum, int status) {

		this.id = id;
		this.name = name;
		this.content = content;
		this.imagePath = imagePath;
		this.clickNum = clickNum;
		this.likeNum = likeNum;
		this.status = status;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public String getShowName() {
		String t = this.name;
		if (this.name.length() > nameNum)
			return t.substring(0, nameNum) + "...";
		else
			return getName();
	}

	public String getRemName() {
		String t = this.name;
		if (this.name.length() > nameRemNum)
			return t.substring(0, nameRemNum) + "...";
		else
			return getName();
	}
	
	public void setName(String name) {
		this.name = name;
	}

	public String getShowContent() {
		String t = this.content;
		if (this.content.length() > contentNum)
			return t.substring(0, contentNum) + "...";
		else
			return getContent();
	}

	public String getRemContent() {
		String t = this.content;
		if (this.content.length() > contentRemNum)
			return t.substring(0, contentRemNum) + "...";
		else
			return getContent();
	}

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}

	public String getImagePath() {
		return imagePath;
	}

	public void setImagePath(String imagePath) {
		this.imagePath = imagePath;
	}

	public int getClickNum() {
		return clickNum;
	}

	public void setClickNum(int clickNum) {
		this.clickNum = clickNum;
	}

	public int getLikeNum() {
		return likeNum;
	}

	public void setLikeNum(int likeNum) {
		this.likeNum = likeNum;
	}

	public int getStatus() {
		return status;
	}

	public void setStatus(int status) {
		this.status = status;
	}

	public enum InfoOrder {
		/* 按照热度 */
		CLICK,
		/* 按照评分 */
		POINT,
		/* 按照时间 */
		TIME;
	}
}
