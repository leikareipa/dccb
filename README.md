# DOS C Compiler Benchmark (DCCB)
Provides a small but non-trivial real-world codebase for recreational performance testing of older C compilers.

The code is that of a simple VGA mode 13h software 3d rasterizer, which operates mostly but not exclusively on integers. DOS is its target environment.

### Building
Batch files are provided under the ```build``` directory for building DCCB with various C compilers:
* Microsoft C
* Borland Turbo C
* HI-TECH Pacific C
* Digital Mars C/C++
* Open Watcom C/C++

Your job is to set up the toolchains, and to adapt the batch files as needed.

![A screenshot of DCCB](http://tarpeeksihyvaesoft.com/soft/img/dccb.png)
