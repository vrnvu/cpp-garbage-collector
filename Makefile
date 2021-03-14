default:
	@g++ main.cpp vm.cpp -std=c++17 -o target
	@./target

clean:
	rm target