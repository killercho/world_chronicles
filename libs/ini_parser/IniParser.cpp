#include "IniParser.h"
#include <string>
#include <fstream>
#include <filesystem>

const String& IniParser::GetLatestError() const noexcept {
    return m_fileError;
}

void IniParser::CheckFileExisting(const String& filename) const {
    if (!std::filesystem::exists(filename.ToPath())) {
        m_fileError = "File given (" + filename + ") does not exist!";
    }
}

IniParser::IniParser(const String& filename) noexcept {
    CheckFileExisting(filename);

    if (m_fileError.Empty()) {
        LoadFromFile(filename);
    }
}

void IniParser::LoadNewFile(const String& filename) noexcept {
    m_fileError.Clear();
    CheckFileExisting(filename);

    if (m_fileError.Empty()) {
        LoadFromFile(filename);
    }
}

void IniParser::LoadFromFile(const String& filename) noexcept {
    std::ifstream file(filename.GetData());
    if (!file.is_open()) {
        m_fileError =
            "The file (" + filename + ") could not be opened for reading!";
        return;
    }

    std::string lineGetter;
    while (std::getline(file, lineGetter)) {
        String actualLine(lineGetter);
        actualLine.Trim();
        if (actualLine.Empty()) {
            // Only spaces on the line.
            continue;
        }

        auto afterComment = actualLine.Split("#").back();
        if (afterComment.Empty()) {
            // Only a comment on the line.
            continue;
        }

        if (!afterComment.Contains("[") && !afterComment.Contains("]")) {
            // No section on the line.
            continue;
        }

        afterComment.Remove("[");
        afterComment.Remove("]");
        if (afterComment.Empty()) {
            // No section name given.
            continue;
        }

        if (m_allSections.contains(afterComment)) {
            m_fileError = "Section with name '" + afterComment +
                          "' loaded more than once!";
            break;
        }

        std::shared_ptr<SectionParser> newSection =
            std::make_shared<SectionParser>();
        newSection->LoadSection(file);
        if (!newSection->GetLatestError().Empty()) {
            m_fileError = "Section '" + afterComment +
                          "':" + newSection->GetLatestError();
            break;
        }
        m_allSections.insert({ afterComment, newSection });
    }

    file.close();
}

const SectionParser& IniParser::GetSection(const String& section) const {
    if (m_allSections.contains(section)) {
        throw std::runtime_error(
            ("Section with name '" + section + "' was not found!").c_str());
    }
    return *m_allSections.at(section);
}

const std::shared_ptr<SectionParser>&
IniParser::GetSectionPtr(const String& section) const {
    if (m_allSections.contains(section)) {
        throw std::runtime_error(
            ("Section with name '" + section + "' was not found!").c_str());
    }
    return m_allSections.at(section);
}
