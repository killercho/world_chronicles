#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

// A custom string class that encorporates std::string as a member
// and enchances its uses.
// This string will be used throughout the game.
// The functions in the string class does not follow the common
// codestyle and naming, because of the std convention.
class String {
 private:
    // Actual data for the string.
    std::string m_data;

 public:
    static constexpr unsigned long NPOS = -1;

    // TODO: Create tests for the string functionality
    // preferably with the gtest library.
    // These tests need to be defined in the current folder together with the string
    // so that they are a single package.

    String();
    explicit String(const std::string& otherString);
    explicit String(const char* otherString);
    explicit String(const String& otherString);

    String& operator=(const String& otherString);
    String& operator=(const std::string& otherString);
    String& operator=(const char* otherString);

    explicit String(std::string&& otherString);
    explicit String(String&& otherString);

    ~String() = default;

    // Returns the raw std::string data in a const format.
    const std::string& GetData() const;
    // Returns the raw std::string but with the ability for it to be changed.
    std::string& GetData();

    // Return the position-th element of the string for modification.
    char& operator[](const unsigned int position);
    // Return the position-th element of the string as a copy, forbidding modification.
    const char operator[](const unsigned int position) const;
    // Return the position-th element of the string for modification,
    // does checks for whether it is out of range.
    char& at(const unsigned int position);
    // Return the position-th element of the string as a copy, forbidding modification
    // does checks for whether it is out of range.
    const char at(const unsigned int position) const;

    // Returns the const char* of the std::string inside.
    const char* c_str() const;

    // Iterators for the data inside the class.
    const std::const_iterator begin() const;
    std::iterator             begin();
    const std::const_iterator end() const;
    std::iterator             end();

    // Returns true if the string is empty.
    bool empty() const;
    // Return the size of the data in the string.
    unsigned long size() const;
    unsigned long length() const;

    // Clears the contents of the data.
    void clear();

    // Adds the other string to the end of the current string.
    // The rest of the data types that can be used (like const char* and char)
    // are covered by the constructor so will not be written.
    String& operator+=(const String& other);
    String& operator+=(char other);

    // Return the index of the first occurence of the target string/char
    // into the current string.
    unsigned long find(const String& target) const;
    unsigned long find(char target) const;

    // Returns true if the string/char is contained into the current string.
    bool contains(const String& target) const;
    bool contains(char target) const;

    // Returns a new string that is the concatination of the current string
    // with the other string given.
    String operator+(const String& right) const;

    // Returns true if the strings given are the same.
    bool operator==(const String& other) const;
    // Returns true if the strings given are different.
    bool operator!=(const String& other) const;

    // Returns the current string data being cast to the type
    // from the template.
    template<typename Type> Type CastFromString() const {
        if (std::is_same_v<Type, int>) {
            return std::stoi(m_data);
        } else if (std::is_same_v<Type, unsigned int>) {
            return std::stoul(m_data);
        } else if (std::is_same_v<Type, unsigned long>) {
            return std::stoul(m_data);
        } else if (std::is_same_v<Type, unsigned long long>) {
            return std::stoull(m_data);
        } else if (std::is_same_v<Type, long long>) {
            return std::stoll(m_data);
        } else if (std::is_same_v<Type, long>) {
            return std::stol(m_data);
        } else if (std::is_same_v<Type, bool>) {
            if (m_data == "true") {
                return true;
            }
            return false;
        }
        throw std::runtime_error("Cast from string failed! Type not recognized!");
        return Type();
    }

    // Split the current string by a delimiter given
    std::vector<String> split(const String& delimiter) const;
};

// Get any type of data as the custom string type, for everything but bool.
template<typename Type, std::enable_if_t<!std::is_same_v<Type, bool>>>
String ToString(const Type type) {
    return std::to_string(type);
}
// The same function but only for the boolean conversions.
template<typename Type, std::enable_if_t<std::is_same_v<Type, bool>>>
String ToString(const Type type) {
    return (type ? "true" : "false");
}
