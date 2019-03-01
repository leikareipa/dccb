# DOS C Compiler Benchmark (dccb)
Provides a small but non-trivial real-world 16-bit DOS codebase for recreational performance-testing of older C compilers.

The code is that of a simple VGA mode 13h software 3d rasterizer, which operates mostly but not exclusively on integers. It renders a spinning ball on screen for a dozen or so seconds, then exits with an FPS count.

# Building
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

# Results
The following table provides benchmark results for various compilers. These benchmarks were run in DOSBox (cycles = 67000).
<table>
    <tr>
        <th align="left">Compiler</th>
        <th align="left">FPS</th>
    </tr>
    <tr>
        <td align="left">Microsoft C/C++ 8</td>
        <td align="center">57</td>
    </tr>
        <tr>
        <td align="left">Digital Mars C/C++ 8</td>
        <td align="center">41</td>
    </tr>
        <tr>
        <td align="left">Open Watcom</td>
        <td align="center">37</td>
    </tr>
        <tr>
        <td align="left">Borland Turbo C 2</td>
        <td align="center">33</td>
    </tr>
        <tr>
        <td align="left">Borland C++ 2</td>
        <td align="center">32</td>
    </tr>
        <tr>
        <td align="left">Microsoft C 5</td>
        <td align="center">32</td>
    </tr>
        <tr>
        <td align="left">Microsoft QuickC 1</td>
        <td align="center">31</td>
    </tr>
        <tr>
        <td align="left">HI-TECH Pacific C 7</td>
        <td align="center">30</td>
    </tr>
        </tr>
        <tr>
        <td align="left">Mix Power C 2</td>
        <td align="center">14</td>
    </tr>
</table>

![A screenshot of dccb](http://tarpeeksihyvaesoft.com/soft/img/dccb_b.png)
