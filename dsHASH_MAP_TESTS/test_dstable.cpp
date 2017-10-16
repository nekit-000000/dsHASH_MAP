/* START OF "tests_dstable.cpp" FILE */

#include <gtest/gtest.h>

#include "dshashmap.h"


class TABLE_TEST : public testing::Test,
   public testing::WithParamInterface<int> {
   void SetUp (void)
   {
      size = GetParam();
      testTable = dsTABLE<int>(size);
      for (int i = 0; i < size; i++) {
         testTable.Insert(i, i);
      }
   }

   void TearDown (void)
   {
   }

public:
   size_t size;
   dsTABLE<int> testTable;
};


TEST_P (TABLE_TEST, SizeAfterInsertion)
{
   EXPECT_EQ(size, testTable.Size());
}


TEST_P (TABLE_TEST, GetTestWrongIndex)
{
   auto it = testTable.Get(size);
   EXPECT_EQ(it, testTable.End());
}


TEST (TableSizeTest, IsEmptyInitially)
{
   dsTABLE<int> testTable;
   EXPECT_EQ(0, testTable.Size());
}


TEST_P (TABLE_TEST, SizeAfterRemoval)
{
   testTable.Delete(size - 1);
   EXPECT_EQ(size - 1, testTable.Size());
}


TEST (FindTest, IfElemDoesntExist)
{
   dsTABLE<int> testTable;

   testTable.Insert(0, 0);
   EXPECT_EQ(testTable.End(), testTable.Find(1));
}


TEST (FindTest, IfElemExists)
{
   dsTABLE<int> testTable;

   testTable.Insert(0, 0);
   auto it = testTable.Find(0);
   EXPECT_EQ(0, *it);
}


TEST_P(TABLE_TEST, ErasesCorrectly)
{
   for (int i = size - 1; i > size / 2; i--) {
      testTable.Delete(i);
      EXPECT_EQ(testTable.End(), testTable.Find(i));
   }
}


TEST_P (TABLE_TEST, ClearTestIfNotEmpty)
{
   testTable.Clear();
   EXPECT_EQ(testTable.Begin(), testTable.End());
}


TEST_P (TABLE_TEST, CopyTest)
{
   dsTABLE<int> copy;
   copy = testTable;

   auto it1 = testTable.Begin();
   auto it2 = copy.Begin();

   while (it1 != testTable.End()) {
      EXPECT_EQ(*it1, *it2);
      it1++;
      it2++;
   }
}


TEST_P(TABLE_TEST, MoveCopyTest)
{
   dsTABLE<int> copy1, copy2;

   copy2 = testTable;
   copy1 = std::move(copy2);

   auto it1 = testTable.Begin();
   auto it2 = copy1.Begin();

   while (it1 != testTable.End()) {
      EXPECT_EQ(*it1, *it2);
      it1++;
      it2++;
   }
}


TEST (PrefixIteratorTest, PassesAllVallues)
{
   dsTABLE<int> testTable;

   for (int i = 0; i < 1000; i++) {
      testTable.Insert(0, i);
   }

   int iterCnt = 0;
   for (auto it = testTable.Begin(); it != testTable.End(); ++it) {
      (*it)++;
      iterCnt++;
   }

   EXPECT_EQ(testTable.Size(), iterCnt);

   for (auto it = testTable.Begin(); it != testTable.End(); ++it) {
      EXPECT_EQ(*it, 1);
   }
}


TEST (PostfixIteratorTest, PassesAllVallues)
{
   dsTABLE<int> testTable;

   for (int i = 0; i < 1000; i++) {
      testTable.Insert(0, i);
   }

   int iterCnt = 0;
   for (auto it = testTable.Begin(); it != testTable.End(); it++) {
      (*it)++;
      iterCnt++;
   }

   EXPECT_EQ(testTable.Size(), iterCnt);

   for (auto it = testTable.Begin(); it != testTable.End(); it++) {
      EXPECT_EQ(*it, 1);
   }
}


INSTANTIATE_TEST_CASE_P(TableTestParameters,
   TABLE_TEST,
   testing::Values(1, 100, 1000, 10000));


/* END OF "tests_dstable.cpp" FILE */
