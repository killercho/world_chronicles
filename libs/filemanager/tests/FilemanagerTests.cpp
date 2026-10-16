#include <gtest/gtest.h>
#include <string/String.h>
#include "../Filemanager.h"

TEST(Filemanager, InitializationAndEmpty) {
    EXPECT_NO_FATAL_FAILURE(Filemanager());

    Filemanager filemanager;

    EXPECT_NO_FATAL_FAILURE(filemanager.CloseAllFiles());
    EXPECT_NO_FATAL_FAILURE(filemanager.CloseAllInputFiles());
    EXPECT_NO_FATAL_FAILURE(filemanager.CloseAllOutputFiles());
}

TEST(Filemanager, OutputFiles) {
    Filemanager filemanager;

    EXPECT_NO_FATAL_FAILURE(
        filemanager.GetOpenedOutputFile("testOutput", false));
    EXPECT_TRUE(std::filesystem::exists("testOutput"));

    EXPECT_TRUE(filemanager.GetOpenedOutputFile("testOutput", false).is_open());

    EXPECT_NO_FATAL_FAILURE(
        filemanager.GetOpenedOutputFile("input/testOutput", true));
    EXPECT_TRUE(std::filesystem::exists("input/testOutput"));

    EXPECT_NO_FATAL_FAILURE(
        filemanager.WriteToFile("testing", "input/testOutput", false));
    EXPECT_TRUE(std::filesystem::exists("input/testOutput"));
    EXPECT_GT(std::filesystem::file_size("input/testOutput"), 0);

    EXPECT_NO_FATAL_FAILURE(
        filemanager.WriteToFile("", "input/testOutput", true));
    EXPECT_TRUE(std::filesystem::exists("input/testOutput"));
    EXPECT_EQ(std::filesystem::file_size("input/testOutput"), 0);

    EXPECT_NO_FATAL_FAILURE(filemanager.CloseAllInputFiles());
}

TEST(Filemanager, InputFiles) {
    Filemanager filemanager;

    EXPECT_NO_FATAL_FAILURE(
        filemanager.GetOpenedInputFile("input/testInput.txt"));
    EXPECT_TRUE(
        filemanager.GetOpenedInputFile("input/testInput.txt").is_open());
    EXPECT_THROW(filemanager.GetOpenedInputFile("input/nonexisting.txt"),
                 std::runtime_error);
    EXPECT_THROW(filemanager.GetOpenedInputFile("nonexisting/testInput.txt"),
                 std::runtime_error);

    EXPECT_NO_FATAL_FAILURE(filemanager.ReadFromFile("input/testInput.txt"));
    EXPECT_THROW(filemanager.GetOpenedInputFile("input/nonexisting.txt"),
                 std::runtime_error);
    EXPECT_EQ(filemanager.ReadFromFile("input/testInput.txt").size(), 5);

    EXPECT_NO_FATAL_FAILURE(filemanager.CloseAllOutputFiles());
}
