package com.aaronpages.recom.dto;

public class RecomInfo {

	/**
	 * 用户id
	 */
	private int userId;

	/**
	 * 项目id
	 */
	private int producedId;

	/**
	 * 点击分数
	 */
	private int point1;

	/**
	 * 喜欢分数
	 */
	private int point2;

	public RecomInfo(int userId, int producedId, int point1, int point2) {

		this.userId = userId;
		this.producedId = producedId;
		this.point1 = point1;
		this.point2 = point2;
	}

	public int getUserId() {
		return userId;
	}

	public void setUserId(int userId) {
		this.userId = userId;
	}

	public int getProducedId() {
		return producedId;
	}

	public void setProducedId(int producedId) {
		this.producedId = producedId;
	}

	public int getPoint1() {
		return point1;
	}

	public void setPoint1(int point1) {
		this.point1 = point1;
	}

	public int getPoint2() {
		return point2;
	}

	public void setPoint2(int point2) {
		this.point2 = point2;
	}

}
