package com.yql.java8.impl;

import com.yql.java8.MethodReference;

import java.util.ArrayList;
import java.util.List;

public class MethodReferenceImpl implements MethodReference {

    public static boolean isRealUser(String user) {
        if (user.equals("u1")) {
            return true;
        }
        return false;
    }

    public boolean isLegalName(String name) {
        if (name.equals("u1")) {
            return true;
        }
        return false;
    }

    public List<String> newUser() {
        List<String> users = new ArrayList<>();
        users.add("u1");
        return users;
    }

    public MethodReferenceImpl newMethodInterface(String x) {
        return new MethodReferenceImpl();
    }
}
