//
// Created by mehran on 2022-02-06.
//

#ifndef ARECORD_PRODUCER_H
#define ARECORD_PRODUCER_H

#include <vector>
#include "../utility.h"
#include "task.h"
#include <RtAudio.h>

using std::vector;

class producer: public task {
public:
    producer(int sample_rate);
    friend int record( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                       double streamTime, RtAudioStreamStatus status, void *userData );
    std::shared_ptr<BlockingReaderWriterQueue<vector<format>>> get_queue() { return queue; }

protected:
    void thread_code() override;

private:
};


#endif //ARECORD_PRODUCER_H
