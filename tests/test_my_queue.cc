#include <queue>

#include "../my_queue.h"
#include "gtest/gtest.h"

class QueueTest1 : public testing::Test {
 protected:
  void SetUp() override {
    stdQueue.push(10);
    myQueue.push(10);
  }

  void TearDown() override {
    EXPECT_EQ(stdQueue.size(), myQueue.size());
    EXPECT_EQ(stdQueue.empty(), myQueue.empty());
    if (!stdQueue.empty()) {
      EXPECT_EQ(stdQueue.back(), myQueue.back());
      EXPECT_EQ(stdQueue.front(), myQueue.front());
    }

    stdQueue.push(10);
    myQueue.push(10);

    EXPECT_EQ(stdQueue.size(), myQueue.size());
    EXPECT_EQ(stdQueue.empty(), myQueue.empty());
    if (!stdQueue.empty()) {
      EXPECT_EQ(stdQueue.back(), myQueue.back());
      EXPECT_EQ(stdQueue.front(), myQueue.front());
    }

    stdQueue.push(30);
    myQueue.push(30);

    EXPECT_EQ(stdQueue.size(), myQueue.size());
    EXPECT_EQ(stdQueue.empty(), myQueue.empty());
    if (!stdQueue.empty()) {
      EXPECT_EQ(stdQueue.back(), myQueue.back());
      EXPECT_EQ(stdQueue.front(), myQueue.front());
    }

    stdQueue.push(20);
    myQueue.push(20);

    EXPECT_EQ(stdQueue.size(), myQueue.size());
    EXPECT_EQ(stdQueue.empty(), myQueue.empty());
    if (!stdQueue.empty()) {
      EXPECT_EQ(stdQueue.back(), myQueue.back());
      EXPECT_EQ(stdQueue.front(), myQueue.front());
    }

    stdQueue.pop();
    myQueue.pop();

    EXPECT_EQ(stdQueue.size(), myQueue.size());
    EXPECT_EQ(stdQueue.empty(), myQueue.empty());
    if (!stdQueue.empty()) {
      EXPECT_EQ(stdQueue.back(), myQueue.back());
      EXPECT_EQ(stdQueue.front(), myQueue.front());
    }

    stdQueue.pop();
    myQueue.pop();

    EXPECT_EQ(stdQueue.size(), myQueue.size());
    EXPECT_EQ(stdQueue.empty(), myQueue.empty());
    if (!stdQueue.empty()) {
      EXPECT_EQ(stdQueue.back(), myQueue.back());
      EXPECT_EQ(stdQueue.front(), myQueue.front());
    }

    stdQueue.pop();
    myQueue.pop();

    EXPECT_EQ(stdQueue.size(), myQueue.size());
    EXPECT_EQ(stdQueue.empty(), myQueue.empty());
    if (!stdQueue.empty()) {
      EXPECT_EQ(stdQueue.back(), myQueue.back());
      EXPECT_EQ(stdQueue.front(), myQueue.front());
    }
  }

  std::queue<int> stdQueue;
  mycontainers::MyQueue<int> myQueue;
};

class QueueTest2 : public QueueTest1 {
 protected:
  void SetUp() override {
    stdQueue.push(10);
    myQueue.push(10);

    std::initializer_list<int> items{10, 30, 20, 50, 40};
    for (auto &item : items) {
      stdQueue1.push(item);
    }
    for (auto &item : items) {
      myQueue1.push(item);
    }
  }

  std::queue<int> stdQueue1;
  mycontainers::MyQueue<int> myQueue1;
};

TEST_F(QueueTest1, TestQueueIntDefault) {
  EXPECT_EQ(stdQueue.size(), myQueue.size());
  EXPECT_EQ(stdQueue.size(), 1);

  stdQueue.pop();
  myQueue.pop();
}

TEST_F(QueueTest1, TestQueueIntInitList) {
  stdQueue.pop();
  myQueue.pop();

  stdQueue.push(10);
  stdQueue.push(30);
  stdQueue.push(20);

  mycontainers::MyQueue<int> myQueue1{10, 30, 20};
  myQueue = myQueue1;

  if (!stdQueue.empty()) {
    EXPECT_EQ(stdQueue.back(), myQueue.back());
  }
}

TEST_F(QueueTest2, TestQueueIntCopy) {
  std::queue<int> stdQueue2(stdQueue1);
  stdQueue = stdQueue2;

  mycontainers::MyQueue<int> myQueue2(myQueue1);
  myQueue = myQueue2;

  EXPECT_EQ(stdQueue1.size(), myQueue1.size());
  EXPECT_EQ(stdQueue1.empty(), myQueue1.empty());
  if (!stdQueue.empty()) {
    EXPECT_EQ(stdQueue.back(), myQueue.back());
  }

  EXPECT_EQ(stdQueue2.size(), myQueue2.size());
  EXPECT_EQ(stdQueue2.empty(), myQueue2.empty());
  if (!stdQueue.empty()) {
    EXPECT_EQ(stdQueue.back(), myQueue.back());
  }
}

TEST_F(QueueTest2, TestQueueIntMove) {
  std::queue<int> stdQueue2(std::move(stdQueue1));
  stdQueue = stdQueue2;

  mycontainers::MyQueue<int> myQueue2(std::move(myQueue1));
  myQueue = myQueue2;

  EXPECT_EQ(stdQueue1.size(), myQueue1.size());
  EXPECT_EQ(stdQueue1.empty(), myQueue1.empty());

  EXPECT_EQ(stdQueue2.size(), myQueue2.size());
  EXPECT_EQ(stdQueue2.empty(), myQueue2.empty());
  if (!stdQueue2.empty()) {
    EXPECT_EQ(stdQueue2.back(), myQueue2.back());
    EXPECT_EQ(stdQueue2.front(), myQueue2.front());
  }
}

TEST_F(QueueTest2, TestQueueIntCopyOp) {
  stdQueue = stdQueue1;
  myQueue = myQueue1;

  EXPECT_EQ(stdQueue1.size(), myQueue1.size());
  EXPECT_EQ(stdQueue1.empty(), myQueue1.empty());
  if (!stdQueue1.empty()) {
    EXPECT_EQ(stdQueue1.back(), myQueue1.back());
    EXPECT_EQ(stdQueue1.front(), myQueue1.front());
  }
}

TEST_F(QueueTest2, TestQueueIntMoveOp) {
  EXPECT_EQ(stdQueue.size(), myQueue.size());
  stdQueue = std::move(stdQueue1);
  myQueue = std::move(myQueue1);

  EXPECT_EQ(stdQueue1.size(), myQueue1.size());
  EXPECT_EQ(stdQueue1.empty(), myQueue1.empty());
}

TEST_F(QueueTest2, TestQueueIntSwap) {
  stdQueue.push(30);
  myQueue.push(30);

  stdQueue.swap(stdQueue1);
  myQueue.swap(myQueue1);

  EXPECT_EQ(stdQueue1.size(), myQueue1.size());
  EXPECT_EQ(stdQueue1.empty(), myQueue1.empty());
  if (!stdQueue1.empty()) {
    EXPECT_EQ(stdQueue1.back(), myQueue1.back());
    EXPECT_EQ(stdQueue1.front(), myQueue1.front());
  }
}

TEST_F(QueueTest2, TestQueueIntInsertMany) {
  stdQueue.push(100);
  stdQueue.push(1000);
  stdQueue.push(10000);
  myQueue.insert_many_back(100, 1000, 10000);
}

TEST_F(QueueTest2, TestQueueIntConst) {
  const std::queue<int> stdQueue2(stdQueue1);
  const mycontainers::MyQueue<int> myQueue2(myQueue1);

  EXPECT_EQ(stdQueue2.size(), myQueue2.size());
  EXPECT_EQ(stdQueue2.empty(), myQueue2.empty());
  EXPECT_FALSE(stdQueue2.empty());
  EXPECT_FALSE(myQueue2.empty());
  if (!stdQueue2.empty()) {
    EXPECT_EQ(stdQueue2.back(), myQueue2.back());
    EXPECT_EQ(stdQueue2.front(), myQueue2.front());
  }
}