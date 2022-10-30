compiler := g++
optimization := -O0
compiler_flags := -Wall -Wextra -g $(optimization)
src_files := src/main.cpp src/vector3.cpp
obj_files := obj/main.o obj/vector3.o
src_dir := src
obj_dir := obj
binary_name := physics

all: $(binary_name)

$(binary_name): obj/main.o
	$(compiler) $^ -o $@

$(obj_dir)/%.o: $(src_dir)/%.cpp
	$(compiler) $(compiler_flags) -c $^ -o $@

clean:
	rm -rf $(binary) $(obj_files)
