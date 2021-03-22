#pragma once

#include "JSONBaseVisitor.h"

#include <any>
#include <string>

namespace jsonner {
namespace visitors {
   using namespace std;
   using namespace antlr4;

   class JSONPairVisitor : public JSONBaseVisitor
   {
    public:
      JSONPairVisitor(const string &key)
         : _key("\"" + key + "\"")
      {}
      virtual antlrcpp::Any visitObj(JSONParser::ObjContext *ctx) override
      {
         antlrcpp::Any result = defaultResult();
         for (auto pair : ctx->pair())
         {
            if (pair->STRING()->getText() == _key)
            {
               return (ParserRuleContext *)pair;
            }
         }
         return result;
      }

    private:
      const string _key;
   };
}  // namespace visitors
}  // namespace jsonner