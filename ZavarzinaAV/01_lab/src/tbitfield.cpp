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
    if (len < 0)
        throw invalid_argument("ОТРИЦАТЕЛЬНАЯ ДЛИНА");
    BitLen = len;
    MemLen = (BitLen + BITS_IN_ELEMENT_MINUS_ONE) / BITS_IN_ELEMENT; 
    pMem = new TELEM[MemLen]();

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
    pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const// в каком элементe pMem находится элемент с номером n?
{
    return n/ BITS_IN_ELEMENT;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return (TELEM)1<<(n % BITS_IN_ELEMENT); 
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= BitLen)
        throw out_of_range("БИТ ВЫХОДИТ ИЗ ГРАНИЦ");

    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen)
        throw out_of_range("БИТ ВЫХОДИТ ИЗ ГРАНИЦ");

    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen)
        throw out_of_range("БИТ ВЫХОДИТ ИЗ ГРАНИЦ");

    return (pMem[GetMemIndex(n)] & GetMemMask(n))!=0;
}

// битовые операции

const TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this == &bf)
        return *this;

    if (MemLen != bf.MemLen)
    {
        TELEM* newMem = new TELEM[bf.MemLen];

        delete[] pMem;
        pMem = newMem;
        MemLen = bf.MemLen;
    }

    BitLen = bf.BitLen;

    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];

    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 0;

    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return 0;

    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или" 
{
    TBitField res(max(BitLen, bf.BitLen));
    int i = 0;
    for ( i ; i < min(MemLen, bf.MemLen); ++i) {
        res.pMem[i] = this->pMem[i] | bf.pMem[i];
    }
    while (i < MemLen) {
        res.pMem[i] = this->pMem[i];
        i++;
    }
    while (i < bf.MemLen) {
        res.pMem[i] = bf.MemLen;
        i++;
    }
    return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и" 
{
    TBitField res(max(BitLen, bf.BitLen));

    for (int i = 0; i < min(MemLen, bf.MemLen); ++i) {
        res.pMem[i] = this->pMem[i] & bf.pMem[i];
    }

    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);
    for (int i = 0; i < BitLen; i++) {
        if (GetBit(i) == 0)
            res.SetBit(i);
    }
    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    for (int i = 0; i < bf.BitLen; i++) {
        int bit;
        istr >> bit;

        if (bit == 1)
            bf.SetBit(i);
        else
            bf.ClrBit(i);
    }

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        ostr << bf.GetBit(i);

    return ostr;
}
