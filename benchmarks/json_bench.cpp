#include "jsonner.h"

#include <benchmark/benchmark.h>
#include <fstream>

static void BM_SomeFunction(benchmark::State &state)
{
   // std::ifstream jsonFile("test.json");

   // jsonner::parser parser(jsonFile);
   // Perform setup here
   for (auto _ : state)
   {
      // parser.parse();
   }
}
// Register the function as a benchmark
BENCHMARK(BM_SomeFunction);