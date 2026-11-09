// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__
#include <cassert>
#include <iostream>
#include <utility>
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
    if (sz == 0 || sz >= MAX_VECTOR_SIZE)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {};  // У типа T д.б. констуктор по умолчанию
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
          pMem = new T[sz]();
          std::copy(v.pMem, v.pMem + v.sz, this->pMem);

  
      
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  { 
      pMem = nullptr;
      Swap(*this, v);
      
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  void Swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept {
      std::swap(lhs.sz, rhs.sz);
      std::swap(lhs.pMem, rhs.pMem);
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          TDynamicVector tmp(v);
          Swap(*this, tmp);
       }
      
      return *this;
      
  }
  TDynamicVector & operator=(TDynamicVector && v) noexcept
  {     
      Swap(*this, v); 
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
  T& at(int ind)
  {
      if (ind >= sz || ind < 0) {
          throw std::out_of_range("");
      }
      return pMem[ind];
  }
  const T& at(int ind) const
  {
      if (ind >= sz || ind < 0) {
          throw std::out_of_range("");
      }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (sz != v.sz) {
        return false;
    }
      
    for (int i = 0; i < sz;i++) {
        if (pMem[i] != v.pMem[i])
            return false;
        continue;
    }
    return true;
     
      
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return!(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      if (val != 0) {
          for (int i = 0; i < sz; i++) {
              pMem[i] += val;
          }
      }
      return *this;
  }
  TDynamicVector operator-(T val)
  {
      if (val != 0) {
          for (int i = 0; i < sz; i++) {
              pMem[i] -= val;
          }
      }
      return *this;
  }
  TDynamicVector operator*(T val)
  {
      for (int i = 0; i < sz; i++)
          pMem[i] *= val;
      return *this;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v){
      if (sz != v.sz) {
          throw std::exception(" different sizes");
      }
          
      TDynamicVector res(sz);
      for (int i = 0; i < sz; ++i)
          res.pMem[i] = this->pMem[i] + v.pMem[i];
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw std::exception(" different sizes");
      TDynamicVector res(sz);
      for (int i = 0; i < sz; ++i) {
          res.pMem[i] = this->pMem[i] - v.pMem[i];
      }
      return res;
  }
  T operator*(const TDynamicVector& v)// noexcept(noexcept(T()))
  {
      if (sz != v.sz) {
          throw std::exception("");
      }
      T res = 0;
      for (int i = 0; i < sz; ++i) {
          res += this->pMem[i] * v.pMem[i];
      }
      return res;
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
      ostr << v.pMem[i] << '\t'; // требуется оператор<< для типа T
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
  TDynamicMatrix(size_t s = 1):TDynamicVector<TDynamicVector<T>>(check_max_size(s))
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz - i);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;

  static size_t check_max_size(size_t s) {
      if (s > MAX_MATRIX_SIZE) {
          throw std::out_of_range("");
      }
      return s;
  }
  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator ==(m);
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return !(*this == m);
  }
  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {             
      TDynamicMatrix<T> res(sz);

      for (int i = 0; i < res.sz; i++) {
          res.pMem[i] =this->pMem[i] *val;
      }
      return res;
  }

  //матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v){
  
      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; i++) {
          res[i] = this->pMem[i] * v;
      }
      return res;
      
  }

  //матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T> res(sz);

      for (int i = 0; i < res.sz; i++) {
          res.pMem[i] = this->pMem[i] + m.pMem[i];
      }
      return res;
  }
  
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T> res(sz);

      for (int i = 0; i < res.sz; i++) {
          res.pMem[i] = this->pMem[i] - m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if (this->sz != m.sz) {
        throw std::exception("");
    }
    TDynamicMatrix<T> res(sz);
    for (int i = 0; i < res.sz; i++) {
        for (int j = i; j < res.sz; j++) {
            T sum = 0;
            for (int k = i; k <= j; k++) {
                sum += this->pMem[i][k - i] * m.pMem[k][j - k];
            }
            res.pMem[i][j - i] = sum;
        }
          
    }
    return res;
  }

  //ввод/вывод
   friend istream& operator>>(istream& istr, TDynamicMatrix& v)
   {
    for (int i = 0; i < v.sz; ++i)
        istr >> v[i];
    return istr;
   }
   friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
   {
       for (int i = 0; i < v.sz; i++)
       {
           for (int j = 0; j < i; j++)
               ostr << 0 << '\t';
           ostr << v[i] << "\n";
       }
            
        return ostr;
    }
};

#endif


