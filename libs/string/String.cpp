#include "String.h"
#include <string>
#include <utility>
#include <vector>

String::String() : m_data("") { }

String::String(const std::string& otherString) : m_data(otherString) { }
String::String(const char* otherString) : m_data(otherString) { }
String::String(const String& otherString) : m_data(otherString.GetData()) { }

String& String::operator=(const String& otherString) {
    if (this == &otherString) {
        return *this;
    }
    m_data = otherString.GetData();
    return *this;
}
String& String::operator=(const std::string& otherString) {
    m_data = otherString;
    return *this;
}
String& String::operator=(const char* otherString) {
    m_data = otherString;
    return *this;
}

String::String(std::string&& otherString) : m_data(std::move(otherString)) { }
String::String(String&& otherString) : m_data(std::move(otherString).GetData()) { }

const std::string& String::GetData() const {
    return m_data;
}

std::string& String::GetData() {
    return m_data;
}

char& String::operator[](const unsigned int position) {
    return m_data[position];
}

const char String::operator[](const unsigned int position) const {
    return m_data[position];
}

char& String::at(const unsigned int position) {
    return m_data.at(position);
}

const char String::at(const unsigned int position) const {
    return m_data.at(position);
}

const char* String::c_str() const {
    return m_data.c_str();
}

const std::const_iterator String::begin() const {
    return m_data.begin();
}

std::iterator String::begin() {
    return m_data.begin();
}

const std::const_iterator String::end() const {
    return m_data.end();
}

std::iterator String::end() {
    return m_data.end();
}

bool String::empty() const {
    return m_data.empty();
}
unsigned long String::size() const {
    return m_data.size();
}
unsigned long String::length() const {
    m_data.length();
}

void String::clear() {
    return m_data.clear();
}

String& String::operator+=(const String& other) {
    m_data += other.GetData();
    return *this;
}
String& String::operator+=(char other) {
    m_data += other;
    return *this;
}

unsigned long String::find(const String& target) const {
    return m_data.find(target.GetData());
}

unsigned long String::find(char target) const {
    return m_data.find(target);
}

bool String::contains(const String& target) const {
    return m_data.contains(target.GetData());
}

bool String::contains(char target) const {
    return m_data.contains(target);
}

String String::operator+(const String& right) const {
    return String(m_data + right.GetData());
}

bool String::operator==(const String& other) const {
    return m_data == other.GetData();
}

bool String::operator!=(const String& other) const {
    return m_data != other.GetData();
}

std::vector<String> String::split(const String& delimiter) const {
    std::vector<String> result;

    const std::string& delimiterNormalString = delimiter.GetData();
    std::string        dataCopy              = m_data;

    unsigned long pos = dataCopy.find(delimiterNormalString);

    while (pos != String::NPOS) {
        result.emplace_back(dataCopy.substr(0, pos));
        dataCopy.erase(0, pos + delimiterNormalString.length());
        pos = dataCopy.find(delimiterNormalString);
    }
    result.emplace_back(dataCopy);
    return result;
}
