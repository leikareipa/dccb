# DOS C Compiler Benchmark (dccb)
Provides a small but non-trivial real-world 16-bit DOS codebase for recreational performance testing of older C compilers.

The code is that of a simple VGA mode 13h software 3d rasterizer, which operates mostly but not exclusively on integers. It renders a spinning ball on screen for a dozen or so seconds, then exits with an FPS count that you can compare between compilers.

## Building
Batch files are provided under the [build/](build/) directory for building dccb with various C compilers:
- Microsoft C 5
- Microsoft QuickC 1
- Mix Power C 2.2
- Borland Turbo C 2
- HI-TECH Pacific C 7

Build scripts for several C/C++ compilers are also included:
- Digital Mars C/C++ 8
- Open Watcom C/C++
- Microsoft C/C++ 8
- Borland C++ 2

## Usage
Once you have it, put the executable in the [bin/](bin/) directory, and run it &ndash; preferably in DOS, DOSBox, or the like. The program will render a spinning ball for a dozen or so seconds, then exit with an FPS count.

Note that the directory in which you run the executable should also contain the files `mesh`, `palette`, and `texture`, as provided in this repo. The first file contains the 3d mesh to be rendered (in a custom format, of which no specification is available at this time), the second file defines the VGA mode 13h palette (three bytes &ndash; RGB &ndash; per color for 256 colors, each byte expressing a value between 0 and 63), and the last one is the texture with which the ball will be rendered (each byte in the file an index to the palette).

## Sample results
The following table provides results for various compilers using this benchmark, which was run in DOSBox (cycles = 67000).

| Compiler             | FPS |
| -------------------- |:---:|
| Microsoft C/C++ 8    | 57  |
| Digital Mars C/C++ 8 | 41  |
| Open Watcom          | 37  |
| Borland Turbo C 2    | 33  |
| Borland C++ 2        | 32  |
| Microsoft C 5        | 32  |
| Microsoft QuickC 1   | 31  |
| HI-TECH Pacific C 7  | 30  |
| Mix Power C 2        | 14  |

![A screenshot of dccb](http://tarpeeksihyvaesoft.com/soft/img/dccb_b.png)
