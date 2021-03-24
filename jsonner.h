#pragma once

#include "JSONLexer.h"
#include "JSONParser.h"
#include "visitors.h"

#include <antlr4-runtime.h>
#include <any>
#include <iostream>
#include <string_view>

namespace jsonner {
using namespace std;
using namespace antlr4;

class doc;

class parser
{
 public:
   parser(istream &input)
      : _input(input)
      , _lexer(&_input)
      , _tokens(&_lexer)
      , _parser(&_tokens)
   {}

   ParserRuleContext *parse()
   {
      return _parser.json();
   }

   JSONParser *get_parser_ptr()
   {
      return &_parser;
   }

   void reset(istream &in)
   {
      _input.reset();
      _lexer.reset();
      _tokens.reset();
      _parser.reset();

      _input.load(in);
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
   doc() = default;
   doc(ParserRuleContext *tree, shared_ptr<parser> parser)
      : _tree(tree)
      , _parser(parser)
   {}

   friend ostream &operator<<(ostream &output, const doc &d)
   {
      if (d._parser && d._tree)
      {
         output << d._tree->toStringTree(d._parser->get_parser_ptr(), true);
      }
      return output;
   }
   friend istream &operator>>(istream &in, doc &d)
   {
      if (!d._parser)
      {
         d._parser = make_shared<parser>(in);
      }
      else
      {
         d._parser->reset(in);
      }
      d._tree = d._parser->parse();
      return in;
   }

   doc operator[](const string &key)
   {
      visitors::JSONPairVisitor visitor{key};
      auto                      node = _tree->accept(&visitor);
      if (node.isNotNull())
      {
         return doc(node.as<ParserRuleContext *>(), _parser);
      }
      else
      {
         throw exception();
      }
   }

   template <typename T>
   T as()
   {
      try
      {
         JSONParser::PairContext *pair  = dynamic_cast<JSONParser::PairContext *>(_tree);
         auto                     value = pair->value()->STRING();
         if (value)
         {
            return value->getText();
         }
         else
         {
            throw std::bad_cast();
         }
      }
      catch (std::bad_cast &ex)
      {
         throw ex;
      }
   }

 private:
   ParserRuleContext *_tree;
   shared_ptr<parser> _parser;
};

}  // namespace jsonner
