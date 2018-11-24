#pragma once

#include <string>
#include <iostream>
#include <tchar.h>

using namespace std;

//для автоматического выбора юникода или ANSI 
#ifdef UNICODE 
#define outputstream    wostream
#define inputStream     wistream
#define myout           wcout
//#define typeS			wchar_t
#define typeS			TCHAR
#else
#define outputstream    ostream
#define inputStream     istream
#define myout           cout
#define typeS			char
#endif


class Student
{
public:
	Student();
	Student(const Student&);

	void setName(basic_string<typeS>);
	basic_string<typeS> getName();

	void setLastname(basic_string<typeS>);
	basic_string<typeS> getLastname();

	void setSurname(basic_string<typeS>);
	basic_string<typeS> getSurname();

	void setYearOfBirht(int);
	short int getYearOfBirht();

	void setAverMark(float);
	float getAverMark();

	Student& operator = (const Student&);
	bool operator == (const Student&);
	bool operator != (const Student&);
	bool operator >= (const Student&);
	bool operator <= (const Student&);
	bool operator > (const Student&);
	bool operator < (const Student&);

	friend outputstream& operator << (outputstream&, Student&);
	friend inputStream& operator >> (inputStream&, Student&);

private:
	/*  отчество, имя и фамилия
	0 - полное совпадение
	1 - текущий студент больше (первые символы имени/фамилии/отчестве стоят выше по алфавиту)
	-1 - текущий студент меньше
	*/
	int compareStudents(const Student&) const;

	basic_string<typeS> studentName{}; //объявляем строку сразу пустой
	basic_string<typeS> studentLastname{};
	basic_string<typeS> studentSurname{};
	short int YearOfBirht;
	float mark;

/*public:
	CString studentName, studentLastname, studentSurname{};*/
};
