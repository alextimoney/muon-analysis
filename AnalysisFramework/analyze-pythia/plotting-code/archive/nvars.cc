// FinalCuts.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

    TFile infile[9] = {"$PWD/histograms/run1/bottomonium.root", "$PWD/histograms/run1/charmonium.root",
                        "$PWD/histograms/run1/bbbar.root", "$PWD/histograms/run1/ccbar.root", 
                        "$PWD/histograms/run1/ttbar-dilep.root", "$PWD/histograms/run1/ttbar-semilep.root",
                        "$PWD/histograms/run1/wbos.root", "$PWD/histograms/run1/zbos.root", "$PWD/histograms/run1/gamma.root"};

  const char *var[2] = {"nJets", "nMuons"};
  const char *outfiles[2] = {"./plots/variables/nJets.png", "./plots/variables/nMuons.png"};
  const char *titles[2] = {"Number of Jets", "Number of Muons"};
  double xmax[2] = {5, 5};
  
  for(int i = 0; i < 2; i++) {
    // Get the histograms
    // ==================
    TH1F *bottomonium = (TH1F*)infile[0].Get(var[i]);
    TH1F *charmonium = (TH1F*)infile[1].Get(var[i]);
    TH1F *bbbar = (TH1F*)infile[2].Get(var[i]);
    TH1F *ccbar = (TH1F*)infile[3].Get(var[i]);
    TH1F *ttbar = (TH1F*)infile[4].Get(var[i]);
    TH1F *wbos = (TH1F*)infile[5].Get(var[i]);
    TH1F *zbos = (TH1F*)infile[6].Get(var[i]);
    TH1F *gamma = (TH1F*)infile[7].Get(var[i]);
    TH1F *sum = new TH1F(titles[i], "n", 50, 0, xmax[i]);
    

    TCanvas *cx = new TCanvas("cx","cx", 800, 600);
    cx->cd();

    gStyle->SetOptStat(0);
    gStyle->SetTitleFont(132, "t");

    sum->Add(bottomonium);
    sum->Add(charmonium);
    sum->Add(bbbar);
    sum->Add(ccbar);
    sum->Add(ttbar);
    sum->Add(wbos);
    sum->Add(zbos);
    sum->Add(gamma);

    auto mg  = new TMultiGraph();

    double x[5];
    double y[5];
    for(int j = 0; j < 5; j++) {
        x[j] = j;
        y[j] = sum->GetBinContent(1+(j*10));
    }

    auto g = new TGraph(5,x,y);
    g->SetLineColor(46);
    g->SetLineWidth(3);
    g->SetMarkerColor(46);
    g->SetMarkerStyle(107);

    for(int j = 0; j < 5; j++) {
        x[j] = j;
        y[j] = bottomonium->GetBinContent(1+(j*10));
    }
    auto g1 = new TGraph(5, x, y);
    g1->SetLineColor(42);
    g1->SetLineWidth(3);
    g1->SetMarkerColor(42);
    g1->SetMarkerStyle(107);
    for(int j = 0; j < 5; j++) {
        x[j] = j;
        y[j] = charmonium->GetBinContent(1+(j*10));
    }
    auto g2 = new TGraph(5, x, y);
    g2->SetLineColor(41);
    g2->SetLineWidth(3);
    g2->SetMarkerColor(41);
    g2->SetMarkerStyle(107);

    for(int j = 0; j < 5; j++) {
        x[j] = j;
        y[j] = bbbar->GetBinContent(1+(j*10));
    }
    auto g3 = new TGraph(5, x, y);
    g3->SetLineColor(30);
    g3->SetLineWidth(3);
    g3->SetMarkerColor(30);
    g3->SetMarkerStyle(107);

    for(int j = 0; j < 5; j++) {
        x[j] = j;
        y[j] = ccbar->GetBinContent(1+(j*10));
    }
    auto g4 = new TGraph(5, x, y);
    g4->SetLineColor(29);
    g4->SetLineWidth(3);
    g4->SetMarkerColor(29);
    g4->SetMarkerStyle(107);

    for(int j = 0; j < 5; j++) {
        x[j] = j;
        y[j] = ttbar->GetBinContent(1+(j*10));
    }
    auto g5 = new TGraph(5, x, y);
    g5->SetLineColor(38);
    g5->SetLineWidth(3);
    g5->SetMarkerColor(38);
    g5->SetMarkerStyle(107);

    for(int j = 0; j < 5; j++) {
        x[j] = j;
        y[j] = wbos->GetBinContent(1+(j*10));
    }
    auto g6 = new TGraph(5, x, y);
    g6->SetLineColor(36);
    g6->SetLineWidth(3);
    g6->SetMarkerColor(36);
    g6->SetMarkerStyle(107);

    for(int j = 0; j < 5; j++) {
        x[j] = j;
        y[j] = zbos->GetBinContent(1+(j*10));
    }
    auto g7 = new TGraph(5, x, y);
    g7->SetLineColor(48);
    g7->SetLineWidth(3);
    g7->SetMarkerColor(48);
    g7->SetMarkerStyle(107);

    for(int j = 0; j < 5; j++) {
        x[j] = j;
        y[j] = gamma->GetBinContent(1+(j*10));
    }
    auto g8 = new TGraph(5, x, y);
    g8->SetLineColor(40);
    g8->SetLineWidth(3);
    g8->SetMarkerColor(40);
    g8->SetMarkerStyle(107);

    mg->Add(g, "ALP");
    mg->Add(g1, "ALP");
    mg->Add(g2, "ALP");
    mg->Add(g3, "ALP");
    mg->Add(g4, "ALP");
    mg->Add(g5, "ALP");
    mg->Add(g6, "ALP");
    mg->Add(g7, "ALP");
    mg->Add(g8, "ALP");

    mg->Draw("A");

    auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
    leg->AddEntry(g, "All Events", "f");
    leg->AddEntry(g1, "Bottomonium","f");
    leg->AddEntry(g2, "Charmonium", "f");
    leg->AddEntry(g3, "bbbar", "f");
    leg->AddEntry(g4, "ccbar", "f");
    leg->AddEntry(g5, "ttbar", "f");
    leg->AddEntry(g6, "wbos", "f");
    leg->AddEntry(g7, "zbos", "f");
    leg->AddEntry(g8, "gamma*", "f");
    leg->SetTextSize(0.035);
    leg->Draw();

    cx->SetLogy();
    cx->Print(outfiles[i]);
    cx->Close();
  }
}