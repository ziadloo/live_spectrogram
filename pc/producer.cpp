//
// Created by mehran on 2022-02-06.
//

#include "producer.h"
#include <string>
#include <thread>
#include <utility>
#include <cstring>

#include "RtAudio.h"
#include <iostream>
#include <cstdlib>
#include <csignal>

using namespace std;

producer::producer(int sample_rate)
    : task(make_shared<BlockingReaderWriterQueue<vector<format>>>(100), sample_rate) {}


int record( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
            double streamTime, RtAudioStreamStatus status, void *userData )
{
    producer* p = (producer*) userData;
    if ( status )
        std::cout << "Stream overflow detected! size:" << nBufferFrames << std::endl;

    vector<format> s(nBufferFrames);
    std::memcpy(&s[0], inputBuffer, nBufferFrames * sizeof(format));
    p->queue->enqueue(s);

    return 0;
}

void producer::thread_code() {
    while (!EXIT) {
        RtAudio adc;
        if (adc.getDeviceCount() < 1) {
            std::cout << "\nNo audio devices found!\n";
            exit(1);
        }
        adc.showWarnings(true);

        RtAudio::StreamParameters parameters;
        parameters.deviceId = adc.getDefaultInputDevice();
        parameters.nChannels = 1;
        parameters.firstChannel = 0;
        unsigned int sampleRate = SAMPLE_RATE;
        unsigned int bufferFrames = _SAMPLES_PER_FRAME_;

        try {
            adc.openStream(NULL, &parameters, RTAUDIO_SINT16,
                           sampleRate, &bufferFrames, &record, (void *) this);
            adc.startStream();
        }
        catch (RtAudioError &e) {
            e.printMessage();
            if (adc.isStreamOpen()) adc.closeStream();
            exit(1);
        }

        RESET = false;
        while (!EXIT && !RESET) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        try {
            // Stop the stream
            adc.stopStream();
        }
        catch (RtAudioError &e) {
            e.printMessage();
            if (adc.isStreamOpen()) adc.closeStream();
        }
    }
}
