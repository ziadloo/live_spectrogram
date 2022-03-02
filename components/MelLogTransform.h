//
// Created by mehran on 2022-02-25.
//

#ifndef LIVE_SPECTROGRAM_MELLOGTRANSFORM_H
#define LIVE_SPECTROGRAM_MELLOGTRANSFORM_H


#include <QwtTransform>

class MelLogTransform : public QwtTransform
{
public:
    MelLogTransform();
    virtual ~MelLogTransform();

    virtual double transform( double value ) const QWT_OVERRIDE;
    virtual double invTransform( double value ) const QWT_OVERRIDE;

    virtual double bounded( double value ) const QWT_OVERRIDE;

    virtual QwtTransform* copy() const QWT_OVERRIDE;

    static const double LogMin;
    static const double LogMax;
};


#endif //LIVE_SPECTROGRAM_MELLOGTRANSFORM_H
