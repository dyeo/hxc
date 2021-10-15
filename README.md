# HXC: The Header-Only Extension Library for C

Intended to be as simple as including (or [submoduling](https://git-scm.com/book/en/v2/Git-Tools-Submodules)) in your own project, this library contains useful generified containers and other utilities which are commonly developed for most C projects, so that you can spend less time writing boilerplate and more time writing code that actually matters for your project.

This project is heavily inspired by the likes of [stb](https://github.com/nothings/stb) and [klib](https://github.com/attractivechaos/klib), both fantastic projects in their own right. It is intended to be a [boost](https://www.boost.org)-like companion to the C standard library, with well-documented, well-tested code that can be relied upon by the next generation of C developers. The only external dependencies should be the C standard library, or platform-specific libraries (in the case of [xplat.h](xplat.h)), which are conditionally included for their relevant platforms.

## Features

### Collections

- [ ] Resizable Arrays ([xarr.h](xarr.h))
- [ ] Binary Trees ([xtree.h](xtree.h))
- [ ] Hash Tables ([xhash.h](xhash.h))

### Utilities

- [ ] Command-line flags ([xflag.h](xflag.h))
- [ ] Logging ([xlog.h](xlog.h))
- [ ] Platform-dependant compilation ([xplat.h](xplat.h))

## Licensing

In order to make this library as available as possible, every single component is dually licensed under both The MIT License and Public Domain. This is purely to encourage contribution to the project, and use of the library's components to write robust, reusable, portable, and elegant C code. See [LICENSE.txt](LICENSE.txt) for a summary of the two licenses.