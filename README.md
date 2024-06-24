# xnqscfg - simple config language + parser for C++

xnqscfg is a very simple and minimal configuration language.

### Features:
- Strings (also multiline strings)
- Arrays (also multidimensional arrays)
- Comments

# Motivation

This was mainly made because I wanted to write a lexer and a parser and because I wanted to write my own library in order to learn everything that comes with this project (not to forget the satisfaction that comes with doing that). Also, I want to add better configuration support to some of my other personal projects such as [xnqsbar](https://github.com/xnqs/xnqsbar) and maybe [turbofetch](https://github.com/xnqs/turbofetch) if I ever decide to revive it. I also don't want to go for anything overkill such as JSON, because it's truly not necessary for my use cases. I just want a dead-simple and minimal configuration library which does its job well.

# Syntax and usage

## The config file
The syntax is outlined in `sample.xnqscfg`. This file contains pretty much every feature used in xnqscfg.

## Usage in programs
Usage in C++ is ran over in `src/demo.cxx`.

# High priority todo list / ideas

- implement this as a dynamic library so it's not such a pain to set up

# Low priority todo list / ideas

I'm probably never gonna add these because I don't think I'll ever have a need for these, but:

- better API syntax? (`config["variable"]->arr[0]->arr[0]...->str` is not very nice)
- add variable concatenation?
