#include <optional>
#include "object.h"

#define STACK_MAX 256
#define VM_MAX_NUM_OBJECTS 4

struct VM {
	Object *stack[STACK_MAX];
	Object *head;

	int stackSize;
	int numObjects;
	int maxObjects;
};

VM* newVM();

void push(VM *vm, Object *value);

Object* pop(VM *vm);

std::optional<Object*> peek(VM *vm, int i);

void mark(Object* object);

void markAllObjects(VM *vm);

void sweep(VM* vm);

void gc(VM* vm);

Object* newObject(VM *vm, ObjectType type);

void pushInt(VM *vm, int intValue);

Object* pushPair(VM *vm);

void printStack(VM *vm);

void freeVM(VM* vm);
