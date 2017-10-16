/* START OF "main.cpp" FILE */

#pragma comment (lib, "Shlwapi.lib")

#include <benchmark\benchmark.h>

int main (int argc, char * argv[])
{
   benchmark::Initialize(&argc, argv);
   benchmark::RunSpecifiedBenchmarks();
   return 0;
}

/* END OF "main.cpp" FILE */
