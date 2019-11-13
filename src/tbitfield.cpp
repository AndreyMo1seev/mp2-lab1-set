// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"


TBitField::TBitField(int len)
{
	if (len <= 0) throw - 1;
	BitLen = len;
	MemLen = (len / 32) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
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
	return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n >= BitLen)
		throw("Ошибка");
	else
	{
		TELEM mask = 1;
		int position = n % (sizeof(TELEM) * 8);
		mask = mask << position;
		return mask;
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen; //было memlen
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen) throw - 1;
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || n >= BitLen) throw - 1;
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int pos = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	int res;
	res = pMem[pos] & mask;
	return res;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[]pMem;
	pMem = new TELEM[bf.MemLen];
	for (int i = 0; i < bf.MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 0;
	else {
		for (int i = 0; i < MemLen - 1; i++)
			if (pMem[i] != bf.pMem[i]) return 0;
			else for (int i = (MemLen - 1) * 32; i < BitLen; i++)
				if (GetBit(i) != bf.GetBit(i)) return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 1;
	for (int i = 0; i < MemLen - 1; i++) {
		if (pMem[i] != bf.pMem[i]) return 1;
	}
	for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
		if (GetBit(i) != bf.GetBit(i)) return 1;
	}
	return 0;;
}

TBitField TBitField::operator|(const TBitField & bf) // операция "или"
{
	int n;
	if (BitLen >= bf.BitLen) n = BitLen;
	else n = bf.BitLen;
	TBitField t(n);
	for (int i = 0; i < t.MemLen; i++) {
		t.pMem[i] = bf.pMem[i] | pMem[i];
	}
	return t;
}

TBitField TBitField::operator&(const TBitField & bf) // операция "и"
{
	TBitField tmp(BitLen > bf.BitLen ? BitLen : bf.BitLen);
	for (int i = 0; i < MemLen && i < bf.MemLen; i++)
		tmp.pMem[i] = pMem[i] & bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int n = BitLen;
	TBitField res(n);
	for (int i = 0; i < BitLen; i++)
		if (GetBit(i) == 0)
			res.SetBit(i);
		else
			res.ClrBit(i);
	return res;
}

// ввод/вывод

istream& operator>>(istream & istr, TBitField & bf) // ввод
{
	char c;
	int i = 0;
	do
	{
		istr >> c;
		if (c == '0')
		{
			bf.ClrBit(i);
		}
		if (c == '1')
		{
			bf.SetBit(i);
		}
		i++;
	} while (c == '0' || c == '1');
	return istr;
}

ostream& operator<<(ostream & ostr, const TBitField & bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i) == 0)
		{
			ostr << 0;
		}
		else
		{
			ostr << 1;
		}
	}
	return ostr;
}


// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
/*
#include "tbitfield.h"


TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = len / (sizeof(TELEM) * 8)+1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
	else
		throw "Ошибка!Неправильный ввод";
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < bf.MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()//Деструктор
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n >= BitLen)
		throw("Ошибка");
	else
	{
		TELEM mask = 1;
		int position = n % (sizeof(TELEM) * 8);
		mask = mask << position;
		return mask;
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >=0 && n < BitLen)
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	else
		throw("Ошибка ввода");
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen)
	{
		int bit = GetMemIndex(n);
		pMem[bit]&=~GetMemMask(n);
	}
	else
		throw("Ошибка ввода");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int bit = GetMemIndex(n);
	if ((pMem[bit] & GetMemMask(n)) == GetMemMask(n))
		return 1;
	else
		return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[]pMem;
	pMem = new TELEM[bf.MemLen];
	for (int i = 0; i < bf.MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	else
	{
		for (int i = 0; i < bf.MemLen; i++)
		{
			if (this->pMem[i] != bf.pMem[i])
				return 0;
		}
		return 1;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;
	else
	{
		for (int i = 0; i < bf.MemLen; i++)
		{
			if (this->pMem[i] != bf.pMem[i])
				return 1;
		}
		return 0;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tmp(BitLen > bf.BitLen ? BitLen : bf.BitLen);
	for (int i = 0; i < MemLen && i < bf.MemLen; i++)
		tmp.pMem[i] = pMem[i] | bf.pMem[i];
	return tmp;
}
TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField tmp(BitLen > bf.BitLen ? BitLen : bf.BitLen);
	for (int i = 0; i < MemLen && i < bf.MemLen; i++)
		tmp.pMem[i] = pMem[i] & bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i)==0)
			tmp.SetBit(i);
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char bit;
	for (int i = 0; i <= bf.BitLen; i++)
	{
		istr >> bit;
		if ((int)bit == 1)
			bf.SetBit(i);
		if ((int)bit == 0)
			bf.ClrBit(i);
		else
			throw("Неправильный ввод");
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int bit;
	for (int i = 0; i < bf.BitLen; i++)
	{
		bit = bf.GetBit(i) == 1 ? 1 : 0;
		ostr << bit;
	}
	return ostr;
}
*/