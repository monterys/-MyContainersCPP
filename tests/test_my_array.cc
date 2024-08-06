#include "../my_array.h"
#include "gtest/gtest.h"

TEST(array, constructor) {
  mycontainers::array<std::string, 3> myarray;
  std::array<std::string, 3> stdarray;
  ASSERT_EQ(myarray.size(), stdarray.size());
  ASSERT_EQ(myarray.empty(), stdarray.empty());
}

TEST(array, constructor_initializer) {
  mycontainers::array<int, 5> myarray{1, 2, 3, 4, 5};
  std::array<int, 5> stdarray{1, 2, 3, 4, 5};
  ASSERT_EQ(myarray.size(), stdarray.size());
  ASSERT_EQ(myarray.empty(), stdarray.empty());
  for (size_t i = 0; i < myarray.size(); ++i) {
    ASSERT_EQ(myarray[i], stdarray[i]);
  }
}

TEST(array, constructor_copy) {
  mycontainers::array<int, 5> myarray{1, 2, 3, 4, 5};
  std::array<int, 5> stdarray{1, 2, 3, 4, 5};
  mycontainers::array<int, 5> myarray2(myarray);
  std::array<int, 5> stdarray2(stdarray);
  ASSERT_EQ(myarray.size(), stdarray.size());
  ASSERT_EQ(myarray.empty(), stdarray.empty());
  ASSERT_EQ(myarray2.size(), stdarray2.size());
  ASSERT_EQ(myarray2.empty(), stdarray2.empty());
  for (size_t i = 0; i < myarray2.size(); ++i) {
    ASSERT_EQ(myarray2[i], stdarray2[i]);
  }
}

TEST(array, constructor_move) {
  mycontainers::array<int, 5> myarray{1, 2, 3, 4, 5};
  std::array<int, 5> stdarray{1, 2, 3, 4, 5};
  mycontainers::array<int, 5> myarray2(std::move(myarray));
  std::array<int, 5> stdarray2(std::move(stdarray));
  ASSERT_EQ(myarray.size(), stdarray.size());
  ASSERT_EQ(myarray.empty(), stdarray.empty());
  ASSERT_EQ(myarray2.size(), stdarray2.size());
  ASSERT_EQ(myarray2.empty(), stdarray2.empty());
  for (size_t i = 0; i < myarray2.size(); ++i) {
    ASSERT_EQ(myarray2[i], stdarray2[i]);
  }
}

TEST(array, operator_copy) {
  mycontainers::array<int, 5> myarray{1, 2, 3, 4, 5};
  std::array<int, 5> stdarray{1, 2, 3, 4, 5};
  mycontainers::array<int, 5> myarray2;
  std::array<int, 5> stdarray2;
  myarray2 = myarray;
  stdarray2 = stdarray;
  ASSERT_EQ(myarray.size(), stdarray.size());
  ASSERT_EQ(myarray.empty(), stdarray.empty());
  ASSERT_EQ(myarray2.size(), stdarray2.size());
  ASSERT_EQ(myarray2.empty(), stdarray2.empty());
  for (size_t i = 0; i < myarray2.size(); ++i) {
    ASSERT_EQ(myarray2[i], stdarray2[i]);
  }
}

TEST(array, operator_move) {
  mycontainers::array<int, 5> myarray{1, 2, 3, 4, 5};
  std::array<int, 5> stdarray{1, 2, 3, 4, 5};
  mycontainers::array<int, 5> myarray2;
  std::array<int, 5> stdarray2;
  myarray2 = std::move(myarray);
  stdarray2 = std::move(stdarray);
  ASSERT_EQ(myarray.size(), stdarray.size());
  ASSERT_EQ(myarray.empty(), stdarray.empty());
  ASSERT_EQ(myarray2.size(), stdarray2.size());
  ASSERT_EQ(myarray2.empty(), stdarray2.empty());
  for (size_t i = 0; i < myarray2.size(); ++i) {
    ASSERT_EQ(myarray2[i], stdarray2[i]);
  }
}

TEST(array, front_and_back) {
  mycontainers::array<int, 5> myarray{1, 2, 3, 4, 5};
  std::array<int, 5> stdarray{1, 2, 3, 4, 5};
  ASSERT_EQ(myarray.size(), stdarray.size());
  ASSERT_EQ(myarray.empty(), stdarray.empty());
  ASSERT_EQ(myarray.front(), stdarray.front());
  // ASSERT_EQ(myarray.back(), stdarray.back());
}

TEST(array, front_trow) {
  mycontainers::array<int, 0> myarray;
  std::array<int, 0> stdarray;
  ASSERT_EQ(myarray.size(), stdarray.size());
  ASSERT_EQ(myarray.empty(), stdarray.empty());
  ASSERT_ANY_THROW(myarray.front());
  ASSERT_ANY_THROW(myarray.back());
}

TEST(array, over_range) {
  mycontainers::array<int, 5> myarray{1, 2, 3, 4, 5};
  ASSERT_ANY_THROW(myarray[10] = 0);
}

TEST(array, data) {
  mycontainers::array<int, 5> myarray{1, 2, 3, 4, 5};
  std::array<int, 5> stdarray{1, 2, 3, 4, 5};
  ASSERT_EQ(myarray.size(), stdarray.size());
  ASSERT_EQ(myarray.empty(), stdarray.empty());
  ASSERT_EQ(myarray.front(), stdarray.front());
  ASSERT_EQ(myarray.back(), stdarray.back());
  int *mytmp = myarray.data();
  int *stdtmp = myarray.data();
  for (size_t i = 0; i < myarray.size(); ++i) {
    ASSERT_EQ(mytmp[i], stdtmp[i]);
  }
}

TEST(array, begin) {
  mycontainers::array<int, 5> myarray{1, 2, 3, 4, 5};
  std::array<int, 5> stdarray{1, 2, 3, 4, 5};
  ASSERT_EQ(myarray.size(), stdarray.size());
  ASSERT_EQ(myarray.empty(), stdarray.empty());
  mycontainers::array<int, 5>::ArrayIterator myit = myarray.begin();
  auto stdit = stdarray.begin();
  for (size_t i = 0; i < myarray.size(); ++i) {
    ASSERT_EQ(*myit, *stdit);
    ++myit;
    ++stdit;
  }
}

TEST(array, end) {
  mycontainers::array<int, 5> myarray{1, 2, 3, 4, 5};
  std::array<int, 5> stdarray{1, 2, 3, 4, 5};
  ASSERT_EQ(myarray.size(), stdarray.size());
  ASSERT_EQ(myarray.empty(), stdarray.empty());
  mycontainers::array<int, 5>::ArrayIterator myit;
  myit = myarray.begin();
  auto stdit = stdarray.begin();
  while (myit != myarray.end()) {
    ASSERT_EQ(*myit, *stdit);
    ++myit;
    ++stdit;
  }
}

TEST(array, max_size) {
  mycontainers::array<int, 5> myarray{1, 2, 3, 4, 5};
  std::array<int, 5> stdarray{1, 2, 3, 4, 5};
  ASSERT_EQ(myarray.max_size(), stdarray.max_size());
}

TEST(array, swap) {
  mycontainers::array<int, 5> myarray{1, 2, 3};
  std::array<int, 5> stdarray{1, 2, 3};
  mycontainers::array<int, 5> myarray2{1, 2, 3};
  std::array<int, 5> stdarray2{1, 2, 3};
  myarray.swap(myarray2);
  stdarray.swap(stdarray2);
  ASSERT_EQ(myarray.size(), stdarray.size());
  ASSERT_EQ(myarray.empty(), stdarray.empty());
  ASSERT_EQ(myarray2.size(), stdarray2.size());
  ASSERT_EQ(myarray2.empty(), stdarray2.empty());
  for (size_t i = 0; i < myarray2.size(); ++i) {
    ASSERT_EQ(myarray2[i], stdarray2[i]);
  }
  for (size_t i = 0; i < myarray.size(); ++i) {
    ASSERT_EQ(myarray[i], stdarray[i]);
  }
}

TEST(array, fill) {
  mycontainers::array<int, 5> myarray{1, 2, 3};
  std::array<int, 5> stdarray{1, 2, 3};
  myarray.fill(10);
  stdarray.fill(10);
  ASSERT_EQ(myarray.size(), stdarray.size());
  ASSERT_EQ(myarray.empty(), stdarray.empty());
  for (size_t i = 0; i < myarray.size(); ++i) {
    ASSERT_EQ(myarray[i], stdarray[i]);
  }
}