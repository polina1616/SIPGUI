﻿#pragma once

#include "stdafx.h"
//#include "blist.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename T > class Iterator;

template <class T>
class List
{
private:
	friend Iterator<T>;

	struct TElem
	{
		T Inf;
		TElem *Next;
	};
	TElem *tail, *elem; //указатель на хвост списка, elem - указатель на текущий элемент
	int k = 0;

public:

	List() {
		elem = tail = NULL;
	}

	bool isEmpty()
	{
		return (tail == NULL);
	}

	//сортировка слиянием
	void sort()
	{
		if (tail) {
			TElem *head = tail->Next;
			tail->Next = NULL; // делаем из кольцевого - односвязный список
			mergeSort(head); // сортируем
							 // ищем конец, чтобы закольцевать
			TElem *tmp = head;
			do
			{
				tmp = tmp->Next;
			} while (tmp->Next);
			tail = tmp;
			tail->Next = head; // закольцевали список
							   //cout << "\n Количество рекурсивных вызовов: " << k << "\n";
			k = 0;
		}
	}

	//функция добавления элемента в конец списка
	void addToEnd(T value)
	{
		TElem *tmp = new TElem; // выделяем память на новый элемент
		tmp->Inf = value;	// записываем значение
		if (tail)
		{
			tmp->Next = tail->Next;
			tail = tail->Next = tmp;
		}
		else
		{
			tail = tmp;
			tmp->Next = tail;
		}
		elem = tail;
	}

	//Добавление в начало списка
	void addToBegin(T value)
	{
		TElem *tmp = new TElem; // выделяем память на новый элемент
		tmp->Inf = value;	// записываем значение
		if (tail)
			tmp->Next = tail->Next;
		else
			tail = tmp;
		tail->Next = tmp; //указатель с первого элемента на второй
		elem = tail->Next;
	}

	//Поиск элемента
	bool found(T a) {
		if (tail)
		{
			TElem *element = tail;
			do
			{
				if (element->Inf == a) {
					elem = element;
					return true;
				}
				element = element->Next;
			} while (element != tail);
		}
		elem = NULL;
		return false;
	}

	

	//Удаление элемента с указанной инф. частью
	void del_Inf(T a) {
		if (tail)
		{
			TElem *prev = tail;
			TElem *cur = tail->Next;
			do {
				if (cur->Inf == a) {
					if (cur != cur->Next) {
						prev->Next = cur->Next;
						if (cur == tail)
							tail = prev;
					}
					else
						tail = NULL;

					break;
				}

				prev = cur;
				cur = cur->Next;

			} while (cur != tail);

			delete cur;
		}
	}

	//delete all
	void del_all() {
		if (tail) {
			TElem *current, *next;
			current = tail->Next;
			tail->Next = NULL;
			tail = current;
			// = current->Next;

			while (tail)
			{
				current = tail;
				tail = tail->Next;
				delete current;
			}

			delete tail;
			tail = NULL;
			elem = NULL;
		}
	}

	//упорядочение нового элемента
	void sort_elem(T value) {
		if (tail) {
			TElem *newElement = new TElem;
			newElement->Inf = value;
			TElem *current = tail;
			if (current->Inf < value) { //если вставляем после хвоста
				newElement->Next = current->Next;
				current->Next = newElement;
				tail = newElement;
			}
			else {
				while (current->Next->Inf < value) {
					current = current->Next;
				}
				newElement->Next = current->Next;
				current->Next = newElement;
			}

		}
	}

	void sort_now_elem()
	{
		// elem - текущий элемент (сортируемый)
		if (tail)
		{
			TElem *prevNew = NULL; // элемент после которого надо вставлять current
			TElem *prev = tail, *cur = tail->Next; // элемент перед current и временный курсор
			bool findFlag = false;

			while (cur != elem) // пока не найдем предыдущий перед текущим (elem)
			{
				if (cur->Inf >= elem->Inf) // Если нашли место для вставки
				{
					prevNew = prev;
					findFlag = true;
					break;
				}
				prev = cur;
				cur = cur->Next;
			}

			for (; cur != elem; prev = cur, cur = cur->Next);

			if (!findFlag) //вставляем справа от сортируемого элемента
			{
				cur = cur->Next;
				prevNew = prev;
				while (cur != tail->Next)
				{
					if (cur->Inf >= elem->Inf) //если уже прошли цикл и не нашли (значит надо вставлять после хвоста)
					{
						if (elem == tail)
							tail = elem->Next;
						prev->Next = elem->Next; // вырезаем элемент
						elem->Next = prevNew->Next; //вставка
						prevNew->Next = elem;
						return;
					}
					prevNew = cur;
					cur = cur->Next;
				}

				//Если в списке так и не нашли место -> надо вставлять в конец
				//вставка в конец списка
				if (elem != tail)
				{
					prev->Next = elem->Next; // вырезаем элемент
					elem->Next = prevNew->Next; //вставка
					prevNew->Next = elem;
					tail = elem;
				}

				return;
			}

			//вставляем слева от сортируемого элемента
			if (elem == tail)
				tail = prev;

			if (prevNew != elem)
			{
				prev->Next = elem->Next;// вырезаем элемент
				elem->Next = prevNew->Next;//вставка
				prevNew->Next = elem;
			}
		}
	}


	/* //óïîðÿäî÷åíèå òåêóùåãî ýëåìåíòà (âûäåëÿåì åãî èç ñïèñêà è âñòàâëÿåì â íóæíîå ìåñòî)
	void sort_now_elem() {
	if (tail) // åñëè åñòü ñïèñîê
	{
	TElem *prevNew = NULL; // ýëåìåíò ïîñëå êîòîðîãî áóäåò âñòàâêà
	TElem *prev = tail, *cur = tail->Next;
	bool found = false;

	while (cur != elem)
	{
	if (cur->Inf >= elem->Inf) // íàøëè êóäà âñòàâëÿòü
	{
	prevNew = prev;
	found = true;
	break;
	}
	prev = cur;
	cur = cur->Next;
	}

	for (; cur != elem; prev = cur, cur = cur->Next);

	if (!found)
	{
	cur = cur->Next;
	while (cur != tail->Next)
	{
	if (cur->Inf <= elem->Inf) {
	if (elem->Next != cur) {

	}
	return;
	}

	prevNew = cur;
	cur = cur->Next;


	}
	return;
	}


	if (prevNew != prev) // åñëè íàéäåííîå ìåñòî íå ðàâíî ïðåäûäóùåìó ïåðåä ñîðòèðóåìûì ýëåìåíòîì, çíà÷èò íàäî ñîðòèðîâàòü
	{
	if (!prevNew)
	prevNew = tail;

	if (prevNew == elem && prev == tail)
	{
	prev->Next = elem->Next;
	elem->Next = prev->Next;
	prev->Next = elem;
	}
	else
	{
	if (elem == tail)
	tail = prev;
	//âûðåçàåì ýëåìåíò
	prev->Next = elem->Next;

	//âñòàâêà
	elem->Next = prevNew->Next;
	prevNew->Next = elem;
	}

	}

	if (prevNew == tail)
	{
	elem->Inf > tail->Inf ? tail = elem : tail = tail;
	}
	}
	}*/

	//Вывод списка
	void show()
	{
		if (tail) // если список отсутствует ()
		{
			TElem *tmp = tail->Next;
			do
			{
				//cout << tmp->Inf << "   ";
				tmp = tmp->Next; //доходим до конца списка
			} while (tmp != tail->Next); //в случае кольцевого списка проверяем есть ли данный элемент последним
		}
	}
	/*******************************************************************/

	T& getCurrInf() // get current elem copy Inf - получение копии информационной части 
	{
		return elem->Inf;
	}

	//переводит указатель на текущий элемент в начало
	void setCurrToHead()
	{
		if (tail)
			elem = tail->Next;
	}

	//переводит указатель на текущий элемент в конец
	void setCurrToTail() {
		elem = tail;
	}

	//перегруженный оператор !, определяющий существование элементов в структуре данных
	bool operator! () {
		return tail != NULL;
	}

	//перегруженный оператор присваивания
	List<T>& operator=(const List<T>& right)
	{
		if (this != &right && &right != NULL) //проверка на самоприсваивание 
		{
			TElem *leftHead = tail, *leftCur, *leftCurPrev;
			TElem *rightHead = right.tail, *rightCur;

			if (rightHead) // если есть правый список
			{
				rightHead = rightHead->Next; //переход с хвоста на голову
				rightCur = rightHead;

				if (tail)
				{
					leftHead = leftHead->Next;
					leftCur = leftHead;
					do //пока есть right and left
					{
						leftCur->Inf = rightCur->Inf;
						leftCurPrev = leftCur;
						leftCur = leftCur->Next;
						rightCur = rightCur->Next;
					} while (rightCur != rightHead && leftCur != leftHead);

					//правый закончился, удаляем оставшиеся элементы левого
					if (rightCur == rightHead && leftCur != leftHead) {
						TElem *del;
						leftCurPrev->Next = leftHead;
						tail = leftCurPrev;
						do {
							del = leftCur;
							leftCur = leftCur->Next;
							delete del;
						} while (leftCur != leftHead);
					}

					if (leftCur == leftHead) {
						do //пока есть right
						{
							addToEnd(rightCur->Inf);
							rightCur = rightCur->Next;
						} while (rightCur != right.tail->Next);
					}
				}
				//левый закончился, добавляем элементы из правого в конец
				else {
					//if (rightCur != rightHead) {
						do //пока есть right
						{
							addToEnd(rightCur->Inf);
							rightCur = rightCur->Next;
						} while (rightCur != right.tail->Next);
					//}
				}
			}
			else del_all(); //удаляем все элементы из left
		}
		return *this;
	}

	//конструктор копирования
	List<T>(const List<T>& right)
	{
		elem = tail = NULL;
		*this = right; // присваиваем с помощью перегруженного оператора присваивания
	}

	//перегруженный оператор - переход к следующему элементу
	List<T>& operator++()
	{
		elem = elem ? elem->Next : tail;
		return *this;
	}

	/*******************************************************************/
	/*Деструктор*/
	~List()
	{
		del_all();
	}

	//пузырек
	bool isSorted() {
		TElem *tmp = tail;
		if (tail)
		{
			do
			{
				tmp = tmp->Next;
				if (tmp->Inf > tmp->Next->Inf)
					return false;
			} while (tmp->Next != tail);
			return true;
		}
		return false;
	}

	//Получение указателя на информационную часть текущего элемента
	T& GetCurrInfPtr()
	{
		if (tail)
			return elem->Inf;
		throw - 1; //errcode -1 - отсутствует список
	}

	T* getElemWithID(int index) {
		if (tail)
		{
			elem = tail->Next;
			for (int i = 0; i < index; i++) {
				elem = elem->Next;
			}
			return &elem->Inf;
		}
	}


private:
	void mergeSort(TElem *&root)
	{
		k++; //количество рекурсивных вызовов
		TElem *list1, *list2;
		TElem *head = root;
		if ((head == NULL) || (head->Next == NULL))
		{
			return;
		}

		findMid(head, list1, list2);

		mergeSort(list1); //сортируем каждую часть
		mergeSort(list2);

		root = mergeList(list1, list2);

	}

	TElem* mergeList(TElem *list1, TElem *list2)
	{
		TElem temphead = { 0, NULL }, *tail = &temphead;
		k++;
		while ((list1 != NULL) && (list2 != NULL)) //пока в подсписке еще есть элементы
		{
			TElem **min = (list1->Inf < list2->Inf) ? &list1 : &list2; //выбираем меньший
			TElem *Next = (*min)->Next;
			tail = tail->Next = *min;
			*min = Next;
		}
		tail->Next = list1 ? list1 : list2; //если один из подсписков закончился
		return temphead.Next;
	}

	void findMid(TElem *root, TElem *&list1, TElem *&list2)
	{
		/**
		Возвращает указатель на элемент структуры TElem<T> рядом с серединой списка
		и после обрезаем оригинальный список перед этим элементом
		*/
		TElem *slow, *fast;

		//â ñëó÷àå ïóñòîãî ñïèñêà (èëè îäèí ýëåìåíò)
		if ((root == NULL) || (root->Next == NULL))
		{
			list1 = root;
			list2 = NULL;
			return;
		}
		else
		{
			/*
			два курсора, fast движется в 2 раза быстрее slow, на одну итерацию slow происходит 2 итерации fast
			за счет этого находится середина списка (когда fast == NULL, slow будет ровно в центре списка)
			*/
			slow = root;
			fast = root->Next;
			while (fast != NULL)
			{
				fast = fast->Next;
				if (fast != NULL)
				{
					slow = slow->Next;
					fast = fast->Next;
				}
			}
			list1 = root;
			list2 = slow->Next;
			slow->Next = NULL;
		}
	}

	//получить указатель на голову
	TElem* getHead()
	{
		if (tail)
			return tail->Next;
	}

};

template <class T>
class Iterator {
private:
	typename List<T>::TElem *cur; //указатель на список

public:
	Iterator()
	{
		cur = NULL;
	}

	Iterator(List<T>& list)
	{
		cur = list.tail;
	}

	//Итератор на основе существующего
	Iterator(Iterator<T>& iterator)
	{
		cur = iterator.cur;
	}

	Iterator<T>& operator++()
	{
		cur = cur ? cur->Next : tail;
		return *this;
	}

	Iterator<T>& operator=(Iterator<T>& right)
	{
		cur = right.cur;
		return *this;
	}

	Iterator<T>& operator=(List<T>& list)
	{
		cur = list.tail;
		return *this;
	}

	bool operator!()
	{
		return cur;
	}

	bool getCurrInf(T& tmp)
	{
		if (cur)
		{
			tmp = cur->Inf;
			return true;
		}
	}

	T& getCurrInfRef() // Ссылка на информационную часть элемента
	{
		if (cur)
		{
			return cur->Inf;
		}
	}

};





/*if (cur != 0)
{
cur = cur->Next;
}
return *this;*/


