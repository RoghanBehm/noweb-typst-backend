#pragma once
#include <string>
#include <vector>

struct Line {
  enum class Kind { Text, Use };

  Kind kind;
  std::string text;
  std::string name;
};

struct Block {
  enum class Kind { Docs, CodeDefn };

  Kind kind;
  std::string name;
  std::string docsText;
  std::vector<Line> body;
};

struct Document {
  std::vector<Block> blocks;
};
