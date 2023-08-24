CXX = g++
CXXFLAGS = -D _DEBUG -D _SHOW_STACK_TRACE -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla -Wno-write-strings -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr #-flto-odr-type-merging

files = SolverUtils.cpp Solver.cpp IOFunctions.cpp main.cpp Tester.cpp Logger.cpp ColorConsole.cpp
objects = $(files:.cpp=.o)

buildDir = build

.PHONY: all clean prepare
all: prepare SquareSolver

build_docs:
	doxygen Doxyfile

$(addprefix $(buildDir)/, $(objects)): $(buildDir)/%.o: %.cpp SolverUtils.h Solver.h IOFunctions.h Tester.h ColorConsole.h Logger.h
	@echo [CC] $< -o $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

SquareSolver: $(addprefix $(buildDir)/, $(objects))
	@echo [CC] $^ -o $@
	@$(CXX) $(CXXFLAGS) $^ -o $(addprefix $(buildDir)/, $@)

clean:
	rm -f build/*.o all
	rm build/SquareSolver

prepare:
	@mkdir -p $(buildDir)

