#include <iostream>

int ** convert(const int *, size_t, const size_t *, size_t);
int ** copy (int **, size_t, size_t);
void destroy(int **, size_t);
int ** create(size_t, size_t);
void construct(int **, int, size_t, size_t);
void input(int **, size_t, size_t);
void output(int **, size_t, size_t);
void convert_testing();

int ** convert(const int * t, size_t n, const size_t * lns, size_t rows)
{
  int ** table;
  size_t i = 0, j = 0;
  try {
    table = new int * [rows];
    for (; j < rows; ++j) {
      table[j] = new int[lns[j]];
      for (size_t k = 0; k < lns[j]; ++k) {
        table[j][k] = t[i];
        ++i;
      }
    }
  } catch (const std::bad_alloc & e) {
    destroy(table, j);
    throw;
  }
  return table;
}

int ** copy(int ** mtx, size_t rows, size_t cols)
{
  size_t i = 0;
  int ** new_mtx = new int * [rows];
  try {
    for (; i < rows; ++i) {
      new_mtx[i] = new int[cols];
      for (size_t j; j < cols; ++j) {
        new_mtx[i][j] = mtx[i][j];
      }
    }
  } catch (const std::bad_alloc & e) {
    destroy(new_mtx, i);
    throw;
  }
  return new_mtx;
}

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

void output(int ** mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    std::cout << mtx[i][0];
    for (size_t j = 1; j < cols; ++j) {
      std::cout << " " << mtx[i][j];
    }
    std::cout << "\n";
  }
}

void convert_testing() {
  int t[] = {5, 5, 5, 5, 6, 6, 7, 7, 7, 7, 7, 8};
  size_t n = 12;
  size_t lns[] = {4, 2, 5, 1};
  size_t rows = 4;
  int ** table = convert(t, n, lns, rows);
  for (size_t i = 0; i < rows; ++i) {
    std::cout << table[i][0];
    for (size_t j = 0; j < lns[i]; ++j) {
      std::cout << " " << table[i][j];
    }
    std::cout << "\n";
  }
  destroy(table, rows);
}

int main()
{
  convert_testing();
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

  construct(matrix, 0, rows, cols);

  input(matrix, rows, cols);
  if (!std::cin) {
    std::cerr << "bad input\n";
    destroy(matrix, rows);
    return 1;
  }

  output(matrix, rows, cols);

  int ** copied_matrix = copy(matrix, rows, cols);
  output(matrix, rows, cols);
  destroy(copied_matrix, rows);

  destroy(matrix, rows);
}
