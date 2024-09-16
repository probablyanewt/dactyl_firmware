#include <lhs.h>
#include <rhs.h>

void matrix_init() {
  lhs_init();
  rhs_init();
}

void matrix_scan(int keystate[12][6]) {
  int lhs_keystate[6][6] = {{0}} , rhs_keystate[6][6] = {{0}};
  lhs_scan(lhs_keystate);
  rhs_scan(rhs_keystate);
  int column, row;
  for (row = 0; row < 6; row++) {
    for (column = 0; column < 6; column++) {
      keystate[column][row] = lhs_keystate[column][row];
    }

    for (column = 0; column < 6; column++) {
      keystate[column + 6][row] = rhs_keystate[column][row];
    }
  }
}

