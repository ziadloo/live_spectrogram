# Live Spectrogram
A simple program to acquire and calculate the spectrogram, mel-spectrogram, and MFCC from the system's audio live. While I don't have any practical use case for this program myself, I still think it's a good tool that provides intuition on the relationship between the three aforementioned spectrum.

## How to install
This program needs CMake v3.21 and C++ v17. You might be able to compile it using older versions of CMakes but changing the C++ version could be more challenging.

There are a handful of libraries that you need to have before you can compile this program. Namely:

1. fftw
1. RTAudio
1. Qt
1. Qwt

### 1. fftw

Download the source code from this website:

[fftw.org](http://fftw.org/)

You can compile the fftw with the following commands:

```
./configure --prefix=${PWD}/binary
make
make install
```

At this point, the compiled binary files and corresponding headers can be found in the `binary` folder. Copy them into some sub folder of this project to address them in the CMake file. I suggest into `live_spectrogram/binary/fftw` folder.

You should end up with these folders:

* live_spectrogram/binary/fftw/include
* live_spectrogram/binary/fftw/lib

### 2. RTAudio

Before you can compile this project, make sure that you have `alsa`, `pulse` and `jack` packages are installed on your OS. You can refer to your specific distribution how to install them.

Once you've installed the prerequisites, download the source code for RTAudio from here:

[github.com/thestk/rtaudio](https://github.com/thestk/rtaudio)

Navigate into that folder and compile it by running these commands:

```
./configure --prefix=${PWD}/binary --with-alsa --with-jack --with-pulse
make
make install
```

And again, the contents of the `binary` folder needs to be moved into this project's `binary` folder, under the subfolder `rtaudio`.

### 3 & 4. Qt & Qwt

While you definitely can compile and install these two from their source code, it's much easier to install them using your distro's app store. These are common packages and should be available to install easily.

### Compiling the project

If you followed the steps with the name conventions suggested  for the folders, you should be good to just compile the project. But if your folder names are different, then you need to make some minor changes in the `CMakeLists.txt` file so the paths are pointing to correct files and folders.

Namely, these are the lines you might want to update to make them match your computer's folder structure:

```
set(CMAKE_PREFIX_PATH "/usr/include/qt;/usr/include/qwt")
target_include_directories(live_spectrogram PRIVATE "/usr/include;/usr/include/qwt")
target_link_libraries(live_spectrogram PRIVATE Qt5::Core Qt5::Widgets "/usr/lib/libqwt.so")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/binary/rtaudio/include/rtaudio)
target_link_libraries(live_spectrogram PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/binary/rtaudio/lib/librtaudio.a)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/binary/fftw/include)
target_link_libraries(live_spectrogram PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/binary/fftw/lib/libfftw3.a)
```
Once you feel comfortable with the `CMakeLists.txt` file, you can compile it into a folder this way:

```
mkdir debug
cd debug
cmake ..
make
```

And to run the program:

```
./live_spectrogram
```

# DISCLAIMER

There are source code within this repo borrowed from these projects:

* https://github.com/cameron314/readerwriterqueue
* https://github.com/dspavankumar/compute-mfcc
