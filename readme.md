GLFW window application
======================

![assets/logo.png]{logo.png}

Compiling and Testing
---------------------

1. Download and Install `premake5`
2. run `premake5 vs2015` or whatever build system you ware using
3. build _appwrapper_ and _app_
4. run _app.exe_ and make sure the _assets_ folder is located in the working dir.

Usage and Documents
-------------------

See the `docs` directory for *maybe* the project documentation.

System Requirements
-------------------

Requires OpenGL 3.1

Dependencies
------------

* `Premake5`
* `GLFW` 
* `GLEW`
* `LodePNG`
* `Catch`

Structure
---------
* `build` - generated workspace
* `projects` - source code for workspace projects
* `lib` - external and internal libraries, need to add prcompiled `GLFW`, `GLEW` and includes for the remaining libs.


Acknowledgements
----------------

> mgrlllmgrlrrr - Old Murk-Eye
