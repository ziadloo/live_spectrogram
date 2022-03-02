//
// Created by mehran on 2022-02-24.
//

#include <QVBoxLayout>
#include "MainWindow.h"
#include "../utility.h"

MainWindow::MainWindow(QWidget *parent)
        : QWidget(parent), mfcc(_SAMPLE_RATE_) {
    setWindowTitle("Live Spectrogram");

    QSizePolicy spDouble(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spDouble.setVerticalStretch(2);

    QSizePolicy spSingle(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spSingle.setVerticalStretch(1);

    plot1 = new SpectrogramPlot();
    plot1->setSizePolicy(spDouble);

    plot2 = new MelSpectrogramPlot();
    plot2->setSizePolicy(spDouble);

    plot3 = new MfccPlot();
    plot3->setSizePolicy(spSingle);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(plot1);
    layout->addWidget(plot2);
    layout->addWidget(plot3);
}

void MainWindow::onNewSpectrum(vector_double spectrum) {
    auto cc = mfcc.processFrame(spectrum);
    plot3->setData(cc);
}

void MainWindow::onNewDecibel(vector_double decibels) {
    plot1->setData(decibels);
    plot2->setData(decibels);
}

#include "moc_MainWindow.cpp"
