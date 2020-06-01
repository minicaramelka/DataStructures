#include "VectorStack.h"

void VectorStack::push(const ValueType& value) {
	MyVector::pushBack(value);
}

void VectorStack::pop() {
	MyVector::popBack();
}

const ValueType& VectorStack::top() const {
	return (*this)[MyVector::size() - 1];
}

bool VectorStack::isEmpty() const {
	if (MyVector::size() == 0)
		return true;
	return false;
}

size_t VectorStack::size() const {
	return this->MyVector::size();
}
