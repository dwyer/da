CFLAGS+=-Wall -Wextra
INSTALL_PREFIX=/usr/local

.PHONY: test clean install uninstall

libda.a: da.o
	ar rc $@ $+
	ranlib $@

install:
	install $(PWD)/da.h $(INSTALL_PREFIX)/include/da.h
	install $(PWD)/libda.a $(INSTALL_PREFIX)/lib/libda.a

uninstall:
	$(RM) $(INSTALL_PREFIX)/include/da.h
	$(RM) $(INSTALL_PREFIX)/lib/libda.a

da_test: da_test.o libda.a

test: da_test
	./$< 'hello world!' this is a test

clean:
	$(RM) da.o libda.a da_test da_test.o

blackjack: blackjack.o libda.a
