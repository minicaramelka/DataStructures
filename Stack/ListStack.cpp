#include "ListStack.h"

void ListStack::push(const ValueType& value) {
	this->pushFront(value);
}

void ListStack::pop() {
    this->removeFront();
}

const ValueType& ListStack::top() const{
	return getNode(0)->value;
}

bool ListStack::isEmptyStack() const {
	if (this->sizeStack() == 0)
		return true;
	return false;
}
size_t ListStack::sizeStack() const {
	return this->size();
}