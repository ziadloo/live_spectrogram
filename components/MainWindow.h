//
// Created by mehran on 2022-02-24.
//

#ifndef LIVE_SPECTROGRAM_MAINWINDOW_H
#define LIVE_SPECTROGRAM_MAINWINDOW_H

#include <QTimer>
#include "SpectrogramPlot.hpp"
#include "MelSpectrogramPlot.hpp"
#include "MfccPlot.hpp"
#include "../lib/mfcc.hpp"

class MainWindow : public QWidget {
Q_OBJECT
    SpectrogramPlot* plot1;
    MelSpectrogramPlot* plot2;
    MfccPlot* plot3;
    MFCC mfcc;
public:
    MainWindow(QWidget * = NULL);

public slots:
    void onNewSpectrum(vector_double);
    void onNewDecibel(vector_double);
};


#endif //LIVE_SPECTROGRAM_MAINWINDOW_H
