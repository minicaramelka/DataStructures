#include "List2Queue.h"

void List2Queue::pushQueue(const ValueType& value) {
	this->pushFront(value);
}

void List2Queue::popQueue() {
    this->removeBack();
}

const ValueType& List2Queue::top() const{
	return getNode(size()-1)->value;
}

bool List2Queue::isEmptyQueue() const {
	if (this->sizeQueue() == 0)
		return true;
	return false;
}
size_t List2Queue::sizeQueue() const {
	return this->size();
}
