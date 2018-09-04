libda.a: da.o
	ar rc $@ $+
	ranlib $@

install:
	ln -s $(PWD)/da.h /usr/local/include/da.h
	ln -s $(PWD)/libda.a /usr/local/lib/libda.a

uninstall:
	$(RM) /usr/local/include/da.h
	$(RM) /usr/local/lib/libda.a

da_test: da_test.o libda.a
	$(CC) -L. -lda -o $@ $<

test: da_test
	./$< 'hello world!' this is a test

clean:
	$(RM) da.o libda.a da_test da_test.o

blackjack: blackjack.o libda.a
	$(CC) -L. -lda -o $@ $<
