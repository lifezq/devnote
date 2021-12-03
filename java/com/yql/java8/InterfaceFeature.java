package com.yql.java8;

public interface InterfaceFeature {
    static String producer() {
        return "abc";
    }

    default String getOverview() {
        return "ATV made by " + producer();
    }
}
