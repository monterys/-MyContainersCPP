#include "../my_multiset.h"
#include "gtest/gtest.h"

class MultisetTest1 : public testing::Test {
 protected:
  void TearDown() override {
    EXPECT_EQ(stdMultiset.size(), myMultiset.size());
    EXPECT_EQ(stdMultiset.max_size(), myMultiset.max_size());
    EXPECT_EQ(stdMultiset.empty(), myMultiset.empty());

    EXPECT_EQ(*stdMultiset.begin(), *myMultiset.begin());
    EXPECT_EQ(*stdMultiset.end(), *myMultiset.end());

    std::multiset<int>::iterator stdIt = stdMultiset.begin();
    mycontainers::MyMultiset<int>::iterator myIt = myMultiset.begin();
    for (; stdIt != stdMultiset.end(); ++stdIt, ++myIt) {
      EXPECT_EQ(*stdIt, *myIt);
    }
  }

  std::multiset<int> stdMultiset;
  mycontainers::MyMultiset<int> myMultiset;
};

TEST_F(MultisetTest1, TestMultisetIntDefault) {
  EXPECT_TRUE(stdMultiset.empty());
  EXPECT_TRUE(myMultiset.empty());
}

TEST_F(MultisetTest1, TestMultisetIntInitList) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  stdMultiset = stdMultiset1;
  myMultiset = myMultiset1;
}

TEST_F(MultisetTest1, TestMultisetIntCopy) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  std::multiset<int> stdMultiset2(stdMultiset1);
  mycontainers::MyMultiset<int> myMultiset2(myMultiset1);

  stdMultiset = stdMultiset2;
  myMultiset = myMultiset2;

  EXPECT_EQ(stdMultiset1.size(), myMultiset1.size());
  EXPECT_EQ(stdMultiset1.max_size(), myMultiset1.max_size());
  EXPECT_EQ(stdMultiset1.empty(), myMultiset1.empty());
  EXPECT_EQ(*stdMultiset1.begin(), *myMultiset1.begin());
  EXPECT_EQ(*stdMultiset1.end(), *myMultiset1.end());
}

TEST_F(MultisetTest1, TestMultisetIntMove) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  std::multiset<int> stdMultiset2(std::move(stdMultiset1));
  mycontainers::MyMultiset<int> myMultiset2(std::move(myMultiset1));

  stdMultiset = stdMultiset2;
  myMultiset = myMultiset2;

  EXPECT_EQ(stdMultiset1.size(), myMultiset1.size());
  EXPECT_EQ(stdMultiset1.max_size(), myMultiset1.max_size());
  EXPECT_EQ(stdMultiset1.empty(), myMultiset1.empty());
  EXPECT_EQ(*stdMultiset1.begin(), *myMultiset1.begin());
  EXPECT_EQ(*stdMultiset1.end(), *myMultiset1.end());
}

TEST_F(MultisetTest1, TestMultisetIntCopyOp) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  stdMultiset = stdMultiset1;
  myMultiset = myMultiset1;

  EXPECT_EQ(stdMultiset1.size(), myMultiset1.size());
  EXPECT_EQ(stdMultiset1.max_size(), myMultiset1.max_size());
  EXPECT_EQ(stdMultiset1.empty(), myMultiset1.empty());
  EXPECT_EQ(*stdMultiset1.begin(), *myMultiset1.begin());
  EXPECT_EQ(*stdMultiset1.end(), *myMultiset1.end());
}

TEST_F(MultisetTest1, TestMultisetIntMoveOp) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  stdMultiset = std::move(stdMultiset1);
  myMultiset = std::move(myMultiset1);

  EXPECT_EQ(stdMultiset1.size(), myMultiset1.size());
  EXPECT_EQ(stdMultiset1.max_size(), myMultiset1.max_size());
  EXPECT_EQ(stdMultiset1.empty(), myMultiset1.empty());
  EXPECT_EQ(*stdMultiset1.begin(), *myMultiset1.begin());
  EXPECT_EQ(*stdMultiset1.end(), *myMultiset1.end());
}

TEST_F(MultisetTest1, TestMultisetIntViewing) {
  std::initializer_list<int> items{3, 2, 5, 3, 12, 5, 5, 7, 9, 12};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  stdMultiset = stdMultiset1;
  myMultiset = myMultiset1;

  EXPECT_EQ(stdMultiset.count(11111), myMultiset.contains(11111));
  EXPECT_EQ(*stdMultiset.find(11111), *myMultiset.find(11111));
  EXPECT_EQ(stdMultiset.count(11111), myMultiset.count(11111));

  for (auto &i : items) {
    EXPECT_EQ(stdMultiset.count(i) > 0, myMultiset.contains(i));
    EXPECT_EQ(*stdMultiset.find(i), *myMultiset.find(i));
    EXPECT_EQ(stdMultiset.count(i), myMultiset.count(i));
    EXPECT_EQ(*stdMultiset.lower_bound(i), *myMultiset.lower_bound(i));
    EXPECT_EQ(*stdMultiset.upper_bound(i), *myMultiset.upper_bound(i));
  }

  EXPECT_EQ(*stdMultiset.lower_bound(-10), *myMultiset.lower_bound(-10));
  EXPECT_EQ(*stdMultiset.lower_bound(8), *myMultiset.lower_bound(8));
  EXPECT_EQ(*stdMultiset.lower_bound(10), *myMultiset.lower_bound(10));
  EXPECT_EQ(*stdMultiset.lower_bound(100), *myMultiset.lower_bound(100));

  EXPECT_EQ(*stdMultiset.upper_bound(-10), *myMultiset.upper_bound(-10));
  EXPECT_EQ(*stdMultiset.upper_bound(8), *myMultiset.upper_bound(8));
  EXPECT_EQ(*stdMultiset.upper_bound(10), *myMultiset.upper_bound(10));
  EXPECT_EQ(*stdMultiset.upper_bound(100), *myMultiset.upper_bound(100));

  for (auto &i : items) {
    auto stdResult = stdMultiset.equal_range(i);
    auto myResult = myMultiset.equal_range(i);

    for (; stdResult.first != stdResult.second;
         ++stdResult.first, ++myResult.first) {
      EXPECT_EQ(*stdResult.first, *myResult.first);
    }
  }
}

TEST_F(MultisetTest1, TestMultisetIntClear) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  stdMultiset = stdMultiset1;
  myMultiset = myMultiset1;

  stdMultiset.clear();
  myMultiset.clear();
}

TEST_F(MultisetTest1, TestMultisetIntInsert1) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  stdMultiset = stdMultiset1;
  myMultiset = myMultiset1;

  auto stdResult = stdMultiset.insert(6);
  auto myResult = myMultiset.insert(6);

  EXPECT_EQ(*stdResult, *myResult);
}

TEST_F(MultisetTest1, TestMultisetIntInsert2) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  stdMultiset = stdMultiset1;
  myMultiset = myMultiset1;

  auto stdResult = stdMultiset.insert(-6);
  auto myResult = myMultiset.insert(-6);

  EXPECT_EQ(*stdResult, *myResult);
}

TEST_F(MultisetTest1, TestMultisetIntInsert3) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  stdMultiset = stdMultiset1;
  myMultiset = myMultiset1;

  auto stdResult = stdMultiset.insert(66);
  auto myResult = myMultiset.insert(66);

  EXPECT_EQ(*stdResult, *myResult);
}

TEST_F(MultisetTest1, TestMultisetIntInsert4) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  stdMultiset = stdMultiset1;
  myMultiset = myMultiset1;

  auto stdResult = stdMultiset.insert(6);
  auto myResult = myMultiset.insert(6);

  EXPECT_EQ(*stdResult, *myResult);
}

TEST_F(MultisetTest1, TestMultisetIntInsertMany) {
  std::initializer_list<int> items{3, 2, 5, 5, 5, 7, 9, 7, 12};
  std::multiset<int> stdMultiset1(items);

  mycontainers::MyMultiset<int> myMultiset1;

  stdMultiset = stdMultiset1;
  myMultiset = myMultiset1;

  auto myResult = myMultiset.insert_many(3, 2, 5, 5);
  auto myResult1 = myMultiset.insert_many(5, 7, 9, 7, 12);

  EXPECT_EQ(4, myResult.size());

  EXPECT_EQ(true, myResult[0].second);
  EXPECT_EQ(3, *(myResult[0].first));

  EXPECT_EQ(true, myResult[1].second);
  EXPECT_EQ(2, *(myResult[1].first));

  EXPECT_EQ(true, myResult[2].second);
  EXPECT_EQ(5, *(myResult[2].first));

  EXPECT_EQ(true, myResult[3].second);
  EXPECT_EQ(5, *(myResult[3].first));

  EXPECT_EQ(5, myResult1.size());

  EXPECT_EQ(true, myResult1[0].second);
  EXPECT_EQ(5, *(myResult1[0].first));

  EXPECT_EQ(true, myResult1[1].second);
  EXPECT_EQ(7, *(myResult1[1].first));

  EXPECT_EQ(true, myResult1[2].second);
  EXPECT_EQ(9, *(myResult1[2].first));

  EXPECT_EQ(true, myResult1[3].second);
  EXPECT_EQ(7, *(myResult1[3].first));

  EXPECT_EQ(true, myResult1[4].second);
  EXPECT_EQ(12, *(myResult1[4].first));
}

TEST_F(MultisetTest1, TestMultisetIntErase1) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  stdMultiset = stdMultiset1;
  myMultiset = myMultiset1;

  stdMultiset.erase(stdMultiset.find(5));
  myMultiset.erase(myMultiset.find(5));
}

TEST_F(MultisetTest1, TestMultisetIntErase2) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  stdMultiset = stdMultiset1;
  myMultiset = myMultiset1;

  stdMultiset.erase(stdMultiset.find(12));
  myMultiset.erase(myMultiset.find(12));
}

TEST_F(MultisetTest1, TestMultisetIntErase3) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12, 5, 3, 5};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  EXPECT_EQ(stdMultiset1.size(), myMultiset1.size());

  stdMultiset = stdMultiset1;
  myMultiset = myMultiset1;

  stdMultiset.erase(stdMultiset.find(2));
  myMultiset.erase(myMultiset.find(2));
}

TEST_F(MultisetTest1, TestMultisetIntSwap) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset2(items);
  mycontainers::MyMultiset<int> myMultiset2(items);

  stdMultiset = stdMultiset2;
  myMultiset = myMultiset2;

  items = {10, 10000, 1000, 100, -10};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  stdMultiset.swap(stdMultiset1);
  myMultiset.swap(myMultiset1);

  EXPECT_EQ(stdMultiset1.size(), myMultiset1.size());
  EXPECT_EQ(stdMultiset1.max_size(), myMultiset1.max_size());
  EXPECT_EQ(stdMultiset1.empty(), myMultiset1.empty());
  EXPECT_EQ(*stdMultiset1.begin(), *myMultiset1.begin());
  EXPECT_EQ(*stdMultiset1.end(), *myMultiset1.end());
}

TEST_F(MultisetTest1, TestMultisetIntMerge1) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset2(items);
  mycontainers::MyMultiset<int> myMultiset2(items);

  stdMultiset = stdMultiset2;
  myMultiset = myMultiset2;

  items = {10, 5, 10000, -1000, 12, -10, 100, 7};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  stdMultiset.merge(stdMultiset1);
  myMultiset.merge(myMultiset1);

  EXPECT_EQ(stdMultiset1.size(), myMultiset1.size());
  EXPECT_EQ(stdMultiset1.max_size(), myMultiset1.max_size());
  EXPECT_EQ(stdMultiset1.empty(), myMultiset1.empty());
  EXPECT_EQ(*stdMultiset1.begin(), *myMultiset1.begin());
  EXPECT_EQ(*stdMultiset1.end(), *myMultiset1.end());
}

TEST_F(MultisetTest1, TestMultisetIntMerge2) {
  EXPECT_TRUE(stdMultiset.empty());
  EXPECT_TRUE(myMultiset.empty());

  std::initializer_list<int> items = {10, 5, 10000, -1000, 12, -10, 100, 7};
  std::multiset<int> stdMultiset1(items);
  mycontainers::MyMultiset<int> myMultiset1(items);

  stdMultiset.merge(stdMultiset1);
  myMultiset.merge(myMultiset1);

  EXPECT_EQ(stdMultiset1.size(), myMultiset1.size());
  EXPECT_EQ(stdMultiset1.max_size(), myMultiset1.max_size());
  EXPECT_EQ(stdMultiset1.empty(), myMultiset1.empty());
  EXPECT_EQ(*stdMultiset1.begin(), *myMultiset1.begin());
  EXPECT_EQ(*stdMultiset1.end(), *myMultiset1.end());
}

TEST_F(MultisetTest1, TestMultisetIntMerge3) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset2(items);
  mycontainers::MyMultiset<int> myMultiset2(items);

  stdMultiset = stdMultiset2;
  myMultiset = myMultiset2;

  std::multiset<int> stdMultiset1;
  mycontainers::MyMultiset<int> myMultiset1;

  stdMultiset.merge(stdMultiset1);
  myMultiset.merge(myMultiset1);

  EXPECT_EQ(stdMultiset1.size(), myMultiset1.size());
  EXPECT_EQ(stdMultiset1.max_size(), myMultiset1.max_size());
  EXPECT_EQ(stdMultiset1.empty(), myMultiset1.empty());
  EXPECT_EQ(*stdMultiset1.begin(), *myMultiset1.begin());
  EXPECT_EQ(*stdMultiset1.end(), *myMultiset1.end());
}

TEST(MultisetTest, TestMultisetIntConst) {
  std::initializer_list<int> items{3, 2, 5, 3, 7, 9, 12};
  const std::multiset<int> stdMultiset(items);
  const mycontainers::MyMultiset<int> myMultiset(items);

  EXPECT_EQ(stdMultiset.size(), myMultiset.size());
  EXPECT_EQ(stdMultiset.max_size(), myMultiset.max_size());
  EXPECT_EQ(stdMultiset.empty(), myMultiset.empty());

  for (auto &i : items) {
    EXPECT_EQ(stdMultiset.count(i) > 0, myMultiset.contains(i));
    EXPECT_EQ(*stdMultiset.find(i), *myMultiset.find(i));
    EXPECT_EQ(stdMultiset.count(i), myMultiset.count(i));
    EXPECT_EQ(*stdMultiset.lower_bound(i), *myMultiset.lower_bound(i));
    EXPECT_EQ(*stdMultiset.upper_bound(i), *myMultiset.upper_bound(i));

    auto stdResult = stdMultiset.equal_range(i);
    auto myResult = myMultiset.equal_range(i);

    for (; stdResult.first != stdResult.second;
         ++stdResult.first, ++myResult.first) {
      EXPECT_EQ(*stdResult.first, *myResult.first);
    }
  }

  EXPECT_EQ(stdMultiset.count(11111), myMultiset.contains(11111));
  EXPECT_EQ(*stdMultiset.find(11111), *myMultiset.find(11111));

  EXPECT_EQ(*stdMultiset.begin(), *myMultiset.begin());
  EXPECT_EQ(*stdMultiset.end(), *myMultiset.end());

  EXPECT_EQ(stdMultiset.begin() == stdMultiset.end(),
            myMultiset.begin() == myMultiset.end());
  EXPECT_EQ(stdMultiset.begin() != stdMultiset.end(),
            myMultiset.begin() != myMultiset.end());

  std::multiset<int>::iterator stdIt = stdMultiset.begin();
  mycontainers::MyMultiset<int>::iterator myIt = myMultiset.begin();
  for (; stdIt != stdMultiset.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(*stdIt, *myIt);
  }

  stdIt = stdMultiset.end();
  myIt = myMultiset.end();
  while (stdIt != stdMultiset.begin()) {
    --stdIt;
    --myIt;
    EXPECT_EQ(*stdIt, *myIt);
  }
}

TEST(MultisetTest, TestMultisetIntIterator) {
  std::initializer_list<int> items{3, 2, 5, 7, 9, 12};
  std::multiset<int> stdMultiset(items);
  mycontainers::MyMultiset<int> myMultiset(items);

  EXPECT_EQ(*stdMultiset.begin(), *myMultiset.begin());
  EXPECT_EQ(*stdMultiset.end(), *myMultiset.end());

  EXPECT_EQ(stdMultiset.begin() == stdMultiset.begin(),
            myMultiset.begin() == myMultiset.begin());
  EXPECT_EQ(stdMultiset.begin() != stdMultiset.begin(),
            myMultiset.begin() != myMultiset.begin());

  EXPECT_EQ(stdMultiset.end() == stdMultiset.end(),
            myMultiset.end() == myMultiset.end());
  EXPECT_EQ(stdMultiset.end() != stdMultiset.end(),
            myMultiset.end() != myMultiset.end());

  EXPECT_EQ(stdMultiset.begin() == stdMultiset.end(),
            myMultiset.begin() == myMultiset.end());
  EXPECT_EQ(stdMultiset.begin() != stdMultiset.end(),
            myMultiset.begin() != myMultiset.end());

  std::multiset<int>::iterator stdIt = stdMultiset.begin();
  mycontainers::MyMultiset<int>::iterator myIt = myMultiset.begin();
  for (; stdIt != stdMultiset.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(*stdIt, *myIt);
  }

  stdIt = stdMultiset.end();
  myIt = myMultiset.end();
  while (stdIt != stdMultiset.begin()) {
    --stdIt;
    --myIt;
    EXPECT_EQ(*stdIt, *myIt);
  }

  std::multiset<int>::iterator stdIt1(stdIt);
  mycontainers::MyMultiset<int>::iterator myIt1(myIt);
  EXPECT_EQ(*stdIt1, *myIt1);
  EXPECT_EQ(*stdIt, *myIt);

  std::multiset<int>::iterator stdIt2(std::move(stdIt));
  mycontainers::MyMultiset<int>::iterator myIt2(std::move(myIt));
  EXPECT_EQ(*stdIt2, *myIt2);
  EXPECT_EQ(*stdIt, *myIt);

  std::multiset<int>::iterator stdIt3;
  stdIt3 = stdIt2;
  mycontainers::MyMultiset<int>::iterator myIt3;
  myIt3 = myIt2;

  EXPECT_EQ(*stdIt3, *myIt3);
  EXPECT_EQ(*stdIt2, *myIt2);

  std::multiset<int>::iterator stdIt4;
  stdIt4 = std::move(stdIt2);
  mycontainers::MyMultiset<int>::iterator myIt4;
  myIt4 = std::move(myIt2);

  EXPECT_EQ(*stdIt4, *myIt4);
  EXPECT_EQ(*stdIt2, *myIt2);
}

TEST(MultisetTest, TestMultisetDoubleIterator) {
  std::initializer_list<double> items{3.3, 2.2, 5.7, 7.5, 9.999, 12.0, 2.2};
  std::multiset<double> stdMultiset(items);
  mycontainers::MyMultiset<double> myMultiset(items);

  EXPECT_EQ(stdMultiset.size(), myMultiset.size());
  EXPECT_EQ(stdMultiset.empty(), myMultiset.empty());

  EXPECT_EQ(*stdMultiset.begin(), *myMultiset.begin());
  EXPECT_EQ(*stdMultiset.end(), *myMultiset.end());

  EXPECT_EQ(stdMultiset.begin() == stdMultiset.begin(),
            myMultiset.begin() == myMultiset.begin());
  EXPECT_EQ(stdMultiset.begin() != stdMultiset.begin(),
            myMultiset.begin() != myMultiset.begin());

  EXPECT_EQ(stdMultiset.end() == stdMultiset.end(),
            myMultiset.end() == myMultiset.end());
  EXPECT_EQ(stdMultiset.end() != stdMultiset.end(),
            myMultiset.end() != myMultiset.end());

  EXPECT_EQ(stdMultiset.begin() == stdMultiset.end(),
            myMultiset.begin() == myMultiset.end());
  EXPECT_EQ(stdMultiset.begin() != stdMultiset.end(),
            myMultiset.begin() != myMultiset.end());

  std::multiset<double>::iterator stdIt = stdMultiset.begin();
  mycontainers::MyMultiset<double>::iterator myIt = myMultiset.begin();
  for (; stdIt != stdMultiset.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(*stdIt, *myIt);
  }
}

TEST(MultisetTest, TestMultisetCharIterator) {
  std::initializer_list<char> items{'a', 'B', '.', 0, '7', '/', 77, '.'};
  std::multiset<char> stdMultiset(items);
  mycontainers::MyMultiset<char> myMultiset(items);

  EXPECT_EQ(stdMultiset.size(), myMultiset.size());
  EXPECT_EQ(stdMultiset.empty(), myMultiset.empty());

  EXPECT_EQ(*stdMultiset.begin(), *myMultiset.begin());
  EXPECT_EQ(*stdMultiset.end(), *myMultiset.end());

  EXPECT_EQ(stdMultiset.begin() == stdMultiset.begin(),
            myMultiset.begin() == myMultiset.begin());
  EXPECT_EQ(stdMultiset.begin() != stdMultiset.begin(),
            myMultiset.begin() != myMultiset.begin());

  EXPECT_EQ(stdMultiset.end() == stdMultiset.end(),
            myMultiset.end() == myMultiset.end());
  EXPECT_EQ(stdMultiset.end() != stdMultiset.end(),
            myMultiset.end() != myMultiset.end());

  EXPECT_EQ(stdMultiset.begin() == stdMultiset.end(),
            myMultiset.begin() == myMultiset.end());
  EXPECT_EQ(stdMultiset.begin() != stdMultiset.end(),
            myMultiset.begin() != myMultiset.end());

  std::multiset<char>::iterator stdIt = stdMultiset.begin();
  mycontainers::MyMultiset<char>::iterator myIt = myMultiset.begin();
  for (; stdIt != stdMultiset.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(*stdIt, *myIt);
  }
}

TEST(MultisetTest, TestMultisetBoolIterator) {
  std::initializer_list<bool> items{true, true, false, true, false, false};
  std::multiset<bool> stdMultiset(items);
  mycontainers::MyMultiset<bool> myMultiset(items);

  EXPECT_EQ(stdMultiset.size(), myMultiset.size());
  EXPECT_EQ(stdMultiset.empty(), myMultiset.empty());

  EXPECT_EQ(*stdMultiset.begin(), *myMultiset.begin());

  EXPECT_EQ(stdMultiset.begin() == stdMultiset.begin(),
            myMultiset.begin() == myMultiset.begin());
  EXPECT_EQ(stdMultiset.begin() != stdMultiset.begin(),
            myMultiset.begin() != myMultiset.begin());

  EXPECT_EQ(stdMultiset.end() == stdMultiset.end(),
            myMultiset.end() == myMultiset.end());
  EXPECT_EQ(stdMultiset.end() != stdMultiset.end(),
            myMultiset.end() != myMultiset.end());

  EXPECT_EQ(stdMultiset.begin() == stdMultiset.end(),
            myMultiset.begin() == myMultiset.end());
  EXPECT_EQ(stdMultiset.begin() != stdMultiset.end(),
            myMultiset.begin() != myMultiset.end());

  std::multiset<bool>::iterator stdIt = stdMultiset.begin();
  mycontainers::MyMultiset<bool>::iterator myIt = myMultiset.begin();
  for (; stdIt != stdMultiset.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(*stdIt, *myIt);
  }
}

TEST(MultisetTest, TestMultisetStringIterator) {
  std::initializer_list<std::string> items{"aB", ".0", "7/*+-", "77", "aB"};
  std::multiset<std::string> stdMultiset(items);
  mycontainers::MyMultiset<std::string> myMultiset(items);

  EXPECT_EQ(stdMultiset.size(), myMultiset.size());
  EXPECT_EQ(stdMultiset.empty(), myMultiset.empty());

  EXPECT_EQ(*stdMultiset.begin(), *myMultiset.begin());

  EXPECT_EQ(stdMultiset.begin() == stdMultiset.begin(),
            myMultiset.begin() == myMultiset.begin());
  EXPECT_EQ(stdMultiset.begin() != stdMultiset.begin(),
            myMultiset.begin() != myMultiset.begin());

  EXPECT_EQ(stdMultiset.end() == stdMultiset.end(),
            myMultiset.end() == myMultiset.end());
  EXPECT_EQ(stdMultiset.end() != stdMultiset.end(),
            myMultiset.end() != myMultiset.end());

  EXPECT_EQ(stdMultiset.begin() == stdMultiset.end(),
            myMultiset.begin() == myMultiset.end());
  EXPECT_EQ(stdMultiset.begin() != stdMultiset.end(),
            myMultiset.begin() != myMultiset.end());

  std::multiset<std::string>::iterator stdIt = stdMultiset.begin();
  mycontainers::MyMultiset<std::string>::iterator myIt = myMultiset.begin();
  for (; stdIt != stdMultiset.end(); ++stdIt, ++myIt) {
    EXPECT_EQ(*stdIt, *myIt);
  }
}
