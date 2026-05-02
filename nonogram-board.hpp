#include <cassert>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <sys/types.h>
#include <vector>

namespace NonogramSolver {
// enum square{
//   IMPOSSIBLE, // -1
//   POSSIBLE, // at least once set, 2
//   AMBIGUOUS, // at least once not set and once set, -3
//   SUDOIMPOSSIBLE, // at least once not set, -2
//   SET, // 1
//   UNSET // 0
// };

class NonogramBoard {
  public:
      NonogramBoard(size_t w, size_t h) {
        width = w;
        height = h;
        rows_restrictions = std::vector<std::vector<u_int32_t>>(h);
        cols_restrictions = std::vector<std::vector<u_int32_t>>(w);
        board = std::vector<std::vector<int32_t>>(h, std::vector<int32_t>(w, 0));
      }

      int get_width() {
        return width;
      }

      int get_height() {
        return height;
      }

      std::vector<u_int32_t> get_row_restriction(size_t r) {
        return rows_restrictions[r];
      }

      std::vector<u_int32_t> get_col_restriction(size_t c) {
        return cols_restrictions[c];
      }

      void set_row_restriction(size_t r, std::vector<u_int32_t> row_restrictions) {
        assert(std::reduce(row_restrictions.begin(), row_restrictions.end()) + row_restrictions.size() - 1 <= width);
        std::vector<u_int32_t> copy(row_restrictions);
        rows_restrictions[r] = copy;
      }

      void set_col_restriction(size_t c, std::vector<u_int32_t> column_restrictions) {
        assert(std::reduce(column_restrictions.begin(), column_restrictions.end()) + column_restrictions.size() - 1 <= height);
        std::vector<u_int32_t> copy(column_restrictions);
        cols_restrictions[c] = copy;
      }

      std::vector<int32_t> get_row(size_t r) {
        return std::vector<int32_t>(board[r]);
      }

      std::vector<int32_t> get_col(size_t c) {
        std::vector<int32_t> res(height);
        for (size_t i = 0; i < height; i++) {
          res[i] = board[i][c];
        }
        return res;
      }

      int get(size_t r, size_t c) {
        return board[r][c];
      }

      void mark_impossible(size_t r, size_t c) {
        board[r][c] = -1;
      }

      void mark_sudoimpossible(size_t r, size_t c) {
        board[r][c] = -2;
      }

      void mark_ambiguous(size_t r, size_t c) {
        board[r][c] = -3;
      }

      void mark_possible(size_t r, size_t c) {
        board[r][c] = 2;
      }

      void set(size_t r, size_t c) {
        board[r][c] = 1;
      }

      void unset(size_t r, size_t c) {
        board[r][c] = 0;
      }

      bool validate_row(size_t r) {
        std::vector<u_int32_t> restrictions = rows_restrictions[r];
        u_int32_t count = 0;
        size_t curr = 0;
        for (size_t c = 0; c < width; c++) {
          if (board[r][c] == 1) {
            count += 1;
          } else {
            if (count > 0) {
              if (curr >= restrictions.size() || restrictions[curr] != count) {
                return false;
              }
              curr += 1;
            }
            count = 0;
          }
        }
        if (curr >= restrictions.size() || restrictions[curr] != count) {
          return false;
        }
        return true;
      }

      bool validate_column(size_t c) {
        std::vector<u_int32_t> restrictions = cols_restrictions[c];
        u_int32_t count = 0;
        size_t curr = 0;
        for (size_t r = 0; r < height; r++) {
          if (board[r][c] == 1) {
            count += 1;
          } else {
            if (count > 0) {
              if (curr >= restrictions.size() || restrictions[curr] != count) {
                return false;
              }
              curr += 1;
            }
            count = 0;
          }
        }
        if (curr >= restrictions.size() || restrictions[curr] != count) {
          return false;
        }
        return true;
      }
      

  private:
    size_t width;
    size_t height;
    std::vector<std::vector<u_int32_t>> rows_restrictions;
    std::vector<std::vector<u_int32_t>> cols_restrictions;
    std::vector<std::vector<int32_t>> board;
};
} // namespace NonogramSolver