all: headers libs

headers:
	mkdir -p include
	cp -f slre/*.h include
	cp -f asprintf/*.h include
	
libs: lib/libslre.a lib/libasprintf.a

lib/lib%.a: lib
	$(CC) -c $(CFLAGS) -o $*/$*.o $*/$*.c
	$(AR) $(ARFLAGS) $@ $*/$*.o
	
lib:
	mkdir -p lib
	
clean:
	$(RM) **/*.o
	$(RM) -r lib include
