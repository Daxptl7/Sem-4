#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace std::chrono;

typedef vector<vector<int>> Matrix;

void printMatrix(const Matrix &matrix) {
  for (const auto &row : matrix) {
    for (int val : row) {
      cout << setw(5) << val << " ";
    }
    cout << "\n";
  }
  cout << "\n";
}

Matrix add(const Matrix &A, const Matrix &B) {
  int n = A.size();
  Matrix C(n, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      C[i][j] = A[i][j] + B[i][j];
  return C;
}

Matrix subtract(const Matrix &A, const Matrix &B) {
  int n = A.size();
  Matrix C(n, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      C[i][j] = A[i][j] - B[i][j];
  return C;
}

Matrix generateRandomMatrix(int n) {
  Matrix matrix(n, vector<int>(n));
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distr(-10, 10);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i][j] = distr(gen);
    }
  }
  return matrix;
}

int nextPowerOf2(int n) {
  int power = 1;
  while (power < n) {
    power *= 2;
  }
  return power;
}

Matrix padMatrix(const Matrix &A, int newSize) {
  int oldSize = A.size();
  Matrix C(newSize, vector<int>(newSize, 0));
  for (int i = 0; i < oldSize; i++) {
    for (int j = 0; j < oldSize; j++) {
      C[i][j] = A[i][j];
    }
  }
  return C;
}

Matrix standardMultiply(const Matrix &A, const Matrix &B) {
  int n = A.size();
  Matrix C(n, vector<int>(n, 0));
  for (int i = 0; i < n; i++) {
    for (int k = 0; k < n; k++) {
      for (int j = 0; j < n; j++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return C;
}

Matrix strassenMultiplyRecursive(const Matrix &A, const Matrix &B) {
  int n = A.size();

  if (n <= 64) {
    return standardMultiply(A, B);
  }

  int half = n / 2;
  Matrix a11(half, vector<int>(half)), a12(half, vector<int>(half)),
      a21(half, vector<int>(half)), a22(half, vector<int>(half)),
      b11(half, vector<int>(half)), b12(half, vector<int>(half)),
      b21(half, vector<int>(half)), b22(half, vector<int>(half));

  for (int i = 0; i < half; i++) {
    for (int j = 0; j < half; j++) {
      a11[i][j] = A[i][j];
      a12[i][j] = A[i][j + half];
      a21[i][j] = A[i + half][j];
      a22[i][j] = A[i + half][j + half];

      b11[i][j] = B[i][j];
      b12[i][j] = B[i][j + half];
      b21[i][j] = B[i + half][j];
      b22[i][j] = B[i + half][j + half];
    }
  }

  Matrix S1 = subtract(b12, b22);
  Matrix S2 = add(a11, a12);
  Matrix S3 = add(a21, a22);
  Matrix S4 = subtract(b21, b11);
  Matrix S5 = add(a11, a22);
  Matrix S6 = add(b11, b22);
  Matrix S7 = subtract(a12, a22);
  Matrix S8 = add(b21, b22);
  Matrix S9 = subtract(a11, a21);
  Matrix S10 = add(b11, b12);

  Matrix P1 = strassenMultiplyRecursive(a11, S1);
  Matrix P2 = strassenMultiplyRecursive(S2, b22);
  Matrix P3 = strassenMultiplyRecursive(S3, b11);
  Matrix P4 = strassenMultiplyRecursive(a22, S4);
  Matrix P5 = strassenMultiplyRecursive(S5, S6);
  Matrix P6 = strassenMultiplyRecursive(S7, S8);
  Matrix P7 = strassenMultiplyRecursive(S9, S10);

  Matrix c11 = add(subtract(add(P5, P4), P2), P6);
  Matrix c12 = add(P1, P2);
  Matrix c21 = add(P3, P4);
  Matrix c22 = subtract(subtract(add(P5, P1), P3), P7);

  Matrix C(n, vector<int>(n));
  for (int i = 0; i < half; i++) {
    for (int j = 0; j < half; j++) {
      C[i][j] = c11[i][j];
      C[i][j + half] = c12[i][j];
      C[i + half][j] = c21[i][j];
      C[i + half][j + half] = c22[i][j];
    }
  }
  return C;
}

Matrix strassenMultiply(const Matrix &A, const Matrix &B) {
  int n = A.size();
  int m = nextPowerOf2(n);

  Matrix A_padded = padMatrix(A, m);
  Matrix B_padded = padMatrix(B, m);

  Matrix C_padded = strassenMultiplyRecursive(A_padded, B_padded);

  Matrix C(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      C[i][j] = C_padded[i][j];
    }
  }
  return C;
}

int main() {

  vector<int> sizes = {2, 4, 8, 16, 32, 64, 128, 256, 512};

  cout << setw(8) << "N x N" << " | " << setw(16) << "Standard O(n^3)" << " | "
       << setw(16) << "Strassen O(n^2.81)" << " | "
       << "Faster Algorithm\n";
  cout << string(68, '-') << "\n";

  for (int n : sizes) {
    Matrix A = generateRandomMatrix(n);
    Matrix B = generateRandomMatrix(n);

    auto startStd = high_resolution_clock::now();
    Matrix CStandard = standardMultiply(A, B);
    auto endStd = high_resolution_clock::now();
    double timeStd = duration_cast<microseconds>(endStd - startStd).count();

    auto startStr = high_resolution_clock::now();
    Matrix CStrassen = strassenMultiply(A, B);
    auto endStr = high_resolution_clock::now();
    double timeStr = duration_cast<microseconds>(endStr - startStr).count();

    cout << setw(8) << n << " | " << setw(13) << timeStd << " us | " << setw(13)
         << timeStr << " us | ";

    if (timeStr < timeStd) {
      cout << "STRASSEN WINS!\n";
    } else {
      cout << "STANDARD WINS\n";
    }
  }

  cout << "\n\nNote: For exact constants C_1, C_2 in C_1*n^3 and C_2*n^2.81,\n";
  cout << "Substitute the time metrics measured at the largest size bounds "
          "(e.g. N=512) into:\n";
  cout << "C_1 = time_std / (512^3)\n";
  cout << "C_2 = time_strassen / (512^2.81)\n";

  return 0;
}