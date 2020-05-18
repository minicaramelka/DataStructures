#include "ListQueue.h"

void ListQueue::pushQueue(const ValueType& value) {
	this->pushFront(value);
}

void ListQueue::popQueue() {
    this->removeBack();
}

const ValueType& ListQueue::top() const{
	return getNode(size()-1)->value;
}

bool ListQueue::isEmptyQueue() const {
	if (this->sizeQueue() == 0)
		return true;
	return false;
}
size_t ListQueue::sizeQueue() const {
	return this->size();
}

