#include "../my_set.h"
#include "gtest/gtest.h"

class SetTest1 : public testing::Test {
 protected:
  void TearDown() override {
    EXPECT_EQ(stdSet.size(), mySet.size());
    EXPECT_EQ(stdSet.max_size(), mySet.max_size());
    EXPECT_EQ(stdSet.empty(), mySet.empty());

    EXPECT_EQ(*stdSet.begin(), *mySet.begin());
    EXPECT_EQ(*stdSet.end(), *mySet.end());

    std::set<int>::iterator stdIt = stdSet.begin();
    mycontainers::MySet<int>::iterator myIt = mySet.begin();
    for (; stdIt != stdSet.end(); ++stdIt, ++myIt) {
      EXPECT_EQ(*stdIt, *myIt);
    }
  }

  std::set<int> stdSet;
  mycontainers::MySet<int> mySet;
};

TEST_F(SetTest1, TestSetIntDefault) {
  EXPECT_TRUE(stdSet.empty());
  EXPECT_TRUE(mySet.empty());
}

TEST_F(SetTest1, TestSetIntInitList) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::set<int> stdSet1(items);
  mycontainers::MySet<int> mySet1(items);

  stdSet = stdSet1;
  mySet = mySet1;
}

TEST_F(SetTest1, TestSetIntCopy) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::set<int> stdSet1(items);
  mycontainers::MySet<int> mySet1(items);

  std::set<int> stdSet2(stdSet1);
  mycontainers::MySet<int> mySet2(mySet1);

  stdSet = stdSet2;
  mySet = mySet2;

  EXPECT_EQ(stdSet1.size(), mySet1.size());
  EXPECT_EQ(stdSet1.max_size(), mySet1.max_size());
  EXPECT_EQ(stdSet1.empty(), mySet1.empty());
  EXPECT_EQ(*stdSet1.begin(), *mySet1.begin());
  EXPECT_EQ(*stdSet1.end(), *mySet1.end());
}

TEST_F(SetTest1, TestSetIntMove) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::set<int> stdSet1(items);
  mycontainers::MySet<int> mySet1(items);

  std::set<int> stdSet2(std::move(stdSet1));
  mycontainers::MySet<int> mySet2(std::move(mySet1));

  stdSet = stdSet2;
  mySet = mySet2;

  EXPECT_EQ(stdSet1.size(), mySet1.size());
  EXPECT_EQ(stdSet1.max_size(), mySet1.max_size());
  EXPECT_EQ(stdSet1.empty(), mySet1.empty());
  EXPECT_EQ(*stdSet1.begin(), *mySet1.begin());
  EXPECT_EQ(*stdSet1.end(), *mySet1.end());
}

TEST_F(SetTest1, TestSetIntCopyOp) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::set<int> stdSet1(items);
  mycontainers::MySet<int> mySet1(items);

  stdSet = stdSet1;
  mySet = mySet1;

  EXPECT_EQ(stdSet1.size(), mySet1.size());
  EXPECT_EQ(stdSet1.max_size(), mySet1.max_size());
  EXPECT_EQ(stdSet1.empty(), mySet1.empty());
  EXPECT_EQ(*stdSet1.begin(), *mySet1.begin());
  EXPECT_EQ(*stdSet1.end(), *mySet1.end());
}

TEST_F(SetTest1, TestSetIntMoveOp) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::set<int> stdSet1(items);
  mycontainers::MySet<int> mySet1(items);

  stdSet = std::move(stdSet1);
  mySet = std::move(mySet1);

  EXPECT_EQ(stdSet1.size(), mySet1.size());
  EXPECT_EQ(stdSet1.max_size(), mySet1.max_size());
  EXPECT_EQ(stdSet1.empty(), mySet1.empty());
  EXPECT_EQ(*stdSet1.begin(), *mySet1.begin());
  EXPECT_EQ(*stdSet1.end(), *mySet1.end());
}

TEST_F(SetTest1, TestSetIntViewing) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::set<int> stdSet1(items);
  mycontainers::MySet<int> mySet1(items);

  stdSet = stdSet1;
  mySet = mySet1;

  for (auto &i : items) {
    EXPECT_EQ(stdSet.count(i), mySet.contains(i));
    EXPECT_EQ(*stdSet.find(i), *mySet.find(i));
  }

  EXPECT_EQ(stdSet.count(11111), mySet.contains(11111));
  EXPECT_EQ(*stdSet.find(11111), *mySet.find(11111));
}

TEST_F(SetTest1, TestSetIntClear) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::set<int> stdSet1(items);
  mycontainers::MySet<int> mySet1(items);

  stdSet = stdSet1;
  mySet = mySet1;

  stdSet.clear();
  mySet.clear();
}

TEST_F(SetTest1, TestSetIntInsert1) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::set<int> stdSet1(items);
  mycontainers::MySet<int> mySet1(items);

  stdSet = stdSet1;
  mySet = mySet1;

  std::pair<std::set<int>::iterator, bool> stdResult;
  std::pair<mycontainers::MySet<int>::iterator, bool> myResult;

  for (int i = 0; i < 100; i++) {
    stdResult = stdSet.insert(i);
    myResult = mySet.insert(i);

    EXPECT_EQ(stdResult.second, myResult.second);
    EXPECT_EQ(*stdResult.first, *myResult.first);
  }
}

TEST_F(SetTest1, TestSetIntInsert2) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::set<int> stdSet1(items);
  mycontainers::MySet<int> mySet1(items);

  stdSet = stdSet1;
  mySet = mySet1;

  std::pair<std::set<int>::iterator, bool> stdResult;
  std::pair<mycontainers::MySet<int>::iterator, bool> myResult;

  for (int i = 100; i > 0; i--) {
    stdResult = stdSet.insert(i);
    myResult = mySet.insert(i);

    EXPECT_EQ(stdResult.second, myResult.second);
    EXPECT_EQ(*stdResult.first, *myResult.first);
  }
}

TEST_F(SetTest1, TestSetIntInsert3) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::set<int> stdSet1(items);
  mycontainers::MySet<int> mySet1(items);

  stdSet = stdSet1;
  mySet = mySet1;

  auto stdResult = stdSet.insert(66);
  auto myResult = mySet.insert(66);

  EXPECT_EQ(stdResult.second, myResult.second);
  EXPECT_EQ(*stdResult.first, *myResult.first);
}

TEST_F(SetTest1, TestSetIntInsert4) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::set<int> stdSet1(items);
  mycontainers::MySet<int> mySet1(items);

  stdSet = stdSet1;
  mySet = mySet1;

  auto stdResult = stdSet.insert(7);
  auto myResult = mySet.insert(7);
  EXPECT_EQ(stdResult.second, myResult.second);
  EXPECT_EQ(*stdResult.first, *myResult.first);
}

TEST_F(SetTest1, TestSetIntInsertMany) {
  std::initializer_list<int> items{3, 2, 5, 5, 5, 7, 9, 7, 12};
  std::set<int> stdSet1(items);

  mycontainers::MySet<int> mySet1;

  stdSet = stdSet1;
  mySet = mySet1;

  auto myResult = mySet.insert_many(3, 2, 5, 5);
  auto myResult1 = mySet.insert_many(5, 7, 9, 7, 12);

  EXPECT_EQ(4, myResult.size());

  EXPECT_EQ(true, myResult[0].second);
  EXPECT_EQ(3, *(myResult[0].first));

  EXPECT_EQ(true, myResult[1].second);
  EXPECT_EQ(2, *(myResult[1].first));

  EXPECT_EQ(true, myResult[2].second);
  EXPECT_EQ(5, *(myResult[2].first));

  EXPECT_EQ(false, myResult[3].second);

  EXPECT_EQ(5, myResult1.size());

  EXPECT_EQ(false, myResult1[0].second);

  EXPECT_EQ(true, myResult1[1].second);
  EXPECT_EQ(7, *(myResult1[1].first));

  EXPECT_EQ(true, myResult1[2].second);
  EXPECT_EQ(9, *(myResult1[2].first));

  EXPECT_EQ(false, myResult1[3].second);

  EXPECT_EQ(true, myResult1[4].second);
  EXPECT_EQ(12, *(myResult1[4].first));
}

TEST_F(SetTest1, TestSetIntErase1) {
  for (int i = 10; i <= 100; i += 10) {
    stdSet.insert(i);
    mySet.insert(i);
  }

  stdSet.erase(stdSet.find(80));
  mySet.erase(mySet.find(80));
}

TEST_F(SetTest1, TestSetIntErase2) {
  for (int i = 100; i >= 10; i -= 10) {
    stdSet.insert(i);
    mySet.insert(i);
  }

  stdSet.erase(stdSet.find(20));
  mySet.erase(mySet.find(20));
}

TEST_F(SetTest1, TestSetIntErase3) {
  for (int i = 100; i >= 10; i -= 10) {
    stdSet.insert(i);
    mySet.insert(i);
  }
  stdSet.insert(35);
  mySet.insert(35);

  stdSet.erase(stdSet.find(50));
  mySet.erase(mySet.find(50));
}

TEST_F(SetTest1, TestSetIntErase4) {
  for (int i = 100; i >= 10; i -= 10) {
    stdSet.insert(i);
    mySet.insert(i);
  }

  stdSet.erase(stdSet.find(60));
  mySet.erase(mySet.find(60));
}

TEST_F(SetTest1, TestSetIntErase5) {
  for (int i = 10; i <= 100; i += 10) {
    stdSet.insert(i);
    mySet.insert(i);
  }

  stdSet.erase(stdSet.find(50));
  mySet.erase(mySet.find(50));
}

TEST_F(SetTest1, TestSetIntErase6) {
  for (int i = 10; i <= 90; i += 10) {
    stdSet.insert(i);
    mySet.insert(i);
  }
  stdSet.insert(85);
  mySet.insert(85);

  stdSet.erase(stdSet.find(70));
  mySet.erase(mySet.find(70));
}

TEST_F(SetTest1, TestSetIntErase7) {
  for (int i = 100; i >= 20; i -= 10) {
    stdSet.insert(i);
    mySet.insert(i);
  }
  stdSet.insert(25);
  mySet.insert(25);

  stdSet.erase(stdSet.find(40));
  mySet.erase(mySet.find(40));
}

TEST_F(SetTest1, TestSetIntSwap) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::set<int> stdSet2(items);
  mycontainers::MySet<int> mySet2(items);

  stdSet = stdSet2;
  mySet = mySet2;

  items = {10, 10000, 1000, 100, -10};
  std::set<int> stdSet1(items);
  mycontainers::MySet<int> mySet1(items);

  stdSet.swap(stdSet1);
  mySet.swap(mySet1);

  EXPECT_EQ(stdSet1.size(), mySet1.size());
  EXPECT_EQ(stdSet1.max_size(), mySet1.max_size());
  EXPECT_EQ(stdSet1.empty(), mySet1.empty());
  EXPECT_EQ(*stdSet1.begin(), *mySet1.begin());
  EXPECT_EQ(*stdSet1.end(), *mySet1.end());
}

TEST_F(SetTest1, TestSetIntMerge1) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::set<int> stdSet2(items);
  mycontainers::MySet<int> mySet2(items);

  stdSet = stdSet2;
  mySet = mySet2;

  items = {10, 5, 10000, -1000, 12, -10, 100, 7};
  std::set<int> stdSet1(items);
  mycontainers::MySet<int> mySet1(items);

  stdSet.merge(stdSet1);
  mySet.merge(mySet1);

  EXPECT_EQ(stdSet1.size(), mySet1.size());
  EXPECT_EQ(stdSet1.max_size(), mySet1.max_size());
  EXPECT_EQ(stdSet1.empty(), mySet1.empty());
  EXPECT_EQ(*stdSet1.begin(), *mySet1.begin());
  EXPECT_EQ(*stdSet1.end(), *mySet1.end());
}

TEST_F(SetTest1, TestSetIntMerge2) {
  EXPECT_TRUE(stdSet.empty());
  EXPECT_TRUE(mySet.empty());

  std::initializer_list<int> items = {10, 5, 10000, -1000, 12, -10, 100, 7};
  std::set<int> stdSet1(items);
  mycontainers::MySet<int> mySet1(items);

  stdSet.merge(stdSet1);
  mySet.merge(mySet1);

  EXPECT_EQ(stdSet1.size(), mySet1.size());
  EXPECT_EQ(stdSet1.max_size(), mySet1.max_size());
  EXPECT_EQ(stdSet1.empty(), mySet1.empty());
  EXPECT_EQ(*stdSet1.begin(), *mySet1.begin());
  EXPECT_EQ(*stdSet1.end(), *mySet1.end());
}

TEST_F(SetTest1, TestSetIntMerge3) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::set<int> stdSet2(items);
  mycontainers::MySet<int> mySet2(items);

  stdSet = stdSet2;
  mySet = mySet2;

  std::set<int> stdSet1;
  mycontainers::MySet<int> mySet1;

  stdSet.merge(stdSet1);
  mySet.merge(mySet1);

  EXPECT_EQ(stdSet1.size(), mySet1.size());
  EXPECT_EQ(stdSet1.max_size(), mySet1.max_size());
  EXPECT_EQ(stdSet1.empty(), mySet1.empty());
  EXPECT_EQ(*stdSet1.begin(), *mySet1.begin());
  EXPECT_EQ(*stdSet1.end(), *mySet1.end());
}

TEST(SetTest, TestSetIntConst) {
  std::initializer_list<int> items{3, 2, 5, 3, 7, 9, 12};
  const std::set<int> stdSet(items);
  const mycontainers::MySet<int> mySet(items);

  EXPECT_EQ(stdSet.size(), mySet.size());
  EXPECT_EQ(stdSet.max_size(), mySet.max_size());
  EXPECT_EQ(stdSet.empty(), mySet.empty());

  for (auto &i : items) {
    EXPECT_EQ(stdSet.count(i), mySet.contains(i));
    EXPECT_EQ(*stdSet.find(i), *mySet.find(i));
  }

  EXPECT_EQ(stdSet.count(11111), mySet.contains(11111));
  EXPECT_EQ(*stdSet.find(11111), *mySet.find(11111));

  EXPECT_EQ(*stdSet.begin(), *mySet.begin());
  EXPECT_EQ(*stdSet.end(), *mySet.end());

  EXPECT_EQ(stdSet.begin() == stdSet.end(), mySet.begin() == mySet.end());
  EXPECT_EQ(stdSet.begin() != stdSet.end(), mySet.begin() != mySet.end());

  std::set<int>::iterator stdIt = stdSet.begin();
  mycontainers::MySet<int>::iterator myIt = mySet.begin();
  for (; stdIt != stdSet.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(*stdIt, *myIt);
  }

  stdIt = stdSet.end();
  myIt = mySet.end();
  while (stdIt != stdSet.begin()) {
    --stdIt;
    --myIt;
    EXPECT_EQ(*stdIt, *myIt);
  }
}

TEST(SetTest, TestSetIntIterator) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::set<int> stdSet(items);
  mycontainers::MySet<int> mySet(items);

  EXPECT_EQ(*stdSet.begin(), *mySet.begin());
  EXPECT_EQ(*stdSet.end(), *mySet.end());

  EXPECT_EQ(stdSet.begin() == stdSet.begin(), mySet.begin() == mySet.begin());
  EXPECT_EQ(stdSet.begin() != stdSet.begin(), mySet.begin() != mySet.begin());

  EXPECT_EQ(stdSet.end() == stdSet.end(), mySet.end() == mySet.end());
  EXPECT_EQ(stdSet.end() != stdSet.end(), mySet.end() != mySet.end());

  EXPECT_EQ(stdSet.begin() == stdSet.end(), mySet.begin() == mySet.end());
  EXPECT_EQ(stdSet.begin() != stdSet.end(), mySet.begin() != mySet.end());

  std::set<int>::iterator stdIt = stdSet.begin();
  mycontainers::MySet<int>::iterator myIt = mySet.begin();
  for (; stdIt != stdSet.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(*stdIt, *myIt);
  }

  stdIt = stdSet.end();
  myIt = mySet.end();
  while (stdIt != stdSet.begin()) {
    --stdIt;
    --myIt;
    EXPECT_EQ(*stdIt, *myIt);
  }

  std::set<int>::iterator stdIt1(stdIt);
  mycontainers::MySet<int>::iterator myIt1(myIt);
  EXPECT_EQ(*stdIt1, *myIt1);
  EXPECT_EQ(*stdIt, *myIt);

  std::set<int>::iterator stdIt2(std::move(stdIt));
  mycontainers::MySet<int>::iterator myIt2(std::move(myIt));
  EXPECT_EQ(*stdIt2, *myIt2);
  EXPECT_EQ(*stdIt, *myIt);

  std::set<int>::iterator stdIt3;
  stdIt3 = stdIt2;
  mycontainers::MySet<int>::iterator myIt3;
  myIt3 = myIt2;

  EXPECT_EQ(*stdIt3, *myIt3);
  EXPECT_EQ(*stdIt2, *myIt2);

  std::set<int>::iterator stdIt4;
  stdIt4 = std::move(stdIt2);
  mycontainers::MySet<int>::iterator myIt4;
  myIt4 = std::move(myIt2);

  EXPECT_EQ(*stdIt4, *myIt4);
  EXPECT_EQ(*stdIt2, *myIt2);
}

TEST(SetTest, TestSetDoubleIterator) {
  std::initializer_list<double> items{3.3, 2.2, 5.7, 7.5, 9.999, 12.0, 2.2};
  std::set<double> stdSet(items);
  mycontainers::MySet<double> mySet(items);

  EXPECT_EQ(stdSet.size(), mySet.size());
  EXPECT_EQ(stdSet.max_size(), mySet.max_size());
  EXPECT_EQ(stdSet.empty(), mySet.empty());

  EXPECT_EQ(*stdSet.begin(), *mySet.begin());

  EXPECT_EQ(stdSet.begin() == stdSet.begin(), mySet.begin() == mySet.begin());
  EXPECT_EQ(stdSet.begin() != stdSet.begin(), mySet.begin() != mySet.begin());

  EXPECT_EQ(stdSet.end() == stdSet.end(), mySet.end() == mySet.end());
  EXPECT_EQ(stdSet.end() != stdSet.end(), mySet.end() != mySet.end());

  EXPECT_EQ(stdSet.begin() == stdSet.end(), mySet.begin() == mySet.end());
  EXPECT_EQ(stdSet.begin() != stdSet.end(), mySet.begin() != mySet.end());

  std::set<double>::iterator stdIt = stdSet.begin();
  mycontainers::MySet<double>::iterator myIt = mySet.begin();
  for (; stdIt != stdSet.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(*stdIt, *myIt);
  }
}

TEST(SetTest, TestSetCharIterator) {
  std::initializer_list<char> items{'a', 'B', '.', 0, '7', '/', 77, '.'};
  std::set<char> stdSet(items);
  mycontainers::MySet<char> mySet(items);

  EXPECT_EQ(stdSet.size(), mySet.size());
  EXPECT_EQ(stdSet.max_size(), mySet.max_size());
  EXPECT_EQ(stdSet.empty(), mySet.empty());

  EXPECT_EQ(*stdSet.begin(), *mySet.begin());

  EXPECT_EQ(stdSet.begin() == stdSet.begin(), mySet.begin() == mySet.begin());
  EXPECT_EQ(stdSet.begin() != stdSet.begin(), mySet.begin() != mySet.begin());

  EXPECT_EQ(stdSet.end() == stdSet.end(), mySet.end() == mySet.end());
  EXPECT_EQ(stdSet.end() != stdSet.end(), mySet.end() != mySet.end());

  EXPECT_EQ(stdSet.begin() == stdSet.end(), mySet.begin() == mySet.end());
  EXPECT_EQ(stdSet.begin() != stdSet.end(), mySet.begin() != mySet.end());

  std::set<char>::iterator stdIt = stdSet.begin();
  mycontainers::MySet<char>::iterator myIt = mySet.begin();
  for (; stdIt != stdSet.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(*stdIt, *myIt);
  }
}

TEST(SetTest, TestSetBoolIterator) {
  std::initializer_list<bool> items{true, true, false, true, false, false};
  std::set<bool> stdSet(items);
  mycontainers::MySet<bool> mySet(items);

  EXPECT_EQ(stdSet.size(), mySet.size());
  EXPECT_EQ(stdSet.max_size(), mySet.max_size());
  EXPECT_EQ(stdSet.empty(), mySet.empty());

  EXPECT_EQ(*stdSet.begin(), *mySet.begin());

  EXPECT_EQ(stdSet.begin() == stdSet.begin(), mySet.begin() == mySet.begin());
  EXPECT_EQ(stdSet.begin() != stdSet.begin(), mySet.begin() != mySet.begin());

  EXPECT_EQ(stdSet.end() == stdSet.end(), mySet.end() == mySet.end());
  EXPECT_EQ(stdSet.end() != stdSet.end(), mySet.end() != mySet.end());

  EXPECT_EQ(stdSet.begin() == stdSet.end(), mySet.begin() == mySet.end());
  EXPECT_EQ(stdSet.begin() != stdSet.end(), mySet.begin() != mySet.end());

  std::set<bool>::iterator stdIt = stdSet.begin();
  mycontainers::MySet<bool>::iterator myIt = mySet.begin();
  for (; stdIt != stdSet.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(*stdIt, *myIt);
  }
}

TEST(SetTest, TestSetStringIterator) {
  std::initializer_list<std::string> items{"aB", ".0", "7/*+-", "77", "aB"};
  std::set<std::string> stdSet(items);
  mycontainers::MySet<std::string> mySet(items);

  EXPECT_EQ(stdSet.size(), mySet.size());
  EXPECT_EQ(stdSet.empty(), mySet.empty());

  EXPECT_EQ(*stdSet.begin(), *mySet.begin());

  EXPECT_EQ(stdSet.begin() == stdSet.begin(), mySet.begin() == mySet.begin());
  EXPECT_EQ(stdSet.begin() != stdSet.begin(), mySet.begin() != mySet.begin());

  EXPECT_EQ(stdSet.end() == stdSet.end(), mySet.end() == mySet.end());
  EXPECT_EQ(stdSet.end() != stdSet.end(), mySet.end() != mySet.end());

  EXPECT_EQ(stdSet.begin() == stdSet.end(), mySet.begin() == mySet.end());
  EXPECT_EQ(stdSet.begin() != stdSet.end(), mySet.begin() != mySet.end());

  std::set<std::string>::iterator stdIt = stdSet.begin();
  mycontainers::MySet<std::string>::iterator myIt = mySet.begin();
  for (; stdIt != stdSet.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(*stdIt, *myIt);
  }
}
