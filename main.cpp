#include <iostream>

#include "vm.h"

void assert(int condition, const char* message) {
  if (!condition) {
    printf("%s\n", message);
    exit(1);
  }
}

int main() {
	VM* vm = newVM();
	pushInt(vm, 1);
	pushInt(vm, 2);
	pushInt(vm, 3);
	printStack(vm);
	// pop and markAll
	pop(vm);
	markAllObjects(vm);
	// gc then free
	gc(vm);
	assert(vm->numObjects == 2, "gc vm");
	freeVM(vm);
	assert(vm->numObjects == 0, "freed vm");
	return 0;
}
