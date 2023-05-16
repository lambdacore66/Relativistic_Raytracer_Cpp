# Relativistic Raytracer in C/C++ with Python/imageio video renderer

Compile code with:

                   g++ main.cpp -O3 -o main -static-libstdc++ -fopenmp

- Do not use -O3 if you want no compiletor optimizations.
- Do not use -fopenmp if you want no multithread support.

If python and imageio are not correctly set up, the code will still run and output all the video frames, but it will not render them into a single .mp4 file.


# Examples

Two cubes and a sphere moving at 0.95c seeing by two different cameras. Relativistic effects such as Terrel Rotation can be seen.

![](https://github.com/lambdacore66/Relativistic_Raytracer_Cpp/blob/master/examples/cam1.gif) ![](https://github.com/lambdacore66/Relativistic_Raytracer_Cpp/blob/master/examples/cam2.gif)


A perpendicular plane coming at 0.9c before and after crossing the camera view.

![](https://github.com/lambdacore66/Relativistic_Raytracer_Cpp/blob/master/examples/planebefore.jpeg) ![](https://github.com/lambdacore66/Relativistic_Raytracer_Cpp/blob/master/examples/planeafter.jpeg)

