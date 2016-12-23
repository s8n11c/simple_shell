run:
	gcc shell.c -o shell
clean:
	rm -f shell
install:
	cp shell /usr/bin
uninstall:
	rm -rf /usr/bin/shell
