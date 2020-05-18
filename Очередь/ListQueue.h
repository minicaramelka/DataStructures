#pragma once

#include"LinkedList.h"
#include "QueueImplementation.h"
 // меняете на include вашего листа

// вариант с использованием ранее написанного списка и множественного наследования
// если бы список не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class ListQueue : public QueueImplementation, public LinkedList
{

	void pushQueue(const ValueType& value);
	// удаление с хвоста
	void popQueue();
	// посмотреть элемент в хвосте
	const ValueType& top() const;
	// проверка на пустоту
	bool isEmptyQueue() const;
	// размер 
	size_t sizeQueue() const;
};

