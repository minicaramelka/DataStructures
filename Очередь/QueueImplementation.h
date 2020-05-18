#pragma once
#include <iostream>
// приходится тянуть ValueType во все места,
// наглядная демонстрация того, почему с шаблонами было бы легче.
// Ждем, когда дойдете до этого на МиСП.
using ValueType = double;

// интерфейс для конкретных реализаций контейнера для стека
class QueueImplementation {
public:
	// добавление в хвост
	virtual void pushQueue(const ValueType& value) = 0;
	// удаление с хвоста
	virtual void popQueue() = 0;
	// посмотреть элемент в хвосте
	virtual const ValueType& top() const = 0;
	// проверка на пустоту
	virtual bool isEmptyQueue() const = 0;
	// размер 
	virtual size_t sizeQueue() const = 0;
	// виртуальный деструктор
	~QueueImplementation() {};
};
