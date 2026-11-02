// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//           ☦

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz > MAX_VECTOR_SIZE) throw length_error("The vector size is too large");

    if (sz == 0) throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
    this->sz = v.sz;
    pMem = new T[this->sz];
    for (size_t i = 0; i < this->sz; i++) {
      pMem[i] = v.pMem[i];
    }
    //copy(v.pMem, v.pMem + v.sz, this->pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
    this->sz = v.sz;
    this->pMem = v.pMem;
    v.pMem = nullptr;
    v.sz = 0;
  }
  ~TDynamicVector() { delete[] this->pMem; }

  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this == &v) return *this;
    if (this->sz != v.sz) {
      delete[] this->pMem;
      this->pMem = new T[v.sz];
    }
    this->sz = v.sz;
    for (size_t i = 0; i < this->sz; i++) {
      pMem[i] = v.pMem[i];
    }
    //copy(v.pMem, v.pMem-v.sz,this->pMem);
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    if (this == &v) return *this;
    delete[] this->pMem;
    this->sz = v.sz;
    this->pMem = v.pMem;
    v.pMem = nullptr;
    v.sz = 0;
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if (ind >= this->sz) throw out_of_range("Invalid vector element index");
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if (ind >= this->sz) throw out_of_range("Invalid vector element index");
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (this->sz != v.sz) return false;
    for (size_t i = 0; i < this->sz; i++) {
      if (pMem[i] != v.pMem[i]) return false;
    }
    return true;
    //return equal(pMem, pMem + sz, v.pMem);
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector<T> res(*this);
    for (size_t i = 0; i < res.sz; i++) {
      res.pMem[i] += val;
    }
    return res;
  }
  TDynamicVector operator-(T val)
  {
    return (*this + (val*(-1)));
  }
  TDynamicVector operator*(T val)
  {
    TDynamicVector<T> res(*this);
    for (size_t i = 0; i < res.sz; i++) {
      res.pMem[i] *= val;
    }
    return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v) 
  {
    if (this->sz != v.sz) throw invalid_argument("Addition of vectors of different lengths");
    TDynamicVector<T> res(*this);
    for (size_t i = 0; i < res.sz; i++) {
      res.pMem[i] += v.pMem[i];
    }
    return res;
  }
  TDynamicVector operator-(const TDynamicVector& v) 
  {
    if (this->sz != v.sz) throw invalid_argument("Subtraction of vectors of different lengths");
    TDynamicVector<T> res(*this);
    for (size_t i = 0; i < res.sz; i++) {
      res.pMem[i] -= v.pMem[i];
    }
    return res;
    //return (*this + (v*(-1)));
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
    if (this->sz != v.sz) throw invalid_argument("The dot product for vectors of different lengths");
    T res{};
    for (size_t i = 0; i < this->sz; i++) {
      res += pMem[i] * v.pMem[i];
    }
    return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};

//==========================================================================================
// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (s > MAX_MATRIX_SIZE) throw length_error("The matrix size is too large");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz-i);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    if (this->sz != m.sz) return false;
    for (size_t i = 0; i < sz;i++) {
      if (pMem[i] != m.pMem[i]) return false;
    }
    return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
    TDynamicMatrix<T> res(*this);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = res.pMem[i] * val;
    }
    return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    if (sz!=v.size()) throw invalid_argument("Multiplying matrix by vector of different size");
    TDynamicVector<T> res(sz);
    T sum;
    for (size_t i = 0; i < sz; i++) {
      sum = T{};
      for (size_t j = i; j < sz; j++) {
        sum += pMem[i][j - i] * v[j];
      }
      res[i] = sum;
    }
    return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    if(sz!=m.sz) throw invalid_argument("Addition of matrices of different sizes");
    TDynamicMatrix<T> res(*this);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = res.pMem[i] + m.pMem[i];
    }
    return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if (sz != m.sz) throw invalid_argument("Substraction of matrices of different sizes");
    TDynamicMatrix<T> res(*this);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = res.pMem[i] - m.pMem[i];
    }
    return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if (sz != m.sz) throw invalid_argument("Multiply of matrices of different sizes");
    TDynamicMatrix<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t j = i; j < sz; j++) {
        T sum{};
        for (size_t k = i; k <= j; k++) {
          sum += pMem[i][k - i] * m.pMem[k][j - k];
        }
        res[i][j - i] = sum;
      }
    }
    return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for (size_t i = 0; i < m.sz; i++)
      istr >> m.pMem[i];
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++) {
      cout << "   ";
      for (size_t j = 0; j < i; j++) {
        ostr << "0 ";
      }
      ostr << v.pMem[i] << endl;
     }
    return ostr;
  }

  //определитель
  T det() const noexcept {
    T det{};
    det = pMem[0][0];
    for (size_t i = 1; i < sz; i++) {
      det *= pMem[i][0];
    }
    return det;
  }

  //след матрицы
  T trace() const noexcept {
    T tr{};
    tr = pMem[0][0];
    for (size_t i = 1; i < sz; i++) {
      tr += pMem[i][0];
    }
    return tr;
  }

  //собственные числа
  TDynamicVector<T> eigen_values() const {
    TDynamicVector<T> ev(sz);
    for (size_t i = 0; i < sz; i++) {
      ev[i] = pMem[i][0];
    }
    return ev;
  }
};

#endif __TDynamicMatrix_H__
