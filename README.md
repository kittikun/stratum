stratum
=======

More info when the project reach a certain maturirty

### Prerequisites


- Boost 1.53.0 - http://www.boost.org/
- Boost Log - http://sourceforge.net/projects/boost-log/


### Linux

- CMake files in build/linux
- GLES2 libraries
  $ sudo apt-get install libgles2-mesa-dev

### Windows

- VS2012 Solution file in build/win
- EGL + GLES emulation (nVidia's OpenGL ES 2.0 was used)

### Android

Export $(NDK_ROOT)

Boost:
- build boost https://github.com/MysticTreeGames/Boost-for-Android
- put boost include folder in build/android/jni/include
- put libraries in build/android/jni/lib
