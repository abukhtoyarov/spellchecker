#include "gtest/gtest.h"
#include "../src/distance.hpp"

// "hello", "Hell",     // delete
// "Hello", "hallo",    // replace
// "hello", "helloWEen" // insert

TEST(distance, insert) {
    EXPECT_EQ(4, distance("hello", "helloWEen")) << "hello & helloWEen, expected 4";
    EXPECT_EQ(4, distance("helloWEen", "hello")) << "helloWEen & hello, expected 4";
    
    EXPECT_EQ(4, distance("hello", to_lower("helloWEen"))) << "hello & to_lower(helloWEen), expected 4";
    EXPECT_EQ(4, distance("helloWEen", to_lower("hello"))) << "to_lower(helloWEen) & hello, expected 4";
}

TEST(distance, deleteSymbol) {
    EXPECT_EQ(8, distance("Hold the door", "Hodor")) << "Hodor, expected 7";

    EXPECT_EQ(2, distance("hello", "Hell")) << "hello & Hell, expected 2";
    EXPECT_EQ(2, distance("Hell", "hello")) << "Hell & hello, expected 2";
    
    EXPECT_EQ(1, distance("hello", to_lower("Hell"))) << "hello & to_lower(Hell), expected 1";
    EXPECT_EQ(1, distance(to_lower("Hell"), "hello")) << "to_lower(Hell) & hello, expected 1";

    EXPECT_EQ(1, distance("hello", "hell")) << "hello & Hell, expected 1";
    EXPECT_EQ(2, distance("hello", "ell")) << "hello & ell, expected 2";
    EXPECT_EQ(3, distance("hello", "el")) << "hello & el, expected 3";
    EXPECT_EQ(4, distance("hello", "l")) << "hello & l, expected 4";
    EXPECT_EQ(5, distance("hello", "")) << "hello & , expected 5";
}

TEST(distance, replace) {
    EXPECT_EQ(2, distance("Hello", "hallo")) << "Hello & hallo, expected 2";
    EXPECT_EQ(2, distance("hallo", "Hello")) << "hallo & Hello, expected 2";
    
    EXPECT_EQ(1, distance("hallo", to_lower("Hello"))) << "hallo & to_lower(Hello), expected 1";
    EXPECT_EQ(1, distance(to_lower("Hello"), "hallo")) << "to_lower(Hello) & hallo, expected 1";
}