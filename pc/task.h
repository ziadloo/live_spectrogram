//
// Created by mehran on 2022-02-06.
//

#ifndef ARECORD_TASK_H
#define ARECORD_TASK_H

#include <QObject>

#include <utility>
#include <vector>
#include <thread>
#include "../utility.h"
#include "lib/queue/readerwriterqueue.h"

using std::vector;
using namespace moodycamel;

class task: public QObject {
    Q_OBJECT
public:
    task(std::shared_ptr<BlockingReaderWriterQueue<vector<format>>> queue, int sample_rate) :
        queue(std::move(queue)), SAMPLE_RATE(sample_rate) {}
    virtual void run();
    virtual void stop();
    virtual void reset();

protected:
    virtual void thread_code() = 0;
    bool EXIT = false;
    bool RESET = false;
    int SAMPLE_RATE;
    std::shared_ptr<BlockingReaderWriterQueue<vector<format>>> queue;

private:
    std::unique_ptr<std::thread> thread_ptr;
};


#endif //ARECORD_TASK_H
