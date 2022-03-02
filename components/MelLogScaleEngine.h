//
// Created by mehran on 2022-02-25.
//

#ifndef LIVE_SPECTROGRAM_MELLOGSCALEENGINE_H
#define LIVE_SPECTROGRAM_MELLOGSCALEENGINE_H


#include <QwtScaleEngine>

class MelLogScaleEngine : public QwtScaleEngine
{
public:
explicit MelLogScaleEngine( unsigned int base = 10 );
virtual ~MelLogScaleEngine();

virtual void autoScale( int maxNumSteps,
                        double& x1, double& x2, double& stepSize ) const QWT_OVERRIDE;

virtual QwtScaleDiv divideScale( double x1, double x2,
                                 int maxMajorSteps, int maxMinorSteps,
                                 double stepSize = 0.0 ) const QWT_OVERRIDE;

protected:
QwtInterval align( const QwtInterval&, double stepSize ) const;

void buildTicks(
        const QwtInterval&, double stepSize, int maxMinorSteps,
        QList< double > ticks[QwtScaleDiv::NTickTypes] ) const;

QList< double > buildMajorTicks(
        const QwtInterval& interval, double stepSize ) const;

void buildMinorTicks( const QList< double >& majorTicks,
                      int maxMinorSteps, double stepSize,
                      QList< double >& minorTicks, QList< double >& mediumTicks ) const;
};


#endif //LIVE_SPECTROGRAM_MELLOGSCALEENGINE_H
