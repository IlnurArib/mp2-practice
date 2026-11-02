// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <stdexcept>

TBitField::TBitField(int len)
{
    if (len < 0) {
        throw invalid_argument("negative len");
    }
    BitLen = len;
    MemLen = (BitLen + BITS - 1) / BITS; 
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n >= BitLen || n < 0) {
        throw out_of_range("bit index out of range");
    }
    return n / BITS; 
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n >= BitLen || n < 0) {
        throw out_of_range("bit index out of range");
    }
    return (TELEM)1 << (n % BITS); 
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n >= BitLen || n < 0) {
        throw out_of_range("bit index out of range");
    }
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n >= BitLen || n < 0) {
        throw out_of_range("bit index out of range");
    }
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= BitLen || n < 0) {
        throw out_of_range("bit index out of range");
    }
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;;
}

// битовые операции

const TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf) {
        BitLen = bf.BitLen;
        if (MemLen != bf.MemLen) {
            delete[] pMem;
            MemLen = bf.MemLen;
            pMem = new TELEM[MemLen];
        }
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField & bf) const // сравнение
{
    if (BitLen != bf.BitLen) {
        return 0;
    }
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i])
            return 0;
    }
    return 1;

}


int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int MinLen = min(MemLen, bf.MemLen);
    int MaxLen = max(MemLen, bf.MemLen);
    TBitField Result(max(BitLen, bf.BitLen));
    for (int i = 0; i < MinLen; i++)
        Result.pMem[i] = pMem[i] | bf.pMem[i];
    for (int i = MinLen; i < MemLen; i++)
        Result.pMem[i] = pMem[i];
    for (int i = MinLen; i < bf.MemLen; i++)
        Result.pMem[i] = bf.pMem[i];
    return Result;

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField Result(max(BitLen, bf.BitLen));
    for (int i = 0; i < min(MemLen, bf.MemLen); i++)
        Result.pMem[i] = pMem[i] & bf.pMem[i];
    return Result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField Result(BitLen);
    for (int i = 0; i < MemLen; i++) {
        Result.pMem[i] = ~pMem[i];
    }
    if (Result.MemLen * BITS != Result.BitLen) { 
        TELEM Mask = ((TELEM)1 << (Result.BitLen % BITS)) - 1;  
        Result.pMem[Result.MemLen - 1] = Result.pMem[Result.MemLen - 1] & Mask;
    }
    return Result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    for (int i = 0; i < bf.BitLen; i++) {
        int bit;
        istr >> bit;
        if (bit == 1) {
            bf.SetBit(i);
        }
        else {
            bf.ClrBit(i);
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        ostr << bf.GetBit(i);
    return ostr;
}
