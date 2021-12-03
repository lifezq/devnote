package com.yql.java8;

import com.yql.java8.bo.OptionalUser;
import com.yql.java8.bo.User;
import com.yql.java8.exception.CustomException;
import com.yql.java8.impl.InterfaceFeatureImpl;
import com.yql.java8.impl.MethodReferenceImpl;
import com.yql.java8.impl.OptionalFeatureImpl;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.function.Supplier;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.stream.Stream;

public class Entry {
    private static Logger logger = Logger.getLogger("logger");

    public static void runInterfaceFeature() {
        logger.log(Level.INFO, "InterfaceFeature.producer:{0}", InterfaceFeature.producer());
        InterfaceFeatureImpl interfaceFeature = new InterfaceFeatureImpl();
        logger.log(Level.INFO, "InterfaceFeature.getOverview.producer:{0}", interfaceFeature.getOverview());
    }

    public static void runMethodReference() {
        List<String> list = new ArrayList<>();
        list.add("u1");
        logger.log(Level.INFO, "MethodReference.isRealUser:{0}",
                list.stream().anyMatch(MethodReferenceImpl::isRealUser));

        // reference to an interface method
        MethodReferenceImpl methodReference = new MethodReferenceImpl();
        logger.log(Level.INFO, "MethodReference.isLegalName:{0}", list.stream().anyMatch(methodReference::isLegalName));

        // Reference to an Instance Method of an Object of a Particular Type
        logger.log(Level.INFO, "MethodReference.ParticularType:{0}", list.stream().filter(String::isEmpty).count());

        // Reference to a Constructor
        Stream<MethodReferenceImpl> stream = list.stream().map(methodReference::newMethodInterface);
        logger.log(Level.INFO, "MethodReference.Constructor:{0}", stream);
    }

    public static void runOptionalFeature() {
        OptionalFeatureImpl optionalFeature = new OptionalFeatureImpl();
        Supplier<String> supplier = () -> "sssssskkk";
        logger.log(Level.INFO, "OptionalFeature.supplier.get:{0}", supplier.get());
        logger.log(Level.INFO, "OptionalFeature.optional.empty:{0}",
                optionalFeature.optional.orElseGet(() -> "or else get"));

        String str = "value";
        Optional<String> optional = Optional.of(str);
        logger.log(Level.INFO, "OptionalFeature.optional.get:{0}", optional.get());

        optional = Optional.ofNullable(supplier.get());
        logger.log(Level.INFO, "OptionalFeature.optional.get:{0}", optional.get());

        User user = new User();
        User.Address address = new User.Address();
        address.setStreet("ChaoYang");
        user.setAddress(address);
        Optional<User> optionalUser = Optional.of(user);
        logger.log(Level.INFO, "OptionalFeature.optionalUser.getStreet:{0}",
                optionalUser.map(User::getAddress).map(User.Address::getStreet).orElse("not specified"));

        Optional<OptionalUser> optionalUser1 = Optional.ofNullable(new OptionalUser());
        logger.log(Level.INFO, "OptionalFeature.optionalUser.getStreet:{0}",
                optionalUser1.flatMap(OptionalUser::getOptionalAddress).flatMap(OptionalUser.OptionalAddress::getStreet)
                        .orElse("not specified"));

        try {
            String value = null;
            Optional<String> valueOpt = Optional.ofNullable(value);
            String result = valueOpt.orElseThrow(CustomException::new).toUpperCase();
            logger.log(Level.INFO, "OptionalFeature.orElseThrow:{0}", result);
        } catch (CustomException e) {
            // nothing
        }
    }

    public static void main(String[] args) {
//        runInterfaceFeature();
//        runMethodReference();
        runOptionalFeature();
    }
}
