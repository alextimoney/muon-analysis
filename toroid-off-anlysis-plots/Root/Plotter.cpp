#include "Plotter.h"
#include <TROOT.h>
#include <TStyle.h>

#include <TLatex.h>

TStyle *AtlasStyle()
{
    TStyle *atlasStyle = new TStyle("ATLAS", "Atlas style");

    // use plain black on white colors
    Int_t icol = 0; // WHITE
    atlasStyle->SetFrameBorderMode(icol);
    atlasStyle->SetFrameFillColor(icol);
    atlasStyle->SetCanvasBorderMode(icol);
    atlasStyle->SetCanvasColor(icol);
    atlasStyle->SetPadBorderMode(icol);
    atlasStyle->SetPadColor(icol);
    atlasStyle->SetStatColor(icol);
    // atlasStyle->SetFillColor(icol); // don't use: white fill color for *all* objects

    // set the paper & margin sizes
    atlasStyle->SetPaperSize(20, 26);

    // set margin sizes
    atlasStyle->SetPadTopMargin(0.05);
    atlasStyle->SetPadRightMargin(0.2);
    atlasStyle->SetPadBottomMargin(0.16);
    atlasStyle->SetPadLeftMargin(0.16);

    // set title offsets (for axis label)
    atlasStyle->SetTitleXOffset(1.4);
    atlasStyle->SetTitleYOffset(2.0);

    // use large fonts
    // Int_t font=72; // Helvetica italics
    //   Int_t font=42; // Helvetica
    //   Double_t tsize=0.05;
    // --- Michele
    Int_t font = 43;
    //   Double_t tsize=24;
    Double_t tsize = 21;
    // ---
    atlasStyle->SetTextFont(font);

    atlasStyle->SetTextSize(tsize);
    atlasStyle->SetLabelFont(font, "x");
    atlasStyle->SetTitleFont(font, "x");
    atlasStyle->SetLabelFont(font, "y");
    atlasStyle->SetTitleFont(font, "y");
    atlasStyle->SetLabelFont(font, "z");
    atlasStyle->SetTitleFont(font, "z");

    atlasStyle->SetLabelSize(tsize, "x");
    atlasStyle->SetTitleSize(tsize, "x");
    atlasStyle->SetLabelSize(tsize, "y");
    atlasStyle->SetTitleSize(tsize, "y");
    atlasStyle->SetLabelSize(tsize, "z");
    atlasStyle->SetTitleSize(tsize, "z");

    // --- Michele
    atlasStyle->SetLegendFont(font);
    // ---

    // use bold lines and markers
    atlasStyle->SetMarkerStyle(20);
    atlasStyle->SetMarkerSize(1.2);
    atlasStyle->SetHistLineWidth(2.);
    atlasStyle->SetLineStyleString(2, "[12 12]"); // postscript dashes

    // get rid of X error bars
    // atlasStyle->SetErrorX(0.001);
    // get rid of error bar caps
    atlasStyle->SetEndErrorSize(0.);

    // do not display any of the standard histogram decorations
    atlasStyle->SetOptTitle(0);
    // atlasStyle->SetOptStat(1111);
    atlasStyle->SetOptStat(0);
    // atlasStyle->SetOptFit(1111);
    atlasStyle->SetOptFit(0);

    // put tick marks on top and RHS of plots
    atlasStyle->SetPadTickX(1);
    atlasStyle->SetPadTickY(1);

    return atlasStyle;
}

void SetAtlasStyle()
{
    static TStyle *atlasStyle = 0;
    std::cout << "\nApplying ATLAS style settings...\n"
              << std::endl;
    if (atlasStyle == 0)
        atlasStyle = AtlasStyle();
    gROOT->SetStyle("ATLAS");
    gROOT->ForceStyle();
    gStyle->SetErrorX(0.5);
}

Plotter::Plotter(int canvas_x = 1000, int canvas_y = 850) : m_canvas_x(canvas_x), m_canvas_y(canvas_y)
{
    SetAtlasStyle();
};

FitInfo Plotter::CreateSagPlot(std::string name, TH1 *thehist, std::string outputdirectory, int canvas_size_x, int canvas_size_y)
{
    // Create canvas
    std::string canvasname = name + "_canv";
    TCanvas *cx = new TCanvas(canvasname.c_str(), name.c_str(), canvas_size_x, canvas_size_y);
    gStyle->SetOptStat(0);
    cx->cd();

    float max_y = thehist->GetMaximum();

    // Fitting
    TF1 *f1 = new TF1("f1", "[0]*TMath::CauchyDist(x,[1],[2])+[3]", -30, 30);
    f1->SetParameters(10 * thehist->GetMaximum(), 0, 1, 0);
    f1->SetParNames("Normalization", "b", "m", "Constant1");
    thehist->Fit(f1, "0");

    if (f1->GetMaximum() > max_y)
    {
        max_y = f1->GetMaximum();
        thehist->SetMaximum(1.4 * max_y);
    };

    thehist->Draw("HIST");
    thehist->GetXaxis()->SetTitle("Sagitta (mm)");
    thehist->GetYaxis()->SetTitle("Entries");
    f1->Draw("SAME");

    // Annotate canvas with fit info
    double x0 = f1->GetParameter(1);
    double sigma_x0 = f1->GetParError(1);
    double m = f1->GetParameter(2);
    double sigma_m = f1->GetParError(2);
    std::string text;
    text = "x0: " + std::to_string(x0);
    TText *annotation_x0 = new TText(.6, .88, text.c_str());
    annotation_x0->SetNDC(kTRUE);
    annotation_x0->SetTextColor(kBlack);
    annotation_x0->SetTextFont(43);
    annotation_x0->SetTextSize(20);
    annotation_x0->SetTextAlign(10);
    annotation_x0->Draw("SAME");
    text = "HWHM: " + std::to_string(m);
    TText *annotation_m = new TText(.6, .84, text.c_str());
    annotation_m->SetNDC(kTRUE);
    annotation_m->SetTextColor(kBlack);
    annotation_m->SetTextFont(43);
    annotation_m->SetTextSize(20);
    annotation_m->SetTextAlign(10);
    annotation_m->Draw("SAME");

    // ATLASLabelNew(0.2, 0.88, "Internal", kBlack, gStyle->GetTextSize(), 0.09);
    TLatex n;
    n.SetNDC();
    n.SetTextFont(43);
    n.SetTextColor(kBlack);
    n.SetTextSize(gStyle->GetTextSize());
    std::string labelname = ReplaceAll(name, "_", " ");
    n.DrawLatex(0.2, 0.84, labelname.c_str());

    // Write to file
    std::string outputfile = outputdirectory + name;
    std::vector<std::string> extensions = {".pdf", ".C"};

    for (auto extension : extensions)
    {
        std::string savefile = outputfile + extension;
        cx->SaveAs(savefile.c_str());
    }
    FitInfo _fit_info(thehist->GetEntries(), x0, sigma_x0, m, sigma_m);
    delete cx;
    delete f1;
    return _fit_info;
};

void Plotter::Create1DPlot(std::string name, std::string xaxis_title, std::string yaxis_title, TH1 *thehist, std::string outputdirectory, int canvas_size_x, int canvas_size_y)
{
    std::cout << "making canvas" << std::endl;
    // std::cout << m_canvas_x << std::endl;
    std::cout << name << std::endl;
    std::string canvasname = name + "_canv";

    TCanvas *cx = new TCanvas(canvasname.c_str(), name.c_str(), canvas_size_x, canvas_size_y);
    // gStyle->SetOptStat(0);
    cx->cd();
    std::cout << "made canvas" << std::endl;

    thehist->SetMaximum(1.4 * thehist->GetMaximum());

    thehist->Draw("p");
    std::cout << "drew hist" << std::endl;

    thehist->GetXaxis()->SetTitle(xaxis_title.c_str());
    thehist->GetYaxis()->SetTitle(yaxis_title.c_str());
    std::cout << "decorated hist" << std::endl;

    // ATLASLabelNew(0.2, 0.88, "Internal", kBlack, gStyle->GetTextSize(), 0.09);

    TLatex n;
    n.SetNDC();
    n.SetTextFont(43);
    n.SetTextColor(kBlack);
    n.SetTextSize(gStyle->GetTextSize());
    std::string labelname = ReplaceAll(name, "_", " ");
    n.DrawLatex(0.2, 0.84, labelname.c_str());

    std::string outputfile = outputdirectory + name;
    std::vector<std::string> extensions = {".pdf", ".C"};

    for (auto extension : extensions)
    {
        std::string savefile = outputfile + extension;
        cx->SaveAs(savefile.c_str());
    }
    delete cx;
};

void Plotter::Create1DPlotMomenta(std::vector<std::string> names, std::vector<TH1 *> thehists, std::vector<std::string> colors, std::string xaxis_title, std::string yaxis_title, std::string outputdirectory, std::string filename, int canvas_size_x, int canvas_size_y, bool normalize)
{
    std::cout << "making canvas" << std::endl;
    // std::cout << m_canvas_x << std::endl;
    std::string canvasname = "canvas_multiple_momenta";

    TCanvas *cx = new TCanvas(canvasname.c_str(), canvasname.c_str(), canvas_size_x, canvas_size_y);
    // gStyle->SetOptStat(0);
    cx->cd();
    bool first = true;

    auto legend = new TLegend(0.58, 0.75, 0.75, 0.9);
    legend->SetTextFont(43);
	legend->SetTextSize(20);
	legend->SetFillColor(0);
	legend->SetLineColor(0);
	legend->SetBorderSize(0);
    for(int i=0; i<names.size(); i++){
        std::string histname = "hist_"+i;
        TH1 *thehist = (TH1*)thehists.at(i)->Clone(histname.c_str());
        std::string name = names.at(i);
        std::string color = colors.at(i);
        if(normalize){
            thehist->Scale(1./thehist->Integral());
            thehist->SetMaximum(0.25);

        }
        else{
            thehist->SetMaximum(1.4 * thehist->GetMaximum());
        }
        

        thehist->SetLineColor(TColor::GetColor(color.c_str()));

        if(first){
            thehist->Draw("HIST");
        }
        else{
            thehist->Draw("HISTSAME");
    
        }
        std::cout << "drew hist" << std::endl;

        thehist->GetXaxis()->SetTitle(xaxis_title.c_str());
        thehist->GetYaxis()->SetTitle(yaxis_title.c_str());

        legend->AddEntry(thehist, name.c_str(), "l");
        std::cout << "decorated hist" << std::endl;
        first=false;

    // ATLASLabelNew(0.2, 0.88, "Internal", kBlack, gStyle->GetTextSize(), 0.09);

    }
    
    TLatex n;
    n.SetNDC();
    n.SetTextFont(43);
    n.SetTextColor(kBlack);
    n.SetTextSize(gStyle->GetTextSize());
    std::string labelname = ""; //ReplaceAll(name, "_", " ");
    n.DrawLatex(0.2, 0.84, labelname.c_str());

    legend->Draw();


    std::string outputfile = outputdirectory + filename;
    std::vector<std::string> extensions = {".pdf", ".C"};

    for (auto extension : extensions)
    {
        std::string savefile = outputfile + extension;
        cx->SaveAs(savefile.c_str());
    }
    delete cx;
};

// template<typename T> // for the member template
void Plotter::Create2DPlot(std::string name, std::string xaxis_title, std::string yaxis_title, TH2 *thehist, std::string outputdirectory, int canvas_size_x, int canvas_size_y)
{
    std::cout << "making canvas" << std::endl;
    // std::cout << m_canvas_x << std::endl;
    std::cout << name << std::endl;
    std::string canvasname = name + "_canv";

    TCanvas *cx = new TCanvas(canvasname.c_str(), name.c_str(), canvas_size_x, canvas_size_y);
    gStyle->SetOptStat(0);
    cx->cd();
    std::cout << "made canvas" << std::endl;

    thehist->Draw("COLZ");
    std::cout << "drew hist" << std::endl;

    thehist->GetXaxis()->SetTitle(xaxis_title.c_str());
    thehist->GetYaxis()->SetTitle(yaxis_title.c_str());
    thehist->GetYaxis()->SetTitle(yaxis_title.c_str());
    std::cout << "decorated hist" << std::endl;

    std::string outputfile = outputdirectory + name;
    std::vector<std::string> extensions = {".pdf", ".C"};

    for (auto extension : extensions)
    {
        std::string savefile = outputfile + extension;
        cx->SaveAs(savefile.c_str());
    }
    delete cx;
};

void Plotter::CreateMuonSelectionPlot(std::string name, TH1 *hist1, TH1 *hist2, std::string outputdirectory, int canvas_size_x, int canvas_size_y)
{
    std::cout << "making canvas" << std::endl;
    // std::cout << m_canvas_x << std::endl;
    std::cout << name << std::endl;
    std::string canvasname = name + "_canv";

    TCanvas *cx = new TCanvas(canvasname.c_str(), name.c_str(), canvas_size_x, canvas_size_y);
    gStyle->SetOptStat(0);
    cx->cd();
    std::cout << "made canvas" << std::endl;

    hist1->Draw("HIST");
    hist2->Draw("HIST SAME");
    std::cout << "drew hist" << std::endl;

    hist1->GetXaxis()->SetTitle("muon momentum (GeV)");
    hist1->SetLineColor(kBlack);
    hist2->SetLineColor(kBlue);
    // hist1->GetYaxis()->SetTitle("");
    std::cout << "decorated hist" << std::endl;

    auto legend = new TLegend(0.64, 0.7, 0.85, 0.8);
    legend->AddEntry(hist1, "No cuts");
    legend->AddEntry(hist2, "Segment quality cuts");
    legend->Draw();

    std::string outputfile = outputdirectory + name;
    std::vector<std::string> extensions = {".pdf", ".C"};

    for (auto extension : extensions)
    {
        std::string savefile = outputfile + extension;
        cx->SaveAs(savefile.c_str());
    }
    delete cx;
};

void Plotter::ATLASLabel(Double_t x, Double_t y, const char *text, Color_t color)
{
    TLatex l; // l.SetTextAlign(12); l.SetTextSize(tsize);
    l.SetNDC();
    //   l.SetTextFont(72);
    l.SetTextFont(73);
    l.SetTextColor(color);

    double delx = 0.115 * 696 * gPad->GetWh() / (472 * gPad->GetWw());

    l.DrawLatex(x, y, "ATLAS");
    if (text)
    {
        TLatex p;
        p.SetNDC();
        //     p.SetTextFont(42);
        p.SetTextFont(43);
        p.SetTextColor(color);
        p.DrawLatex(x + delx, y, text);
        //    p.DrawLatex(x,y,"#sqrt{s}=900GeV");
    }
}

void Plotter::ATLASLabelNew(Double_t x, Double_t y, const char *text, Color_t color, float text_size, float delx)
{

    TLatex l;
    l.SetNDC();
    l.SetTextFont(73);
    l.SetTextColor(color);
    l.SetTextSize(text_size);

    l.DrawLatex(x, y, "ATLAS");
    if (text)
    {
        TLatex p;
        p.SetNDC();
        p.SetTextFont(43);
        p.SetTextColor(color);
        p.SetTextSize(text_size);
        p.DrawLatex(x + delx, y, text);
    }
    return;
}

std::string Plotter::ReplaceAll(std::string str, const std::string &from, const std::string &to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}