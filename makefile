comfy: setup
	clang src/*.c -o build/comfy
	
setup:
	mkdir -p build
	
clean:
	rm -rf build
	