/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.aaronpages.config;

import com.aaronpages.info.dao.IInfoDao;
import com.aaronpages.info.dao.impl.InfoDaoImpl;
import com.aaronpages.info.service.IInfoService;
import com.aaronpages.info.service.impl.InfoServiceImpl;
import com.aaronpages.user.dao.IUserDao;
import com.aaronpages.user.dao.impl.UserDaoImpl;
import com.aaronpages.user.service.IUserService;
import com.aaronpages.user.service.impl.UserServiceImpl;
import com.google.inject.AbstractModule;
import com.google.inject.Singleton;
/**
 *
 * @author admin
 */
public class GuicyDummyModel extends AbstractModule{

    protected void configure() {
//    	bind(IHelloGuice.class).to(HelloGuiceImpl.class).in(Singleton.class);
    	bind(IInfoService.class).to(InfoServiceImpl.class).in(Singleton.class);
    	bind(IUserService.class).to(UserServiceImpl.class).in(Singleton.class);
    	
    	bind(IInfoDao.class).to(InfoDaoImpl.class).in(Singleton.class);
    	bind(IUserDao.class).to(UserDaoImpl.class).in(Singleton.class);
    }
    
}
