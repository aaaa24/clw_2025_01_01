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

void construct(int ** mtx, int init, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      mtx[i][j] = init;
    }
  }
}

void input(int ** mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      std::cin >> mtx[i][j];
    }
  }
}

int main()
{
  size_t rows = 0, cols = 0;
  std::cin >> rows >> cols;
  if (!std::cin) {
    std::cerr << "bad input\n";
    return 2;
  }

  int ** matrix = nullptr;
  try {
    matrix = create(rows, cols);
  } catch (const std::bad_alloc & e) {
    std::cerr << e.what() << "\n";
    return 1;
  }

  construct(matrix, 2, rows, cols);

  input(matrix, rows, cols);
  if (!std::cin) {
    std::cerr << "bad input\n";
    return 1;
  }

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      std::cout << matrix[i][j];
      if (j != cols - 1) std::cout << " ";
    }
    std::cout << "\n";
  }

  destroy(matrix, rows);
}
