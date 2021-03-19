#include "jsonner.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
   if (argc == 1)
   {
      cout << "Usage: main json-file" << endl;
      return -1;
   }

   ifstream jsonFile(argv[1]);
   if (jsonFile.is_open())
   {
      jsonner::parser parser(jsonFile);
      try
      {
         auto doc = parser.parse();
         cout << doc;
      }
      catch (exception &e)
      {
         cerr << e.what() << endl;
      }

      jsonFile.close();
   }
   return 0;
}