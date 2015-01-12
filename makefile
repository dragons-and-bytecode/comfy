CLANG_ARGS = -g
DEPEND_DIRS = -I ./dependencies/include -L ./dependencies/lib
DEPEND_ARGS = $(DEPEND_DIRS) -lslre

comfy: setup
	clang $(CLANG_ARGS) $(DEPEND_ARGS) src/*.c src/features/*.c -o build/comfy
	
setup:
	mkdir -p build
	
run: comfy
	@echo ""
	./build/comfy --source ./src --watch
	@echo ""
	
debug: comfy
	@echo ""
	lldb -- ./build/comfy --source ./src --watch
	@echo ""

comfy_test:
	clang $(CLANG_ARGS) $(DEPEND_ARGS) filetests/comfy_test.c -o build/comfy_test

test: comfy comfy_test
	@rm -rf filetests/target
	@mkdir -p filetests/target
	@echo ""
	@echo ""
	@./build/comfy --source ./filetests/source --target ./filetests/target
	@echo ""
	@echo ""
	@./build/comfy_test ./filetests/source ./filetests/target ./filetests/expected
	
clean:
	rm -rf build
	rm -rf _site
	
dependencies: slre

slre:
	@mkdir -p dependencies/lib
	@mkdir -p dependencies/include
	clang -c $(CLANG_ARGS) dependencies/slre/slre.c -o dependencies/slre/slre.o
	ar rs dependencies/lib/libslre.a dependencies/slre/*.o
	@rm dependencies/slre/*.o
	cp -rf dependencies/slre/*.h dependencies/include
