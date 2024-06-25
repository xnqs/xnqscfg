# xnqscfg - simple config language + parser for C++

xnqscfg is a very simple and minimal configuration language.

### Features:
- Strings (also multiline strings)
- Arrays (also multidimensional arrays)
- Comments

# Motivation

This was mainly made because I wanted to write a lexer and a parser and because I wanted to write my own library in order to learn everything that comes with this project (not to forget the satisfaction that comes with doing that). Also, I want to add better configuration support to some of my other personal projects such as [xnqsbar](https://github.com/xnqs/xnqsbar) and maybe [turbofetch](https://github.com/xnqs/turbofetch) if I ever decide to revive it. I also don't want to go for anything overkill such as JSON, because it's truly not necessary for my use cases. I just want a dead-simple and minimal configuration library which does its job well.

# Installation

## Arch or Arch-based distros
I put together a PKGBUILD for xnqscfg that you can use [right here](https://github.com/xnqs/pkgbuilds).

## Everything else

### Cloning the repo
```
git clone https://github.com/xnqs/xnqscfg.git
cd xnqscfg
```

### Building
```
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make
sudo make install
```

# Syntax and usage

## The config file
The syntax is outlined in `sample.xnqscfg`. This file contains pretty much every feature used in xnqscfg.

## Usage in programs
Usage in C++ is ran over in `src/demo.cxx`.

### Compilation
Say you want to compile a program that uses xnqscfg, be it `demo.cxx`. You'll obviously have to link it to the xnqscfg library. Example for GCC:

`g++ demo.cxx -o demo -lxnqscfg`

You can (probably, I haven't tested this) also dynamically link it at runtime if that's what you want to do.

# High priority todo list / ideas
nothing right now :D

# Low priority todo list / ideas

I'm probably never gonna add these because I don't think I'll ever have a need for these, but:

- better API syntax? (`config["variable"]->arr[0]->arr[0]...->str` is not very nice)
- add variable concatenation?
