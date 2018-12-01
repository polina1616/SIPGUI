#pragma once

#include "ringList.h"
#include <tchar.h>
#include <string>

template <typename infType> class NamedList : public List<infType>
{
protected:
	std::basic_string<TCHAR> listName;

public:
	NamedList() {
		listName = _T("");
	}

	NamedList(const std::basic_string<TCHAR> str) {
		listName = str;
	}

	~NamedList() {
		listName.clear();
	}

	std::basic_string<TCHAR> getListName() const {
		return listName;
	}

	void setListName(const std::basic_string<TCHAR> &str) {
		listName = str;
	}

	NamedList& operator=(NamedList& right)
	{
		List::operator=(right);
		listName = right.listName;
		return *this;
	}

	bool operator==(NamedList& right)
	{
		return (listName == right.listName);
	}

	bool operator!=(NamedList& right)
	{
		return !(listName == right.listName);
	}

	bool operator>(NamedList& right)
	{
		return (listName.compare(right.listName) > 0);
	}

	bool operator<(NamedList& right)
	{
		return (listName.compare(right.getListName()) < 0);
	}

	bool operator>=(NamedList& right)
	{
		return (listName.compare(right) >= 0);
	}

	bool operator<=(NamedList& right)
	{
		return (listName.compare(right) <= 0);
	}

	//Поиск элемента по ID
	

};