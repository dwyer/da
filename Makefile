CFLAGS+=-Wall -Wextra
INSTALL_PREFIX=/usr/local

.PHONY: test clean install uninstall

libda.a: da.o
	ar rc $@ $+
	ranlib $@

install:
	install $(PWD)/da.h $(INSTALL_PREFIX)/include/da.h
	install -d $(PWD)/da/ $(INSTALL_PREFIX)/include/da/
	install $(PWD)/da/da.h $(INSTALL_PREFIX)/include/da/da.h
	install $(PWD)/da/da_util.h $(INSTALL_PREFIX)/include/da/da_util.h
	install $(PWD)/da/da_int.h $(INSTALL_PREFIX)/include/da/da_int.h
	install $(PWD)/da/da_str.h $(INSTALL_PREFIX)/include/da/da_str.h
	install $(PWD)/libda.a $(INSTALL_PREFIX)/lib/libda.a

uninstall:
	$(RM) -r $(INSTALL_PREFIX)/include/da
	$(RM) $(INSTALL_PREFIX)/include/da.h
	$(RM) $(INSTALL_PREFIX)/lib/libda.a

da_test: da_test.o libda.a

test: da_test
	./$< 'hello world!' this is a test

clean:
	$(RM) da.o libda.a da_test da_test.o

blackjack: blackjack.o libda.a
