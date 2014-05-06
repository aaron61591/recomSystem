package com.aaronpages.info.dao.impl;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import play.db.DB;

import com.aaronpages.info.dao.IInfoDao;
import com.aaronpages.info.dto.TravelInfo;
import com.aaronpages.info.dto.TravelInfo.InfoOrder;

public class InfoDaoImpl implements IInfoDao {

	@Override
	public List<Integer> getList(InfoOrder order, int start, int num) {

		List<Integer> list = new ArrayList<Integer>();
		String sql = null;
		if (order != null) {
			if (order.equals(InfoOrder.CLICK))
				sql = "SELECT ID FROM TRAVEL_INFO ORDER BY CLICK_NUM DESC LIMIT ?,?";
			else if (order.equals(InfoOrder.POINT))
				sql = "SELECT ID FROM TRAVEL_INFO ORDER BY LIKE_NUM DESC LIMIT ?,?";
			else
				sql = "SELECT ID FROM TRAVEL_INFO ORDER BY ID DESC LIMIT ?,?";
		} else {
			sql = "SELECT ID FROM TRAVEL_INFO ORDER BY ID DESC LIMIT ?,?";
		}
		Connection conn = DB.getConnection();
		PreparedStatement statement = null;
		ResultSet rs = null;
		try {
			statement = conn.prepareStatement(sql);
			statement.setInt(1, start);
			statement.setInt(2, num);
			rs = statement.executeQuery();
			while (rs.next()) {
				list.add(rs.getInt("ID"));
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
		return list;
	}

	@Override
	public TravelInfo getOne(int id) {

		TravelInfo e = null;
		String sql = "SELECT * FROM TRAVEL_INFO WHERE ID = ?";
		Connection conn = DB.getConnection();
		PreparedStatement statement = null;
		ResultSet rs = null;
		try {
			statement = conn.prepareStatement(sql);
			statement.setInt(1, id);
			rs = statement.executeQuery();
			while (rs.next()) {
				e = new TravelInfo(id, rs.getString("NAME"),
						rs.getString("CONTENT"), rs.getString("IMAGE_PATH"),
						rs.getInt("CLICK_NUM"), rs.getInt("LIKE_NUM"),
						rs.getInt("STATUS"));
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
	public void incrClick(int id) {

		String sql = "UPDATE TRAVEL_INFO SET CLICK_NUM = CLICK_NUM + 1 WHERE ID = ?";
		Connection conn = DB.getConnection();
		PreparedStatement statement = null;
		try {
			statement = conn.prepareStatement(sql);
			statement.setInt(1, id);
			statement.execute();
		} catch (SQLException ex) {
			ex.printStackTrace();
		} finally {
			try {
				statement.close();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
		}
	}

	@Override
	public void incrLike(int id) {

		String sql = "UPDATE TRAVEL_INFO SET LIKE_NUM = LIKE_NUM + 1 WHERE ID = ?";
		Connection conn = DB.getConnection();
		PreparedStatement statement = null;
		try {
			statement = conn.prepareStatement(sql);
			statement.setInt(1, id);
			statement.execute();
		} catch (SQLException ex) {
			ex.printStackTrace();
		} finally {
			try {
				statement.close();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
		}
	}

}
