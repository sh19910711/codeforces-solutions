
// @snippet<sh19910711/contest:unit-tests.cpp>
#define __MY_UNIT_TEST__
#include "./main.cpp"
#include <gtest/gtest.h>

/*
 *  # Example
 *
 *  int add( int x, int y ) {
 *    return x + y;
 *  }
 *
 *  TEST(AddTest, Test1) {
 *    ASSERT_EQ(2, add(1, 1));
 *  }
 */

std::string call_get_lucky_number( int a, int b, int c, int d ) {
  solution::a = a;
  solution::b = b;
  solution::c = c;
  solution::d = d;
  return solution::Solver().get_lucky_number();
}

TEST(get_lucky_number, PatA) {
  ASSERT_EQ("474", call_get_lucky_number(2, 1, 1, 1));
  ASSERT_EQ("47474", call_get_lucky_number(3, 2, 2, 2));
  ASSERT_EQ("4444447474", call_get_lucky_number(8, 2, 2, 2));
  ASSERT_EQ("444444444747777777774", call_get_lucky_number(11, 10, 2, 2));
  ASSERT_EQ("747", call_get_lucky_number(1, 2, 1, 1));
  ASSERT_EQ("74747", call_get_lucky_number(2, 3, 2, 2));
  ASSERT_EQ("447477777774", call_get_lucky_number(4, 8, 2, 2));
  ASSERT_EQ("447774", call_get_lucky_number(3, 3, 1, 1));
  ASSERT_EQ("474774", call_get_lucky_number(3, 3, 2, 2));
  ASSERT_EQ("477774", call_get_lucky_number(2, 4, 1, 1));
  ASSERT_EQ("74777777", call_get_lucky_number(1, 7, 1, 1));
}

TEST(get_lucky_number, PatB) {
  ASSERT_EQ("7444444747777774", call_get_lucky_number(8, 8, 2, 3));
  ASSERT_EQ("4747", call_get_lucky_number(2, 2, 2, 1));
  ASSERT_EQ("7474", call_get_lucky_number(2, 2, 1, 2));
  ASSERT_EQ("74474", call_get_lucky_number(3, 2, 1, 2));
}

TEST(get_lucky_number, PatE) {
  ASSERT_EQ("-1", call_get_lucky_number(1, 1, 1, 1));
  ASSERT_EQ("-1", call_get_lucky_number(1, 1, 1000, 1));
  ASSERT_EQ("-1", call_get_lucky_number(1000000, 1000000, 1000000, 1000000));
}


