#pragma once
#include <iostream>
#include "QueueImplementation.h"
#include "MyVector.h"
 // меняете на include вашего вектора

// вариант с использованием ранее написанного вектора и множественного наследования
// если бы вектор не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class VectorQueue : public QueueImplementation, public MyVector
{
	public:
	VectorQueue();
	void pushQueue(const ValueType& value);
	void popQueue();
	const ValueType& top() const;
	bool isEmptyQueue() const;
	size_t sizeQueue() const;
	~VectorQueue();
	
};
