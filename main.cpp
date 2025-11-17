#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv) {
    if (argc <  2) {
        std::cerr << "usage: noweb-typst <file>\n";
    }

    std::string filename = argv[1];
    std::ifstream inputFile(filename);
    
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }
    
    std::string line;

    while (std::getline(inputFile, line)) {
        if (line.rfind("@begin docs", 0) == 0) {
            // start docs
        } else if (line.rfind("@begin code", 0) == 0) {
            //end code
        } else if (line.rfind("@end ", 0) == 0) {
            // end block
        } else if (line.rfind("@text ", 0) == 0) {
            //string
        } else if (line.rfind("@nl", 0) == 0) {
            // newline
        } else if (line.rfind("@defn ", 0) == 0) {
            // code chunk
        } else if (line.rfind("@use ", 0) == 0) {
            // reference code chunk
        } else if (line.rfind("@quote", 0) == 0) {
            // start quoted code in doc chunk
        } else if (line.rfind("@endquote", 0) == 0) {
            // end quoted code
        } else if (line.rfind("@fatal", 0) == 0) {
            // fatal error
        } else if (line.rfind("@literal", 0) == 0) {
            // copy text to output
        }
    }
}