/* START OF "comparison.cpp" FILE */


#include <benchmark\benchmark.h>

#include "dshashmap.h"
#include "dsmap.h"


static void BM_MapFindTest (benchmark::State & state) {
   dsMAP<int, int> map;

   int size = state.range(0);
   for (int i = 0; i < size; i++) {
      map[i] = i;
   }

   while (state.KeepRunning()) {
      map.Find(rand() % size);
   }


   state.SetComplexityN(state.range(0));
}


static void BM_HashMapFindTest(benchmark::State & state) {
   // Minimize the collizion number
   dsHASH_MAP<int, int> hashMap(state.range(0) * 2);

   int size = state.range(0);
   for (int i = 0; i < size; i++) {
      hashMap[i] = i;
   }

   while (state.KeepRunning()) {
      hashMap.Find(rand() % size);
   }

   state.SetComplexityN(state.range(0));
}


static void BM_MapInsertNTest (benchmark::State & state) {
   dsMAP<int, int> map;

   while (state.KeepRunning()) {
      int size = state.range(0);
      for (int i = 0; i < size; i++) {
         if (i != size / 2) {
            map[i] = i;
         }
      }
   }


   state.SetComplexityN(state.range(0));
}


static void BM_HashMapInsertNWithoutRehashTest (benchmark::State & state) {
   dsHASH_MAP<int, int> hashMap(state.range(0) * 2);

   while (state.KeepRunning()) {
      int size = state.range(0);
      for (int i = 0; i < size; i++) {
         hashMap[i] = i;
      }
   }

   state.SetComplexityN(state.range(0));
}


static void BM_HashMapInsertNWithRehashTest (benchmark::State & state) {
   dsHASH_MAP<int, int> hashMap;

   while (state.KeepRunning()) {
      int size = state.range(0);
      for (int i = 0; i < size; i++) {
         hashMap[i] = i;
      }
   }

   state.SetComplexityN(state.range(0));
}


static void BM_MapDeleteTest (benchmark::State & state) {
   dsMAP<int, int> map;

   int size = state.range(0);
   for (int i = 0; i < size; i++) {
      map[i] = i;
   }

   while (state.KeepRunning()) {
      map.Erase(rand() % size);
   }


   state.SetComplexityN(state.range(0));
}


static void BM_HashMapDeleteTest (benchmark::State & state) {
   dsHASH_MAP<int, int> hashMap(state.range(0));

   int size = state.range(0);
   for (int i = 0; i < size; i++) {
      hashMap[i] = i;
   }

   while (state.KeepRunning()) {
      hashMap.Erase(rand() % size);
   }

   state.SetComplexityN(state.range(0));
}


// Find element tests
BENCHMARK(BM_MapFindTest)->RangeMultiplier(2)->Range(1 << 8, 1 << 18)->Complexity();
BENCHMARK(BM_HashMapFindTest)->RangeMultiplier(2)->Range(1 << 8, 1 << 18)->Complexity();

// Insert N elements tests
BENCHMARK(BM_MapInsertNTest)->RangeMultiplier(2)->Range(1 << 8, 1 << 18)->Complexity();
BENCHMARK(BM_HashMapInsertNWithoutRehashTest)->RangeMultiplier(2)->Range(1 << 8, 1 << 18)->Complexity();
BENCHMARK(BM_HashMapInsertNWithRehashTest)->RangeMultiplier(2)->Range(1 << 8, 1 << 18)->Complexity();

// Delete element tests
BENCHMARK(BM_MapDeleteTest)->RangeMultiplier(2)->Range(1 << 8, 1 << 19)->Complexity();
BENCHMARK(BM_HashMapDeleteTest)->RangeMultiplier(2)->Range(1 << 8, 1 << 19)->Complexity();


/* END OF "comparison.cpp" FILE */
