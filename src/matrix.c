#include <lhs.h>
#include <rhs.h>

int matrix_init() {
  lhs_init();
  return rhs_init();
}

void matrix_scan() {
  lhs_scan();
  rhs_scan();
}
