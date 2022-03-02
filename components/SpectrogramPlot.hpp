#pragma once

#include <QwtPlot>
#include "utility.h"
#include <QwtInterval>
#include <cmath>
#include <vector>
#include <cstring>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <QwtColorMap>
#include <QwtPlotSpectrogram>
#include <QwtScaleWidget>
#include <QwtPlotZoomer>
#include <QwtPlotPanner>
#include <QwtPlotLayout>

#include <QPen>
#include <QElapsedTimer>
#include <QwtLogScaleEngine>

class SpectrogramData : public QwtRasterData {
public:
    SpectrogramData(int rows, int columns, int bufferIndex, double *buffer) :
            rows(rows), columns(columns), bufferIndex(bufferIndex), buffer(buffer) {

        setAttribute(QwtRasterData::WithoutGaps, true);

        m_intervals[Qt::XAxis] = QwtInterval(-20.0, 0.0);
        m_intervals[Qt::YAxis] = QwtInterval(0.0, 20000.0);
        m_intervals[Qt::ZAxis] = QwtInterval(-100.0, 100.0);
    }

    virtual QwtInterval interval(Qt::Axis axis) const QWT_OVERRIDE {
        if (0 <= axis && axis <= 2)
            return m_intervals[axis];

        return QwtInterval();
    }

    virtual double value(double x, double y) const QWT_OVERRIDE {
        int row = (static_cast<int>(x / 20.0 * (rows - 1)) + ((bufferIndex - 1 + rows) % rows) + rows) % rows;
        int column = static_cast<int>(y / m_intervals[Qt::YAxis].maxValue() * (columns - 1));

        return buffer[row * columns + column];
    }

private:
    QwtInterval m_intervals[3];
    int rows, columns;
    double *buffer;
    int bufferIndex;
};

class SpectrogramLinearColorMap : public QwtLinearColorMap {
public:
    SpectrogramLinearColorMap()
            : QwtLinearColorMap(Qt::black, Qt::white) {
        setFormat(QwtColorMap::RGB);

        addColorStop(0.25, Qt::blue);
        addColorStop(0.50, Qt::red);
        addColorStop(0.75, Qt::yellow);
    }
};

class SpectrogramPlot : public QwtPlot {
Q_OBJECT

public:
    SpectrogramPlot(QWidget* parent = NULL): QwtPlot(parent) {
        setContentsMargins( 0, 0, 0, 0);

        m_spectrogram = new QwtPlotSpectrogram();
        m_spectrogram->setRenderThreadCount(0); // use system specific thread count
        m_spectrogram->setCachePolicy(QwtPlotRasterItem::PaintCache);

        rows = static_cast<int>(20 * static_cast<double>(_SAMPLE_RATE_) / static_cast<double>(_WINDOW_HOP_));
        columns = static_cast<int>(_NUM_POINTS_ / 2);
        buffer = new double[rows * columns];

        spectrogramData = new SpectrogramData(rows, columns, bufferIndex, buffer);
        m_spectrogram->setData(spectrogramData);
        m_spectrogram->attach(this);

        const QwtInterval zInterval = m_spectrogram->data()->interval(Qt::ZAxis);
        for (int i=0; i<rows * columns; i++) {
            buffer[i] = zInterval.minValue();
        }

        // A color bar on the right axis
        QwtScaleWidget *rightAxis = axisWidget(QwtAxis::YRight);
        rightAxis->setTitle("Spectrogram (dB)");
        rightAxis->setColorBarEnabled(true);

        setAxisScale(QwtAxis::YRight, zInterval.minValue(), zInterval.maxValue());
        setAxisVisible(QwtAxis::YRight);

        plotLayout()->setAlignCanvasToScales(true);

        {
            QwtScaleWidget *axis = axisWidget(QwtAxis::YRight);
            const QwtInterval zInterval = m_spectrogram->data()->interval(Qt::ZAxis);

            m_spectrogram->setColorMap(new SpectrogramLinearColorMap());
            axis->setColorMap(zInterval, new SpectrogramLinearColorMap());
            m_spectrogram->setAlpha(255);

            replot();
        }
    }
    virtual ~SpectrogramPlot() {
        delete spectrogramData;
    }
    void setData(vector_double data) {
        std::memcpy(&buffer[columns * bufferIndex], &data[0], sizeof (data[0]) * data.size());
        bufferIndex = (bufferIndex + 1) % rows;

        spectrogramData = new SpectrogramData(rows, columns, bufferIndex, buffer);
        m_spectrogram->setData(spectrogramData);

        replot();
    }

private:
    QwtPlotSpectrogram *m_spectrogram;
    SpectrogramData* spectrogramData;
    int rows, columns;
    double* buffer;
    int bufferIndex = 0;
};
