#include "gtest/gtest.h"
#include "../src/spellchecker.hpp"

TEST(spellchecker, simpleTest) {
    std::string dic = "hello world how are you";

    std::string str = "Hello wold! Cow ArE you?";
    std::string eta = "Hello world! how are you?";

    spellchecker::Spellchecker sc;
    sc.load(dic);

    auto r = sc.check(str);
    std::cout << r << std::endl;
}
