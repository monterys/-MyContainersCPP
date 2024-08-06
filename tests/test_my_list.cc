#include <list>

#include "../my_list.h"
#include "gtest/gtest.h"

TEST(list, constructor) {
  mycontainers::list<std::string> myList;
  std::list<std::string> stdList;
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
}

TEST(list, constructor_size) {
  mycontainers::list<std::string> myList(7);
  std::list<std::string> stdList(7);
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  mycontainers::list<std::string>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, constructor_initializer) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, constructor_copy) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  mycontainers::list<int> mytmp(myList);
  std::list<int> stdtmp(stdList);
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, constructor_move) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  mycontainers::list<int> mytmp(std::move(myList));
  std::list<int> stdtmp(std::move(stdList));
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  mycontainers::list<int>::ListIterator myit = mytmp.begin();
  auto it = stdtmp.begin();
  for (size_t i = 0; i < mytmp.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, operator_copy) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  mycontainers::list<int> mytmp{1, 2};
  std::list<int> stdtmp{1, 2};
  mytmp = myList;
  stdtmp = stdList;
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  mycontainers::list<int>::ListIterator myit = mytmp.begin();
  auto it = stdtmp.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, operator_move) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  mycontainers::list<int> mytmp;
  std::list<int> stdtmp;
  mytmp = std::move(myList);
  stdtmp = std::move(stdList);
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  mycontainers::list<int>::ListIterator myit = mytmp.begin();
  auto it = stdtmp.begin();
  for (size_t i = 0; i < mytmp.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, front_back) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  ASSERT_EQ(myList.front(), stdList.front());
  ASSERT_EQ(myList.back(), stdList.back());
}

TEST(list, begin) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  ASSERT_EQ(*it, *myit);
  ++it;
  ++myit;
  ASSERT_EQ(*it, *myit);
}

TEST(list, end) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  mycontainers::list<int>::ListIterator myit = myList.end();
  auto it = stdList.end();
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  ASSERT_EQ(*it, *myit);
  ++it;
  ++myit;
  ASSERT_EQ(*it, *myit);
}

TEST(list, max_size) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  ASSERT_EQ(myList.max_size(), stdList.max_size());
}

TEST(list, clear) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  myList.clear();
  stdList.clear();
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  ASSERT_EQ(myList.front(), stdList.front());
  ASSERT_EQ(myList.back(), stdList.back());
}

TEST(list, insert) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  ++it;
  ++myit;
  myList.insert(myit, 10);
  stdList.insert(it, 10);
  ASSERT_EQ(*it, *myit);
  ASSERT_EQ(myList.front(), stdList.front());
  ASSERT_EQ(myList.back(), stdList.back());
}

TEST(list, erase) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  ++it;
  ++myit;
  myList.erase(myit);
  stdList.erase(it);
  ASSERT_EQ(myList.front(), stdList.front());
  ASSERT_EQ(myList.back(), stdList.back());
}

TEST(list, push_front) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  myList.push_front(10);
  stdList.push_front(10);
  myList.push_front(20);
  stdList.push_front(20);
  myList.push_front(30);
  stdList.push_front(30);
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  ASSERT_EQ(myList.front(), stdList.front());
  ASSERT_EQ(myList.back(), stdList.back());
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, push_back) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  myList.push_back(10);
  stdList.push_back(10);
  myList.push_back(20);
  stdList.push_back(20);
  myList.push_back(30);
  stdList.push_back(30);
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  ASSERT_EQ(myList.front(), stdList.front());
  ASSERT_EQ(myList.back(), stdList.back());
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, pop_front) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  myList.pop_front();
  stdList.pop_front();
  myList.pop_front();
  stdList.pop_front();
  myList.pop_front();
  stdList.pop_front();
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  ASSERT_EQ(myList.front(), stdList.front());
  ASSERT_EQ(myList.back(), stdList.back());
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, pop_back) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  myList.pop_back();
  stdList.pop_back();
  myList.pop_back();
  stdList.pop_back();
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  ASSERT_EQ(myList.front(), stdList.front());
  ASSERT_EQ(myList.back(), stdList.back());
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, swap) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  mycontainers::list<int> mytmp;
  std::list<int> stdtmp;
  mytmp.swap(myList);
  stdtmp.swap(stdList);
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  ASSERT_EQ(mytmp.size(), stdtmp.size());
  ASSERT_EQ(mytmp.empty(), stdtmp.empty());
  mycontainers::list<int>::ListIterator myit = mytmp.begin();
  auto it = stdtmp.begin();
  for (size_t i = 0; i < mytmp.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, merge_1) {
  mycontainers::list<int> myList{1, 3, 5};
  std::list<int> stdList{1, 3, 5};
  mycontainers::list<int> mytmp{2, 4, 6, 7};
  std::list<int> stdtmp{2, 4, 6, 7};
  mytmp.merge(myList);
  stdtmp.merge(stdList);
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  ASSERT_EQ(mytmp.size(), stdtmp.size());
  ASSERT_EQ(mytmp.empty(), stdtmp.empty());
  mycontainers::list<int>::ListIterator myit = mytmp.begin();
  auto it = stdtmp.begin();
  for (size_t i = 0; i < mytmp.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, merge_2) {
  mycontainers::list<int> myList{2, 4, 6, 7};
  std::list<int> stdList{2, 4, 6, 7};
  mycontainers::list<int> mytmp{1, 3, 5};
  std::list<int> stdtmp{1, 3, 5};
  mytmp.merge(myList);
  stdtmp.merge(stdList);
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  ASSERT_EQ(mytmp.size(), stdtmp.size());
  ASSERT_EQ(mytmp.empty(), stdtmp.empty());
  mycontainers::list<int>::ListIterator myit = mytmp.begin();
  auto it = stdtmp.begin();
  for (size_t i = 0; i < mytmp.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, splice) {
  mycontainers::list<int> myList{1, 3, 5};
  std::list<int> stdList{1, 3, 5};
  mycontainers::list<int> mytmp{2, 4, 6, 7};
  std::list<int> stdtmp{2, 4, 6, 7};
  mycontainers::list<int>::ListConstIterator myit1 = myList.cbegin();
  auto it1 = stdList.begin();
  ++it1;
  ++myit1;
  myList.splice(myit1, mytmp);
  stdList.splice(it1, stdtmp);
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  ASSERT_EQ(mytmp.empty(), stdtmp.empty());
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
  }
}

TEST(list, splice_head_size) {
  mycontainers::list<int> myList{1, 3, 5};
  std::list<int> stdList{1, 3, 5};
  mycontainers::list<int> mytmp{2, 4, 6, 7};
  std::list<int> stdtmp{2, 4, 6, 7};
  mycontainers::list<int>::ListConstIterator myit1 = myList.cbegin();
  auto it1 = stdList.begin();
  myList.splice(myit1, mytmp);
  stdList.splice(it1, stdtmp);
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  ASSERT_EQ(mytmp.empty(), stdtmp.empty());
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
  }
}

TEST(list, splice_0_size) {
  mycontainers::list<int> myList{2, 4, 6, 7};
  std::list<int> stdList{2, 4, 6, 7};
  mycontainers::list<int> mytmp;
  std::list<int> stdtmp;
  mycontainers::list<int>::ListConstIterator myit1 = mytmp.cbegin();
  auto it1 = stdtmp.begin();
  ++it1;
  ++myit1;
  mytmp.splice(myit1, myList);
  stdtmp.splice(it1, stdList);
  ASSERT_EQ(myList.empty(), stdList.empty());
  ASSERT_EQ(mytmp.size(), stdtmp.size());
  mycontainers::list<int>::ListIterator myit = mytmp.begin();
  auto it = stdtmp.begin();
  for (size_t i = 0; i < mytmp.size(); ++i) {
    ASSERT_EQ(*it, *myit);
  }
}

TEST(list, reverse) {
  mycontainers::list<int> myList{1, 2, 3, 4, 5, 6};
  std::list<int> stdList{1, 2, 3, 4, 5, 6};
  myList.reverse();
  stdList.reverse();
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, unique) {
  mycontainers::list<int> myList{1, 2, 2, 2, 3, 3, 4, 3, 3, 5, 5, 5, 6};
  std::list<int> stdList{1, 2, 2, 2, 3, 3, 4, 3, 3, 5, 5, 5, 6};
  myList.unique();
  stdList.unique();
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, sort) {
  mycontainers::list<double> myList{2, 6, 4, 1, 100, 2.5, 0.1, 0.005};
  std::list<double> stdList{2, 6, 4, 1, 100, 2.5, 0.1, 0.005};
  myList.unique();
  stdList.unique();
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  mycontainers::list<double>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, insert_many) {
  mycontainers::list<int> myList{1, 2, 3, 4};
  std::list<int_least16_t> stdList{1, 5, 6, 2, 3, 4};
  mycontainers::list<int>::ListConstIterator myitc = myList.cbegin();
  ++myitc;
  myList.insert_many(myitc, 5, 6);
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, insert_many_back) {
  mycontainers::list<int> myList{1, 2, 3, 4};
  std::list<int_least16_t> stdList{1, 2, 3, 4, 5, 6};
  myList.insert_many_back(5, 6);
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}

TEST(list, insert_many_front) {
  mycontainers::list<int> myList{1, 2, 3, 4};
  std::list<int_least16_t> stdList{5, 6, 1, 2, 3, 4};
  myList.insert_many_front(5, 6);
  ASSERT_EQ(myList.size(), stdList.size());
  ASSERT_EQ(myList.empty(), stdList.empty());
  mycontainers::list<int>::ListIterator myit = myList.begin();
  auto it = stdList.begin();
  for (size_t i = 0; i < myList.size(); ++i) {
    ASSERT_EQ(*it, *myit);
    ++it;
    ++myit;
  }
}
