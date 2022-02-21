<img align="left" width="80" height="80" src="https://raw.githubusercontent.com/mark-sed/ebe/main/docs/logo.png" alt="Logo">

# Ebe (Edit By Example)

**Ebe** [_i:bi:_ or _ebe_] is a program (compiler and interpreter) for editting files just from given examples.
This program does not require any knowledge of any programming language to edit files and promises editting options similar to ones provided by editting programming languages (like awk).

[Ebe wiki](https://github.com/mark-sed/ebe/wiki)

## What can Ebe do

Ebe works the best with structured data and allows for batch editing (multiple files can be editted during one interpretation), but can be used even for smaller files to save your time with writing a script to do these edits.

Ebe also support user defined expressions and thus it is easy to modify numeric values.

Example use cases can be:
* removing columns from CSV file,
* converting units (°F to °C) in dataset,
* reordering columns and lines in log file,
* changing `null` value for `0`...

# Getting started

## Installation

Current release of Ebe was tested and compiled only on Linux and the following installation talks only about this case. But source code is available as well as CMake file, so building Ebe on Windows should be possible (if anyone does this I would love to know more about it).

### Requirements

To compile Ebe from source only requirements are a C++ compiler that supports C++17, but to make compilation easier a CMake is setup so only requirements are:
* [C++17 compiler](https://gcc.gnu.org/).
* [CMake](https://cmake.org/)

For __developers__ the following might be needed as well:
* `doxygen` and `dot` for documentation
* `flex` and `bison` for recompiling lexers and parsers

### Building Ebe

1. Clone (or download using GitHub webpage) Ebe to your PC:
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

We now need to create example inputs for Ebe to find correct edits. So we take for example the first line from `hellos.txt` and save it to file `example.in`:
```
Hello Earth world!
```

And then we need to edit this snipped by hand into the format we expect Ebe to do on all lines - `example.out`:
```
Earth
```

Now we can have Ebe find correct edits and apply them to files `hellos.txt` and `goodbyes.txt`:
```bash
ebe -x -in example.in -out example.out hellos.txt goodbyes.txt -o .
```
After running this the Ebe should output something along:
```
Perfectly fitting program found. 

Best compiled program has 100% precision (0.0 s).
```

__Output__ from editing will be in current directoru (`-o .`) under the same file names with prefix `edited-` (`edited-hellos.txt` and `edited-goodbyes.txt`). 

What the used options mean:
* `-x` - signifies that we want to compile and interpret in one run,
* `-in example.in` - signifies that `example.in` will is the expected input pattern,
* `-out example.out` - signifies that `example.out` will be the expected output after applying edits to `example.in`,
* `-o .` - signifies that edited output will be saved in this directory. In this case, where there are multiple input files (`hellos.txt` and `goodbyes.txt`) `-o` needs to be a folder, if the input was only one file, then the `-o` should be output file name.

If `-o` was not used, then the output will be printed to the terminal, which is more useful for single input file.

## User expression example

## Advanced usage examples

## Understanding Ebe

### How is text parsed

### How is Ebel generated

### How Ebel works

## Other resources

# Ebe Tools

Tools for advanced work and analysis of Ebe can be found in its own [repository](https://github.com/mark-sed/ebe-tools).

# Contributing

Contributions are not open until version 1.0.

Any bug reports or feature requests are more than welcome, for this please use the [issues](https://github.com/mark-sed/ebe/issues) section on GitHub.

# Feedback

Any feedback and critique is welcome and I will be used in further development, this can range from your use cases and requests to make Ebe more usable there to requesting tips on how to use or optimize Ebe in certain cases.

For this please use the [discussions](https://github.com/mark-sed/ebe/discussions) section on GitHub
