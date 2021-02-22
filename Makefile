CC=clang
FLAGS=-fPIC -shared -lc

all: text

test: text check
	$(CC) -g test.c -L. -lMyFuncs
	./a.out
	rm a.out
	make replace

io: __io.h IO.c
	$(CC) $(FLAGS) -o libMyFuncs.so IO.c

string: __string.h STRING.c io
	$(CC) $(FLAGS) -o libMyFuncs.so	IO.c STRING.c -L. -lMyFuncs

text: __text.h TEXT.c string
	$(CC) $(FLAGS) -o libMyFuncs.so IO.c STRING.c TEXT.c -L. -lMyFuncs

check:
	sudo mv /lib/x86_64-linux-gnu/libMyFuncs.so original.so
	sudo mv libMyFuncs.so /lib/x86_64-linux-gnu/libMyFuncs.so

replace:
	sudo mv /lib/x86_64-linux-gnu/libMyFuncs.so libMyFuncs.so
	sudo mv original.so /lib/x86_64-linux-gnu/libMyFuncs.so

remove:
	rm *.so

submit:
	sudo mv libMyFuncs.so /lib/x86_64-linux-gnu/libMyFuncs.so || rm original.so 

mv_hdr: *.h
	for file in $^;						\
	do									\
	sudo cp $$file /usr/include/$$file;	\
	done				
	
