# all, test, dependencies, clean

CFLAGS+=-g
CFLAGS+=-Idependencies/include

LDFLAGS+=-Ldependencies/lib 
LDLIBS+=-lasprintf -lslre

#DEPEND_DIRS = -I ./dependencies/include -L ./dependencies/lib
#DEPEND_ARGS = $(DEPEND_DIRS) -lslre -lasprintf

all_objs=$(patsubst %.c,%.o,$(wildcard src/*.c)) 
all_objs+=$(patsubst %.c,%.o,$(wildcard src/features/*.c))

.PHONY: dependencies clean test

comfy: $(all_objs)
	$(LINK.o) $^ $(LDFLAGS) $(LDLIBS) -o $@
	
test: comfy filetests/comfy_test
	@$(RM) -r filetests/target
	@mkdir -p filetests/target
	@echo ""
	@echo ""
	@./comfy --source ./filetests/source --target ./filetests/target
	@echo ""
	@echo ""
	@./filetests/comfy_test ./filetests/source ./filetests/target ./filetests/expected

clean:
	$(RM) $(all_objs)
	$(RM) comfy
	$(RM) filetests/comfy_test
	$(RM) -r **/*.dSYM
	$(MAKE) -C dependencies clean

dependencies:
	$(MAKE) -C dependencies
