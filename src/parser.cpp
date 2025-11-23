#include "parser.hpp"
#include <cassert>
#include <iostream>

Document parse_markup(std::istream &input) {
  Document doc;
  Block current;
  Line current_line;
  bool have_block = false;
  bool have_line = false;
  std::string line;

  while (std::getline(input, line)) {
    if (line.rfind("@begin docs", 0) == 0) {
      // start docs
      assert(!have_block);
      current = Block{};
      current.kind = Block::Kind::Docs;
      current.name.clear();
      current.docsText.clear();
      have_block = true;
      continue;
    }

    if (line.rfind("@begin code", 0) == 0) {
      // start code
      assert(!have_block);
      current = Block{};
      current.kind = Block::Kind::CodeDefn;
      current.name.clear();
      current.docsText.clear();
      current.body.clear();
      have_block = true;
      have_line = false;
      continue;
    }

    if (line.rfind("@end ", 0) == 0) {
      // end block
      assert(have_block);
      if (current.kind == Block::Kind::CodeDefn && have_line) {
        current.body.push_back(current_line);
        have_line = false;
      }

      doc.blocks.push_back(std::move(current));
      have_block = false;
      continue;
    }

    if (current.kind == Block::Kind::Docs) {
      if (line.rfind("@text ", 0) == 0) {
        current.docsText += line.substr(6);
      } else if (line == "@nl") {
        current.docsText += "\n";
      } else if (line.rfind("@literal ", 0) == 0) {
        current.docsText += line.substr(9) + "\n";
      } else if (line.rfind("@fatal", 0) == 0) {
        std::cerr << "noweb markup fatal: " << line << "\n";
      } else if (line == "@quote" || line == "@endquote") {
        // TODO
      } else {
        // unknown
      }

      continue;
    }

    if (line.rfind("@defn ", 0) == 0) {
      assert(current.name.empty());
      current.name = line.substr(6);
      continue;
    }

    if (line.rfind("@text ", 0) == 0) {
      // code text
      if (line.empty())
        continue;
      if (!have_line || current_line.kind != Line::Kind::Text) {
        // start a new text line
        current_line = Line{Line::Kind::Text, "", ""};
        have_line = true;
      }
      current_line.text += line.substr(6);
      continue;
    }

    if (line == "@nl") {
      // end of current logical line
      if (have_line) {
        current.body.push_back(current_line);
        have_line = false;
      }
      continue;
    }

    if (line.rfind("@use ", 0) == 0) {
      // flush pending text line
      if (have_line) {
        current.body.push_back(current_line);
        have_line = false;
      }

      std::string name = line.substr(5);
      current.body.push_back(Line{Line::Kind::Use, "", name});
      continue;
    }

    if (line.rfind("@literal ", 0) == 0) {
      // treat literal as a text line in code
      if (!have_line || current_line.kind != Line::Kind::Text) {
        current_line = Line{Line::Kind::Text, "", ""};
        have_line = true;
      }
      current_line.text += line.substr(9) + "\n";
      continue;
    }

    if (line.rfind("@fatal", 0) == 0) {
      std::cerr << "noweb markup fatal: " << line << "\n";
      continue;
    }

    // TODO
    if (line == "@quote" || line == "@endquote") {
      continue;
    }
  }
  if (have_block) {
    if (current.kind == Block::Kind::CodeDefn && have_line) {
      current.body.push_back(current_line);
    }
    doc.blocks.push_back(std::move(current));
  }

  return doc;
}
