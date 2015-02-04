# all, test, dependencies, clean

CFLAGS+=-g -std=c11
CFLAGS+=-Idependencies/include

LDFLAGS+=-Ldependencies/lib 
LDLIBS+=-lasprintf -lslre

PREFIX?=/usr/local
INSTALL_BIN=$(PREFIX)/bin
INSTALL=install

#DEPEND_DIRS = -I ./dependencies/include -L ./dependencies/lib
#DEPEND_ARGS = $(DEPEND_DIRS) -lslre -lasprintf

all_src=$(wildcard src/*.c)
all_src+=$(wildcard src/features/*.c)

all_objs=$(patsubst src/%,build/o/%,$(patsubst %.c,%.o,$(all_src)))

.PHONY: dependencies clean test setup

comfy: $(all_objs)
	$(LINK.o) $^ $(LDFLAGS) $(LDLIBS) -o build/$@

build/o/%.o: src/%.c | setup
	$(CC) -c $(CFLAGS) -o $@ $?
	
setup:
	@mkdir -p build/o/features
	
test: comfy filetests/comfy_test
	@$(RM) -r filetests/target
	@mkdir -p filetests/target
	@echo ""
	@echo ""
	@./build/comfy --source ./filetests/source --target ./filetests/target
	@echo ""
	@echo ""
	@./filetests/comfy_test ./filetests/source ./filetests/target ./filetests/expected

clean:
	$(RM) -r build
	$(RM) filetests/comfy_test
	$(RM) -r filetests/target
	$(RM) -r **/*.dSYM
	
install:
	$(INSTALL) build/comfy $(INSTALL_BIN)

cleanDependencies:
	$(MAKE) -C dependencies clean

dependencies:
	$(MAKE) -C dependencies
