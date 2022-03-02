#include "components/MainWindow.h"

#include <QApplication>
#include "utility.h"
#include "pc/producer.h"
#include "pc/consumer.h"

using namespace moodycamel;
using namespace std;

int main(int argc, char *argv[]) {
    qRegisterMetaType<vector_double>("vector_double");

    producer* producer_pointer = new producer(_SAMPLE_RATE_);
    consumer* consumer_pointer = new consumer(producer_pointer, _SAMPLE_RATE_, _NUM_POINTS_);

    consumer_pointer->run();
    producer_pointer->run();

    QApplication app(argc, argv);

    MainWindow window;
    window.resize(1200, 800);
    window.show();

    QObject::connect(consumer_pointer, SIGNAL(onNewSpectrum(vector_double)), &window, SLOT(onNewSpectrum(vector_double)));
    QObject::connect(consumer_pointer, SIGNAL(onNewDecibel(vector_double)), &window, SLOT(onNewDecibel(vector_double)));

    int r = app.exec();

    consumer_pointer->stop();
    producer_pointer->stop();

    delete consumer_pointer;
    delete producer_pointer;

    return r;
}
