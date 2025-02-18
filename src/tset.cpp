
// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.MaxPower)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf.GetLength())
{
	MaxPower = BitField.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (BitField.GetBit(Elem))
		return 1;
	else
		return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0 || Elem >= MaxPower) throw - 1;
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem >= 0 && Elem < MaxPower)
		BitField.ClrBit(Elem);
	else throw "Ошибка";
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet & s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet & s) const // сравнение
{
	if (MaxPower == s.MaxPower)
	{
		if (BitField == s.BitField)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

int TSet::operator!=(const TSet & s) const // сравнение
{
	if (MaxPower != s.MaxPower)
	{
		return 1;
	}
	else
	{
		if (BitField != s.BitField)
			return 1;
		else
			return 0;
	}
}

TSet TSet::operator+(const TSet & s) // объединение
{
	TSet tmp(MaxPower > s.MaxPower ? MaxPower : s.MaxPower);
	tmp.BitField = BitField | s.BitField;
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem < 0 || Elem >= MaxPower)
		throw("Ошибка");
	else
	{
		TSet tmp(MaxPower);
		tmp.BitField.SetBit(Elem);
		return tmp;
	}
}

TSet TSet::operator-(const int Elem) // разность с элементом
{

	if (Elem < 0 || Elem >= MaxPower)
		throw("Ошибка");
	else
	{
		TSet tmp(MaxPower);
		tmp.BitField.ClrBit(Elem);
		return tmp;
	}
}

TSet TSet::operator*(const TSet & s) // пересечение
{
	int size = MaxPower > s.MaxPower ? MaxPower : s.MaxPower;
	TSet tmp(size);
	tmp.BitField = BitField & s.BitField;
	return tmp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet res(~BitField);
	return res;

}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
	int a;
	istr >> a;
	while (a >= 0) istr >> a;
	return istr;
}
ostream& operator<<(ostream & ostr, const TSet & s) // вывод
{
	ostr << "{";
	for (int i = 0; i < s.MaxPower; i++) {
		if (s.IsMember(i)) {
			ostr << i;
			if (i != s.MaxPower - 1) ostr << ", ";
		}
	}
	ostr << "}" << endl;
	return ostr;
}
