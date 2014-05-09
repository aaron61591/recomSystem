-- phpMyAdmin SQL Dump
-- version 3.5.8.1deb1
-- http://www.phpmyadmin.net
--
-- 主机: localhost
-- 生成日期: 2014 年 04 月 26 日 16:30
-- 服务器版本: 5.5.34-0ubuntu0.13.04.1
-- PHP 版本: 5.4.9-4ubuntu2.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

--
-- 数据库: `aprs`
--

-- --------------------------------------------------------

--
-- 表的结构 `RECOM`
--

CREATE TABLE IF NOT EXISTS `RECOM` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `USER_ID` int(11) NOT NULL,
  `PRO_ID` int(11) NOT NULL,
  `POINT1` smallint(6) NOT NULL DEFAULT '0' COMMENT '点击浏览分数',
  `POINT2` int(11) NOT NULL DEFAULT '0' COMMENT '喜欢分数',
  PRIMARY KEY (`ID`),
  KEY `USER_ID` (`USER_ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=0 ;

-- --------------------------------------------------------

--
-- 表的结构 `TRAVEL_INFO`
--

CREATE TABLE IF NOT EXISTS `TRAVEL_INFO` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `NAME` varchar(100) COLLATE utf8_unicode_ci NOT NULL COMMENT '旅游景点名称',
  `CONTENT` text COLLATE utf8_unicode_ci NOT NULL COMMENT '景点描述内容',
  `IMAGE_PATH` varchar(100) COLLATE utf8_unicode_ci NOT NULL COMMENT '景点图片',
  `STATUS` tinyint(4) NOT NULL DEFAULT '1',
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=0 ;

-- --------------------------------------------------------

--
-- 表的结构 `USER`
--

CREATE TABLE IF NOT EXISTS `USER` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `MAIL` varchar(50) COLLATE utf8_unicode_ci NOT NULL COMMENT '邮箱地址',
  `USER_NAME` varchar(10) COLLATE utf8_unicode_ci NOT NULL COMMENT '用户昵称',
  `PASSWORD` varchar(40) COLLATE utf8_unicode_ci NOT NULL COMMENT '用户密码',
  `STATUS` tinyint(11) NOT NULL DEFAULT '1',
  PRIMARY KEY (`ID`),
  UNIQUE KEY `MAIL` (`MAIL`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=0 ;

