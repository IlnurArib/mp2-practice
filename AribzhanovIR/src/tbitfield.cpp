// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string.h>
#include <stdexcept>
// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static const int sizeTELEM = sizeof(TELEM);
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len > 0) {
        
     
        BitLen = len;
        MemLen = (BitLen + 31) / 32;
        
        
        pMem = new TELEM[MemLen];
        std::memset(pMem, 0, sizeTELEM * MemLen);
        

    }
    
    else {
        throw std::out_of_range("length can not be < 0");
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    this->pMem = new TELEM[this->MemLen];
    for (int i = 0; i < this->MemLen; ++i)
        this->pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
    
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{   
    if(n >= 0 && n < BitLen){
        return n >>(sizeTELEM+1);/*FAKE_INT*/;
    }
    else
    {
        throw std::out_of_range("index can not be < 0");
    }
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{   if(n >= 0 && n < BitLen){
    return 1u << (n & (sizeTELEM * 8 - 1))/*FAKE_INT*/;
   
    }
    else{throw std::out_of_range("index can not be < 0"); }
    
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return this->BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n >= 0 && n < BitLen)
        pMem[GetMemIndex(n)]|= GetMemMask(n);
    else
        throw std::out_of_range("index can not be < 0");
}

void TBitField::ClrBit(const int n) // очистить бит
{   if(n >= 0 && n < BitLen)
        pMem[GetMemIndex(n)] &= (~(GetMemMask(n)));
    else
        throw std::out_of_range("index can not be < 0");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= 0 && n < BitLen)
    {   
        int index = GetMemIndex(n);
        if ((pMem[index] & GetMemMask(n)) != 0)
            return 1;
        else
            return 0;
    }
    else {
        throw std::out_of_range("");
    }
    
}

// битовые операции

const TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (*this != bf) {

         this->BitLen = bf.BitLen;
         this->MemLen = bf.MemLen;
         delete[] pMem;
         this->pMem = new TELEM[this->MemLen];
         for (int i = 0; i < this->MemLen; ++i)
             this->pMem[i] = bf.pMem[i];

   
    }
    /*return FAKE_BITFIELD;*/
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
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
    return ~(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{   
    int res_sz = std::max(this->BitLen, bf.BitLen);
    TBitField result(res_sz);
    TELEM a, b;
    for (int i = 0; i < result.MemLen; i++){
        a = 0, b = 0;
        if (i < this->BitLen) {
            a = pMem[i];
        }
        if (i < bf.BitLen) {
            b = bf.pMem[i];
        }
        result.pMem[i] = a | b;
    }
        
    return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int res_sz = std::max(this->BitLen, bf.BitLen);
    TBitField result(res_sz);
    for (int i = 0; i < result.MemLen; i++) {
        if (i < this->BitLen && i < bf.BitLen)
            result.pMem[i] = pMem[i] & bf.pMem[i];
        else
            result.pMem[i] = 0;
    }
    return result;
}

 TBitField TBitField::operator~(void) // отрицание
 {
    TBitField result(BitLen);
    for (int i = 0; i < MemLen;++i) {
        result.pMem[i] = ~pMem[i];
    }
    int tailbits = BitLen % (8 * sizeof(TELEM));
    if (tailbits != 0 && result.MemLen > 0) {
        TELEM mask = ((TELEM)1 << tailbits) - 1;
        result.pMem[MemLen - 1] &= mask;
    }
    return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string s;
    istr >> s;
    for (int i = 0; i < bf.BitLen; i++){
        int bitIndex = bf.BitLen - 1 - i;
        if (i < (int)s.size() && s[s.size() - 1 - i] == '1')
            bf.SetBit(bitIndex);
        else
            bf.ClrBit(bitIndex);
    }
       
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        ostr << bf.GetBit(i) << "\t";;
    return ostr;
}
