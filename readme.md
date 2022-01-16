<img align="left" width="80" height="80" src="https://raw.githubusercontent.com/mark-sed/ebe/master/docs/logo.png" alt="Logo">

# Ebe (Edit By Example)

[Ebe wiki](https://github.com/mark-sed/ebe/wiki)

**Ebe** [_i:bi:_ or _ebe_] is a program (compiler and interpreter) for editting files just from given examples.
This program does not require any knowledge of any programming language to edit files and promises editting options similar to ones provided by editting programming languages (like awk).

_This project was created as my diploma thesis._

## Ebe workflow

![workflow](https://github.com/mark-sed/ebe/blob/main/docs/ebe_workflow.png?raw=true)

## What edits can/will Ebe do

Ebe does not change text directly, it takes words (letters separated by whitespace or symbols) as an object with set of possible modifications (such as capitalization). But Ebe mainly focuses on modification of structure of these objects (moving words around, deleting them, splitting...).

### Example

Lets say that we have a text file with names in such format (file `ex1.in`):
```
Sedlacek Marek & Lattner Chris
Musk Elon & Svidler Peter
Ford Harrison & Daniels Anthony
```

And we want to change it in a way so that first name is before last name (file `ex1.out`):
```
Marek Sedlacek & Chris Lattner
Elon Musk & Peter Svidler
Harrison Ford & Anthony Daniels
```

We can give these 2 files to Ebe compiler and it should be able to find a program which modifies any text written in this way and rewrite it in an expected format. There is also a chance that Ebe will not be able to find such a program, in that case program with best fitness will be compiled. Compiled program can then be used for modification on any input file which follows input example given.

## Requirements for full build
These tools are not needed to compile `ebe` program, but when using `cmake` they are needed for the all target.
* `cmake`
* `doxygen` and `dot` for documentation
* `flex` and `bison` for recompiling lexers and parsers

## Ebe Tools

Tools for advanced work and analysis of Ebe can be found in its own [repository](https://github.com/mark-sed/ebe-tools).