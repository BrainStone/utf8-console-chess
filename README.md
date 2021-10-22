# utf8-console-chess

A little application to render FEN positions in the console with UTF-8 characters.

## Usage

```
Usage: ./u8cc [OPTION]... [FEN]
A little application to render FEN positions in the console with UTF-8 characters.

  -h, --help                 display this message and exit

  -f, --file FILE            instead of from the arguments, read the FEN from
                             FILE, or when FILE is -, read from standard input
      --stdin                equivalent to -f -

  -d, --double-size          print the chess board in a larger font. This may
                             not be supported by all consoles
  -i, --invert-board         print the board from black's perspective
```

*Note*: Only the position part until the first space in the FEN string is required. The rest after it is ignored anyways.

## Building

### Windows

Make sure you have VisualStudio installed as this is needed as the compiler.

```cli
./gradlew installReleaseWindows
```

The executable will be located in `.\build\install\main\release\windows\lib`

### Linux

Make sure you have `g++` or `clang++` installed that support C++17

```cli
./gradlew installReleaseLinux
```

The executable will be located in `.\build\install\main\release\linux\lib`
