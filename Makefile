CFLAGS=-Wall -Wconversion -Wdangling-else -Wextra -fcf-protection=full -D_FORTIFY_SOURCE=2 -fstack-protector-strong -fstack-clash-protection -fPIE -pie -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now
COPTIM=-O3

all:
	xxd -i evil.h > evil_build.h
	$(CC) $(COPTIM) $(CFLAGS) ogw.c -I. -ltcc -ldl -o ogw
