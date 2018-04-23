C++14 Project Template
======================

Project template for C++11 using the Premake 5 build system.

Compiling and Testing
---------------------

1. Place yourself in the root directory of this project.
2. Acquire the latest version of the `premake5` build system.
3. Thereafter, execute `premake5 gmake` if building on Make.
4. Finally, issue the command `make -j8 -C build` and wait.
5. When complete, either `bin` or `lib` have been built.
6. Tests can be run with the `bin/*-tests` programs.
7. **Shortcuts:** `make run` and `make test`.

Usage and Documents
-------------------

See the `docs` directory for *maybe* the project documentation.

System Requirements
-------------------

Requires OpenGL 1.1

Dependencies
------------

* `Premake5`
* `GLFW` 
* `Catch`

Structure
---------
* `build` - generated workspace
* `build/bin` - compiled binaries
* `projects` - source code for workspace projects
* `lib` - external and internal libraries, need to add prcompiled `GLFW`.


Acknowledgements
----------------

> mgrlllmgrlrrr - Old Murk-Eye
