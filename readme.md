# <center>60-352 Project</center>
<center>By: Majid Joseph, Mostapha Rammo, Steven Bodnar, Abdul Abu Libda</center>

## Overview
The COMP-3520 Final Project outlined within is comprised of three components; 

 - **A 3D OpenGL representation backed by C++ alongside the GLFW, GLM, and assimp libraries.**
 - An SDL2 representation of commonly used primitives in computer graphics.
 - An implementation of a Bezier surface produced using Java's Processing library in conjunction with OpenGL.

**NOTE: the rest of the project readme and code is located [here](https://github.com/majid171/test)**

This document will cover 

## Submission (2/2): 3D OpenGl (+ GLFW, GLM, Assimp) 
We used OpenGL along with the GLFW, Glad, GLM and Assimp libraries to create a Modelled Scene containing animated Hierarchical Models.
We have also implemented a moving POV style camera to explore the scene powered by the mouse and the WASD keys.

#### CheckList
 - 3D Objects / Polyhedrals
 - Hierarchical Models
 - Scene Modelling
 - Rendering (Objects and Surface)
 - 3D Clipping
 - Z-Buffer
 - Backface Culling
 - Ambient Light
 - Light Sources
 - Moving POV Camera
 - Surface Textures
 - Animation

#### Setup

To setup the repo, you will need to have the following libraries installed:
 - GLFW
 - Custom GLAD
 - GLM
 - Assimp
 - OpenGL

Once this is all put together, pull the repo and use cmake to build the `project` executable.

Setup may now be straightforward on your machine (especially in a Windows environment). Because of this I've uploaded a video demonstrating
the final product.  Visit the following [youtube link](https://youtu.be/wA40nn_US_g) to view it.
