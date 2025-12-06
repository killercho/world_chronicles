#include <gtest/gtest.h>
#include <string>
#include <utility>
#include <vector>
#include "../String.h"

TEST(StringTests, StringConstructor) {
    String emptyString;
    EXPECT_STREQ(emptyString.c_str(), "");
    EXPECT_TRUE(emptyString.empty());

    String fromStdString(std::string("normalString"));
    EXPECT_STREQ(fromStdString.c_str(), "normalString");
    EXPECT_FALSE(fromStdString.empty());

    String fromCharPtr("something");
    EXPECT_STREQ(fromCharPtr.c_str(), "something");
    EXPECT_FALSE(fromCharPtr.empty());

    String fromOtherString(fromCharPtr);
    EXPECT_STREQ(fromOtherString.c_str(), "something");
    EXPECT_FALSE(fromOtherString.empty());

    std::string otherString = "something";
    String      fromMoveOther(std::move(otherString));
    EXPECT_STREQ(fromMoveOther.c_str(), "something");
    EXPECT_FALSE(fromMoveOther.empty());

    String fromMove(std::move(fromMoveOther));
    EXPECT_STREQ(fromMove.c_str(), "something");
    EXPECT_FALSE(fromMove.empty());
}

TEST(StringTests, StringOperatorEquals) {
    String myString;
    EXPECT_TRUE(myString.empty());
    myString = "something";
    EXPECT_FALSE(myString.empty());
    EXPECT_STREQ(myString.c_str(), "something");

    std::string normalString = "normalString";
    myString                 = normalString;
    EXPECT_STREQ(myString.c_str(), "normalString");

    String myStringCopy = "someOtherString";
    myString            = myStringCopy;
    EXPECT_STREQ(myString.c_str(), "someOtherString");
}

TEST(StringTests, DataGetters) {
    String myString = "something";
    EXPECT_STREQ(myString.GetData().c_str(), "something");

    myString.GetData() = "somethingChanged";
    EXPECT_STREQ(myString.c_str(), "somethingChanged");

    EXPECT_EQ(myString[0], 's');
    myString[0] = 'b';
    EXPECT_EQ(myString[0], 'b');

    EXPECT_EQ(myString.at(1), 'o');
    myString.at(1) = 's';
    EXPECT_EQ(myString.at(1), 's');
}

TEST(StringTests, Iterators) {
    std::string normalString = "";
    String      myString     = "somethingLoopy";
    for (const char c : myString) {
        normalString += c;
    }
    EXPECT_STREQ(normalString.c_str(), "somethingLoopy");
}

TEST(StringTests, SizeManipulations) {
    String myString = "something";
    EXPECT_FALSE(myString.empty());
    EXPECT_EQ(myString.size(), std::string("something").size());
    EXPECT_EQ(myString.length(), std::string("something").length());
    EXPECT_FALSE(myString.empty());
    EXPECT_NO_FATAL_FAILURE(myString.clear());
    EXPECT_TRUE(myString.empty());
    EXPECT_STREQ(myString.c_str(), "");
}

TEST(StringTests, Addition) {
    String myString  = "";
    myString        += "some";
    EXPECT_STREQ(myString.c_str(), "some");
    myString += String("thing");
    EXPECT_STREQ(myString.c_str(), "something");
    myString += std::string("more");
    EXPECT_STREQ(myString.c_str(), "somethingmore");
    myString += '!';
    EXPECT_STREQ(myString.c_str(), "somethingmore!");

    myString         = "s";
    String newString = myString + "something";
    EXPECT_STREQ(newString.c_str(), "ssomething");
}

TEST(StringTests, Finding) {
    String myString = "something!tofind!";
    EXPECT_EQ(myString.find('s'), 0);
    EXPECT_EQ(myString.find("to"), 10);
    EXPECT_EQ(myString.find("?"), -1);
}

TEST(StringTests, Comparisons) {
    String myString = "something!tofind!";
    EXPECT_TRUE(myString.contains("find"));
    EXPECT_TRUE(myString.contains('!'));
    EXPECT_FALSE(myString.contains('?'));

    myString = "something";
    EXPECT_EQ(myString, std::string("something"));
    EXPECT_NE(myString, "somethingElse");
}

TEST(StringTests, CastsFromString) {
    String num = "3";
    EXPECT_EQ(num.CastFromString<int>(), 3);
    EXPECT_EQ(num.CastFromString<unsigned int>(), 3);
    EXPECT_EQ(num.CastFromString<unsigned long>(), 3);
    EXPECT_EQ(num.CastFromString<unsigned long long>(), 3);
    EXPECT_EQ(num.CastFromString<long long>(), 3);
    EXPECT_EQ(num.CastFromString<long>(), 3);
    num = "true";
    EXPECT_EQ(num.CastFromString<bool>(), true);
}

TEST(StringTests, Splitter) {
    String              myString = "something!to!see!";
    std::vector<String> result;
    EXPECT_NO_FATAL_FAILURE(result = myString.split("!"));
    EXPECT_STREQ(result[0].c_str(), "something");
    EXPECT_STREQ(result[1].c_str(), "to");
    EXPECT_STREQ(result[2].c_str(), "see");
    EXPECT_STREQ(result[3].c_str(), "");
    EXPECT_EQ(result.size(), 4);
}

TEST(StringTests, ToStrings) {
    String myString = ToString(false);
    EXPECT_STREQ(myString.c_str(), "false");
    myString = ToString(3);
    EXPECT_STREQ(myString.c_str(), "3");
    myString = ToString(3.14);
    EXPECT_STREQ(myString.c_str(), "3.140000");
}
