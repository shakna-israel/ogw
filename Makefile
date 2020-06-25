CFLAGS=-Wall -Wconversion -Wdangling-else -Wextra -fcf-protection=full -D_FORTIFY_SOURCE=2 -fstack-protector-strong -fstack-clash-protection -fPIE -pie -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now
COPTIM=-O3

all:
	sh -x check_klib
	cp evil.h evil.h.bak
	cat klib/khash.h >> evil.h
	xxd -i evil.h > evil_build.h
	mv evil.h.bak evil.h
	$(CC) $(COPTIM) $(CFLAGS) MT19937.c ogw.c -I. -ltcc -ldl -o ogw
