#include "../my_map.h"
#include "gtest/gtest.h"

template class mycontainers::MyMap<int, int>;

class MapTest1 : public testing::Test {
 protected:
  void TearDown() override {
    EXPECT_EQ(stdMap.size(), myMap.size());
    EXPECT_EQ(stdMap.max_size(), myMap.max_size());
    EXPECT_EQ(stdMap.empty(), myMap.empty());

    EXPECT_EQ(stdMap.begin()->first, myMap.begin()->first);
    EXPECT_EQ(stdMap.begin()->second, myMap.begin()->second);
    EXPECT_EQ(stdMap.end()->first, myMap.end()->first);
    EXPECT_EQ(stdMap.end()->second, myMap.end()->second);

    std::map<int, int>::iterator stdIt = stdMap.begin();
    mycontainers::MyMap<int, int>::iterator myIt = myMap.begin();
    for (; stdIt != stdMap.end(); ++stdIt, ++myIt) {
      EXPECT_EQ(stdIt->first, myIt->first);
      EXPECT_EQ(stdIt->second, myIt->second);
    }
  }

  std::map<int, int> stdMap;
  mycontainers::MyMap<int, int> myMap;
};

TEST_F(MapTest1, TestMapIntDefault) {
  EXPECT_TRUE(stdMap.empty());
  EXPECT_TRUE(myMap.empty());
}

TEST_F(MapTest1, TestMapIntInitList) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap1{items};
  mycontainers::MyMap<int, int> myMap1{items};

  stdMap = stdMap1;
  myMap = myMap1;
}

TEST_F(MapTest1, TestMapIntCopy) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 10}, {3, 30}, {2, 20}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  std::map<int, int> stdMap2(stdMap1);
  mycontainers::MyMap<int, int> myMap2(myMap1);

  stdMap = stdMap2;
  myMap = myMap2;

  EXPECT_EQ(stdMap1.size(), myMap1.size());
  EXPECT_EQ(stdMap1.max_size(), myMap1.max_size());
  EXPECT_EQ(stdMap1.empty(), myMap1.empty());

  EXPECT_EQ(stdMap1.begin()->first, myMap1.begin()->first);
  EXPECT_EQ(stdMap1.begin()->second, myMap1.begin()->second);
  EXPECT_EQ(stdMap1.end()->first, myMap1.end()->first);
  EXPECT_EQ(stdMap1.end()->second, myMap1.end()->second);
}

TEST_F(MapTest1, TestMapIntMove) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {5, 4}, {3, 6}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  std::map<int, int> stdMap2(std::move(stdMap1));
  mycontainers::MyMap<int, int> myMap2(std::move(myMap1));

  stdMap = stdMap2;
  myMap = myMap2;

  EXPECT_EQ(stdMap1.size(), myMap1.size());
  EXPECT_EQ(stdMap1.max_size(), myMap1.max_size());
  EXPECT_EQ(stdMap1.empty(), myMap1.empty());

  EXPECT_EQ(stdMap1.begin()->first, myMap1.begin()->first);
  EXPECT_EQ(stdMap1.begin()->second, myMap1.begin()->second);
  EXPECT_EQ(stdMap1.end()->first, myMap1.end()->first);
  EXPECT_EQ(stdMap1.end()->second, myMap1.end()->second);
}

TEST_F(MapTest1, TestMapIntCopyOp) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {5, 6}, {3, 4}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  stdMap = stdMap1;
  myMap = myMap1;

  EXPECT_EQ(stdMap1.size(), myMap1.size());
  EXPECT_EQ(stdMap1.max_size(), myMap1.max_size());
  EXPECT_EQ(stdMap1.empty(), myMap1.empty());

  EXPECT_EQ(stdMap1.begin()->first, myMap1.begin()->first);
  EXPECT_EQ(stdMap1.begin()->second, myMap1.begin()->second);
  EXPECT_EQ(stdMap1.end()->first, myMap1.end()->first);
  EXPECT_EQ(stdMap1.end()->second, myMap1.end()->second);
}

TEST_F(MapTest1, TestMapIntMoveOp) {
  std::initializer_list<std::pair<const int, int>> items{
      {5, 6}, {3, 4}, {1, 2}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  stdMap = std::move(stdMap1);
  myMap = std::move(myMap1);

  EXPECT_EQ(stdMap1.size(), myMap1.size());
  EXPECT_EQ(stdMap1.max_size(), myMap1.max_size());
  EXPECT_EQ(stdMap1.empty(), myMap1.empty());

  EXPECT_EQ(stdMap1.begin()->first, myMap1.begin()->first);
  EXPECT_EQ(stdMap1.begin()->second, myMap1.begin()->second);
  EXPECT_EQ(stdMap1.end()->first, myMap1.end()->first);
  EXPECT_EQ(stdMap1.end()->second, myMap1.end()->second);
}

TEST_F(MapTest1, TestMapIntViewing) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 6}, {3, 4}, {5, 2}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  stdMap = stdMap1;
  myMap = myMap1;

  for (auto &[key, value] : items) {
    EXPECT_EQ(stdMap.count(key) > 0, myMap.contains(key));
    EXPECT_EQ(stdMap.at(key), myMap.at(key));
    EXPECT_EQ(stdMap[key], myMap[key]);
  }

  EXPECT_EQ(stdMap.count(11111) > 0, myMap.contains(11111));
  EXPECT_THROW(stdMap.at(11111), std::out_of_range);
  EXPECT_THROW(myMap.at(11111), std::out_of_range);
  EXPECT_EQ(stdMap[11111], myMap[11111]);
}

TEST_F(MapTest1, TestMapIntClear) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  stdMap = stdMap1;
  myMap = myMap1;

  stdMap.clear();
  myMap.clear();
}

TEST_F(MapTest1, TestMapIntInsert1) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 4}, {2, 6}, {20, 5}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  stdMap = stdMap1;
  myMap = myMap1;

  auto stdResult = stdMap.insert({6, 7});
  auto myResult = myMap.insert(6, 7);

  EXPECT_EQ(stdResult.second, myResult.second);
  EXPECT_EQ(stdResult.first->first, myResult.first->first);
  EXPECT_EQ(stdResult.first->second, myResult.first->second);
}

TEST_F(MapTest1, TestMapIntInsert2) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {2, 3}, {3, 4}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  stdMap = stdMap1;
  myMap = myMap1;

  auto stdResult = stdMap.insert(std::pair<int, int>(-6, -5));
  auto myResult = myMap.insert(std::pair<int, int>(-6, -5));

  EXPECT_EQ(stdResult.second, myResult.second);
  EXPECT_EQ(stdResult.first->first, myResult.first->first);
  EXPECT_EQ(stdResult.first->second, myResult.first->second);
}

TEST_F(MapTest1, TestMapIntInsert3) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  stdMap = stdMap1;
  myMap = myMap1;

  auto stdResult = stdMap.insert({66, 67});
  auto myResult = myMap.insert({66, 67});

  EXPECT_EQ(stdResult.second, myResult.second);
  EXPECT_EQ(stdResult.first->first, myResult.first->first);
  EXPECT_EQ(stdResult.first->second, myResult.first->second);
}

TEST_F(MapTest1, TestMapIntInsert4) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  stdMap = stdMap1;
  myMap = myMap1;

  auto stdResult = stdMap.insert({5, 7});
  auto myResult = myMap.insert({5, 7});

  EXPECT_EQ(stdMap[5], 6);
  EXPECT_EQ(myMap[5], 6);

  EXPECT_EQ(stdResult.second, myResult.second);
  EXPECT_EQ(stdResult.first->first, myResult.first->first);
  EXPECT_EQ(stdResult.first->second, myResult.first->second);
}

TEST_F(MapTest1, TestMapIntInsertMany) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {3, 4}, {5, 6}, {7, 8}};
  std::map<int, int> stdMap1(items);

  mycontainers::MyMap<int, int> myMap1;

  stdMap = stdMap1;
  myMap = myMap1;

  std::pair<int, int> pair1(1, 2);
  std::pair<int, int> pair2(3, 4);
  std::pair<int, int> pair3(5, 6);
  std::pair<int, int> pair4(7, 8);

  auto myResult = myMap.insert_many(pair1, pair2, pair3);
  auto myResult1 = myMap.insert_many(pair2, pair4);

  EXPECT_EQ(3, myResult.size());

  EXPECT_EQ(true, myResult[0].second);
  EXPECT_EQ(1, myResult[0].first->first);
  EXPECT_EQ(2, myResult[0].first->second);

  EXPECT_EQ(true, myResult[1].second);
  EXPECT_EQ(3, myResult[1].first->first);
  EXPECT_EQ(4, myResult[1].first->second);

  EXPECT_EQ(true, myResult[2].second);
  EXPECT_EQ(5, myResult[2].first->first);
  EXPECT_EQ(6, myResult[2].first->second);

  EXPECT_EQ(2, myResult1.size());

  EXPECT_EQ(false, myResult1[0].second);

  EXPECT_EQ(true, myResult1[1].second);
  EXPECT_EQ(7, myResult1[1].first->first);
  EXPECT_EQ(8, myResult1[1].first->second);
}

TEST_F(MapTest1, TestMapIntInsertOrAssign1) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  stdMap = stdMap1;
  myMap = myMap1;

  auto stdResult = stdMap.insert_or_assign(5, 7);
  auto myResult = myMap.insert_or_assign(5, 7);

  EXPECT_EQ(stdMap[5], 7);
  EXPECT_EQ(myMap[5], 7);

  EXPECT_EQ(stdResult.second, myResult.second);
  EXPECT_EQ(stdResult.first->first, myResult.first->first);
  EXPECT_EQ(stdResult.first->second, myResult.first->second);
}

TEST_F(MapTest1, TestMapIntInsertOrAssign2) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  stdMap = stdMap1;
  myMap = myMap1;

  auto stdResult = stdMap.insert_or_assign(6, 7);
  auto myResult = myMap.insert_or_assign(6, 7);

  EXPECT_EQ(stdMap[6], 7);
  EXPECT_EQ(myMap[6], 7);

  EXPECT_EQ(stdResult.second, myResult.second);
  EXPECT_EQ(stdResult.first->first, myResult.first->first);
  EXPECT_EQ(stdResult.first->second, myResult.first->second);
}

TEST_F(MapTest1, TestMapIntErase1) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  stdMap = stdMap1;
  myMap = myMap1;

  stdMap.erase(stdMap.find(3));
  myMap.erase(myMap.find(3));
}

TEST_F(MapTest1, TestMapIntErase2) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  stdMap = stdMap1;
  myMap = myMap1;

  stdMap.erase(stdMap.find(1));
  myMap.erase(myMap.find(1));
}

TEST_F(MapTest1, TestMapIntErase3) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  stdMap = stdMap1;
  myMap = myMap1;

  stdMap.erase(stdMap.find(5));
  myMap.erase(myMap.find(5));
}

TEST_F(MapTest1, TestMapIntSwap) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap2(items);
  mycontainers::MyMap<int, int> myMap2(items);

  stdMap = stdMap2;
  myMap = myMap2;

  items = {{7, 10}, {2, 10000}, {3, 1000}, {4, 100}, {6, -10}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  stdMap.swap(stdMap1);
  myMap.swap(myMap1);

  EXPECT_EQ(stdMap1.size(), myMap1.size());
  EXPECT_EQ(stdMap1.max_size(), myMap1.max_size());
  EXPECT_EQ(stdMap1.empty(), myMap1.empty());

  EXPECT_EQ(stdMap1.begin()->first, myMap1.begin()->first);
  EXPECT_EQ(stdMap1.begin()->second, myMap1.begin()->second);
  EXPECT_EQ(stdMap1.end()->first, myMap1.end()->first);
  EXPECT_EQ(stdMap1.end()->second, myMap1.end()->second);
}

TEST_F(MapTest1, TestMapIntMerge) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap2(items);
  mycontainers::MyMap<int, int> myMap2(items);

  stdMap = stdMap2;
  myMap = myMap2;

  items = {{7, 10}, {2, -10000}, {3, 1000}, {1, 100}, {-6, 10}};
  std::map<int, int> stdMap1(items);
  mycontainers::MyMap<int, int> myMap1(items);

  stdMap.merge(stdMap1);
  myMap.merge(myMap1);

  EXPECT_EQ(stdMap1.size(), myMap1.size());
  EXPECT_EQ(stdMap1.max_size(), myMap1.max_size());
  EXPECT_EQ(stdMap1.empty(), myMap1.empty());

  EXPECT_EQ(stdMap1.begin()->first, myMap1.begin()->first);
  EXPECT_EQ(stdMap1.begin()->second, myMap1.begin()->second);
  EXPECT_EQ(stdMap1.end()->first, myMap1.end()->first);
  EXPECT_EQ(stdMap1.end()->second, myMap1.end()->second);
}

TEST(MapTest, TestMapIntConst) {
  std::initializer_list<std::pair<const int, int>> items{
      {3, 2}, {5, 3}, {7, 9}, {12, 12}};
  const std::map<int, int> stdMap(items);
  const mycontainers::MyMap<int, int> myMap(items);

  EXPECT_EQ(stdMap.size(), myMap.size());
  EXPECT_EQ(stdMap.max_size(), myMap.max_size());
  EXPECT_EQ(stdMap.empty(), myMap.empty());

  for (auto &[key, value] : items) {
    EXPECT_EQ(stdMap.count(key) > 0, myMap.contains(key));
    EXPECT_EQ(stdMap.find(key)->first, myMap.find(key)->first);

    EXPECT_EQ(stdMap.at(key), myMap.at(key));
  }

  EXPECT_EQ(stdMap.begin() == stdMap.end(), myMap.begin() == myMap.end());
  EXPECT_EQ(stdMap.begin() != stdMap.end(), myMap.begin() != myMap.end());

  std::map<int, int>::const_iterator stdIt = stdMap.begin();
  mycontainers::MyMap<int, int>::iterator myIt = myMap.begin();
  for (; stdIt != stdMap.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(stdIt->first, myIt->first);
    EXPECT_EQ(stdIt->second, myIt->second);
  }

  stdIt = stdMap.end();
  myIt = myMap.end();
  while (stdIt != stdMap.begin()) {
    --stdIt;
    --myIt;
    EXPECT_EQ(stdIt->first, myIt->first);
    EXPECT_EQ(stdIt->second, myIt->second);
  }
}

TEST(MapTest, TestMapIntIterator) {
  std::initializer_list<std::pair<const int, int>> items{
      {1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap(items);
  mycontainers::MyMap<int, int> myMap(items);

  EXPECT_EQ(stdMap.begin()->first, myMap.begin()->first);
  EXPECT_EQ(stdMap.begin()->second, myMap.begin()->second);

  EXPECT_EQ(stdMap.end()->first, myMap.end()->first);
  EXPECT_EQ(stdMap.end()->second, myMap.end()->second);

  EXPECT_EQ(stdMap.begin() == stdMap.begin(), myMap.begin() == myMap.begin());
  EXPECT_EQ(stdMap.begin() != stdMap.begin(), myMap.begin() != myMap.begin());

  EXPECT_EQ(stdMap.end() == stdMap.end(), myMap.end() == myMap.end());
  EXPECT_EQ(stdMap.end() != stdMap.end(), myMap.end() != myMap.end());

  EXPECT_EQ(stdMap.begin() == stdMap.end(), myMap.begin() == myMap.end());
  EXPECT_EQ(stdMap.begin() != stdMap.end(), myMap.begin() != myMap.end());

  std::map<int, int>::iterator stdIt = stdMap.begin();
  mycontainers::MyMap<int, int>::iterator myIt = myMap.begin();
  for (; stdIt != stdMap.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(stdIt->first, myIt->first);
    EXPECT_EQ(stdIt->second, myIt->second);
  }

  stdIt = stdMap.end();
  myIt = myMap.end();
  while (stdIt != stdMap.begin()) {
    --stdIt;
    --myIt;
    EXPECT_EQ(stdIt->first, myIt->first);
    EXPECT_EQ(stdIt->second, myIt->second);
  }

  std::map<int, int>::iterator stdIt1(stdIt);
  mycontainers::MyMap<int, int>::iterator myIt1(myIt);

  EXPECT_EQ(stdIt1->first, myIt1->first);
  EXPECT_EQ(stdIt1->second, myIt1->second);

  EXPECT_EQ(stdIt->first, myIt->first);
  EXPECT_EQ(stdIt->second, myIt->second);

  std::map<int, int>::iterator stdIt2(std::move(stdIt));
  mycontainers::MyMap<int, int>::iterator myIt2(std::move(myIt));

  EXPECT_EQ(stdIt2->first, myIt2->first);
  EXPECT_EQ(stdIt2->second, myIt2->second);

  EXPECT_EQ(stdIt->first, myIt->first);
  EXPECT_EQ(stdIt->second, myIt->second);

  std::map<int, int>::iterator stdIt3;
  stdIt3 = stdIt2;
  mycontainers::MyMap<int, int>::iterator myIt3;
  myIt3 = myIt2;

  EXPECT_EQ(stdIt3->first, myIt3->first);
  EXPECT_EQ(stdIt3->second, myIt3->second);

  EXPECT_EQ(stdIt2->first, myIt2->first);
  EXPECT_EQ(stdIt2->second, myIt2->second);

  std::map<int, int>::iterator stdIt4;
  stdIt4 = std::move(stdIt2);
  mycontainers::MyMap<int, int>::iterator myIt4;
  myIt4 = std::move(myIt2);

  EXPECT_EQ(stdIt4->first, myIt4->first);
  EXPECT_EQ(stdIt4->second, myIt4->second);

  EXPECT_EQ(stdIt2->first, myIt2->first);
  EXPECT_EQ(stdIt2->second, myIt2->second);
}

TEST(MapTest, TestMapDoubleIterator) {
  std::initializer_list<std::pair<const double, double>> items{
      {1.1, 2.2}, {3.4, 4.3}, {5.999, 6.0}};
  std::map<double, double> stdMap(items);
  mycontainers::MyMap<double, double> myMap(items);

  EXPECT_EQ(stdMap.size(), myMap.size());
  EXPECT_EQ(stdMap.empty(), myMap.empty());

  EXPECT_EQ(stdMap.begin()->first, myMap.begin()->first);
  EXPECT_EQ(stdMap.begin()->second, myMap.begin()->second);

  EXPECT_EQ(stdMap.begin() == stdMap.begin(), myMap.begin() == myMap.begin());
  EXPECT_EQ(stdMap.begin() != stdMap.begin(), myMap.begin() != myMap.begin());

  EXPECT_EQ(stdMap.end() == stdMap.end(), myMap.end() == myMap.end());
  EXPECT_EQ(stdMap.end() != stdMap.end(), myMap.end() != myMap.end());

  EXPECT_EQ(stdMap.begin() == stdMap.end(), myMap.begin() == myMap.end());
  EXPECT_EQ(stdMap.begin() != stdMap.end(), myMap.begin() != myMap.end());

  std::map<double, double>::iterator stdIt = stdMap.begin();
  mycontainers::MyMap<double, double>::iterator myIt = myMap.begin();
  for (; stdIt != stdMap.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(stdIt->first, myIt->first);
    EXPECT_EQ(stdIt->second, myIt->second);
  }
}

TEST(MapTest, TestMapCharIterator) {
  std::initializer_list<std::pair<const char, char>> items{
      {1.1, 2.2}, {3.4, 4.3}, {5.999, 6.0}};
  std::map<char, char> stdMap(items);
  mycontainers::MyMap<char, char> myMap(items);

  EXPECT_EQ(stdMap.size(), myMap.size());
  EXPECT_EQ(stdMap.empty(), myMap.empty());

  EXPECT_EQ(stdMap.begin()->first, myMap.begin()->first);
  EXPECT_EQ(stdMap.begin()->second, myMap.begin()->second);

  EXPECT_EQ(stdMap.begin() == stdMap.begin(), myMap.begin() == myMap.begin());
  EXPECT_EQ(stdMap.begin() != stdMap.begin(), myMap.begin() != myMap.begin());

  EXPECT_EQ(stdMap.end() == stdMap.end(), myMap.end() == myMap.end());
  EXPECT_EQ(stdMap.end() != stdMap.end(), myMap.end() != myMap.end());

  EXPECT_EQ(stdMap.begin() == stdMap.end(), myMap.begin() == myMap.end());
  EXPECT_EQ(stdMap.begin() != stdMap.end(), myMap.begin() != myMap.end());

  std::map<char, char>::iterator stdIt = stdMap.begin();
  mycontainers::MyMap<char, char>::iterator myIt = myMap.begin();
  for (; stdIt != stdMap.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(stdIt->first, myIt->first);
    EXPECT_EQ(stdIt->second, myIt->second);
  }
}

TEST(MapTest, TestMapBoolIterator) {
  std::initializer_list<std::pair<const bool, bool>> items{
      {true, true}, {true, false}, {false, true}, {false, false}};
  std::map<bool, bool> stdMap(items);
  mycontainers::MyMap<bool, bool> myMap(items);

  EXPECT_EQ(stdMap.size(), myMap.size());
  EXPECT_EQ(stdMap.empty(), myMap.empty());

  EXPECT_EQ(stdMap.begin()->first, myMap.begin()->first);
  EXPECT_EQ(stdMap.begin()->second, myMap.begin()->second);

  EXPECT_EQ(stdMap.begin() == stdMap.begin(), myMap.begin() == myMap.begin());
  EXPECT_EQ(stdMap.begin() != stdMap.begin(), myMap.begin() != myMap.begin());

  EXPECT_EQ(stdMap.end() == stdMap.end(), myMap.end() == myMap.end());
  EXPECT_EQ(stdMap.end() != stdMap.end(), myMap.end() != myMap.end());

  EXPECT_EQ(stdMap.begin() == stdMap.end(), myMap.begin() == myMap.end());
  EXPECT_EQ(stdMap.begin() != stdMap.end(), myMap.begin() != myMap.end());

  std::map<bool, bool>::iterator stdIt = stdMap.begin();
  mycontainers::MyMap<bool, bool>::iterator myIt = myMap.begin();
  for (; stdIt != stdMap.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(stdIt->first, myIt->first);
    EXPECT_EQ(stdIt->second, myIt->second);
  }
}

TEST(MapTest, TestMapStringIterator) {
  std::initializer_list<std::pair<const std::string, std::string>> items{
      {"A+-8/", "2.2"}, {"b\",%", "4.3"}, {"5.999", "6.0"}};
  std::map<std::string, std::string> stdMap(items);
  mycontainers::MyMap<std::string, std::string> myMap(items);

  EXPECT_EQ(stdMap.size(), myMap.size());
  EXPECT_EQ(stdMap.empty(), myMap.empty());

  EXPECT_EQ(stdMap.begin()->first, myMap.begin()->first);
  EXPECT_EQ(stdMap.begin()->second, myMap.begin()->second);

  EXPECT_EQ(stdMap.begin() == stdMap.begin(), myMap.begin() == myMap.begin());
  EXPECT_EQ(stdMap.begin() != stdMap.begin(), myMap.begin() != myMap.begin());

  EXPECT_EQ(stdMap.end() == stdMap.end(), myMap.end() == myMap.end());
  EXPECT_EQ(stdMap.end() != stdMap.end(), myMap.end() != myMap.end());

  EXPECT_EQ(stdMap.begin() == stdMap.end(), myMap.begin() == myMap.end());
  EXPECT_EQ(stdMap.begin() != stdMap.end(), myMap.begin() != myMap.end());

  std::map<std::string, std::string>::iterator stdIt = stdMap.begin();
  mycontainers::MyMap<std::string, std::string>::iterator myIt = myMap.begin();
  for (; stdIt != stdMap.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(stdIt->first, myIt->first);
    EXPECT_EQ(stdIt->second, myIt->second);
  }
}