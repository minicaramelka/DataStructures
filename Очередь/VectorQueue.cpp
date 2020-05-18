#include "VectorQueue.h"

VectorQueue::VectorQueue() {}

void VectorQueue::pushQueue(const ValueType& value) {
	pushBack(value);
}

void VectorQueue::popQueue() {
	remove(0);
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
	return this->size();
}

VectorQueue::~VectorQueue() {}

