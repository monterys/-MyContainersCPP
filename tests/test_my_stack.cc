#include <stack>

#include "../my_stack.h"
#include "gtest/gtest.h"

class StackTest1 : public testing::Test {
 protected:
  void SetUp() override {
    stdStack.push(10);
    myStack.push(10);
  }

  void TearDown() override {
    EXPECT_EQ(stdStack.size(), myStack.size());
    EXPECT_EQ(stdStack.empty(), myStack.empty());
    if (!stdStack.empty()) {
      EXPECT_EQ(stdStack.top(), myStack.top());
    }

    stdStack.push(10);
    myStack.push(10);

    EXPECT_EQ(stdStack.size(), myStack.size());
    EXPECT_EQ(stdStack.empty(), myStack.empty());
    if (!stdStack.empty()) {
      EXPECT_EQ(stdStack.top(), myStack.top());
    }

    stdStack.push(30);
    myStack.push(30);

    EXPECT_EQ(stdStack.size(), myStack.size());
    EXPECT_EQ(stdStack.empty(), myStack.empty());
    if (!stdStack.empty()) {
      EXPECT_EQ(stdStack.top(), myStack.top());
    }

    stdStack.push(20);
    myStack.push(20);

    EXPECT_EQ(stdStack.size(), myStack.size());
    EXPECT_EQ(stdStack.empty(), myStack.empty());
    if (!stdStack.empty()) {
      EXPECT_EQ(stdStack.top(), myStack.top());
    }

    stdStack.pop();
    myStack.pop();

    EXPECT_EQ(stdStack.size(), myStack.size());
    EXPECT_EQ(stdStack.empty(), myStack.empty());
    if (!stdStack.empty()) {
      EXPECT_EQ(stdStack.top(), myStack.top());
    }

    stdStack.pop();
    myStack.pop();

    EXPECT_EQ(stdStack.size(), myStack.size());
    EXPECT_EQ(stdStack.empty(), myStack.empty());
    if (!stdStack.empty()) {
      EXPECT_EQ(stdStack.top(), myStack.top());
    }

    stdStack.pop();
    myStack.pop();

    EXPECT_EQ(stdStack.size(), myStack.size());
    EXPECT_EQ(stdStack.empty(), myStack.empty());
    if (!stdStack.empty()) {
      EXPECT_EQ(stdStack.top(), myStack.top());
    }
  }

  std::stack<int> stdStack;
  mycontainers::MyStack<int> myStack;
};

class StackTest2 : public StackTest1 {
 protected:
  void SetUp() override {
    stdStack.push(10);
    myStack.push(10);

    std::initializer_list<int> items{10, 30, 20, 50, 40};
    for (auto &item : items) {
      stdStack1.push(item);
    }
    for (auto &item : items) {
      myStack1.push(item);
    }
  }

  std::stack<int> stdStack1;
  mycontainers::MyStack<int> myStack1;
};

TEST_F(StackTest1, TestStackIntDefault) {
  EXPECT_EQ(stdStack.size(), myStack.size());
  EXPECT_EQ(stdStack.size(), 1);

  stdStack.pop();
  myStack.pop();
}

TEST_F(StackTest1, TestStackIntInitList) {
  stdStack.pop();
  myStack.pop();

  stdStack.push(10);
  stdStack.push(30);
  stdStack.push(20);

  mycontainers::MyStack<int> myStack1{10, 30, 20};
  myStack = myStack1;

  if (!stdStack.empty()) {
    EXPECT_EQ(stdStack.top(), myStack.top());
  }
}

TEST_F(StackTest2, TestStackIntCopy) {
  std::stack<int> stdStack2(stdStack1);
  stdStack = stdStack2;

  mycontainers::MyStack<int> myStack2(myStack1);
  myStack = myStack2;

  EXPECT_EQ(stdStack1.size(), myStack1.size());
  EXPECT_EQ(stdStack1.empty(), myStack1.empty());
  if (!stdStack.empty()) {
    EXPECT_EQ(stdStack.top(), myStack.top());
  }

  EXPECT_EQ(stdStack2.size(), myStack2.size());
  EXPECT_EQ(stdStack2.empty(), myStack2.empty());
  if (!stdStack.empty()) {
    EXPECT_EQ(stdStack.top(), myStack.top());
  }
}

TEST_F(StackTest2, TestStackIntMove) {
  std::stack<int> stdStack2(std::move(stdStack1));
  stdStack = stdStack2;

  mycontainers::MyStack<int> myStack2(std::move(myStack1));
  myStack = myStack2;

  EXPECT_EQ(stdStack1.size(), myStack1.size());
  EXPECT_EQ(stdStack1.empty(), myStack1.empty());

  EXPECT_EQ(stdStack2.size(), myStack2.size());
  EXPECT_EQ(stdStack2.empty(), myStack2.empty());
  if (!stdStack2.empty()) {
    EXPECT_EQ(stdStack2.top(), myStack2.top());
  }
}

TEST_F(StackTest2, TestStackIntCopyOp) {
  stdStack = stdStack1;
  myStack = myStack1;

  EXPECT_EQ(stdStack1.size(), myStack1.size());
  EXPECT_EQ(stdStack1.empty(), myStack1.empty());
  if (!stdStack1.empty()) {
    EXPECT_EQ(stdStack1.top(), myStack1.top());
  }
}

TEST_F(StackTest2, TestStackIntMoveOp) {
  EXPECT_EQ(stdStack.size(), myStack.size());
  stdStack = std::move(stdStack1);
  myStack = std::move(myStack1);

  EXPECT_EQ(stdStack1.size(), myStack1.size());
  EXPECT_EQ(stdStack1.empty(), myStack1.empty());
}

TEST_F(StackTest2, TestStackIntSwap) {
  stdStack.push(30);
  myStack.push(30);

  stdStack.swap(stdStack1);
  myStack.swap(myStack1);

  EXPECT_EQ(stdStack1.size(), myStack1.size());
  EXPECT_EQ(stdStack1.empty(), myStack1.empty());
  if (!stdStack1.empty()) {
    EXPECT_EQ(stdStack1.top(), myStack1.top());
  }
}

TEST_F(StackTest2, TestQueueIntInsertMany) {
  stdStack.push(100);
  stdStack.push(1000);
  stdStack.push(10000);
  myStack.insert_many_front(100, 1000, 10000);
}

TEST_F(StackTest2, TestStackIntConst) {
  const std::stack<int> stdStack2(stdStack1);
  const mycontainers::MyStack<int> myStack2(myStack1);

  EXPECT_EQ(stdStack2.size(), myStack2.size());
  EXPECT_EQ(stdStack2.empty(), myStack2.empty());
  EXPECT_FALSE(stdStack2.empty());
  EXPECT_FALSE(myStack2.empty());
  if (!stdStack2.empty()) {
    EXPECT_EQ(stdStack2.top(), myStack2.top());
  }
}
