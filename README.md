# Oh, God, WHY!?

`Oh, God, WHY!?` transforms [cnoevil](https://git.sr.ht/~shakna/cnoevil3/) into a full-blown "language".

---

## Example Code

	comment("A demonstration of a coroutine.");

	declare(example, int);

	proc(example, int)
	  static int i = 1;
	  coroutine();
	  While true then
	    i = i * 2;
	    co_return(i);
	  end
	  co_end();
	  return i;
	end

	Main then
	  For int i = 0; i < 20; i++ then
	    displayln(example());
	  end
	end

---

## CNoEvil

I've written a little about CnoEvil [before](https://gist.github.com/shakna-israel/4fd31ee469274aa49f8f9793c3e71163#lets-destroy-c). The basic idea is to create a super-set of C by abusing macros to generate features to make it _seem_ like the language is higher level than it is.

The name should let you know that this is a terrible idea.

## Oh, God, WHY!?

Expanding on the absolute terrible idea, this program, which can be shortened to `ogw`, acts as a C compiler for CNoEvil programs, without the need to first include the header file.

The name is the first thing that should come to mind when you consider the existence of this project.

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
	#define EVIL_MALLOC

Instead of CNoEvil's random, we have a better set of functions that use a Mersenne Twister instead of C's crippled `rand`:

	void randomseed(unsigned long s);
	unsigned long randomint(void);
	randomrange(min, max)

	
	long randomint_31(void);
	double randomreal(void);
	double randomreal_2(void);
	double randomreal_3(void);
	double randomreal_53(void);

---

## Limitations

C expects you to be able to link against libraries, and to include various headers files. There is no singular way of importing. To help with this, `ogw` does the following:

* The current folder is added as a header search path. (`.`)

* The include folder inside the current path is added as a header search path. (`./include`)

* If there is a file called `libraries.txt` in the same directory as the file being executed, it is treated like a line-deliminated series of libraries to link.

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

I've only run this against Linux.

## Usage

Once built, you can run it with:

	./ogw -run FILE

Or you can generate an executable file with:

	./ogw INPUT_FILE OUTPUT_FILE

---

## License

See the `LICENSE.md` file, taking careful note of point number 1.
