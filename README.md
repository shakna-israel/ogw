# Oh, God, WHY!?

`Oh, God, WHY!?` is a simple wrapper around [cnoevil](https://git.sr.ht/~shakna/cnoevil3/) and [libtcc](https://bellard.org/tcc/) to create a compiler/interpreter for the "language".

---

## CNoEvil

I've written a little about CnoEvil [before](https://gist.github.com/shakna-israel/4fd31ee469274aa49f8f9793c3e71163#lets-destroy-c). The basic idea is to create a super-set of C by abusing macros to generate features to make it _seem_ like the language is higher level than it is.

The name should let you know that this is a terrible idea.

## Oh, God, WHY!?

Expanding on the absolute terrible idea, this program, which can be shortened to `ogw`, acts as a C compiler for CNoEvil programs, without the need to first include the header file.

## Differences

A few features of CNoEvil aren't part of `ogw`:

* Lambdas. These work by abusing a C-extension that wasn't implemented in `libtcc`.

	* We may reimplement this eventually, as we have access to a compiler runtime.

* Klasses. These work by using a C-extension that wasn't implemented in `libtcc`.

	* We will probably reimplement this using a differing syntax.

## Limitations

Currently there is no way to add libraries or header files. (This will be implemented further down the line).

---

## License

See the `LICENSE.md` file, taking careful not of point number 1.
