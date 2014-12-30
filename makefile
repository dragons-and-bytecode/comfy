CLANG_ARGS = -g

comfy: setup
	clang $(CLANG_ARGS) src/*.c -o build/comfy
	
setup:
	mkdir -p build
	
run: comfy
	@echo ""
	./build/comfy --target ~/tmp/out --watch
	@echo ""
	
debug: comfy
	@echo ""
	lldb -- ./build/comfy --target ~/tmp/out --watch
	@echo ""

clean:
	rm -rf build
	rm -rf _site