#include "gtest/gtest.h"
#include "../src/spellchecker.hpp"

class SpellcheckerTest : public ::testing::Test {
public:
    SpellcheckerTest() = default;

protected:
	void SetUp() { 
        static std::string dic = "hello world how are you my friend";
        sc_.load(dic); 
    }
	void TearDown() {}

    spellchecker::Spellchecker<char> sc_;
};

TEST_F(SpellcheckerTest, correct) {
    auto results = sc_.check("Hello world! How Are You?");

    ASSERT_EQ(5, results.size());
    auto it = results.begin();

    EXPECT_EQ(spellchecker::State::correct, it->state_);
    EXPECT_EQ(0, it->word_.compare("hello"));
    EXPECT_EQ(0, it->data_.size());
    
    ++it;
    EXPECT_EQ(spellchecker::State::correct, it->state_);
    EXPECT_EQ(0, it->word_.compare("world"));
    EXPECT_EQ(0, it->data_.size());

    ++it;
    EXPECT_EQ(spellchecker::State::correct, it->state_);
    EXPECT_EQ(0, it->word_.compare("how"));
    EXPECT_EQ(0, it->data_.size());
    
    ++it;
    EXPECT_EQ(spellchecker::State::correct, it->state_);
    EXPECT_EQ(0, it->word_.compare("are"));
    EXPECT_EQ(0, it->data_.size());

    ++it;
    EXPECT_EQ(spellchecker::State::correct, it->state_);
    EXPECT_EQ(0, it->word_.compare("you"));
    EXPECT_EQ(0, it->data_.size());
}

TEST_F(SpellcheckerTest, options) {
    const std::string str = "Helo wold! Hov Ares yoru?";
    auto results = sc_.check(str);
    
    ASSERT_EQ(5, results.size());
    auto it = results.begin();

    EXPECT_EQ(spellchecker::State::options, it->state_);
    EXPECT_EQ(0, it->word_.compare("helo"));
    EXPECT_EQ(1, it->data_.size());
    
    ++it;
    EXPECT_EQ(spellchecker::State::options, it->state_);
    EXPECT_EQ(0, it->word_.compare("wold"));
    EXPECT_EQ(1, it->data_.size());

    ++it;
    EXPECT_EQ(spellchecker::State::options, it->state_);
    EXPECT_EQ(0, it->word_.compare("hov"));
    EXPECT_EQ(1, it->data_.size());
    
    ++it;
    EXPECT_EQ(spellchecker::State::options, it->state_);
    EXPECT_EQ(0, it->word_.compare("ares"));
    EXPECT_EQ(1, it->data_.size());

    ++it;
    EXPECT_EQ(spellchecker::State::options, it->state_);
    EXPECT_EQ(0, it->word_.compare("yoru"));
    EXPECT_EQ(1, it->data_.size());
}

TEST_F(SpellcheckerTest, wrong) {
    const std::string str = "Heloo0 wolde! Hovr dAres yorut?";
    auto results = sc_.check(str);
    
    ASSERT_EQ(5, results.size());
    auto it = results.begin();

    EXPECT_EQ(spellchecker::State::wrong, it->state_);
    EXPECT_EQ(0, it->word_.compare("heloo0"));
    EXPECT_EQ(0, it->data_.size());
    
    ++it;
    EXPECT_EQ(spellchecker::State::wrong, it->state_);
    EXPECT_EQ(0, it->word_.compare("wolde"));
    EXPECT_EQ(0, it->data_.size());

    ++it;
    EXPECT_EQ(spellchecker::State::wrong, it->state_);
    EXPECT_EQ(0, it->word_.compare("hovr"));
    EXPECT_EQ(0, it->data_.size());
    
    ++it;
    EXPECT_EQ(spellchecker::State::wrong, it->state_);
    EXPECT_EQ(0, it->word_.compare("dares"));
    EXPECT_EQ(0, it->data_.size());

    ++it;
    EXPECT_EQ(spellchecker::State::wrong, it->state_);
    EXPECT_EQ(0, it->word_.compare("yorut"));
    EXPECT_EQ(0, it->data_.size());
}

TEST_F(SpellcheckerTest, multipleOptions) {
    sc_.load("hell hallo held");
    
    const std::string str = "Helo wold!";
    auto results = sc_.check(str);
    
    ASSERT_EQ(2, results.size());
    auto it = results.begin();

    EXPECT_EQ(spellchecker::State::options, it->state_);
    EXPECT_EQ(0, it->word_.compare("helo"));
    ASSERT_EQ(3, it->data_.size());

    auto opt = std::begin(it->data_);
    EXPECT_EQ(1, opt->first);
    EXPECT_EQ(0, opt->second.compare("hell"));
    ++opt;
    EXPECT_EQ(1, opt->first);
    EXPECT_EQ(0, opt->second.compare("held"));
    ++opt;
    EXPECT_EQ(1, opt->first);
    EXPECT_EQ(0, opt->second.compare("hello"));
    
    ++it;
    EXPECT_EQ(spellchecker::State::options, it->state_);
    EXPECT_EQ(0, it->word_.compare("wold"));
    EXPECT_EQ(1, it->data_.size());
}