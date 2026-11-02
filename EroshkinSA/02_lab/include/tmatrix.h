// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

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
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE) throw out_of_range("Too big size of vector");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz)
  {
      pMem = v.pMem;
      v.pMem = nullptr;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) return *this;
      if (sz != v.sz) {
          T* newpMem = new T[v.sz];
          sz = v.sz;
          delete[] pMem;
          pMem = newpMem;
      }
      //std::copy(v.pMem, v.pMem + v.sz, pMem);
      for (int i = 0; i < sz; i++) pMem[i] = v.pMem[i];
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v) return *this;
      delete[] pMem;
      pMem = v.pMem;
      sz = v.sz;
      v.pMem = nullptr;
      v.sz = 0;
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind) 
  {
      return at(ind);
  }
  const T& operator[](size_t ind) const
  {
      return at(ind);
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz) throw out_of_range("Incorrect index");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz) throw out_of_range("Incorrect index");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;
      for (int i = 0; i < sz; i++) if (pMem[i] != v.pMem[i]) return false;
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return (!(*this == v));
  }

  // скалярные операции
  TDynamicVector operator+(T val) const 
  {
      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; i++) res.pMem[i] = val + pMem[i];
      return res;
  }

  TDynamicVector operator-(T val) const
  {
      return (*this + (-val));
  }
  TDynamicVector operator*(T val) const
  {
      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; i++) res.pMem[i] = val * pMem[i];
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v) const 
  {
      if (sz != v.sz) throw std::exception("Invalid arguments");
      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; i++) res.pMem[i] = pMem[i] + v.pMem[i];
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v) const
  {
      return (*this + v * (-1));
  }
  T operator*(const TDynamicVector& v) const //noexcept(noexcept(T()))
  {
      if (sz != v.sz) throw std::exception("Invalid arguments");
      T ans{};
      for (int i = 0; i < sz; i++) ans += pMem[i] * v.pMem[i];
      return ans;
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
      if (sz == 0) throw std::exception("Can't create a zero size matrix");
      if (sz > MAX_MATRIX_SIZE) throw std::exception("Too large matrix size");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz - i);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return false;
      for (int i = 0; i < sz; i++) if (pMem[i] != m.pMem[i]) return false;
      return true;
  }


  size_t size() const noexcept
  {
      return sz;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val) const
  {
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++) res.pMem[i] = pMem[i] * val;
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
  {
      if (v.size() != sz) throw std::exception("Invalid argument");
      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz - i; j++) {
              res[i] += pMem[i][j] * v[i + j];
          }
      }
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) const
  {
      if (m.sz != sz) throw std::exception("Invalid argument");
      TDynamicMatrix<T> res(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz - i; j++) res[i][j] = pMem[i][j] + m[i][j];
      }
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m) const
  {
      return (*this + m * (-1));
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m) const
  {
      if (m.sz != sz) throw std::exception("Invalid argument");
      TDynamicMatrix<T> res(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = i; j < sz; j++) {
              for (int k = i; k <= j; k++)
                  res[i][j - i] += pMem[i][k - i] * m[k][j - k];
          }
      }
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      T unused;
      for (int i = 0; i < v.size(); i++) {
          for (int j = 0; j < i; j++) istr >> unused;
          for (int j = 0; j < v.sz - i; j++) istr >> v[i][j];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.size(); i++) {
          for (int j = 0; j < i; j++) ostr << 0 << '\t';
          for (int j = 0; j < v.sz - i; j++) ostr << v[i][j] << '\t';
          ostr << endl;
      }
      return ostr;
  }
};

#endif
