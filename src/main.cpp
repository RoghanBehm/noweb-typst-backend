#include <cassert>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include "document.hpp"
#include "parser.hpp"
#include "emitter.hpp"

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cerr << "usage: noweb-typst <file> <code language>\n";
  }

  std::string filename = argv[1];
  std::string code_lang = argv[2];
  std::ifstream inputFile(filename);

  if (!inputFile.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return 1;
  }

  Document doc = parse_markup(inputFile);
  dump_document(doc);

  std::ofstream file("out.typ");
  emit_typst(file, doc, code_lang);
  return 0;
}