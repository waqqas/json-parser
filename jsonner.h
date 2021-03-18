#pragma once

#include "JSONBaseVisitor.h"
#include "JSONLexer.h"
#include "JSONParser.h"
#include "antlr4-runtime.h"

#include <iostream>

namespace jsonner {
using namespace std;
using namespace antlr4;
using namespace json;
class parser
{

 public:
   parser(ifstream &input)
      : _input(input)
      , _lexer(&_input)
      , _tokens(&_lexer)
      , _parser(&_tokens)
   {}

   void parse()
   {
      JSONParser::JsonContext *_tree;

      _tree = _parser.json();

      cout << _tree->toStringTree(&_parser) << endl;

      // visitor visitor;
      // return visitor.visitJson(_tree);
   }

 private:
   ANTLRInputStream  _input;
   JSONLexer         _lexer;
   CommonTokenStream _tokens;
   JSONParser        _parser;
};
}  // namespace jsonner
