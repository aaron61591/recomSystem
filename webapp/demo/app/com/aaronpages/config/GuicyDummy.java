/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.aaronpages.config;

import play.modules.guice.GuiceSupport;

import com.google.inject.Guice;
import com.google.inject.Injector;

public class GuicyDummy extends GuiceSupport {

    protected Injector configure() {
        Injector injector = Guice.createInjector(new GuicyDummyModel());
        return injector;
    }
}