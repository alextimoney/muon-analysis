
#ifndef FITINFO_H
#define FITINFO_H

#include "vector"
#include "string"

#include <iostream>

class FitInfo
{
public:
    FitInfo(int, double, double, double, double);
    ~FitInfo() = default;

    int m_nevents;
    double m_x0;
    double m_sigma_x0;
    double m_m;
    double m_sigma_m;

    friend std::ostream &operator<<(std::ostream &os, const FitInfo &dt);
};

#endif