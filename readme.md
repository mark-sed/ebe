# ebe (Edit By Example)

**Ebe** [_eebee_] is a compiler that creates a text editing program from given input and output example.
This compiler promises no knowledge of any programming language to edit files in a way similar programming languages (like awk) would.

_This project was created as my diploma thesis._

## What edits can/will ebe do

Ebe does not change text directly, it takes words (letters separated by whitespace or symbols) as an object with set of possible modifications (such as capitalization). But ebe mainly focuses on modification of structure of these objects (moving words around, deleting them, splitting...).
