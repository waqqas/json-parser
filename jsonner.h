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

class doc;

class parser
{
   friend doc;

 public:
   parser(istream &input)
      : _input(input)
      , _lexer(&_input)
      , _tokens(&_lexer)
      , _parser(&_tokens)
   {}

   tree::ParseTree *parse()
   {
      return _parser.json();
   }

 private:
   ANTLRInputStream  _input;
   JSONLexer         _lexer;
   CommonTokenStream _tokens;
   JSONParser        _parser;
};

class doc
{

 public:
   friend ostream &operator<<(ostream &output, const doc &d)
   {
      if (d._parser)
      {
         output << d._tree->toStringTree(&d._parser->_parser);
      }
      return output;
   }
   friend istream &operator>>(istream &in, doc &d)
   {
      if (!d._parser)
      {
         d._parser = make_shared<parser>(in);
      }
      d._tree = d._parser->parse();
      return in;
   }

 private:
   tree::ParseTree *  _tree;
   shared_ptr<parser> _parser;
};

}  // namespace jsonner
