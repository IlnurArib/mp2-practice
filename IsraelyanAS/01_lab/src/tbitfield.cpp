// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
#include <stdexcept>
#include "tbitfield.h"
#include <cmath>
static const int Telembite = sizeof(TELEM);
static const int Telembit = 8 * sizeof(TELEM);

TBitField::TBitField(int len)
{
    if (len < 0) {
        throw std::out_of_range("0");
    }
    BitLen = len;
    MemLen = (BitLen + Telembit - 1) / Telembit;
    pMem = new TELEM[MemLen];
    std::memset(pMem, 0, Telembite * MemLen);
}
TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    pMem = new TELEM[this->MemLen];   
    for (int i = 0; i < this->MemLen; ++i) {  
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n<0 || n >= GetLength()) {
        throw std::out_of_range("0");
    }
    return n / Telembit;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n<0 || n >= GetLength()) {
        throw std::out_of_range("0");
    }
    return ((TELEM)1 << (n % Telembit));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= GetLength()) {
        throw std::out_of_range("0");
    }
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n<0 || n >= GetLength()) {
        throw std::out_of_range("0");
    }
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n<0 || n >= GetLength()) {
        throw std::out_of_range("0");
    }
    return (pMem[GetMemIndex(n)] & GetMemMask(n))!=0;
}

// битовые операции

const TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this == &bf) {
        return *this;
    }
    if (MemLen != bf.MemLen) {
        this->MemLen = bf.MemLen;
        delete[] pMem;
        pMem = new TELEM[this->MemLen];
    }
    this->BitLen = bf.BitLen;
    
    for (int i = 0; i < this->MemLen; ++i) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (this->BitLen != bf.BitLen) {
        return 0;
    }
    for (int i = 0; i < MemLen; ++i) {
         if (pMem[i] != bf.pMem[i]) {
             return 0;
         }
    }
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    int len = min(MemLen, bf.MemLen);
    int mxlen = max(BitLen, bf.BitLen);
    TBitField res(mxlen);
    int i;
    for (i = 0; i < len; ++i) {
        res.pMem[i] = pMem[i] | bf.pMem[i];
    }
    for (; i < MemLen; ++i) {
        res.pMem[i] = pMem[i];
    }
    for (; i < bf.MemLen; ++i) {
        res.pMem[i] = bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int len = min(MemLen, bf.MemLen);
    int mxlen = max(BitLen, bf.BitLen);
    TBitField res(mxlen);         
    for (int i = 0; i < len; ++i) {
        res.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; ++i) {
        res.pMem[i] = ~pMem[i];
    }
    int t = BitLen % Telembit;
    if (t != 0 && res.MemLen > 0) {
        TELEM mask = ((TELEM)1 << t) - 1;
        res.pMem[res.MemLen - 1] &= mask;
    }
    return res;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    TELEM val;
    if (istr >> val) {
        for (int i = 0; i < bf.GetLength(); ++i) {
            if ((val >> i) & (TELEM)1) {
                bf.SetBit(i);
            }
            else {
                bf.ClrBit(i);
            }
        }
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.GetLength(); ++i) {
        ostr << bf.GetBit(i) << "\t";
    }
    return ostr;
}