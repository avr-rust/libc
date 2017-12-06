/* Copyright (c) 2007  Dmitry Xmelkov
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
 */

/* Test of pow() function.
   $Id: pow-01.c 1923 2009-03-07 14:02:24Z dmix $
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "progmem.h"

union lofl_u {
    long lo;
    float fl;
};

volatile union lofl_u v = { .lo = 1 };

PROGMEM const struct {		/* Table of test cases	*/
    union lofl_u x, y;		/* args		*/
    union lofl_u z;		/* pow(x,y)	*/
} t[] = {

    { { 0x00000000 },{ 0x00000000 },{ 0x3f800000 } }, /*    0    0      1 */
    { { 0x00000000 },{ 0x3f000000 },{ 0x00000000 } }, /*    0  0.5      0 */
    { { 0x00000000 },{ 0x3f800000 },{ 0x00000000 } }, /*    0    1      0 */
    { { 0x00000000 },{ 0x3fc00000 },{ 0x00000000 } }, /*    0  1.5      0 */
    { { 0x00000000 },{ 0x40000000 },{ 0x00000000 } }, /*    0    2      0 */
    { { 0x00000000 },{ 0x40400000 },{ 0x00000000 } }, /*    0    3      0 */
    { { 0x00000000 },{ 0x7f800000 },{ 0x00000000 } }, /*    0  inf      0 */
    { { 0x00000000 },{ 0x7fc00000 },{ 0x7fc00000 } }, /*    0  nan    nan */
    { { 0x00000000 },{ 0x80000000 },{ 0x3f800000 } }, /*    0   -0      1 */
    { { 0x00000000 },{ 0xbf000000 },{ 0x7f800000 } }, /*    0 -0.5    inf */
    { { 0x00000000 },{ 0xbf800000 },{ 0x7f800000 } }, /*    0   -1    inf */
    { { 0x00000000 },{ 0xbfc00000 },{ 0x7f800000 } }, /*    0 -1.5    inf */
    { { 0x00000000 },{ 0xc0000000 },{ 0x7f800000 } }, /*    0   -2    inf */
    { { 0x00000000 },{ 0xc0400000 },{ 0x7f800000 } }, /*    0   -3    inf */
    { { 0x00000000 },{ 0xff800000 },{ 0x7f800000 } }, /*    0 -inf    inf */

    { { 0x80000000 },{ 0x00000000 },{ 0x3f800000 } }, /*   -0    0      1 */
    { { 0x80000000 },{ 0x3f000000 },{ 0x00000000 } }, /*   -0  0.5      0 */
    { { 0x80000000 },{ 0x3f800000 },{ 0x80000000 } }, /*   -0    1     -0 */
    { { 0x80000000 },{ 0x3fc00000 },{ 0x00000000 } }, /*   -0  1.5      0 */
    { { 0x80000000 },{ 0x40000000 },{ 0x00000000 } }, /*   -0    2      0 */
    { { 0x80000000 },{ 0x40400000 },{ 0x80000000 } }, /*   -0    3     -0 */
    { { 0x80000000 },{ 0x7f800000 },{ 0x00000000 } }, /*   -0  inf      0 */
    { { 0x80000000 },{ 0x7fc00000 },{ 0x7fc00000 } }, /*   -0  nan    nan */
    { { 0x80000000 },{ 0x80000000 },{ 0x3f800000 } }, /*   -0   -0      1 */
    { { 0x80000000 },{ 0xbf000000 },{ 0x7f800000 } }, /*   -0 -0.5    inf */
    { { 0x80000000 },{ 0xbf800000 },{ 0xff800000 } }, /*   -0   -1   -inf */
    { { 0x80000000 },{ 0xbfc00000 },{ 0x7f800000 } }, /*   -0 -1.5    inf */
    { { 0x80000000 },{ 0xc0000000 },{ 0x7f800000 } }, /*   -0   -2    inf */
    { { 0x80000000 },{ 0xc0400000 },{ 0xff800000 } }, /*   -0   -3   -inf */
    { { 0x80000000 },{ 0xff800000 },{ 0x7f800000 } }, /*   -0 -inf    inf */

    { { 0x3f000000 },{ 0x00000000 },{ 0x3f800000 } }, /*  0.5    0      1 */
    { { 0x3f000000 },{ 0x3f000000 },{ 0x3f3504f3 } }, /*  0.5  0.5  0.707 */
    { { 0x3f000000 },{ 0x3f800000 },{ 0x3f000000 } }, /*  0.5    1    0.5 */
    { { 0x3f000000 },{ 0x3fc00000 },{ 0x3eb504f3 } }, /*  0.5  1.5  0.354 */
    { { 0x3f000000 },{ 0x40000000 },{ 0x3e800000 } }, /*  0.5    2   0.25 */
    { { 0x3f000000 },{ 0x40400000 },{ 0x3e000000 } }, /*  0.5    3  0.125 */
    { { 0x3f000000 },{ 0x7f800000 },{ 0x00000000 } }, /*  0.5  inf      0 */
    { { 0x3f000000 },{ 0x7fc00000 },{ 0x7fc00000 } }, /*  0.5  nan    nan */
    { { 0x3f000000 },{ 0x80000000 },{ 0x3f800000 } }, /*  0.5   -0      1 */
    { { 0x3f000000 },{ 0xbf000000 },{ 0x3fb504f3 } }, /*  0.5 -0.5   1.41 */
    { { 0x3f000000 },{ 0xbf800000 },{ 0x40000000 } }, /*  0.5   -1      2 */
    { { 0x3f000000 },{ 0xbfc00000 },{ 0x403504f3 } }, /*  0.5 -1.5   2.83 */
    { { 0x3f000000 },{ 0xc0000000 },{ 0x40800000 } }, /*  0.5   -2      4 */
    { { 0x3f000000 },{ 0xc0400000 },{ 0x41000000 } }, /*  0.5   -3      8 */
    { { 0x3f000000 },{ 0xff800000 },{ 0x7f800000 } }, /*  0.5 -inf    inf */

    { { 0xbf000000 },{ 0x00000000 },{ 0x3f800000 } }, /* -0.5    0      1 */
    { { 0xbf000000 },{ 0x3f000000 },{ 0xffc00000 } }, /* -0.5  0.5    nan */
    { { 0xbf000000 },{ 0x3f800000 },{ 0xbf000000 } }, /* -0.5    1   -0.5 */
    { { 0xbf000000 },{ 0x3fc00000 },{ 0xffc00000 } }, /* -0.5  1.5    nan */
    { { 0xbf000000 },{ 0x40000000 },{ 0x3e800000 } }, /* -0.5    2   0.25 */
    { { 0xbf000000 },{ 0x40400000 },{ 0xbe000000 } }, /* -0.5    3 -0.125 */
    { { 0xbf000000 },{ 0x7f800000 },{ 0x00000000 } }, /* -0.5  inf      0 */
    { { 0xbf000000 },{ 0x7fc00000 },{ 0x7fc00000 } }, /* -0.5  nan    nan */
    { { 0xbf000000 },{ 0x80000000 },{ 0x3f800000 } }, /* -0.5   -0      1 */
    { { 0xbf000000 },{ 0xbf000000 },{ 0xffc00000 } }, /* -0.5 -0.5    nan */
    { { 0xbf000000 },{ 0xbf800000 },{ 0xc0000000 } }, /* -0.5   -1     -2 */
    { { 0xbf000000 },{ 0xbfc00000 },{ 0xffc00000 } }, /* -0.5 -1.5    nan */
    { { 0xbf000000 },{ 0xc0000000 },{ 0x40800000 } }, /* -0.5   -2      4 */
    { { 0xbf000000 },{ 0xc0400000 },{ 0xc1000000 } }, /* -0.5   -3     -8 */
    { { 0xbf000000 },{ 0xff800000 },{ 0x7f800000 } }, /* -0.5 -inf    inf */

    { { 0x3f800000 },{ 0x00000000 },{ 0x3f800000 } }, /*    1    0      1 */
    { { 0x3f800000 },{ 0x3f000000 },{ 0x3f800000 } }, /*    1  0.5      1 */
    { { 0x3f800000 },{ 0x3f800000 },{ 0x3f800000 } }, /*    1    1      1 */
    { { 0x3f800000 },{ 0x3fc00000 },{ 0x3f800000 } }, /*    1  1.5      1 */
    { { 0x3f800000 },{ 0x40000000 },{ 0x3f800000 } }, /*    1    2      1 */
    { { 0x3f800000 },{ 0x40400000 },{ 0x3f800000 } }, /*    1    3      1 */
    { { 0x3f800000 },{ 0x7f800000 },{ 0x3f800000 } }, /*    1  inf      1 */
    { { 0x3f800000 },{ 0x7fc00000 },{ 0x3f800000 } }, /*    1  nan      1 */
    { { 0x3f800000 },{ 0x80000000 },{ 0x3f800000 } }, /*    1   -0      1 */
    { { 0x3f800000 },{ 0xbf000000 },{ 0x3f800000 } }, /*    1 -0.5      1 */
    { { 0x3f800000 },{ 0xbf800000 },{ 0x3f800000 } }, /*    1   -1      1 */
    { { 0x3f800000 },{ 0xbfc00000 },{ 0x3f800000 } }, /*    1 -1.5      1 */
    { { 0x3f800000 },{ 0xc0000000 },{ 0x3f800000 } }, /*    1   -2      1 */
    { { 0x3f800000 },{ 0xc0400000 },{ 0x3f800000 } }, /*    1   -3      1 */
    { { 0x3f800000 },{ 0xff800000 },{ 0x3f800000 } }, /*    1 -inf      1 */

    { { 0xbf800000 },{ 0x00000000 },{ 0x3f800000 } }, /*   -1    0      1 */
    { { 0xbf800000 },{ 0x3f000000 },{ 0xffc00000 } }, /*   -1  0.5    nan */
    { { 0xbf800000 },{ 0x3f800000 },{ 0xbf800000 } }, /*   -1    1     -1 */
    { { 0xbf800000 },{ 0x3fc00000 },{ 0xffc00000 } }, /*   -1  1.5    nan */
    { { 0xbf800000 },{ 0x40000000 },{ 0x3f800000 } }, /*   -1    2      1 */
    { { 0xbf800000 },{ 0x40400000 },{ 0xbf800000 } }, /*   -1    3     -1 */
    { { 0xbf800000 },{ 0x7f800000 },{ 0x3f800000 } }, /*   -1  inf      1 */
    { { 0xbf800000 },{ 0x7fc00000 },{ 0x7fc00000 } }, /*   -1  nan    nan */
    { { 0xbf800000 },{ 0x80000000 },{ 0x3f800000 } }, /*   -1   -0      1 */
    { { 0xbf800000 },{ 0xbf000000 },{ 0xffc00000 } }, /*   -1 -0.5    nan */
    { { 0xbf800000 },{ 0xbf800000 },{ 0xbf800000 } }, /*   -1   -1     -1 */
    { { 0xbf800000 },{ 0xbfc00000 },{ 0xffc00000 } }, /*   -1 -1.5    nan */
    { { 0xbf800000 },{ 0xc0000000 },{ 0x3f800000 } }, /*   -1   -2      1 */
    { { 0xbf800000 },{ 0xc0400000 },{ 0xbf800000 } }, /*   -1   -3     -1 */
    { { 0xbf800000 },{ 0xff800000 },{ 0x3f800000 } }, /*   -1 -inf      1 */

    { { 0x3fc00000 },{ 0x00000000 },{ 0x3f800000 } }, /*  1.5    0      1 */
    { { 0x3fc00000 },{ 0x3f000000 },{ 0x3f9cc471 } }, /*  1.5  0.5   1.22 */
    { { 0x3fc00000 },{ 0x3f800000 },{ 0x3fc00000 } }, /*  1.5    1    1.5 */
    { { 0x3fc00000 },{ 0x3fc00000 },{ 0x3feb26a9 } }, /*  1.5  1.5   1.84 */
    { { 0x3fc00000 },{ 0x40000000 },{ 0x40100000 } }, /*  1.5    2   2.25 */
    { { 0x3fc00000 },{ 0x40400000 },{ 0x40580000 } }, /*  1.5    3   3.38 */
    { { 0x3fc00000 },{ 0x7f800000 },{ 0x7f800000 } }, /*  1.5  inf    inf */
    { { 0x3fc00000 },{ 0x7fc00000 },{ 0x7fc00000 } }, /*  1.5  nan    nan */
    { { 0x3fc00000 },{ 0x80000000 },{ 0x3f800000 } }, /*  1.5   -0      1 */
    { { 0x3fc00000 },{ 0xbf000000 },{ 0x3f5105ec } }, /*  1.5 -0.5  0.816 */
    { { 0x3fc00000 },{ 0xbf800000 },{ 0x3f2aaaab } }, /*  1.5   -1  0.667 */
    { { 0x3fc00000 },{ 0xbfc00000 },{ 0x3f0b5948 } }, /*  1.5 -1.5  0.544 */
    { { 0x3fc00000 },{ 0xc0000000 },{ 0x3ee38e39 } }, /*  1.5   -2  0.444 */
    { { 0x3fc00000 },{ 0xc0400000 },{ 0x3e97b426 } }, /*  1.5   -3  0.296 */
    { { 0x3fc00000 },{ 0xff800000 },{ 0x00000000 } }, /*  1.5 -inf      0 */

    { { 0xbfc00000 },{ 0x00000000 },{ 0x3f800000 } }, /* -1.5    0      1 */
    { { 0xbfc00000 },{ 0x3f000000 },{ 0xffc00000 } }, /* -1.5  0.5    nan */
    { { 0xbfc00000 },{ 0x3f800000 },{ 0xbfc00000 } }, /* -1.5    1   -1.5 */
    { { 0xbfc00000 },{ 0x3fc00000 },{ 0xffc00000 } }, /* -1.5  1.5    nan */
    { { 0xbfc00000 },{ 0x40000000 },{ 0x40100000 } }, /* -1.5    2   2.25 */
    { { 0xbfc00000 },{ 0x40400000 },{ 0xc0580000 } }, /* -1.5    3  -3.38 */
    { { 0xbfc00000 },{ 0x7f800000 },{ 0x7f800000 } }, /* -1.5  inf    inf */
    { { 0xbfc00000 },{ 0x7fc00000 },{ 0x7fc00000 } }, /* -1.5  nan    nan */
    { { 0xbfc00000 },{ 0x80000000 },{ 0x3f800000 } }, /* -1.5   -0      1 */
    { { 0xbfc00000 },{ 0xbf000000 },{ 0xffc00000 } }, /* -1.5 -0.5    nan */
    { { 0xbfc00000 },{ 0xbf800000 },{ 0xbf2aaaab } }, /* -1.5   -1 -0.667 */
    { { 0xbfc00000 },{ 0xbfc00000 },{ 0xffc00000 } }, /* -1.5 -1.5    nan */
    { { 0xbfc00000 },{ 0xc0000000 },{ 0x3ee38e39 } }, /* -1.5   -2  0.444 */
    { { 0xbfc00000 },{ 0xc0400000 },{ 0xbe97b426 } }, /* -1.5   -3 -0.296 */
    { { 0xbfc00000 },{ 0xff800000 },{ 0x00000000 } }, /* -1.5 -inf      0 */

    { { 0x40000000 },{ 0x00000000 },{ 0x3f800000 } }, /*    2    0      1 */
    { { 0x40000000 },{ 0x3f000000 },{ 0x3fb504f3 } }, /*    2  0.5   1.41 */
    { { 0x40000000 },{ 0x3f800000 },{ 0x40000000 } }, /*    2    1      2 */
    { { 0x40000000 },{ 0x3fc00000 },{ 0x403504f3 } }, /*    2  1.5   2.83 */
    { { 0x40000000 },{ 0x40000000 },{ 0x40800000 } }, /*    2    2      4 */
    { { 0x40000000 },{ 0x40400000 },{ 0x41000000 } }, /*    2    3      8 */
    { { 0x40000000 },{ 0x7f800000 },{ 0x7f800000 } }, /*    2  inf    inf */
    { { 0x40000000 },{ 0x7fc00000 },{ 0x7fc00000 } }, /*    2  nan    nan */
    { { 0x40000000 },{ 0x80000000 },{ 0x3f800000 } }, /*    2   -0      1 */
    { { 0x40000000 },{ 0xbf000000 },{ 0x3f3504f3 } }, /*    2 -0.5  0.707 */
    { { 0x40000000 },{ 0xbf800000 },{ 0x3f000000 } }, /*    2   -1    0.5 */
    { { 0x40000000 },{ 0xbfc00000 },{ 0x3eb504f3 } }, /*    2 -1.5  0.354 */
    { { 0x40000000 },{ 0xc0000000 },{ 0x3e800000 } }, /*    2   -2   0.25 */
    { { 0x40000000 },{ 0xc0400000 },{ 0x3e000000 } }, /*    2   -3  0.125 */
    { { 0x40000000 },{ 0xff800000 },{ 0x00000000 } }, /*    2 -inf      0 */

    { { 0xc0000000 },{ 0x00000000 },{ 0x3f800000 } }, /*   -2    0      1 */
    { { 0xc0000000 },{ 0x3f000000 },{ 0xffc00000 } }, /*   -2  0.5    nan */
    { { 0xc0000000 },{ 0x3f800000 },{ 0xc0000000 } }, /*   -2    1     -2 */
    { { 0xc0000000 },{ 0x3fc00000 },{ 0xffc00000 } }, /*   -2  1.5    nan */
    { { 0xc0000000 },{ 0x40000000 },{ 0x40800000 } }, /*   -2    2      4 */
    { { 0xc0000000 },{ 0x40400000 },{ 0xc1000000 } }, /*   -2    3     -8 */
    { { 0xc0000000 },{ 0x7f800000 },{ 0x7f800000 } }, /*   -2  inf    inf */
    { { 0xc0000000 },{ 0x7fc00000 },{ 0x7fc00000 } }, /*   -2  nan    nan */
    { { 0xc0000000 },{ 0x80000000 },{ 0x3f800000 } }, /*   -2   -0      1 */
    { { 0xc0000000 },{ 0xbf000000 },{ 0xffc00000 } }, /*   -2 -0.5    nan */
    { { 0xc0000000 },{ 0xbf800000 },{ 0xbf000000 } }, /*   -2   -1   -0.5 */
    { { 0xc0000000 },{ 0xbfc00000 },{ 0xffc00000 } }, /*   -2 -1.5    nan */
    { { 0xc0000000 },{ 0xc0000000 },{ 0x3e800000 } }, /*   -2   -2   0.25 */
    { { 0xc0000000 },{ 0xc0400000 },{ 0xbe000000 } }, /*   -2   -3 -0.125 */
    { { 0xc0000000 },{ 0xff800000 },{ 0x00000000 } }, /*   -2 -inf      0 */

    { { 0x40400000 },{ 0x00000000 },{ 0x3f800000 } }, /*    3    0      1 */
    { { 0x40400000 },{ 0x3f000000 },{ 0x3fddb3d7 } }, /*    3  0.5   1.73 */
    { { 0x40400000 },{ 0x3f800000 },{ 0x40400000 } }, /*    3    1      3 */
    { { 0x40400000 },{ 0x3fc00000 },{ 0x40a646e1 } }, /*    3  1.5    5.2 */
    { { 0x40400000 },{ 0x40000000 },{ 0x41100000 } }, /*    3    2      9 */
    { { 0x40400000 },{ 0x40400000 },{ 0x41d80000 } }, /*    3    3     27 */
    { { 0x40400000 },{ 0x7f800000 },{ 0x7f800000 } }, /*    3  inf    inf */
    { { 0x40400000 },{ 0x7fc00000 },{ 0x7fc00000 } }, /*    3  nan    nan */
    { { 0x40400000 },{ 0x80000000 },{ 0x3f800000 } }, /*    3   -0      1 */
    { { 0x40400000 },{ 0xbf000000 },{ 0x3f13cd3a } }, /*    3 -0.5  0.577 */
    { { 0x40400000 },{ 0xbf800000 },{ 0x3eaaaaab } }, /*    3   -1  0.333 */
    { { 0x40400000 },{ 0xbfc00000 },{ 0x3e4511a3 } }, /*    3 -1.5  0.192 */
    { { 0x40400000 },{ 0xc0000000 },{ 0x3de38e39 } }, /*    3   -2  0.111 */
    { { 0x40400000 },{ 0xc0400000 },{ 0x3d17b426 } }, /*    3   -3  0.037 */
    { { 0x40400000 },{ 0xff800000 },{ 0x00000000 } }, /*    3 -inf      0 */

    { { 0xc0400000 },{ 0x00000000 },{ 0x3f800000 } }, /*   -3    0      1 */
    { { 0xc0400000 },{ 0x3f000000 },{ 0xffc00000 } }, /*   -3  0.5    nan */
    { { 0xc0400000 },{ 0x3f800000 },{ 0xc0400000 } }, /*   -3    1     -3 */
    { { 0xc0400000 },{ 0x3fc00000 },{ 0xffc00000 } }, /*   -3  1.5    nan */
    { { 0xc0400000 },{ 0x40000000 },{ 0x41100000 } }, /*   -3    2      9 */
    { { 0xc0400000 },{ 0x40400000 },{ 0xc1d80000 } }, /*   -3    3    -27 */
    { { 0xc0400000 },{ 0x7f800000 },{ 0x7f800000 } }, /*   -3  inf    inf */
    { { 0xc0400000 },{ 0x7fc00000 },{ 0x7fc00000 } }, /*   -3  nan    nan */
    { { 0xc0400000 },{ 0x80000000 },{ 0x3f800000 } }, /*   -3   -0      1 */
    { { 0xc0400000 },{ 0xbf000000 },{ 0xffc00000 } }, /*   -3 -0.5    nan */
    { { 0xc0400000 },{ 0xbf800000 },{ 0xbeaaaaab } }, /*   -3   -1 -0.333 */
    { { 0xc0400000 },{ 0xbfc00000 },{ 0xffc00000 } }, /*   -3 -1.5    nan */
    { { 0xc0400000 },{ 0xc0000000 },{ 0x3de38e39 } }, /*   -3   -2  0.111 */
    { { 0xc0400000 },{ 0xc0400000 },{ 0xbd17b426 } }, /*   -3   -3 -0.037 */
    { { 0xc0400000 },{ 0xff800000 },{ 0x00000000 } }, /*   -3 -inf      0 */

    { { 0x7f800000 },{ 0x00000000 },{ 0x3f800000 } }, /*  inf    0      1 */
    { { 0x7f800000 },{ 0x3f000000 },{ 0x7f800000 } }, /*  inf  0.5    inf */
    { { 0x7f800000 },{ 0x3f800000 },{ 0x7f800000 } }, /*  inf    1    inf */
    { { 0x7f800000 },{ 0x3fc00000 },{ 0x7f800000 } }, /*  inf  1.5    inf */
    { { 0x7f800000 },{ 0x40000000 },{ 0x7f800000 } }, /*  inf    2    inf */
    { { 0x7f800000 },{ 0x40400000 },{ 0x7f800000 } }, /*  inf    3    inf */
    { { 0x7f800000 },{ 0x7f800000 },{ 0x7f800000 } }, /*  inf  inf    inf */
    { { 0x7f800000 },{ 0x7fc00000 },{ 0x7fc00000 } }, /*  inf  nan    nan */
    { { 0x7f800000 },{ 0x80000000 },{ 0x3f800000 } }, /*  inf   -0      1 */
    { { 0x7f800000 },{ 0xbf000000 },{ 0x00000000 } }, /*  inf -0.5      0 */
    { { 0x7f800000 },{ 0xbf800000 },{ 0x00000000 } }, /*  inf   -1      0 */
    { { 0x7f800000 },{ 0xbfc00000 },{ 0x00000000 } }, /*  inf -1.5      0 */
    { { 0x7f800000 },{ 0xc0000000 },{ 0x00000000 } }, /*  inf   -2      0 */
    { { 0x7f800000 },{ 0xc0400000 },{ 0x00000000 } }, /*  inf   -3      0 */
    { { 0x7f800000 },{ 0xff800000 },{ 0x00000000 } }, /*  inf -inf      0 */

    { { 0xff800000 },{ 0x00000000 },{ 0x3f800000 } }, /* -inf    0      1 */
    { { 0xff800000 },{ 0x3f000000 },{ 0x7f800000 } }, /* -inf  0.5    inf */
    { { 0xff800000 },{ 0x3f800000 },{ 0xff800000 } }, /* -inf    1   -inf */
    { { 0xff800000 },{ 0x3fc00000 },{ 0x7f800000 } }, /* -inf  1.5    inf */
    { { 0xff800000 },{ 0x40000000 },{ 0x7f800000 } }, /* -inf    2    inf */
    { { 0xff800000 },{ 0x40400000 },{ 0xff800000 } }, /* -inf    3   -inf */
    { { 0xff800000 },{ 0x7f800000 },{ 0x7f800000 } }, /* -inf  inf    inf */
    { { 0xff800000 },{ 0x7fc00000 },{ 0x7fc00000 } }, /* -inf  nan    nan */
    { { 0xff800000 },{ 0x80000000 },{ 0x3f800000 } }, /* -inf   -0      1 */
    { { 0xff800000 },{ 0xbf000000 },{ 0x00000000 } }, /* -inf -0.5      0 */
    { { 0xff800000 },{ 0xbf800000 },{ 0x80000000 } }, /* -inf   -1     -0 */
    { { 0xff800000 },{ 0xbfc00000 },{ 0x00000000 } }, /* -inf -1.5      0 */
    { { 0xff800000 },{ 0xc0000000 },{ 0x00000000 } }, /* -inf   -2      0 */
    { { 0xff800000 },{ 0xc0400000 },{ 0x80000000 } }, /* -inf   -3     -0 */
    { { 0xff800000 },{ 0xff800000 },{ 0x00000000 } }, /* -inf -inf      0 */

    { { 0x7fc00000 },{ 0x00000000 },{ 0x3f800000 } }, /*  nan    0      1 */
    { { 0x7fc00000 },{ 0x3f000000 },{ 0x7fc00000 } }, /*  nan  0.5    nan */
    { { 0x7fc00000 },{ 0x3f800000 },{ 0x7fc00000 } }, /*  nan    1    nan */
    { { 0x7fc00000 },{ 0x3fc00000 },{ 0x7fc00000 } }, /*  nan  1.5    nan */
    { { 0x7fc00000 },{ 0x40000000 },{ 0x7fc00000 } }, /*  nan    2    nan */
    { { 0x7fc00000 },{ 0x40400000 },{ 0x7fc00000 } }, /*  nan    3    nan */
    { { 0x7fc00000 },{ 0x7f800000 },{ 0x7fc00000 } }, /*  nan  inf    nan */
    { { 0x7fc00000 },{ 0x7fc00000 },{ 0x7fc00000 } }, /*  nan  nan    nan */
    { { 0x7fc00000 },{ 0x80000000 },{ 0x3f800000 } }, /*  nan   -0      1 */
    { { 0x7fc00000 },{ 0xbf000000 },{ 0x7fc00000 } }, /*  nan -0.5    nan */
    { { 0x7fc00000 },{ 0xbf800000 },{ 0x7fc00000 } }, /*  nan   -1    nan */
    { { 0x7fc00000 },{ 0xbfc00000 },{ 0x7fc00000 } }, /*  nan -1.5    nan */
    { { 0x7fc00000 },{ 0xc0000000 },{ 0x7fc00000 } }, /*  nan   -2    nan */
    { { 0x7fc00000 },{ 0xc0400000 },{ 0x7fc00000 } }, /*  nan   -3    nan */
    { { 0x7fc00000 },{ 0xff800000 },{ 0x7fc00000 } }, /*  nan -inf    nan */
};

void x_exit (int index)
{
#ifndef	__AVR__
    fprintf (stderr, "t[%d]:  %#lx\n", index - 1, v.lo);
#endif
    exit (index ? index : -1);
}

int main ()
{
    union lofl_u x,y,z;
    int i;
    
    for (i = 0; i < (int) (sizeof(t) / sizeof(t[0])); i++) {
	y.lo = pgm_read_dword (& t[i].y);
	x.lo = pgm_read_dword (& t[i].x);
	z.lo = pgm_read_dword (& t[i].z);
	v.fl = pow (x.fl, y.fl);
	/* Comparison is integer to verify the zero sign.	*/
	if (   (v.lo == z.lo)
	    || (isnan(v.fl) && isnan(z.fl)) )
	  continue;
	if (   isfinite(v.fl)
	    && isfinite(z.fl)
	    && !((v.lo ^ z.lo) & 0x80000000)	/* signbit(v) == signbit(z) */
	    && labs(v.lo - z.lo) <= 4 )
	  continue;
	x_exit (i+1);
    }
    return 0;
}