package com.aaronpages.recom.dao.impl;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import play.db.DB;

import com.aaronpages.recom.dao.IRecomDao;
import com.aaronpages.recom.dto.RecomInfo;
import com.aaronpages.user.dto.UserInfo;

public class RecomDaoImpl implements IRecomDao {

	@Override
	public RecomInfo getOne(int uId, int pId) {


		RecomInfo e = null;
		String sql = "SELECT * FROM RECOM WHERE USER_ID = ? AND PRO_ID = ?";
		Connection conn = DB.getConnection();
		PreparedStatement statement = null;
		ResultSet rs = null;
		try {
			statement = conn.prepareStatement(sql);
			statement.setInt(1, uId);
			statement.setInt(2, pId);
			rs = statement.executeQuery();
			while (rs.next()) {
				e = new RecomInfo(rs.getInt("USER_ID"), rs.getInt("PRO_ID"),
						rs.getInt("POINT1"), rs.getInt("POINT2"));
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
	public void addOne(RecomInfo e) {

		String sql = "INSERT INTO RECOM (USER_ID, PRO_ID, POINT1, POINT2) VALUES (?, ?, ?, ?)";
		Connection conn = DB.getConnection();
		PreparedStatement statement = null;
		try {
			statement = conn.prepareStatement(sql);
			statement.setInt(1, e.getUserId());
			statement.setInt(2, e.getProducedId());
			statement.setInt(3, e.getPoint1());
			statement.setInt(4, e.getPoint2());
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

	@Override
	public void update(RecomInfo e) {

		String sql = "UPDATE RECOM SET POINT1 = ?, POINT2 = ? WHERE USER_ID = ? AND PRO_ID = ?";
		Connection conn = DB.getConnection();
		PreparedStatement statement = null;
		try {
			statement = conn.prepareStatement(sql);
			statement.setInt(1, e.getPoint1());
			statement.setInt(2, e.getPoint2());
			statement.setInt(3, e.getUserId());
			statement.setInt(4, e.getProducedId());
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
