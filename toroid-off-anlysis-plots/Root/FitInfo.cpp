#include "FitInfo.h"

FitInfo::FitInfo(int nevents, double x0, double sigma_x0, double m, double sigma_m) : m_nevents(nevents),
                                                                                      m_x0(x0),
                                                                                      m_sigma_x0(sigma_x0),
                                                                                      m_m(m),
                                                                                      m_sigma_m(sigma_m){};

std::ostream &operator<<(std::ostream &os, const FitInfo &ft)
{
    os << ft.m_nevents << ";" << ft.m_x0 << ";" << ft.m_sigma_x0 << ";" << ft.m_m << ";" << ft.m_sigma_m;
    return os;
}