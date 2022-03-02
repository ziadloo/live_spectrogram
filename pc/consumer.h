//
// Created by mehran on 2022-02-06.
//


#include <vector>
#include <functional>
#include <fftw3.h>
#include "lib/queue/readerwriterqueue.h"
#include "../utility.h"
#include "task.h"
#include "./producer.h"

using namespace std;
using namespace moodycamel;

class consumer: public task {
Q_OBJECT
public:
    consumer(producer* p, int sample_rate, int num_per_points);
    double amplitude(fftw_complex const result) const;
    double magnitude(fftw_complex const result) const;
    double smooth_signal(double arr[]) const;

protected:
    void thread_code() override;

private:
    int NUM_POINTS;
    producer* pro;

signals:
    void onNewSpectrum(vector_double spectrum);
    void onNewDecibel(vector_double decibels);
};
