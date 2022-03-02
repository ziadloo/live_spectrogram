//
// Created by mehran on 2022-02-25.
//

#include "MelLogTransform.h"
#include <cmath>

using namespace std;

MelLogTransform::MelLogTransform():
        QwtTransform()
{
}

//! Destructor
MelLogTransform::~MelLogTransform()
{
}

/*!
   \param value Value to be transformed
   \return log( value )
 */
double MelLogTransform::transform( double value ) const
{
    return 2595.0 * std::log10( 1.0 + value / 700.0 );
}

/*!
   \param value Value to be transformed
   \return exp( value )
 */
double MelLogTransform::invTransform( double value ) const
{
    return 700.0 * (std::pow(10.0, value / 2595.0) - 1.0);
}

/*!
   \param value Value to be bounded
   \return qBound( LogMin, value, LogMax )
 */
double MelLogTransform::bounded( double value ) const
{
    return qBound( MelLogTransform::LogMin, value, MelLogTransform::LogMax);
}

//! \return Clone of the transformation
QwtTransform* MelLogTransform::copy() const
{
    return new MelLogTransform();
}

//! Smallest allowed value for logarithmic scales: 1.0e-150
const double MelLogTransform::LogMin = 0.0;

//! Largest allowed value for logarithmic scales: 1.0e150
const double MelLogTransform::LogMax = 20000.0;
