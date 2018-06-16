# Green Fractals

This application generates fractal animations using the method discovered by Melinda Green to visualize the Mandelbrot set (her version is often referred to as a Buddhabrot).

Melinda's technique samples points in the complex plane, and then tests them through repeated iteration to see if they eventually land outside of a specified escape radius. The number of iterations it takes for an initial value to escape is stored in an array. This array is used as a heat map to produce a representation of the Mandelbrot set.

Here is Melinda's page describing the process and displaying a number of examples: 

[The Buddhabrot Technique](http://superliminal.com/fractals/bbrot/bbrot.htm)

To create the animations, a higher degree generating function is used. The usual Mandelbrot equation is: 

`z = z^2 + C`

The degrees used by this application can be customized, but at least three unique terms are usually used, along with a series of coefficients that drive the animations. Before calculating the next step, the previous value is also replaced with its conjugate:

`w = conj(z)`

`z = P * w^3 + Q * w^2 + R * w^1 + C` 

A single image is created by iterating the equation with a specific set of coefficients. Then the coefficients are transformed as a vector (<P, Q, R>). This slightly alters the image that is produced, allowing the creation of the animations. 
