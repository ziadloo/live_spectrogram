// -----------------------------------------------------------------------------
//  A simple MFCC extractor using C++ STL and C++11
// -----------------------------------------------------------------------------
//
//  Copyright (C) 2016 D S Pavan Kumar
//  dspavankumar [at] gmail [dot] com
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <algorithm>
#include <numeric>
#include <complex>
#include <vector>
#include <map>
#include <math.h>
#include <fstream>
#include <iostream>

typedef std::vector<double> v_d;
typedef std::vector<v_d> m_d;

using namespace std;

class MFCC {

private:
    const double PI = 4*atan(1.0);   // Pi = 3.14...
    int fs;
    size_t numCepstra, numFFT, numFFTBins, numFilters;
    double lowFreq, highFreq;
    m_d fbank, dct;

private:
    // Hertz to Mel conversion
    inline double hz2mel (double f) {
        return 2595*std::log10 (1+f/700);
    }

    // Mel to Hertz conversion
    inline double mel2hz (double m) {
        return 700*(std::pow(10,m/2595)-1);
    }

    // Applying log Mel filterbank (LMFB)
    v_d applyLMFB(v_d spectrum) {
        v_d lmfbCoef;
        lmfbCoef.assign(numFilters,0);

        for (int i=0; i<numFilters; i++) {
            // Multiply the filterbank matrix
            for (int j=0; j<fbank[i].size(); j++)
                lmfbCoef[i] += fbank[i][j] * spectrum[j];
            // Apply Mel-flooring
            if (lmfbCoef[i] < 1.0)
                lmfbCoef[i] = 1.0;
        }

        // Applying log on amplitude
        for (int i=0; i<numFilters; i++)
            lmfbCoef[i] = std::log10 (lmfbCoef[i]);

        return lmfbCoef;
    }

    // Computing discrete cosine transform
    v_d applyDct(v_d lmfbCoef) {
        v_d mfcc;
        mfcc.assign(numCepstra+1,0);
        for (int i=0; i<=numCepstra; i++) {
            for (int j=0; j<numFilters; j++)
                mfcc[i] += dct[i][j] * lmfbCoef[j];
        }
        return mfcc;
    }

    // Initialisation routines
    // Pre-computing Hamming window and dct matrix
    void initHamDct(void) {
        v_d v1(numCepstra+1,0), v2(numFilters,0);
        for (int i=0; i <= numCepstra; i++)
            v1[i] = i;
        for (int i=0; i < numFilters; i++)
            v2[i] = i + 0.5;

        dct.reserve (numFilters*(numCepstra+1));
        double c = sqrt(2.0/numFilters);
        for (int i=0; i<=numCepstra; i++) {
            v_d dtemp;
            for (int j=0; j<numFilters; j++)
                dtemp.push_back (c * cos(PI / numFilters * v1[i] * v2[j]));
            dct.push_back(dtemp);
        }
    }

    // Precompute filterbank
    void initFilterbank () {
        // Convert low and high frequencies to Mel scale
        double lowFreqMel = hz2mel(lowFreq);
        double highFreqMel = hz2mel (highFreq);

        // Calculate filter centre-frequencies
        v_d filterCentreFreq;
        filterCentreFreq.reserve (numFilters+2);
        for (int i=0; i<numFilters+2; i++)
            filterCentreFreq.push_back (mel2hz(lowFreqMel + (highFreqMel-lowFreqMel)/(numFilters+1)*i));

        // Calculate FFT bin frequencies
        v_d fftBinFreq;
        fftBinFreq.reserve(numFFTBins);
        for (int i=0; i<numFFTBins; i++)
            fftBinFreq.push_back (fs/2.0/(numFFTBins-1)*i);

        // Filterbank: Allocate memory
        fbank.reserve (numFilters*numFFTBins);

        // Populate the fbank matrix
        for (int filt=1; filt<=numFilters; filt++) {
            v_d ftemp;
            for (int bin=0; bin<numFFTBins; bin++) {
                double weight;
                if (fftBinFreq[bin] < filterCentreFreq[filt-1])
                    weight = 0;
                else if (fftBinFreq[bin] <= filterCentreFreq[filt])
                    weight = (fftBinFreq[bin] - filterCentreFreq[filt-1]) / (filterCentreFreq[filt] - filterCentreFreq[filt-1]);
                else if (fftBinFreq[bin] <= filterCentreFreq[filt+1])
                    weight = (filterCentreFreq[filt+1] - fftBinFreq[bin]) / (filterCentreFreq[filt+1] - filterCentreFreq[filt]);
                else
                    weight = 0;
                ftemp.push_back (weight);
            }
            fbank.push_back(ftemp);
        }
    }

public:
    // MFCC class constructor
    MFCC(int sampFreq=16000, double lf=50, double hf=6500, int nCep=12, int numFilt=40) {
        fs          = sampFreq;             // Sampling frequency
        numCepstra  = nCep;                 // Number of cepstra
        numFilters  = numFilt;              // Number of Mel warped filters
        lowFreq     = lf;                   // Filterbank low frequency cutoff in Hertz
        highFreq    = hf;                   // Filterbank high frequency cutoff in Hertz
        numFFT      = fs<=20000?512:2048;   // FFT size

        numFFTBins = numFFT/2 + 1;

        initFilterbank();
        initHamDct();
    }

    // Process each frame and extract MFCC
    v_d processFrame(v_d spectrum) {
        auto lmfbCoef = applyLMFB(spectrum);
        auto dct = applyDct(lmfbCoef);
        v_d mfcc;
        mfcc.assign(dct.begin()+1, dct.end());
        return mfcc;
    }
};
