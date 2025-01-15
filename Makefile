.PHONY: default
default: build

cpp_source_files := $(shell find src -name *.cpp) 
cpp_source_files := $(filter-out src/parser.cpp,$(cpp_source_files))
cpp_source_files := $(filter-out src/tokens.cpp,$(cpp_source_files))
cpp_object_files := $(patsubst src/%.cpp, build/%.o, $(cpp_source_files))

CPP_INCLUDE_PATH := include

OUT_NAME := kokac

LIBS := -lm

# commented for now
LLVM_OPTS :=#`llvm-config --cxxflags --ldflags --system-libs --libs all`
OPTS := -fuse-ld=lld -march=native -g -O0 $(LLVM_OPTS)

build/parser.o: src/parser.cpp
	bison -d -o src/parser.cpp parser.y -v -t
# bison interface doesn't seen like it has an easy way to specify output for the header file....
	@mv src/parser.hpp include/parser.hpp 
# nor the output debug...
	@mv src/parser.output debug/ 
	g++ $(OPTS) -c -I $(CPP_INCLUDE_PATH) src/parser.cpp -o $@ $(LIBS)

build/tokens.o: src/tokens.cpp
	flex -o src/tokens.cpp tokens.l
	g++ $(OPTS) -c -I $(CPP_INCLUDE_PATH) src/tokens.cpp -o $@ $(LIBS)


$(cpp_object_files): build/%.o : src/%.cpp
	@mkdir -p $(dir $@)
	g++ $(OPTS) -c -I $(CPP_INCLUDE_PATH) $(patsubst build/%.o, src/%.cpp, $@) -o $@ $(LIBS)

.PHONY: build
build: $(cpp_object_files) build/parser.o build/tokens.o
	g++ $(OPTS) -o $(OUT_NAME) $(cpp_object_files) build/parser.o build/tokens.o $(LIBS)

clean:
	@rm -rfv build/
	@mkdir build
	@echo "CLEAN"