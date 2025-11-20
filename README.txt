An alternative to the C++ STL, highly based of the Outsourced Utils library.

Designed exclusively for me, but can be used by anyone.

Has been tested to work on Windows, Linux and macOS.

Compilation guide:

This is a dependency-free (except some headers included with every compiler) library, compiled to dynamic library (DLL).

0. this library does require C++11 and C99 compilers
0.1. I recommend using clang compiler, because this is what I usually it with.
1. run cmake . and then cmake --build . which will build the library and the unit tester.
2. include the include directory in your CMakeLists.txt, to use the headers.
3. profit
