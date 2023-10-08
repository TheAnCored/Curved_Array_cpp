#include <iostream>

// Звено списка
class Link{
public:
	Link *next_link;
	int digit;
};

// Список
class List{
public:
	Link *first;
	Link *current;
    Link *last;

	size_t length_list;

	// Метод создания списка нужной длины
	List *NewList(size_t length);


	// Очистка списка
	void Delete(List *list);
	
	
	// Методы удаления элемента из списка
	
	// Удаление Конца
    void PopEnd(List *list);

    // Удаление начала
	void PopStart(List *list);
	
	// Удаление по индексу
	void PopLink(List *list, int index);
};