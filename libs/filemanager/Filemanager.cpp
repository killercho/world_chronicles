#include "Filemanager.h"
#include <filesystem>

Filemanager::~Filemanager() {
    CloseAllFiles();
}

void Filemanager::CloseAllFiles() {
    CloseAllInputFiles();
    CloseAllOutputFiles();
}

void Filemanager::CloseAllInputFiles() {
    for (auto& inputFile : m_openedInputFiles) {
        inputFile.close();
    }
    m_openedInputFiles.clear();
}

void Filemanager::CloseAllOutputFiles() {
    for (auto& outputFile : m_openedOutputFiles) {
        outputFile.close();
    }
    m_openedOutputFiles.clear();
}

bool Filemanager::DoesFileExist(const String& filename) const {
    const std::filesystem::path filePath(filename.c_str());
    return std::filesystem::exists(filePath);
}

void Filemanager::CreateParentDirs(const String& filename) const {
    const std::filesystem::path filePath(filename.c_str());
    if (filePath.has_parent_path()) {
        std::filesystem::create_directories(filePath.parent_path());
    }
}

std::ifstream& Filemanager::GetOpenedInputFile(const String& filename) {
    if (!DoesFileExist(filename)) {
        throw std::runtime_error("Filename given '" + filename.GetData() +
                                 "' does not exist!");
    }

    m_openedInputFiles.emplace_back(std::ifstream(filename.GetData()));
    if (!m_openedInputFiles.back().is_open()) {
        throw std::runtime_error("File with name '" + filename.GetData() +
                                 "'could not be opened for some reason!");
    }

    return m_openedInputFiles.back();
}

std::ofstream& Filemanager::GetOpenedOutputFile(const String& filename,
                                                const bool    bTruncate) {
    CreateParentDirs(filename);
    std::ios::openmode flags = std::ios::app;
    if (DoesFileExist(filename) && bTruncate) {
        flags = std::ios::trunc;
    }

    m_openedOutputFiles.emplace_back(std::ofstream(filename.GetData(), flags));
    if (!m_openedOutputFiles.back().is_open()) {
        throw std::runtime_error("File with name '" + filename.GetData() +
                                 "'could not be opened for some reason!");
    }

    return m_openedOutputFiles.back();
}

void Filemanager::WriteToFile(const String& buffer,
                              const String& filename,
                              const bool    bTruncate) const {
    CreateParentDirs(filename);
    std::ios::openmode flags = std::ios::app;
    if (DoesFileExist(filename) && bTruncate) {
        flags = std::ios::trunc;
    }

    std::ofstream file(filename.GetData(), flags);
    if (!file.is_open()) {
        throw std::runtime_error("File with name '" + filename.GetData() +
                                 "'could not be opened for some reason!");
    }

    file << buffer;
    file.close();
}

std::vector<String> Filemanager::ReadFromFile(const String& filename) const {
    if (!DoesFileExist(filename)) {
        throw std::runtime_error("Filename given '" + filename.GetData() +
                                 "' does not exist!");
    }

    std::ifstream file(filename.GetData());
    if (!file.is_open()) {
        throw std::runtime_error("File with name '" + filename.GetData() +
                                 "'could not be opened for some reason!");
    }

    std::vector<String> result;
    std::string         line;
    while (std::getline(file, line)) {
        result.emplace_back(line);
    }
    return result;
}
