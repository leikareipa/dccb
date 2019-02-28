# DOS C Compiler Benchmark (dccb)
Provides a small but non-trivial real-world 16-bit DOS codebase for recreational performance-testing of older C compilers.

The code is that of a simple VGA mode 13h software 3d rasterizer, which operates mostly but not exclusively on integers. It renders a spinning ball on screen for a dozen or so seconds, then exits with an FPS count.

# Building
Batch files are provided under the [build/](build/) directory for building dccb with various C compilers:
- Microsoft C 5
- Mix Power C 2.2
- Borland Turbo C 2
- HI-TECH Pacific C 7

Build scripts for several C/C++ compilers are also included:
- Digital Mars C/C++ 8
- Open Watcom C/C++
- Microsoft C/C++ 8
- Borland C++ 2

![A screenshot of dccb](http://tarpeeksihyvaesoft.com/soft/img/dccb_b.png)
