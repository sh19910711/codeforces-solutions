#include <iostream>
#include <array>

template <int SIZE> struct IndexList {
  static const int START_INDEX = 0;
  static const int OFFSET = 10;
  static const int REAL_SIZE = SIZE + OFFSET * 2;
  int N;
  int id[REAL_SIZE];
  int L[REAL_SIZE];
  int R[REAL_SIZE];

  IndexList(): N(SIZE) {
    update_id();
    update_lr();
  }

  const int get_real_index( const int& raw_id ) {
    return OFFSET + raw_id;
  }

  void update_lr() {
    for ( int i = 0; i < OFFSET; ++ i )
      R[i] = get_real_index(0);
    R[START_INDEX] = get_real_index(0);
    for ( int i = 0; i < N; ++ i ) {
      const int& real_index = get_real_index(i);
      L[real_index] = real_index - 1;
      R[real_index] = real_index + 1;
    }
  }

  void update_id() {
    for ( int i = 0; i < N; ++ i ) {
      id[get_real_index(i)] = i;
    }
  }

  template <class Func> void each( Func func ) {
    std::cout << "N = " << N << std::endl;
    for ( int i = R[START_INDEX]; i < get_real_index(N); i = R[i] ) {
      func(id[i]);
    }
  }

  void remove( const int& raw_id ) {
    const int& real_id = get_real_index(raw_id);
    const int& l_id = L[real_id];
    const int& r_id = R[real_id];
    R[l_id] = r_id;
    L[r_id] = l_id;
  }
};

int main() {
  std::array<int, 5> arr = {3, 1, 2, 4, 5};
  IndexList<5> list;
  list.remove(2);
  list.each( [&]( const int& id ) { std::cout << id << ": " << arr[id] << std::endl; } );
}

