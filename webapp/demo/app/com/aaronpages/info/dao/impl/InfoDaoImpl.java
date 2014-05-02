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
		String sql = "SELECT ID FROM TRAVEL_INFO ORDER BY ? DESC LIMIT ?,?";
		Connection conn = DB.getConnection();
		PreparedStatement statement = null;
		ResultSet rs = null;
		try {
			statement = conn.prepareStatement(sql);
			if (order != null) {
				if (order.equals(InfoOrder.CLICK))
					statement.setString(1, "CLICK_NUM");
				else if (order.equals(InfoOrder.POINT))
					statement.setString(1, "LIKE_NUM");
				else
					statement.setString(1, "CLICK_NUM");
			} else
				statement.setString(1, "CLICK_NUM");
			statement.setInt(2, start);
			statement.setInt(3, num);
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
						rs.getInt("STATUS"));
			}
		} catch (SQLException ex) {
			ex.printStackTrace();
		} finally {
			try {
				rs.close();
				statement.close();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
		}
		return e;
	}

	@Override
	public void incrClick(int id) {
		// TODO Auto-generated method stub

	}

	@Override
	public void incrLike(int id) {
		// TODO Auto-generated method stub

	}

}
