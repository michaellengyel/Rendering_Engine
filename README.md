# Rendering Engine
A rending engine for rendering 3D objects. The objective of this software peoject is to create a rendering engine which enables the rendeing of 3D models and implements a camera view to view said objects from any desirable point. The software should furthermore implement a user input, and make the objects clickable.

### Used Guides
GLFW was integrating as a submodule based the following guide:   
https://www.youtube.com/watch?v=ED-WUk440qc   

GLEW was integrating as a submodule based from the following git repository:   
https://github.com/Perlmint/glew-cmake   
https://stackoverflow.com/questions/49434279/adding-glew-to-project-cmake   

### System Dependencies
#### Linux:   
*Compiler error:* error: GLSL 3.30 is not supported.   
*Resolved by Linux command:* export MESA_GL_VERSION_OVERRIDE=3.3   
