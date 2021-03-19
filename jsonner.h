#pragma once

#include "JSONBaseVisitor.h"
#include "JSONLexer.h"
#include "JSONParser.h"
#include "antlr4-runtime.h"

#include <iostream>
#include <string_view>

namespace jsonner {
using namespace std;
using namespace antlr4;
using namespace json;

class doc
{

 public:
   doc(tree::ParseTree *tree)
      : _tree(tree)
   {}

   friend ostream &operator<<(ostream &output, const doc &d)
   {
      output << d._tree->toStringTree();
      return output;
   }

 private:
   tree::ParseTree *_tree;
};

class parser
{

 public:
   parser(ifstream &input)
      : _input(input)
      , _lexer(&_input)
      , _tokens(&_lexer)
      , _parser(&_tokens)
   {}

   doc parse()
   {
      return doc(_parser.json());
   }

 private:
   ANTLRInputStream  _input;
   JSONLexer         _lexer;
   CommonTokenStream _tokens;
   JSONParser        _parser;
};
}  // namespace jsonner
