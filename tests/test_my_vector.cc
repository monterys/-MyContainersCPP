#include "../my_vector.h"
#include "gtest/gtest.h"

TEST(vector, constructor) {
  mycontainers::vector<std::string> myVector;
  std::vector<std::string> stdVector;
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
}

TEST(vector, constructor_size) {
  mycontainers::vector<std::string> myVector(5);
  std::vector<std::string> stdVector(5);
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
}

TEST(vector, constructor_initializer) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
  for (size_t i = 0; i < myVector.size(); ++i) {
    ASSERT_EQ(myVector[i], stdVector[i]);
  }
}

TEST(vector, constructor_copy) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  mycontainers::vector<int> myVector2(myVector);
  std::vector<int> stdVector2(stdVector);
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
  ASSERT_EQ(myVector2.capacity(), stdVector2.capacity());
  ASSERT_EQ(myVector2.size(), stdVector2.size());
  ASSERT_EQ(myVector2.empty(), stdVector2.empty());
  for (size_t i = 0; i < myVector2.size(); ++i) {
    ASSERT_EQ(myVector2[i], stdVector2[i]);
  }
}

TEST(vector, constructor_move) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  mycontainers::vector<int> myVector2(std::move(myVector));
  std::vector<int> stdVector2(std::move(stdVector));
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
  ASSERT_EQ(myVector2.capacity(), stdVector2.capacity());
  ASSERT_EQ(myVector2.size(), stdVector2.size());
  ASSERT_EQ(myVector2.empty(), stdVector2.empty());
  for (size_t i = 0; i < myVector2.size(); ++i) {
    ASSERT_EQ(myVector2[i], stdVector2[i]);
  }
}

TEST(vector, operator_copy) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  mycontainers::vector<int> myVector2;
  std::vector<int> stdVector2;
  myVector2 = myVector;
  stdVector2 = stdVector;
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
  ASSERT_EQ(myVector2.capacity(), stdVector2.capacity());
  ASSERT_EQ(myVector2.size(), stdVector2.size());
  ASSERT_EQ(myVector2.empty(), stdVector2.empty());
  for (size_t i = 0; i < myVector2.size(); ++i) {
    ASSERT_EQ(myVector2[i], stdVector2[i]);
  }
}

TEST(vector, operator_move) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  mycontainers::vector<int> myVector2;
  std::vector<int> stdVector2;
  myVector2 = std::move(myVector);
  stdVector2 = std::move(stdVector);
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
  ASSERT_EQ(myVector2.capacity(), stdVector2.capacity());
  ASSERT_EQ(myVector2.size(), stdVector2.size());
  ASSERT_EQ(myVector2.empty(), stdVector2.empty());
  for (size_t i = 0; i < myVector2.size(); ++i) {
    ASSERT_EQ(myVector2[i], stdVector2[i]);
  }
}

TEST(vector, front_and_back) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
  ASSERT_EQ(myVector.front(), stdVector.front());
  ASSERT_EQ(myVector.back(), stdVector.back());
}

TEST(vector, data) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
  ASSERT_EQ(myVector.front(), stdVector.front());
  ASSERT_EQ(myVector.back(), stdVector.back());
  int *mytmp = myVector.data();
  int *stdtmp = myVector.data();
  for (size_t i = 0; i < myVector.size(); ++i) {
    ASSERT_EQ(mytmp[i], stdtmp[i]);
  }
}

TEST(vector, begin) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
  mycontainers::vector<int>::VectorIterator myit;
  myit = myVector.begin();
  auto stdit = stdVector.begin();
  for (size_t i = 0; i < myVector.size(); ++i) {
    ASSERT_EQ(*myit, *stdit);
    ++myit;
    ++stdit;
  }
}

TEST(vector, end) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
  mycontainers::vector<int>::VectorIterator myit;
  myit = myVector.begin();
  auto stdit = stdVector.begin();
  while (myit != myVector.end()) {
    ASSERT_EQ(*myit, *stdit);
    ++myit;
    ++stdit;
  }
}

TEST(vector, max_size) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  ASSERT_EQ(myVector.max_size(), stdVector.max_size());
}

TEST(vector, reserve) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  myVector.reserve(50);
  stdVector.reserve(50);
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
  mycontainers::vector<int>::VectorIterator myit;
  myit = myVector.begin();
  auto stdit = stdVector.begin();
  while (myit != myVector.end()) {
    ASSERT_EQ(*myit, *stdit);
    ++myit;
    ++stdit;
  }
}

TEST(vector, shrink_to_fit) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  myVector.reserve(50);
  stdVector.reserve(50);
  myVector.shrink_to_fit();
  stdVector.shrink_to_fit();
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
  mycontainers::vector<int>::VectorIterator myit;
  myit = myVector.begin();
  auto stdit = stdVector.begin();
  while (myit != myVector.end()) {
    ASSERT_EQ(*myit, *stdit);
    ++myit;
    ++stdit;
  }
}

TEST(vector, clear) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  myVector.clear();
  stdVector.clear();
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
}

TEST(vector, insert) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  mycontainers::vector<int>::VectorIterator myit = myVector.begin();
  ;
  auto stdit = stdVector.begin();
  ++myit;
  ++stdit;
  myVector.insert(myit, 10);
  stdVector.insert(stdit, 10);
  ;
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
  for (size_t i = 0; i < myVector.size(); ++i) {
    ASSERT_EQ(myVector[i], stdVector[i]);
  }
}

TEST(vector, erase) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  mycontainers::vector<int>::VectorIterator myit = myVector.begin();
  ;
  auto stdit = stdVector.begin();
  ++myit;
  ++stdit;
  myVector.erase(myit);
  stdVector.erase(stdit);
  ;
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
  for (size_t i = 0; i < myVector.size(); ++i) {
    ASSERT_EQ(myVector[i], stdVector[i]);
  }
}

TEST(vector, push_back) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  myVector.push_back(50);
  stdVector.push_back(50);
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
  mycontainers::vector<int>::VectorIterator myit;
  myit = myVector.begin();
  auto stdit = stdVector.begin();
  while (myit != myVector.end()) {
    ASSERT_EQ(*myit, *stdit);
    ++myit;
    ++stdit;
  }
}

TEST(vector, pop_back) {
  mycontainers::vector<int> myVector{1, 2, 3, 4, 5};
  std::vector<int> stdVector{1, 2, 3, 4, 5};
  myVector.pop_back();
  stdVector.pop_back();
  ASSERT_EQ(myVector.capacity(), stdVector.capacity());
  ASSERT_EQ(myVector.size(), stdVector.size());
  ASSERT_EQ(myVector.empty(), stdVector.empty());
  mycontainers::vector<int>::VectorIterator myit;
  myit = myVector.begin();
  auto stdit = stdVector.begin();
  while (myit != myVector.end()) {
    ASSERT_EQ(*myit, *stdit);
    ++myit;
    ++stdit;
  }
}
