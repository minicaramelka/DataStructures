#include "VectorStack.h"

VectorStack::VectorStack() {}

void VectorStack::push(const ValueType& value) {
	pushBack(value);
}

void VectorStack::pop() {
	popBack();
}

const ValueType& VectorStack::top() const {
	return (*this)[size() - 1];
}

bool VectorStack::isEmptyStack() const {
	if (sizeStack() == 0)
		return true;
	return false;
}

size_t VectorStack::sizeStack() const {
	return this->size();
}

VectorStack::~VectorStack() {}


