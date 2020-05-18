#pragma once
#include <iostream>
// Уровень абстракции
// клиентский код подключает именно этот хедер

// тип значений в стеке
using ValueType = double;

// на основе какого контейнера работает стек
enum class QueueContainer {
	Vector = 0,
	List,
	List2,
	// можно дополнять другими контейнерами
};

// декларация класса с реализацией
class QueueImplementation;

class Queue
{
public:
	// Большая пятерка
	Queue(QueueContainer container = QueueContainer::Vector);
	// элементы массива последовательно подкладываются в стек
	Queue(const ValueType* valueArray, const size_t arraySize, QueueContainer container = QueueContainer::Vector);

	Queue(const Queue& copyStack);
	Queue& operator=(const Queue& copyQueue);

	// Здесь как обычно
	Queue(Queue&& moveQueue) noexcept;
	Queue& operator=(Queue&& moveQueue) noexcept;

	~Queue();

	// добавление в хвост
	void push(const ValueType& value);
	// удаление с хвоста
	void pop();
	// посмотреть элемент в хвосте
	const ValueType& top() const;
	// проверка на пустоту
	bool isEmpty() const;
	// размер 
	size_t size() const;
private:
	// указатель на имплементацию (уровень реализации)
	QueueImplementation* _pimpl = nullptr;
	// тип контейнера, наверняка понадобится
	QueueContainer _containerType;
};

