# Oh, God, WHY!?

`Oh, God, WHY!?` transforms [cnoevil](https://git.sr.ht/~shakna/cnoevil3/) into a full-blown "language".

---

## CNoEvil

I've written a little about CnoEvil [before](https://gist.github.com/shakna-israel/4fd31ee469274aa49f8f9793c3e71163#lets-destroy-c). The basic idea is to create a super-set of C by abusing macros to generate features to make it _seem_ like the language is higher level than it is.

The name should let you know that this is a terrible idea.

## Oh, God, WHY!?

Expanding on the absolute terrible idea, this program, which can be shortened to `ogw`, acts as a C compiler for CNoEvil programs, without the need to first include the header file.

---

## Differences

Usually when using CNoEvil you need to make a series of defines first, to choose what modules you'll enable/disable.

However, `ogw` sets these defines:

	#define EVIL_NO_WARN
	#define EVIL_COROUTINE
	#define EVIL_ASSERT
	#define EVIL_BIT
	#define EVIL_CLI
	#define EVIL_ENCODE
	#define EVIL_HASH
	#define EVIL_HELP
	#define EVIL_LOG
	#define EVIL_MATH
	#define EVIL_RANDOM

---

## Limitations

C expects you to be able to link against libraries, and to include various headers files. There is no singular way of importing. To help with this, `ogw` does the following:

* The current folder is added as a header search path. (`.`)

* The include folder inside the current path is added as a header search path. (`./include`)

* If there is a file called `libraries.txt` in the current working directory, it is treated like a line-deliminated series of libraries to link.

* If there is an environment variable called `LIBRARIES`, it is treated like a `;` deliminated series of libraries to link.

* If there is an environment variable called `LIBRARY_PATHS`, it is treated like a `;` deliminated series of library paths to use for linking.

* If there is an environment variable called `INCLUDE_PATHS`, it is treated like a `;` deliminated series of include paths to search.

---

## Building

You'll need to have `libtcc` installed and available.

You'll need to have `xxd` installed.

You'll need a C compiler, and `make`.

Then run:

	make

### Platforms

I've only run this against Linux. Windows & macOS users will probably have to tweak the Makefile for their platform, but it should be able to get it running with minimal fuss.

## Usage

Once built, you can run it with:

	./ogw FILE

---

## License

See the `LICENSE.md` file, taking careful not of point number 1.
