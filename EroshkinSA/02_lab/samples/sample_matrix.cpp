// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void main()
{
  TDynamicMatrix<int> a(3), b(3), c(3), d(3), e(3), f(3);
  TDynamicVector<int> x(3), y(3);
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класса работы с матрицами"
    << endl;
  int cnt = 1;
  for (i = 0; i < 3; i++)
    for (j = i; j < 3; j++ )
    {
      a[i][j - i] = cnt;
      b[i][j - i] = cnt++;
    }
  for (i = 0; i < 3; i++) x[i] = i + 2;
  c = a + b;
  d = a - b;
  e = a * b;
  f = a * 100;
  y = a * x;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  cout << "Matrix c = a + b" << endl << c << endl;
  cout << "Matrix d = a - b" << endl << d << endl;
  cout << "Matrix e = a * b" << endl << e << endl;
  cout << "Matrix f = a * 100" << endl << f << endl;
  cout << "Vector x = " << endl << x << endl;
  cout << "Vector y = a * x" << endl << y << endl;
}
//---------------------------------------------------------------------------
