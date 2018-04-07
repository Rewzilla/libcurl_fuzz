
export CC			:= clang
export CXX			:= clang++
export CFLAGS		:= -g #-fsanitize=address
export CURLDIR		:= curl-7.59.0

all: fuzzer

fuzzer: fuzzer.c grammer.c
	$(CC) $(CFLAGS) -I./$(CURLDIR)/include -L./$(CURLDIR)/lib/.libs -o fuzzer fuzzer.c grammer.c -lcurl

libcurl:
	cd $(CURLDIR) && ./configure && make

clean:
	rm -rf fuzzer
	cd $(CURLDIR) && make clean