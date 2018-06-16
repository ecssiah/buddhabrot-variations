# Green Fractals

This application generates fractals using a variation of the Buddhabrot method discovered by Melinda Green.

Melinda's technique samples points in the complex plane, and then repeatedly applies the Mandelbrot equation to these points to see if they eventually land outside of an escape radius after a scertain number of iterations. The method keeps track of how many iterations it took for the point to leave the escape radius. It stores this number in an array which is mapped to the pixels on the screen. This array of values is then used as a heat map to determine the brightness of the image at each pixel.

Here is Melinda's page describing the process and displaying a number of examples: 

[The Buddhabrot Technique](http://superliminal.com/fractals/bbrot/bbrot.htm)

This application expands her original technique. The equation used to iterate the points is customizable. Any number of terms of varying degrees are combined together along with matching coefficients to create the generating function. On top of this, at each step in the process the previous value is conjugated before applying the equation again.

Here is an example of a generating function:

w = conjugate(z)

z = Pw<sup>3</sup> + Qw<sup>2</sup> + Rw + C

`C` is the starting point for each test, which is chosen at random from points within the desired complex range. 

This will produce a generalized fractal based on the Buddhabrot method developed by Green. I have called the range of fractals generated using this expanded methods, Green Fractals.

The application is also set up to produce a series of these fractals, which can be combined together to produce animations. The general approach is to treat the coefficients of the generating function as a vector <P, Q, R>, and then transform this vector by small amounts to produce slight variations. This series of fractals can then be combined together to form a smooth animation.

Here is an example of this animation technique:

[Fractals in Motion](https://www.youtube.com/watch?v=lS3p8Gt9PLU)

# Contributions

This software is available under the [MIT Open Source License](https://github.com/ecssiah/green-fractals/blob/master/LICENSE.txt). Contributions to the project are welcome at https://github.com/ecssiah/green-fractals. I would also appreciate it if users shared the fractals and animations they generate using this technique. I can be contacted at [](ecssiah@gmail.com).   
