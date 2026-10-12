#ifndef LIBS_FILEMANAGER_FILEMANAGER_H
#define LIBS_FILEMANAGER_FILEMANAGER_H

#include <string/String.h>
#include <fstream>
#include <vector>

class Filemanager {
 private:
    // Holds all input files that were currently opened and still need to be closed.
    // Will be closed with a function or for sure at the destructor.
    std::vector<std::ifstream> m_openedInputFiles;

    // Holds all output files that were currently opened and still need to be closed.
    // Will be closed with a function or for sure at the destructor.
    std::vector<std::ofstream> m_openedOutputFiles;

    // Returns true if there is a
    // file at the end of the path given that exists.
    bool DoesFileExist(const String& filename) const;

 public:
    Filemanager() = default;
    ~Filemanager();

    // Closes all the files that were opened and returned to the user.
    void CloseAllFiles();
    // Closes all the input files that were opened and returned to the user.
    void CloseAllInputFiles();
    // Closes all the output files that were opened and returned to the user.
    void CloseAllOutputFiles();

    // Returns a reference to an input file that would be opened.
    // Throws an error if for some reason the file cannot be opened.
    // Requires that a file already exists.
    // The filename is the path to the file.
    std::ifstream& GetOpenedInputFile(const String& filename);

    // Returns a reference to an output file that would be opened.
    // Throws an error if for some reason the file cannot be opened.
    // Will create the file and all the parent directories if needed.
    // The filename is the path to the file.
    std::ofstream& GetOpenedOutputFile(const String& filename,
                                       const bool    bTruncate = true);

    // Writes the information from the buffer into the filename given and truncates the file at the start.
    // Automatically creates the parend directories and the file if it does not exist.
    // After the write, the file is closed and the 'transaction' is considered complete.
    // Throws an error if the file cannot be opened.
    void WriteToFile(const String& buffer,
                     const String& filename,
                     const bool    bTruncate = true) const;

    // Opens the file given and returns the contents of it into a vector of strings
    // where each string is a single line.
    // Better suited for small files because of the use of vector.
    // After the read is done closes the file.
    std::vector<String> ReadFromFile(const String& filename) const;
};

#endif  // LIBS_FILEMANAGER_FILEMANAGER_H
