all:
	xxd -i evil.h > evil_build.h
	gcc ogw.c -I. -ltcc -ldl -o ogw
