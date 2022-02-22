<img align="left" width="80" height="80" src="https://raw.githubusercontent.com/mark-sed/ebe/main/docs/logo.png" alt="Logo">

# Ebe (Edit By Example)

**Ebe** [_i:bi:_ or _ebe_] is a program (compiler and interpreter) for editing files just from given examples.
This program does not require any knowledge of any programming language to edit files and promises editing options similar to ones provided by editing programming languages (like awk).

* [Patch notes](https://github.com/mark-sed/ebe/wiki/Patch-notes)  
* [Ebe wiki](https://github.com/mark-sed/ebe/wiki)


#### Table of contents
- [Ebe (Edit By Example)](#ebe--edit-by-example-)
  * [What can Ebe do](#what-can-ebe-do)
- [Getting started](#getting-started)
  * [Installation](#installation)
  * [Simple edit example](#simple-edit-example)
  * [User expression example](#user-expression-example)
  * [Understanding Ebe](#understanding-ebe)
  * [Some tips for compilation](#some-tips-for-compilation)
  * [Other resources](#other-resources)
- [Ebe Tools](#ebe-tools)
- [Contributing](#contributing)
- [Feedback](#feedback)

## What can Ebe do

Ebe works the best with structured data and allows for batch editing (multiple files can be edited during one interpretation), but can be used even for smaller files to save your time with writing a script to do these edits.

Ebe also support user defined expressions and thus it is easy to modify numeric values.

Example use cases can be:
* removing columns from CSV file,
* converting values (°F to °C) in dataset,
* reordering columns and lines in log file,
* changing `null` value for `0`...

# Getting started

## Installation

Current release of Ebe was tested and compiled only on Linux and the following installation talks only about this case. But source code is available as well as CMake file, so building Ebe on Windows should be possible (if anyone does this I would love to know more about it).

There is also precompiled binary version for Linux, but this might not work on all systems and it is in almost all cases better to compile Ebe from source.

### Requirements

To compile Ebe from source only requirements are a C++ compiler that supports C++17, but to make compilation easier a CMake is setup so only requirements are:
* [C++17 compiler](https://gcc.gnu.org/).
* [CMake](https://cmake.org/)

For __developers__ the following might be needed as well:
* `doxygen` and `dot` for documentation
* `flex` and `bison` for recompiling lexers and parsers

### Building Ebe

1. Download latest release from [release tab](https://github.com/mark-sed/ebe/releases) in GitHub, alternatively you can clone main branch for the latest, but unstable version of Ebe:
```bash
git clone https://github.com/mark-sed/ebe.git
```
2. Run installation script. If run as a root, then ebe will be copied to /usr/bin/ebe to use as a command anywhere:
```bash
cd ebe
sudo bash install.sh
```
3. Test correctness running:
```bash
ebe --version
./build/ebe --version
```

__Alternatively:__

```bash
git clone https://github.com/mark-sed/ebe.git
cd ebe
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build --target ebe
```

## Simple edit example

In this example we have multiple files greeting and saying goodbye to different worlds and we want to extract only names of these worlds.

#### 1. Setup files to edit
First file we want to extract from looks the following - `hellos.txt`:
```
Hello Earth world!
Hello Pluto world!
Hello Moon world!
Hello Kamino world!
Hello Calantha world!
```

Second file we want to extract from looks the following - `goodbyes.txt`:
```
Goodbye Arda world!
Goodbye Gliese world!
Goodbye Eternium world!
```

Both files have the same structure and thus only one Ebe edit is needed.

#### 2. Create example snippets for Ebe

##### 2.1. Input example
We now need to create example inputs for Ebe to find correct edits. So we take for example the first line from `hellos.txt` and save it to file `example.in`:
```
Hello Earth world!
```

##### 2.2. Output example
And then we need to edit this snipped by hand into the format we expect Ebe to do on all lines - `example.out`:
```
Earth
```

#### 3. Edit using Ebe
Now we can have Ebe find correct edits and apply them to files `hellos.txt` and `goodbyes.txt`:
```bash
ebe -x -in example.in -out example.out hellos.txt goodbyes.txt -o .
```
After running this the Ebe should output something along:
```
Perfectly fitting program found. 

Best compiled program has 100% precision (0.0 s).
```

#### 4. Check output
Output from editing will be in current directory (`-o .`) under the same file names with prefix `edited-` (`edited-hellos.txt` and `edited-goodbyes.txt`). 

`edited-hellos.txt`:
```
Earth
Pluto
Moon
Kamino
Calantha
```

`edited-goodbyes.txt`:
```
Arda
Gliese
Eternium
```

#### Options choice explanation
What the used options mean:
* `-x` - signifies that we want to compile and interpret in one run,
* `-in example.in` - signifies that `example.in` is the expected input pattern,
* `-out example.out` - signifies that `example.out` is be the expected output after applying edits to `example.in`,
* `-o .` - signifies that edited output will be saved in this directory. In this case, where there are multiple input files (`hellos.txt` and `goodbyes.txt`) `-o` needs to be a folder, if the input was only one file, then the `-o` should be output file name. If `-o` was not used, then the output will be printed to the terminal, which is more useful for single input file.

#### What it should look like 
![screenshot](https://i.imgur.com/dNaJSvg.png)

## User expression example

For Ebe (and generally genetic programming) it's very hard to find arithmetic expressions, for this reason such expressions need to be entered by hand.

In this example we have a dataset with temperature in °F and want to tranform them into °C - `temps.data`:
```
Prague: 42
Paris: 50
Venice: 60
Munich: 38
```

We once again create input example snippet - `example.in`:
```
Prague: 42
```

But for the output we need to specify the transformation expression. This expression needs to be between `!{` and `!}` and to refere to the value at certain position the variable `$` has to be used. `example.out`:
```
Prague: {! (($ - 32) * 5) / 9 !}
```

In our case `$` will be `42`.

In this example we'll use compilation and interpretation as separate operations. When compiling we __have to__ use `-expr` option to parse user expressions:
```
ebe -in example.in -out example.out -expr -eo f2c.ebel
```

This will create `f2c.ebel` file (`-eo f2c.ebel`), which can be used to interpret the dataset:

```
ebe -i f2c.ebel temps.data
```

This will output to the terminal:
```
Prague: 5
Paris: 10
Venice: 15
Munich: 3
```

#### What it should look like
![screenshot](https://i.imgur.com/VsRfYn0.png)

## Understanding Ebe

Although it is not needed to understand how Ebe internally works to use it, it might help with correct example writing, options selection and understanding Ebe's limits.

Ebe uses genetic programming to evolve Ebel code until the evolve code does what the input examples specify. So the input examples are used for fitness functions, where the `-in` file is interpreted over evolved program and then compared with `-out`, where their similarity is what guides the evoluition. Because of this you should make it as easy as possible for Ebe to find the edit and bear in mind, that at this point not all edits can be done in Ebe, such examples are:
* arithmetic expressions (but can be written by the user),
* transforming text,
* generating text.

Since Ebe uses genetic programming, oppose to something like neural network, it does not require much processing power nor does not send any data to some distant servers. On the other hand for more difficult inputs it might take a bit longer to evolve 100 % fitting program, but in many cases this might be faster than writing a script in other language or doing edits by hand.

### Ebe's philosophy

Since Ebe is aimed also on people with little to no programming knowledge, Ebe's philosophy is to not cause exceptions and errors as long as it is not necessary. Meaning that, when an incorrect instruction or input is encountered, rather than exiting the execution with error, only a warning is printed and the instruction or input is ignored.

### Ebe Workflow

How ebe compiles and interprets (`-x` option or compilation followed by interpretation):
1. Ebe loads example input and output (`-in` and `-out`) and parses them into a list of objects, where each object represents the file lexeme and has certain type.
2. Ebe engine (Eben) then creates initial population of programs and starts evolving them with crossovers and mutations, where for each program a fitness is calculated based on how well the program transforms `-in` file into `-out` file.
3. Once 100 % fitting (or sufficient for `-p` or is timeout `-t`) program is found, then this program is returned and evolution stopped.
4. The generated program is then loaded into interpreter (Ebei) and input files are interpreted over it.

![workflow_diagram](https://github.com/mark-sed/ebe/blob/main/docs/ebe_workflow.png?raw=true)

### How is text parsed

For text file Ebe recognizes following types:
* TEXT - `hello`
* NUMBER - `42`
* FLOAT - `3.14159`, `0.5e-89`
* DELIMITER - `,`, `\t`, `.`
* SYMBOL - `%`, `$`

The input is then parsed by lines into list of objects, with type and value.

For example the text `Hello, World 42" would be parsed into:
```
TEXT(Hello) DELIMITER(,) DELIMITER(\0x20) TEXT(World) NUMBER(42)
```

As you can see Ebe recognizes all symbols and words in a file (where as tools such as awk don't work with separators). 

### How Ebel works

Ebel (_Ebe language_) is an imperative, case insensitive, programming language designed for file editing and to work well with genetic programming. 

Ebel is not really meant to be written, but can be and contains some syntactic sugar to make writing and editing it more user-friendly.

It is interpreted over a file, where the Ebel code can be thought of as a pipeline of instructions through which the file objects (called _words_) go and get modified by.

Ebel is composed of multiple sections called passes. Such pass defines in which way the input file is read. `Pass Words` reads input word by word and applies its instructions on these words. `Pass Lines` then interprets instructions over the whole lines and special `Pass Expression` iterprets over a specific word, which is used for user expressions, where the word value is changed.

Example Ebel code:
```
PASS Words
  NOP
  DEL 
  DEL 
  PASS number Expression
    SUB $1, $0, 32
    MUL $2, $1, 5
    DIV $0, $2, 9
    RETURN NOP 
  PASS derived Expression
    RETURN DEL
PASS Lines
  SWAP 1
  LOOP
```

In the example above:
* `PASS Words` - File will be interpreted word by word and for each line it will:
  * `NOP` - 1st object will left as is
  * `DEL` - 2nd object will be deleted
  * `DEL` - 3rd object will be deleted
  * `PASS number Expression` - 4th object, if it is a number will be:
    * `SUB $1, $0, 32` - Subtract 32 from its value
    * `MUL $2, $1, 5` - Multiply the new result by 5
    * `DIV $0, $2, 9` - Divide the result by 9 and save it as the new value for the object (`$0` is `$`)
    * `RETURN NOP` - Don't modify the new result
  * `PASS derived Expression` - If 4th object was not number, then use the following without regarding its type
    * `RETURN DEL` - Delete the object
* `PASS Lines` - File will be interpreted line by line and for each line:
  * `SWAP 1` - Swap current line with the following one
  * `LOOP` - Repeat until all lines were processed

For more information about the instructions see [wiki](https://github.com/mark-sed/ebe/wiki/Ebel-(ebe-language)).

## Some tips for compilation

Ebe has some heuristics for picking evolution attributes, but many of them can be specified by the user (see [arguments](https://github.com/mark-sed/ebe/wiki/Ebe-arguments)).

If the compilation cannot get to 100 % and you're sure the examples are correct, it might help to play with the following compile time options:
* `-expr` - Make sure to use `-expr` when using user expressions.
* `--iterations <number>` - setting a higher number of iterations might help in certain cases, this makes the evolution last longer. Ebe will pick a value around 700. So specifying a lot bigger value might help in some cases. Try value like 1500, 2000, 3000...
* `-p` - This specifier runs evolutions until 100 % fitting program is found (or other if specified after `-p`, such as `-p 75`). But it does not (yet) change the number of iterations, so it might be good to combine with `--iterations`.
* `-f <121/jaro/jw/lev>` - Specifies the fitness function used for file comparison, picking value such as `jw` (Jaro-Winkler distance) might give you better result.

## Other resources

Other information can be found in Ebe's [GitHub wiki](https://github.com/mark-sed/ebe/wiki).
* [Ebe arguments](https://github.com/mark-sed/ebe/wiki/Ebe-arguments)
* [Patch notes](https://github.com/mark-sed/ebe/wiki/Patch-notes)
* [Engine info](https://github.com/mark-sed/ebe/wiki/Engines)
* [Ebel](https://github.com/mark-sed/ebe/wiki/Ebel-(ebe-language))

# Ebe Tools

Tools for advanced work and analysis of Ebe can be found in its own [repository](https://github.com/mark-sed/ebe-tools).

# Contributing

Contributions are not open until version 1.0.

Any bug reports or feature requests are more than welcome, for this please use the [issues](https://github.com/mark-sed/ebe/issues) section on GitHub.

# Feedback

Any feedback and critique is welcome and I will be used in further development, this can range from your use cases and requests to make Ebe more usable there to requesting tips on how to use or optimize Ebe in certain cases.

For this please use the [discussions](https://github.com/mark-sed/ebe/discussions) section on GitHub
