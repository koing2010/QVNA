#ifndef TOUCHSTONE_H
#define TOUCHSTONE_H
#include <string>
#include <vector>
#include <math.h>
#include <complex>
#include <iostream>
using namespace std;


//string TouchstoneFormate_s2p(vector<Matrix2cd> data, double startFreqHz, double stepFreqHz);
string TouchstoneFormate_s1p(vector< complex<double> > data, double startFreqHz, double stepFreqHz);

#endif // TOUCHSTONE_H
