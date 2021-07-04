# Ebe (Edit By Example)

**Ebe** [_eebee_] is a compiler that creates a text editing program from given input and output example.
This compiler promises no knowledge of any programming language to edit files in a way similar programming languages (like awk) would.

_This project was created as my diploma thesis._

## What edits can/will ebe do

Ebe does not change text directly, it takes words (letters separated by whitespace or symbols) as an object with set of possible modifications (such as capitalization). But ebe mainly focuses on modification of structure of these objects (moving words around, deleting them, splitting...).

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

We can give these 2 files to ebe compiler and it should be able to find a program which modifies any text written in this way and rewrite it in an expected format. There is also a chance that ebe will not be able to find such a program, in that case program with best fitness will be compiled. Compiled program can then be used for modification on any input file which follows input example given.
