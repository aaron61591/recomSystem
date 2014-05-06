package com.aaronpages.user.dto;

public class UserInfo {

	private int id;

	private String sessionId;

	private int status;

	public UserInfo(int id, String sessionId) {

		this.id = id;
		this.sessionId = sessionId;
		this.status = 1;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getSession_id() {
		return sessionId;
	}

	public void setSession_id(String session_id) {
		this.sessionId = session_id;
	}

	public int getStatus() {
		return status;
	}

	public void setStatus(int status) {
		this.status = status;
	}

}
