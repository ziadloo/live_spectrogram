cmake_minimum_required(VERSION 3.21)
project(live_spectrogram)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/usr/include/qt;/usr/include/qwt")

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
message(STATUS "QWT_INCLUDE_DIR: ${QWT_INCLUDE_DIR}")
message(STATUS "QWT_LIBRARY: ${QWT_LIBRARY}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(live_spectrogram main.cpp
        components/MainWindow.cpp components/MainWindow.h
        components/SpectrogramPlot.hpp components/MelSpectrogramPlot.hpp components/MfccPlot.hpp
        pc/producer.cpp
        pc/producer.h
        pc/consumer.cpp
        pc/consumer.h
        utility.h
        pc/task.cpp
        pc/task.h components/MelLogTransform.cpp components/MelLogTransform.h components/MelLogScaleEngine.cpp components/MelLogScaleEngine.h lib/mfcc.hpp)

target_include_directories(live_spectrogram PRIVATE "/usr/include;/usr/include/qwt")
target_link_libraries(live_spectrogram PRIVATE Qt5::Core Qt5::Widgets "/usr/lib/libqwt.so")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(live_spectrogram PRIVATE Threads::Threads)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/binary/rtaudio/include/rtaudio)
target_link_libraries(live_spectrogram PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/binary/rtaudio/lib/librtaudio.a)
set(LINKLIBS)
list(APPEND LINKLIBS ${ALSA_LIBRARY})
list(APPEND INCDIRS ${ALSA_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/binary/fftw/include)
target_link_libraries(live_spectrogram PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/binary/fftw/lib/libfftw3.a)

target_link_libraries(live_spectrogram PRIVATE ${LINKLIBS})
target_link_libraries(live_spectrogram PRIVATE jack)
target_link_libraries(live_spectrogram PRIVATE /usr/lib/libasound.so)
target_link_libraries(live_spectrogram PRIVATE /usr/lib/libpulse.so)
target_link_libraries(live_spectrogram PRIVATE /usr/lib/libpulse-simple.so)
