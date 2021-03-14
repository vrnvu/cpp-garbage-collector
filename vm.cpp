#include <iostream>
#include <optional>

#include "vm.h"

VM* newVM() {
	VM *vm = new VM {
		.numObjects = 0,
		.maxObjects = VM_MAX_NUM_OBJECTS
	};
	return vm;
}

void push(VM *vm, Object *value) {	
	vm->stack[vm->stackSize] = value;
	vm->stackSize++;
}

Object* pop(VM *vm) {
	Object *lastObject = vm->stack[vm->stackSize];
	vm->stackSize--;
	return lastObject;
}

std::optional<Object*> peek(VM *vm, int i) {
	if(i < 0 || i > vm->stackSize) {
		return std::nullopt;
	} else {
		return vm->stack[i];
	}
}

void mark(Object* object) {
	if(object == nullptr) return;
	if(object->marked) return;

	object->marked = true;

	if (object->type == PAIR) {
		mark(object->head);
		mark(object->tail);
	}
}

void markAllObjects(VM *vm) {
	for(int i = 0; i < vm->stackSize; i++) {
		if (auto object = peek(vm, i)) {
			mark(*object);
		}
	}
}

void sweep(VM* vm) {
	Object **object = &vm->head;
	while(*object) {
		if (!(*object)->marked) {
			Object *unreached = *object;
			*object = unreached->next;
			free(unreached);
			vm->numObjects--;
		} else {
			(*object)->marked = 0;
			object = &(*object)->next;
		}
	}
}

void gc(VM* vm) {
	markAllObjects(vm);
	sweep(vm);
}



Object* newObject(VM *vm, ObjectType type) {
	if (vm->numObjects == vm->maxObjects) gc(vm);
	Object *head = vm->head;
	Object *object = new Object {
		.type = type,
		.marked = 0,
		.next = head	
	};
	vm->head = object;
	vm->numObjects++;
	return object;
}

void pushInt(VM *vm, int intValue) {
	Object *object = newObject(vm, INT);
	object->value = intValue;
	push(vm, object);
}

Object* pushPair(VM *vm) {
	Object *object = newObject(vm, PAIR);
	object->tail = pop(vm);
	object->head = pop(vm);

	push(vm, object);
	return object;
}

void printStack(VM *vm) {
	for(int i = 0; i < vm->stackSize; i++) {
		if (auto object = peek(vm, i)) {
			switch((*object)->type) {
				case INT:
					std::cout << "{ v:" << (*object)->value << ", m: " << (*object)->marked << "}" << std::endl;
					break;
				case PAIR:
					std::cout << "TODO PRINT STACK OF PAIR" << std::endl;
					break;
			}
		}
	}
}

void freeVM(VM* vm) {
	vm->stackSize = 0;
	gc(vm);
	free(vm);
}