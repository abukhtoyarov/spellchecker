#include "gtest/gtest.h"
#include "../src/bktree.hpp"

TEST(bktree, simpleOperations) {
    bktree::Tree<char, levenshtein::Distance> tree;
    ASSERT_NO_THROW({
        tree.insert("hello");
        tree.insert("hell");
        tree.insert("hll");
        tree.insert("hl");
        tree.insert("l");
        tree.insert("");
        tree.insert("hello2");
        tree.insert("h4ell");
        tree.insert("hlfl");
        tree.insert("hlddfsd");
        tree.insert("ljh");
        tree.insert("");
    });

    auto res = tree.lookup("hello", 0);

    ASSERT_EQ(1, static_cast<int>(res.size())) << "Ожидается 1 результат";
    EXPECT_EQ(0, (res.at(0).first)) << "Ожидается нулевая дистанция";
    EXPECT_EQ(0, res.at(0).second.compare("hello"));

    {
        // [TODO] Сравнение содержимого с эталонным значением
        auto res = tree.lookup("hello", 1);
        ASSERT_EQ(3, static_cast<int>(res.size())) << "Ожидается 3 результата";
        for(const auto &r: res) {
            EXPECT_LE((r.first), 1) << "Ожидается дистанция не больше 1";
        }
    }

    {
        // [TODO] Сравнение содержимого с эталонным значением
        auto res = tree.lookup("hello", 2);
        ASSERT_EQ(5, static_cast<int>(res.size())) << "Ожидается 5 результатов";
        for(const auto &r: res) {
            EXPECT_LE((r.first), 2) << "Ожидается дистанция не больше 1";
        }
    }

    {
        // [TODO] Сравнение содержимого с эталонным значением
        auto res = tree.lookup("hello", 5);
        ASSERT_EQ(10, static_cast<int>(res.size())) << "Ожидается 10 результатов";
        for(const auto &r: res) {
            EXPECT_LE((r.first), 5) << "Ожидается дистанция не больше 5";
        }
    }
}