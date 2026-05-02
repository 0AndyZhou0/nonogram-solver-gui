#include "solver.hpp"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <numeric>
#include <stddef.h>
#include <sys/types.h>
#include <vector>

namespace NonogramSolver {

void solve(NonogramBoard &board) {
  const size_t rows = board.get_height();
  const size_t cols = board.get_width();
  std::vector<bool> solved_rows(rows, false);
  size_t rows_left = rows;
  std::vector<bool> solved_cols(cols, false);
  size_t cols_left = cols;
  int i = 0;

  while (rows_left + cols_left != 0) {
    // std::cout << rows_left + cols_left << std::endl;
    // Rows
    for (size_t r = 0; r < rows; r++) {
      if (solved_rows[r]) {
        continue;
      }
      solve_row(board, r);
      if (board.validate_row(r)) {
        solved_rows[r] = true;
        rows_left -= 1;
      }
    }

    // Columns
    for (size_t c = 0; c < cols; c++) {
      if (solved_cols[c]) {
        continue;
      }
      solve_col(board, c);
      if (board.validate_column(c)) {
        solved_cols[c] = true;
        cols_left -= 1;
      }
    }
    if (i == 20) break;
    i++;
  }
  // for (size_t r = 0; r < board.get_height(); r++) {
  //   for (size_t c = 0; c < board.get_width(); c++) {
  //     board.set(r, c);
  //   }
  // }
}

bool solve_row(NonogramBoard &board, const size_t row) {
  std::vector<u_int32_t> restrictions = board.get_row_restriction(row);
  std::vector<int32_t> curr_row = board.get_row(row);
  std::vector<int32_t> temp_row = board.get_row(row);
  solve_row_helper(curr_row, temp_row, restrictions, 0, 0);

  for (size_t c = 0; c < curr_row.size(); c++) {
    if (curr_row[c] == -2 || curr_row[c] == -1) {
      board.mark_impossible(row, c);
    } else if (curr_row[c] == 1 || curr_row[c] == 2) { 
      board.set(row, c);
    }
  }
  return false;
}

bool solve_col(NonogramBoard &board, const size_t col) {
  std::vector<u_int32_t> restrictions = board.get_col_restriction(col);
  std::vector<int32_t> curr_col = board.get_col(col);
  std::vector<int32_t> temp_col = board.get_col(col);
  solve_row_helper(curr_col, temp_col, restrictions, 0, 0);

  for (size_t r = 0; r < curr_col.size(); r++) {
    if (curr_col[r] == -2 || curr_col[r] == -1) {
      board.mark_impossible(r, col);
    } else if (curr_col[r] == 1 || curr_col[r] == 2) { 
      board.set(r, col);
    }
  }
  return false;
}

bool solve_row_helper(std::vector<int32_t> &row, std::vector<int32_t> temp_row, const std::vector<u_int32_t> &restrictions, const size_t i_restriction, const size_t start){
  if (i_restriction == restrictions.size()) {
    return false;
  }

  size_t len = restrictions[i_restriction];
  size_t max_possible = restrictions.size() - i_restriction - 1;
  for (size_t i = i_restriction; i < restrictions.size(); i++) {
    max_possible += restrictions[i];
  }

  assert(start + len <= temp_row.size());
  // if (start + len > row.size()) {
  //   return false;
  // }

  for (size_t i = start; i <= temp_row.size() - max_possible; i++) {
    if (i > 0 && row[i-1] == 1) {
      break;
    }
    if (set_n(temp_row, i, len)) {
      solve_row_helper(row, temp_row, restrictions, i_restriction+1, i + len + 1);

      if (i_restriction == restrictions.size() - 1) {
        // Check if valid (TODO: Make better)
        size_t count = 0;
        for (size_t c = 0; c < temp_row.size(); c++) {
          if (temp_row[c] == 1) {
            count += 1;
          }
        }

        // Merge with main vector
        if (!(count > std::reduce(restrictions.begin(), restrictions.end()))) {
          for (size_t c = 0; c < temp_row.size(); c++) {
            if (temp_row[c] == 1 || temp_row[c] == 2) {
              add_possible(row[c]);
            } else {
              add_sudoimpossible(row[c]);
            }
          }
        }
      }

      // undo move
      unset_n(temp_row, i, len);
    }
    // if (row[i] == 1) {
    //   break;
    // }
  }

  return true;
}

bool set_n(std::vector<int32_t> &row, const size_t start, const size_t n) {
  for (size_t i = start; i < start + n; i++) {
    if (row[i] == -1) {
      return false;
    }
  }

  for (size_t i = start; i < start + n; i++) {
    row[i] = 1;
  }

  return true;
}

bool unset_n(std::vector<int32_t> &row, const size_t start, const size_t n) {
  for (size_t i = start; i < start + n; i++) {
    if (row[i] == -1) {
      return false;
    }
  }

  for (size_t i = start; i < start + n; i++) {
    row[i] = 0;
  }

  return true;
}

void add_possible(int32_t &x) {
  if (x == 0) {
    x = 2;
  } else if (x == -2) {
    x = -3;
  }
}

void add_sudoimpossible(int32_t &x) {
  if (x == 0) {
    x = -2;
  } else if (x == 2) {
    x = -3;
  }
}

} // namespace NonogramSolver