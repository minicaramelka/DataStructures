#pragma once

#include"LinkedList2.h"
#include "QueueImplementation.h"
 // меняете на include вашего листа

// вариант с использованием ранее написанного списка и множественного наследования
// если бы список не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class List2Queue : public QueueImplementation, public LinkedList2
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
