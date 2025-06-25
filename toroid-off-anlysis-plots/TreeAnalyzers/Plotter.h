#ifndef PLOTTER_H
#define PLOTTER_H

#include "vector"
#include "string"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <math.h>
#include <TVector3.h>
#include <TF1.h>
#include <TLegend.h>
#include <TText.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "string"

#include "iostream"
#include <iostream>

#include "FitInfo.h"

#include <fstream>

class Plotter
{
public:
    Plotter(int, int);
    ~Plotter() = default;

    FitInfo CreateSagPlot(std::string name, TH1 *thehist, std::string outputdirectory, int canvas_size_x = 1000, int canvas_size_y = 800);
    void Create1DPlot(std::string name, std::string xaxis_title, std::string yaxis_title, TH1 *thehist, std::string outputdirectory, int canvas_size_x = 1000, int canvas_size_y = 800);
    void Create2DPlot(std::string name, std::string xaxis_title, std::string yaxis_title, TH2 *thehist, std::string outputdirectory, int canvas_size_x = 1000, int canvas_size_y = 800);
    void CreateMuonSelectionPlot(std::string name, TH1 *hist1, TH1 *hist2, std::string outputdirectory, int canvas_size_x = 1000, int canvas_size_y = 800);
    void Create1DPlotMomenta(std::vector<std::string> name,  std::vector<TH1 *> thehists, std::vector<std::string> colors, std::string xaxis_title, std::string yaxis_title, std::string outputdirectory,  std::string filename, int canvas_size_x = 1000, int canvas_size_y = 800, bool normalize=false);


    int GetCanvasSizeX() { return m_canvas_x; };
    int GetCanvasSizeY() { return m_canvas_y; };

private:
    int m_canvas_x;
    int m_canvas_y;

    void ATLASLabel(Double_t x, Double_t y, const char *text = NULL, Color_t color = 1);
    void ATLASLabelNew(Double_t x, Double_t y, const char *text = NULL, Color_t color = 1, float text_size = 0, float delx = 0.16);
    std::string ReplaceAll(std::string str, const std::string &from, const std::string &to);

    // std::unique_ptr<TCanvas> cx;
};

#endif