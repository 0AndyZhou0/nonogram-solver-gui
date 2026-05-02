#include "nonogram-board.hpp"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <stddef.h>
#include <sys/types.h>
#include <vector>

namespace NonogramSolver {

enum result {
  COMPLETELY_SOLVED,
  REST_IS_IMPOSSIBLE
};

void solve(NonogramBoard &board);
bool solve_row(NonogramBoard &board, size_t row);
bool solve_col(NonogramBoard &board, const size_t col);
bool solve_row_helper(std::vector<int32_t> &row, std::vector<int32_t> temp_row, const std::vector<u_int32_t> &restrictions, const size_t i_restriction, const size_t start);
bool set_n(std::vector<int32_t> &row, const size_t start, const size_t n);
bool unset_n(std::vector<int32_t> &row, const size_t start, const size_t n);

void add_possible(int32_t &x);
void add_sudoimpossible(int32_t &x);
} // namespace NonogramSolver