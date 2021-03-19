#include "jsonner.h"

#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
   if (argc == 1)
   {
      cout << "Usage: main <json>" << endl;
      return -1;
   }

   std::stringstream ss;
   ss << argv[1];
   jsonner::doc doc;
   try
   {
      ss >> doc;
      cout << doc;
   }
   catch (exception &e)
   {
      cerr << e.what() << endl;
   }

   return 0;
}