//
// Created by mehran on 2022-02-06.
//

#ifndef ARECORD_UTILITY_H
#define ARECORD_UTILITY_H

#include <vector>

#define _REAL_ 0
#define _IMAG_ 1
#define _SAMPLE_RATE_ 44100
#define _NUM_POINTS_ 4096 //_SAMPLE_RATE_/16
#define _WINDOW_HOP_ _NUM_POINTS_/8*7

//#define _FRAMES_PER_SEC_ 20
#define _SAMPLES_PER_FRAME_ _WINDOW_HOP_

typedef short format;
typedef std::vector<double> vector_double;


#endif //ARECORD_UTILITY_H
