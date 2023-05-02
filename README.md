# utf8-console-chess

A little application to render [FEN](https://www.chess.com/terms/fen-chess) positions in the console with UTF-8 characters.

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

Example:

![Usage](https://user-images.githubusercontent.com/4106544/138535221-9ee3b80a-3a9b-40c8-95c6-a0f6ddbe624f.png)

*Note*: Only the position part until the first space in the FEN string is required. The rest after it is ignored anyways.

## Building

This is CMake project.

So all you have to do to build it is run these commands

```cli
cmake .
make
```

Then you'll have the binary u8cc in the same directory.  
If you just want to build the binary without the tests, append the parameter
`u8cc` to the make command.
