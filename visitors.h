#pragma once

#include "JSONBaseVisitor.h"

#include <string>

namespace jsonner {
namespace visitors {
   using namespace std;

   class JSONPairVisitor : public JSONBaseVisitor
   {
    public:
      JSONPairVisitor(const string &key)
         : _key(key)
      {}
      virtual antlrcpp::Any visitObj(JSONParser::ObjContext *ctx) override
      {
         antlrcpp::Any result = defaultResult();
         for (auto pair : ctx->pair())
         {
            if (pair->STRING()->getText() == _key)
            {
               result = pair;
               break;
            }
         }
         return result;
      }
      // antlrcpp::Any visitPair(JSONParser::PairContext *ctx) override
      // {
      //    if (ctx->STRING()->getText() == _key)
      //    {
      //       return ctx;
      //    }
      //    return nullptr;
      // }

    private:
      const string &_key;
   };
}  // namespace visitors
}  // namespace jsonner