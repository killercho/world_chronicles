#include "IniParser.h"
#include <fstream>
#include <filesystem>

void IniParser::CheckFileExisting(const String& filename) const {
    if (!std::filesystem::exists(filename.ToPath())) {
        m_fileError = "File given (" + filename + ") does not exist!";
    }
}

IniParser::IniParser(const String& filename) {
    CheckFileExisting(filename);

    if (m_fileError.Empty()) {
        LoadFromFile(filename);
    }
}

void IniParser::LoadFromFile(const String& filename) {
    std::ifstream file(filename.GetData());
    if (!file.is_open()) {
        m_fileError =
            "The file (" + filename + ") could not be opened for reading!";
        return;
    }

    std::string line;
    while (std::getline(file, line)) { }
}
