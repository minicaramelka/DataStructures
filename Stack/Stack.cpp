#include "Stack.h"
#include "ListStack.h"
#include "VectorStack.h"
#include "StackImplementation.h"

#include <stdexcept>

using namespace std;

Stack::Stack(StackContainer container)
	: _containerType(container)
{
	switch (container)
	{
	case StackContainer::List :{
		_pimpl = new ListStack();	// конкретизируйте под ваши конструкторы, если надо
		break;
	}
	case StackContainer::Vector :{
		_pimpl = new VectorStack();	// конкретизируйте под ваши конструкторы, если надо
		break;
	}
	default:
		throw std::runtime_error("Неизвестный тип контейнера");
	}
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container)
: _containerType(container){
    switch (container){
        case StackContainer::List: {
			_pimpl = new ListStack();// конкретизируйте под ваши конструкторы, если надо
			break;
        }
        case StackContainer::Vector: {
			_pimpl = new VectorStack(); // конкретизируйте под ваши конструкторы, если надо
			break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
        }
	for (size_t i = 0; i < arraySize; i++) {
		_pimpl->push(valueArray[i]);
	}
}

Stack::Stack(const Stack& copyStack) 
: Stack(copyStack._containerType) {
	switch (_containerType){
		case StackContainer::List: {
			_pimpl = new ListStack(*(static_cast<ListStack*>(copyStack._pimpl)));
			break;
		}
		case StackContainer::Vector: {
			_pimpl = new VectorStack(*(static_cast<VectorStack*>(copyStack._pimpl)));
			break;
		}
		default:
			throw std::runtime_error("Неизвестный тип контейнера");
	}
}

Stack& Stack::operator=(const Stack& copyStack) {
    int copySize = copyStack.size();
	delete _pimpl;
    if(copyStack._containerType == StackContainer::List) {
        _pimpl = new ListStack();// конкретизируйте под ваши конструкторы, если надо
    }
    if(copyStack._containerType == StackContainer::Vector) {
        _pimpl = new VectorStack();    // конкретизируйте под ваши конструкторы, если надо
    }
    ValueType* array = new ValueType[copySize];
    for (int i = copySize - 1; i >= 0; i--) {
        array[i] = copyStack._pimpl->top();
        copyStack._pimpl->pop();
    }
    for (int i = 0; i < copySize; i++) {
        _pimpl->push(array[i]);
        copyStack._pimpl->push(array[i]);
    }
    delete[] array;
    return *this;
    // TODO: вставьте здесь оператор return
}

Stack::~Stack()
{
	delete _pimpl;		// композиция!
}

void Stack::push(const ValueType& value)
{
	// можно, т.к. pushStack определен в интерфейсе
    _pimpl->push(value);
}

void Stack::pop()
{
    _pimpl->pop();
}

const ValueType& Stack::top() const
{
	return _pimpl->top();
}

bool Stack::isEmpty() const
{
	return _pimpl->isEmptyStack();
}

size_t Stack::size() const
{
	return _pimpl->sizeStack();
}