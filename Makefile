build:
	g++ --std=c++20 -o build comp_pass.cpp main.cpp types.cpp

clean:
	rm build

all: build
