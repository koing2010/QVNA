#include "touchstone.h"
#include "stdio.h"
#include <ctype.h>

#define _USE_MATH_DEFINES
#include "math.h"

using namespace std;
/*
string TouchstoneFormate_s2p(vector<Matrix2cd> data, double startFreqHz, double stepFreqHz) {
    string res;
    res += "# MHz S MA R 50\n";
    saprintf(res,"!   freq        S11              S21              S12              S22       \n");
    for(int i=0;i<(int)data.size();i++) {
        double freqHz = startFreqHz + i*stepFreqHz;
        double freqMHz = freqHz*1e-6;
        Matrix2cd val = data[i];
        double c = 180./M_PI;
        saprintf(res,"%8.3f %8.5f %7.2f %8.5f %7.2f %8.5f %7.2f %8.5f %7.2f\n",
                 freqMHz,
                 abs(val(0,0)), arg(val(0,0))*c,
                 abs(val(1,0)), arg(val(1,0))*c,
                 abs(val(0,1)), arg(val(0,1))*c,
                 abs(val(1,1)), arg(val(1,1))*c);
    }
    return res;
}*/

string TouchstoneFormate_s1p(vector<complex<double> > data, double startFreqHz, double stepFreqHz)
{
    string res;

      res += "# MHz S MA R 50\n";
      res += "!   freq        S11 \n";
    for(int i=0;i<(int)data.size();i++) {
        double freqHz = startFreqHz + i*stepFreqHz;
        double freqMHz = freqHz*1e-6;
        complex<double> val = data[i];
        double c = 180.0/M_PI;
         res = printf("%8.3f %8.5f %7.2f \n",
                 freqMHz,
                 //abs(val(0,0)), arg(val(0,0))*c);
                      val.real(), val.imag());
    }
    return res;
}
