#include "stdafx.h"
#include "Student.h"

using namespace std;

Student::Student()
{
	YearOfBirht = mark = 0;
}

Student::Student(const Student& right)
{
	*this = right;
}

void Student::setName(std::basic_string<typeS> name)
{
	studentName = name;
}

basic_string<typeS> Student::getName()
{
	return studentName;
}

void Student::setLastname(std::basic_string<typeS> lastname)
{
	studentLastname = lastname;
}

basic_string<typeS> Student::getLastname()
{
	return studentLastname;
}

void Student::setSurname(std::basic_string<typeS> surname)
{
	studentSurname = surname;
}

basic_string<typeS> Student::getSurname()
{
	return studentSurname;
}

void Student::setYearOfBirht(int year)
{
	YearOfBirht = year;
}

short int Student::getYearOfBirht()
{
	return YearOfBirht;
}

void Student::setAverMark(float averMark)
{
	mark = averMark;
}

float Student::getAverMark()
{
	return mark;
}

Student& Student::operator=(const Student& right)
{
	if (this != &right)
	{
		studentName = right.studentName;
		studentSurname = right.studentSurname;
		studentLastname = right.studentLastname;
		YearOfBirht = right.YearOfBirht;
		mark = right.mark;
	}

	return *this;
}

int Student::compareStudents(const Student& right) const
{
	int result = studentSurname.compare(right.studentSurname); //сравниваем отчество

	if (result == 0) //если полностью совпадает 
	{
		result = studentName.compare(right.studentName); //проверяем имя

		if (result == 0) //если имя и отчество совпадают
			result = studentLastname.compare(right.studentLastname); //проверяем фамилию
	}
	return result; //возвращаем то, что получили
}

bool Student::operator==(const Student& right)
{
	return compareStudents(right) == 0;
}

bool Student::operator!=(const Student& right)
{
	return compareStudents(right) != 0; //любой результат кроме 0 
}

bool Student::operator>=(const Student& right)
{
	return compareStudents(right) != -1; //любой результат кроме -1 
}

bool Student::operator<=(const Student& right)
{
	return compareStudents(right) != 1; //любой результат кроме 1 
}

bool Student::operator>(const Student& right)
{
	return compareStudents(right) == 1;
}

bool Student::operator<(const Student& right)
{
	return compareStudents(right) == -1; //любой результат кроме -1
}

outputstream& operator<<(outputstream& output, Student& right)
{
	output << right.studentSurname << __T(" ") << right.studentName << __T(" ") //Т - макрос для вывода в Юникоде 
		<< right.studentLastname << __T(" ") << right.YearOfBirht << __T(" ") << right.mark << endl;

	return output;
}


inputStream& operator >> (inputStream& input, Student& right)
{
	input >> right.studentSurname >> right.studentName >> right.studentLastname >> right.YearOfBirht >> right.mark;

	return input;
}
