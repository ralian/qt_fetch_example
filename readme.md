# qt_fetch_example: Linking against Qt6 using CMake FetchContent

**What is this?**

If you have created or built a QT project before, you've probably had to mess with your environment to either set up QT or at least set up QT's downloader/build system. While this is manageable, I wanted to see if it was possible to simplify the process by grabbing Qt straight from the source.

The most interesting part of this is the CMake infrastructure, which actually ended up being quite simple. The examples provided are all either attributed to the CMake documentation, or simple things I threw together myself to demonstrate linking to and using different parts of the QtBase library (Core, Gui, Widgets, and Network - plus all QT's base tools and executables like MOC).

**Should I use this?**

For production, definitely not. I'm not suggesting this is the _correct_ way to link against QT - but it does work! If you like it, feel free to use this method for a demo/non-critical project of your own.

**How do I use this?**

As mentioned, you don't have to have _any_ QT install on your system. You just need a C++ compiler along with CMake (and Ninja unless you switch generators). For Windows, if you have the MSVC dev tools installed, you probably just have to open a "Developer Powershell" session and you're good to go. For Linux or MacOS, you can figure it out :)

To configure: `cmake --preset default .`
(Be aware that this will take at least several minutes the first time, as it needs to download QT! CMake is greedy with FetchContent debug output, so expect to be staring at a blank terminal for awhile. Patience.)

To build: `cmake --build --preset debug .` / `cmake --build --preset release .`
This builds all examples in the repo.

To execute: `..\example_1\Debug\example_1.exe` - replace `example_1.exe` with your example, dropping the `.exe` if not on Windows.
At least on Windows, this must be run from the `build\default\bin` dir with all the QT dlls, since RPaths aren't a thing.

**Caveats**

There are some interesting caveats (and benefits!) to doing things this way.
- You can pin the exact version of QT you want... but you will need a QT install per project you are working on! Unless you want to symlink the install folder which would be insane.
- Longer initial build time - In my experience, not that bad! A few extra minutes for about 1k TUs, depending on which QT features you actually need. (You don't pay for what you don't use!) Subsequent builds are just as fast as you would normally expect.
- Disk space! You will use more of it due to the object files, debug symbols, etc. On Windows, for Example 1, the total size of the debug build + QT libraries is 3.7 GB. Could be worse.
- Qt version - Not only Qt6+, but a very recent version of Qt6. I haven't been able to pin down the exact version, but Qt 6.9+ seems to work. Older versions run into configuration issues, at least on Windows.

This work is licensed under the GNU FDL 1.3 since much of the work is derived from the CMake documentation, under the same license.
https://www.gnu.org/licenses/fdl-1.3.html
