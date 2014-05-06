package com.aaronpages.aprs.impl;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

import com.aaronpages.aprs.IAprsClient;

public class AprsClientImpl implements IAprsClient {

	/**
	 * aprs服务器地址
	 */
	private static final String serAddr = "localhost";

	/**
	 * aprs服务器端口
	 */
	private static final int port = 61591;

	@Override
	public List<Integer> getRecoms(int userId) {

		DatagramSocket clientSocket;
		try {
			clientSocket = new DatagramSocket();
			InetAddress IPAddress = InetAddress.getByName(serAddr);
			byte[] sendBuff = new byte[1024];
			byte[] recBuff = new byte[1024];

			/* set send buff */
			String sms = String.valueOf(userId);
			sms = "0|" + sms;
			sendBuff = sms.getBytes();

			/* send sms */
			DatagramPacket sendPacket = new DatagramPacket(sendBuff,
					sendBuff.length, IPAddress, port);
			clientSocket.send(sendPacket);

			/* receive sms */
			DatagramPacket receivePacket = new DatagramPacket(recBuff,
					recBuff.length);
			clientSocket.receive(receivePacket);

			/* get recommends id */
			String respStr = new String(receivePacket.getData());
			respStr = respStr.substring(0, receivePacket.getLength());
			int len = respStr.length();
			List<Integer> recoms = new ArrayList<Integer>();
			if (respStr != null && !respStr.isEmpty()) {
				StringTokenizer st = new StringTokenizer(respStr, "|");
				while(st.hasMoreTokens()){
					String t = st.nextToken();
					if (t != null && !t.isEmpty()) {
						recoms.add(Integer.parseInt(t));
					}
				}
			}

			/* close socket */
			clientSocket.close();

			return recoms;
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}

}
