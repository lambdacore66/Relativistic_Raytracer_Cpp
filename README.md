# Relativistic Raytracer in C/C++ compatible with ffmpeg for video output.

Compile code with:

                   g++ main.cpp -O3 -o main -static-libstdc++ -fopenmp

- Do not use -O3 if you want no compilator optimizations.
- Do not use -fopenmp if you want no multithread support.

To obtain video ouput, install ffmpeg and add it to the OS´ Path or locate the ffmpeg executable in the same folder as the compiled executable.

Tested and working on Windows and Ubuntu based distros.


# Examples

Two cubes and a sphere moving at 0.95c as seen by two different cameras. Relativistic effects such as Terrel Rotation are present.

![](https://github.com/lambdacore66/Relativistic_Raytracer_Cpp/blob/master/examples/cam1.gif) ![](https://github.com/lambdacore66/Relativistic_Raytracer_Cpp/blob/master/examples/cam2.gif)


A perpendicular plane coming at 0.9c before and after crossing the camera view.

![](https://github.com/lambdacore66/Relativistic_Raytracer_Cpp/blob/master/examples/planebefore.jpeg) ![](https://github.com/lambdacore66/Relativistic_Raytracer_Cpp/blob/master/examples/planeafter.jpeg)

