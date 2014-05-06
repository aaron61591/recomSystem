package com.aaronpages.user.dao.impl;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import play.db.DB;

import com.aaronpages.user.dao.IUserDao;
import com.aaronpages.user.dto.UserInfo;

public class UserDaoImpl implements IUserDao {

	@Override
	public UserInfo getOne(String sessionId) {

		UserInfo e = null;
		String sql = "SELECT * FROM USER WHERE SESSION_ID = ?";
		Connection conn = DB.getConnection();
		PreparedStatement statement = null;
		ResultSet rs = null;
		try {
			statement = conn.prepareStatement(sql);
			statement.setString(1, sessionId);
			rs = statement.executeQuery();
			while (rs.next()) {
				e = new UserInfo(rs.getInt("ID"), sessionId);
			}
		} catch (SQLException ex) {
			ex.printStackTrace();
		} finally {
			try {
				if (rs != null)
					rs.close();
				if (statement != null)
					statement.close();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
		}
		return e;
	}

	@Override
	public void addOne(String sessionId) {

		String sql = "INSERT INTO USER (SESSION_ID, STATUS) VALUES (?, 1)";
		Connection conn = DB.getConnection();
		PreparedStatement statement = null;
		try {
			statement = conn.prepareStatement(sql);
			statement.setString(1, sessionId);
			statement.execute();
		} catch (SQLException ex) {
			ex.printStackTrace();
		} finally {
			try {
				if (statement != null)
					statement.close();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
		}
	}

}
