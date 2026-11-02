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
    system("color F0"); //5-violet 0-black
    setlocale(LC_ALL, "Russian");

    TDynamicMatrix<int> a(5), b(5), c(5), d(5) , e(5), t(5);
    int i, j;
    cout << " Тестирование класса работы с матрицами: " << endl << endl;
    for (i = 0; i < 5; i++)
      for (j = i; j < 5; j++)
      {
        a[i][j - i] = i * 10 + j;
        d[i][j - i] = (i * 10 + j) * 10;
        b[i][j - i] = (i * 10 + j) * 100;
      }
    c = a + b;
    e = b - d;
    t = a * b;
    cout << "  Matrix a = " << endl << a << endl;
    cout << "  Matrix d = " << endl << d << endl;
    cout << "  Matrix b = " << endl << b << endl;
    cout << "  Matrix c = a + b" << endl << c << endl;
    cout << "  Matrix e = b - d" << endl << e << endl;
    cout << "  Matrix t = a * b" << endl << t << endl;
    bool flag = (a == b);
    cout << "   a==b? --> " << boolalpha <<  flag<< endl;
    cout << "======================================================"<< endl;

    TDynamicMatrix<int> p(3);
    TDynamicVector<int> v(3), res(3);
    for (i = 0; i < 3; i++) {
      v[i] = i + 1;
      for (j = i; j < 3; j++)
      {
        p[i][j - i] = (i + 1) * 5 + j;
      }
    }
    res = p * v;
    cout << "  Matrix p = " << endl << p;
    cout << " определитель = " << p.det() <<" |" << " след матрицы = " << p.trace() << " |"
      << " собственные числа --> " << p.eigen_values()<<endl;
    cout << "  Vector v = " << v << endl;
    cout << "  Vector res = p * v = " << res << endl;

}
//---------------------------------------------------------------------------
