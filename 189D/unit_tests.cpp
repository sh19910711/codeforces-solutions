
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

namespace my_unit {
  using namespace std;

  class TestSolution: public solution::Solution {
  public:
    bool action() {
      init();
      solver.solve();
    }
  };

  TEST(test_solution, sample_1) {
    using namespace solution;
    TestSolution sol;
    n = 4;
    m = 2;
    r = 3;

    const int T_base[2][4][4] = {
      {
        {0, 1, 5, 6},
        {2, 0, 3, 6},
        {1, 3, 0, 1},
        {6, 6, 7, 0},
      },
      {
        {0, 3, 5, 6},
        {2, 0, 1, 6},
        {1, 3, 0, 2},
        {6, 6, 7, 0},
      },
    };

    for ( int c = 0; c < m; ++ c ) {
      for ( int i = 0; i < n; ++ i ) {
        for ( int j = 0; j < n; ++ j ) {
          T[c][i][j] = T_base[c][i][j];
        }
      }
    }

    const int QS_base[3] = {1, 1, 1};
    const int QT_base[3] = {4, 4, 4};
    const int QK_base[3] = {2, 1, 3};
    for ( int i = 0; i < 3; ++ i ) {
      QS[i] = QS_base[i];
      QT[i] = QT_base[i];
      QK[i] = QK_base[i];
    }

    sol.run();

    const int query_result_expected[3] = {3, 4, 3};
    for ( int i = 0; i < 3; ++ i ) {
      ASSERT_EQ(query_result_expected[i], query_result[i]);
    }
  }

  TEST(test_solution, sample_2) {
    using namespace solution;
    TestSolution sol;
    n = 4;
    m = 2;
    r = 3;

    const int T_base[2][4][4] = {
      {
        {0, 7, 3, 3},
        {8, 0, 10, 5},
        {1, 1, 0, 4},
        {8, 9, 2, 0},
      },
      {
        {0, 3, 3, 9},
        {7, 0, 4, 9},
        {3, 8, 0, 4},
        {4, 8, 9, 0},
      },
    };

    for ( int c = 0; c < m; ++ c ) {
      for ( int i = 0; i < n; ++ i ) {
        for ( int j = 0; j < n; ++ j ) {
          T[c][i][j] = T_base[c][i][j];
        }
      }
    }

    const int QS_base[3] = {2, 3, 3};
    const int QT_base[3] = {2, 1, 3};
    const int QK_base[3] = {1, 2, 2};
    for ( int i = 0; i < 3; ++ i ) {
      QS[i] = QS_base[i];
      QT[i] = QT_base[i];
      QK[i] = QK_base[i];
    }

    sol.run();

    const int query_result_expected[3] = {4, 5, 3};
    for ( int i = 0; i < 3; ++ i ) {
      ASSERT_EQ(query_result_expected[i], query_result[i]);
    }
  }


}
