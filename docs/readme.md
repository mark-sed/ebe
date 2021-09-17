## Ebe source code structure
```
- ebe                  - Main
- Makefile
- readme.md
- /backend             - Compilation and interpretation resourced
  |- compiler
  |- interpreter
  |- instruction
- /docs                - Documentation material
  |- readme.md         - General documentation and info about the compiler
  |- /backend
  |- /midend
  |- /frontend
- /engine              - Engines
  |- engine
  |- engine_jenn
- /examples            - (Previously inputs) examples for inputs
- /frontend            - Frontend related resources
  |- preprocessor
  |- scanner
- /gp                  - Genetic programming resources
  |- gp
- /midend              - Resources for IR and it's optimization before backend
  |- ir
- /utils               - Utilities for the compiler
  |- arg_aprser
  |- utils
  |- rng
  |- logging
```