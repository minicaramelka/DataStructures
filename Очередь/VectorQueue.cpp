#include "VectorQueue.h"

void VectorQueue::pushQueue(const ValueType& value) {
	pushBack(value);
}

void VectorQueue::popQueue() {
	erase(0);
}

const ValueType& VectorQueue::top() const {
	return (*this)[0];
}

bool VectorQueue::isEmptyQueue() const {
	if (sizeQueue() == 0)
		return true;
	return false;
}

size_t VectorQueue::sizeQueue() const {
	return MyVector::size();
}
