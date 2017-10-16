/* START OF "tests_dshash_map.cpp" FILE */

#include <gtest/gtest.h>

#include "dshashmap.h"


class HASH_MAP_TEST : public testing::Test,
   public testing::WithParamInterface<int> {
   void SetUp(void)
   {
      size = GetParam();
      testMap = dsHASH_MAP<int, int>(size);
      for (int i = 0; i < size; i++) {
         testMap[i] = i;
      }
   }

   void TearDown(void)
   {
   }

public:
   int size;
   dsHASH_MAP<int, int> testMap;
};


TEST (InsertTest, ReturnsCorrectValue)
{
   dsHASH_MAP<int, int> testMap;
   
   auto it = testMap.Insert(std::make_pair(1, 1)).first;
   EXPECT_EQ(it->second, 1);
}


TEST (InsertTest, ChangesValue)
{
   dsHASH_MAP<int, int> testMap;

   testMap[1] = 0;
   testMap.Insert(std::make_pair(1, 1));
   EXPECT_EQ(testMap[1], 1);
}


TEST (EmptyTest, IsEmptyInitially)
{
   dsHASH_MAP<int, int> testMap;
   EXPECT_EQ(true, testMap.Empty());
}


TEST (EmptyTest, NotEmpty)
{
   dsHASH_MAP<int, int> testMap;
   testMap[1] = 1;
   EXPECT_EQ(false, testMap.Empty());
}


TEST_P (HASH_MAP_TEST, SizeAfterInsertion)
{
   EXPECT_EQ(size, testMap.Size());
}


TEST_P(HASH_MAP_TEST, RehashTest)
{
   int * arr = new int[2 * size];

   for (int i = 0; i < size; i++) {
      arr[i] = i;
   }

   testMap.SetMaxLoadFactor(0.5);

   for (int i = size; i < 2 * size; i++) {
      testMap[i] = i;
      arr[i] = i;
   }

   for (auto it = testMap.Begin(); it != testMap.End(); it++) {
      arr[it->first] = 0;
   }

   bool res = true;
   for (int i = 0; i < 2 * size; i++) {
      if (arr[i] != 0) {
         res = false;
         break;
      }
   }

   EXPECT_EQ(res, true);
}


TEST (MapSizeTest, IsEmptyInitially)
{
   dsHASH_MAP<int, int> testMap;
   EXPECT_EQ(0, testMap.Size());
}


TEST_P (HASH_MAP_TEST, SizeAfterRemoval)
{
   testMap.Erase(size - 1);
   EXPECT_EQ(size - 1, testMap.Size());
}


TEST (MapFindTest, IfElemDoesntExist)
{
   dsHASH_MAP<int, int> testMap;

   testMap[1] = 1;
   EXPECT_EQ(testMap.End(), testMap.Find(0));
}


TEST (MapFindTest, IfElemExists)
{
   dsHASH_MAP<int, int> testMap;

   testMap.Insert(std::make_pair(1, 1));
   auto it = testMap.Find(1);
   EXPECT_EQ(1, it->second);
}


TEST_P (HASH_MAP_TEST, ErasesCorrectly)
{
   for (int i = size - 1; i > size / 2; i--) {
      testMap.Erase(i);
      EXPECT_EQ(testMap.End(), testMap.Find(i));
   }
}


TEST_P (HASH_MAP_TEST, ClearTestIfNotEmpty)
{
   testMap.Clear();
   EXPECT_EQ(testMap.Begin(), testMap.End());
}


INSTANTIATE_TEST_CASE_P(TableTestParameters,
   HASH_MAP_TEST,
   testing::Values(1, 5, 10, 100, 1000, 10000));


/* END OF "tests_dshash_map.cpp" FILE */