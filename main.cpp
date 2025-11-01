#include <iostream>

void destroy(int ** mtx, size_t created)
{
  for (size_t i = 0; i < created; i++) {
    delete[] mtx[i];
  }
  delete[] mtx;
}

int ** create(size_t rows, size_t cols)
{
  size_t created = 0;
  int ** mtx = new int * [rows];
  try {
    for (; created < rows; created++) {
      mtx[created] = new int[cols];
    }
  } catch (const std::bad_alloc & e) {
    destroy(mtx, created);
    throw;
  }
  return mtx;
}

int main()
{
  size_t rows = 5, cols = 6;
  int ** matrix = nullptr;
  try {
    matrix = create(rows, cols);
  } catch (const std::bad_alloc & e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  for (size_t i = 0; i < rows; ++i) {
    std::cout << matrix[i][0];
    for (size_t j = 1; j < cols; ++j) {
      std::cout << " " << matrix[i][j];
    }
    std::cout << "\n";
  }
  destroy(matrix, rows);
}
