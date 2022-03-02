//
// Created by mehran on 2022-02-06.
//

#include "task.h"

void task::stop() {
    EXIT = true;
    thread_ptr->join();
}

void task::run() {
    thread_ptr = std::make_unique<std::thread>([&]() {
        thread_code();
    });
}

void task::reset() {
    RESET = true;
}
