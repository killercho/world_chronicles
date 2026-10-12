#include <gtest/gtest.h>
#include <string/String.h>
#include "../IniParser.h"
#include "../SectionParser.h"

TEST(IniParser, Initialization) {
    // This will test the initialization of the section parser as well
    // so such test is not needed.
    EXPECT_NO_FATAL_FAILURE(IniParser());
    EXPECT_NO_FATAL_FAILURE(IniParser("input/non_existing_file.txt"));
    EXPECT_NO_FATAL_FAILURE(IniParser("input/sample_section_test.ini"));

    IniParser parser("input/sample_section_test.ini");
    EXPECT_STREQ(parser.GetLatestError().c_str(), "");

    EXPECT_NO_FATAL_FAILURE(parser.LoadNewFile("input/error_section.ini"));
    EXPECT_STRNE(parser.GetLatestError().c_str(), "");

    EXPECT_NO_FATAL_FAILURE(
        parser.LoadNewFile("input/sample_section_test.ini"));
    EXPECT_STREQ(parser.GetLatestError().c_str(), "");
}

TEST(IniParser, SectionGetters) {
    IniParser parser("input/non_existing_file.txt");
    EXPECT_THROW(parser.GetSection("anySection"), std::runtime_error);
    EXPECT_THROW(parser.GetSectionPtr("anyOtherSection"), std::runtime_error);

    parser.LoadNewFile("input/sample_section_test.ini");
    EXPECT_NO_THROW(parser.GetSection("TestSettings"));
    EXPECT_NO_THROW(parser.GetSectionPtr("TestSettings"));
    EXPECT_NO_FATAL_FAILURE(parser.ClearError());
    EXPECT_NO_THROW(parser.GetSection("TestSettings"));
    EXPECT_NO_FATAL_FAILURE(parser.Clear());
    EXPECT_THROW(parser.GetSection("TestSettings"), std::runtime_error);

    parser.LoadNewFile("input/error_section.ini");
    EXPECT_THROW(parser.GetSection("Section"), std::runtime_error);
}

TEST(IniParser, ValueGetters) {
    IniParser parser("input/non_existing_file.txt");
    EXPECT_THROW(parser.GetValue<int>("anySection", "anyValue"),
                 std::runtime_error);

    parser.LoadNewFile("input/sample_section_test.ini");
    EXPECT_THROW(parser.GetValue<int>("anySection", "anyValue"),
                 std::runtime_error);
    EXPECT_THROW(parser.GetValue<String>("TestSettings", "anyValue"),
                 std::runtime_error);
    EXPECT_THROW(parser.GetValue<int>("TestSettings", "Width"),
                 std::runtime_error);
    EXPECT_EQ(parser.GetValue<unsigned int>("TestSettings", "Width"), 1'024);
    EXPECT_STREQ(parser.GetValue<String>("TestSettings", "Title").c_str(),
                 "World Chronicles");
    EXPECT_EQ(parser.GetValue<int>("TestSettings", "Negative_Value"), -50);

    const bool bCorrectComplexType =
        std::is_same_v<decltype(parser.GetValue<String>("TestSettings",
                                                        "Title")),
                       const String&>;
    EXPECT_TRUE(bCorrectComplexType);

    const bool bCorrectSimpleType =
        std::is_same_v<decltype(parser.GetValue<unsigned int>("TestSettings",
                                                              "Width")),
                       unsigned int>;
    EXPECT_TRUE(bCorrectSimpleType);
}

TEST(SectionParser, ValueGetters) {
    IniParser parser("input/error_section.ini");
    EXPECT_STRNE(parser.GetLatestError().c_str(), "");
    EXPECT_THROW(parser.GetSection("Section"), std::runtime_error);

    parser.LoadNewFile("input/sample_section_test.ini");
    const auto& section = parser.GetSection("TestSettings");
    EXPECT_THROW(section.GetValue<int>("anyValue"), std::runtime_error);
    EXPECT_THROW(section.GetValue<int>("Width"), std::runtime_error);
    EXPECT_EQ(section.GetValue<unsigned int>("Width"), 1'024);
    EXPECT_STREQ(section.GetValue<String>("Title").c_str(), "World Chronicles");
    EXPECT_EQ(section.GetValue<int>("Negative_Value"), -50);

    const bool bCorrectComplexType =
        std::is_same_v<decltype(section.GetValue<String>("Title")),
                       const String&>;
    EXPECT_TRUE(bCorrectComplexType);

    const bool bCorrectSimpleType =
        std::is_same_v<decltype(section.GetValue<unsigned int>("Width")),
                       unsigned int>;
    EXPECT_TRUE(bCorrectSimpleType);

    const bool bCorrectSimpleType2 =
        std::is_same_v<decltype(section.GetValue<int>("Negative_Value")), int>;
    EXPECT_TRUE(bCorrectSimpleType2);
}
