#include "gtest/gtest.h"
#include "../src/distance.hpp"

// "hello", "Hell",     // delete
// "Hello", "hallo",    // replace
// "hello", "helloWEen" // insert

TEST(distance, insert) {
    EXPECT_EQ(4, (distance<char, levenshtein::Distance>("hello", "helloWEen"))) << "hello & helloWEen, expected 4";
    EXPECT_EQ(4, (distance<char, levenshtein::Distance>("helloWEen", "hello"))) << "helloWEen & hello, expected 4";
    
    EXPECT_EQ(4, (distance<char, levenshtein::Distance>("hello", to_lower<char>("helloWEen")))) << "hello & to_lower(helloWEen), expected 4";
    EXPECT_EQ(4, (distance<char, levenshtein::Distance>("helloWEen", to_lower<char>("hello")))) << "to_lower(helloWEen) & hello, expected 4";
}

TEST(distance, deleteSymbol) {
    EXPECT_EQ(8, (distance<char, levenshtein::Distance>("Hold the door", "Hodor"))) << "Hodor, expected 7";

    EXPECT_EQ(2, (distance<char, levenshtein::Distance>("hello", "Hell"))) << "hello & Hell, expected 2";
    EXPECT_EQ(2, (distance<char, levenshtein::Distance>("Hell", "hello"))) << "Hell & hello, expected 2";
    
    EXPECT_EQ(1, (distance<char, levenshtein::Distance>("hello", to_lower<char>("Hell")))) << "hello & to_lower(Hell), expected 1";
    EXPECT_EQ(1, (distance<char, levenshtein::Distance>(to_lower<char>("Hell"), "hello"))) << "to_lower(Hell) & hello, expected 1";

    EXPECT_EQ(1, (distance<char, levenshtein::Distance>("hello", "hell"))) << "hello & Hell, expected 1";
    EXPECT_EQ(2, (distance<char, levenshtein::Distance>("hello", "ell"))) << "hello & ell, expected 2";
    EXPECT_EQ(3, (distance<char, levenshtein::Distance>("hello", "el"))) << "hello & el, expected 3";
    EXPECT_EQ(4, (distance<char, levenshtein::Distance>("hello", "l"))) << "hello & l, expected 4";
    EXPECT_EQ(5, (distance<char, levenshtein::Distance>("hello", ""))) << "hello & , expected 5";
}

TEST(distance, replace) {
    EXPECT_EQ(2, (distance<char, levenshtein::Distance>("Hello", "hallo"))) << "Hello & hallo, expected 2";
    EXPECT_EQ(2, (distance<char, levenshtein::Distance>("hallo", "Hello"))) << "hallo & Hello, expected 2";
    
    EXPECT_EQ(1, (distance<char, levenshtein::Distance>("hallo", to_lower<char>("Hello")))) << "hallo & to_lower(Hello), expected 1";
    EXPECT_EQ(1, (distance<char, levenshtein::Distance>(to_lower<char>("Hello"), "hallo"))) << "to_lower(Hello) & hallo, expected 1";
}

TEST(utill, tolower) {
    std::string et = "hello!1!world";
    EXPECT_EQ(0, et.compare(to_lower<char>("HeLlO!1!WoRlD")));
    EXPECT_EQ(0, to_lower<char>("").compare(""));
}

TEST(utill, trim) {
    const char *delims = " ,:\"'!?@#%$^&*()";
    {
        // empty
        std::string str;
        str = trim(str, delims);
        EXPECT_EQ(0, str.compare("")) << "lempty string trim expected empty string";
    }
    
    {
        // left
        std::string str("#$%^&hello");
        str = trim(str, delims);
        EXPECT_EQ(0, str.compare("hello")) << "left trim expected hello";
    }

    {
        // right
        std::string str("hello  $%^&*");
        str = trim(str, delims);
        EXPECT_EQ(0, str.compare("hello")) << "right trim expected hello";
    }

    {
        // both
        std::string str("?%^&*(hello  $%^&*");
        str = trim(str, delims);
        EXPECT_EQ(0, str.compare("hello")) << "both trim expected hello";
    }
}