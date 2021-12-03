package com.yql.java8.bo;

import java.util.Optional;

public class OptionalUser {

    public Optional<OptionalAddress> getOptionalAddress() {
        return Optional.ofNullable(optionalAddress);
    }

    public void setOptionalAddress(OptionalAddress optionalAddress) {
        this.optionalAddress = optionalAddress;
    }

    private OptionalAddress optionalAddress;

    public static class OptionalAddress {
        private String street;

        public Optional<String> getStreet() {
            return Optional.ofNullable(street);
        }

        public void setStreet(String street) {
            this.street = street;
        }
    }
}
