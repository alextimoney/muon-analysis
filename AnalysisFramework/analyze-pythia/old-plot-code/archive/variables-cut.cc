// FinalCuts.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile[20] = {"$PWD/histograms/run1/ttbar-dilep.root", "$PWD/histograms/run1/ttbar-semilep.root",
                      "$PWD/histograms/run1/wbos.root", "$PWD/histograms/run1/zbos.root", "$PWD/histograms/run1/gamma.root", 
                      "$PWD/histograms/pTmin/bottom2.root", "$PWD/histograms/pTmin/bottom40.root", "$PWD/histograms/pTmin/bottom60.root",
                      "$PWD/histograms/pTmin/charm2.root", "$PWD/histograms/pTmin/charm20.root", "$PWD/histograms/pTmin/charm40.root", "$PWD/histograms/pTmin/charm60.root", 
                      "$PWD/histograms/pTmin/bb2.root", "$PWD/histograms/pTmin/bb40.root", "$PWD/histograms/pTmin/bb60.root", "$PWD/histograms/pTmin/bb120.root", 
                      "$PWD/histograms/pTmin/cc2.root", "$PWD/histograms/pTmin/cc40.root", "$PWD/histograms/pTmin/cc60.root", "$PWD/histograms/pTmin/cc120.root"};

  const char *var[8] = {"JetPt_MetCut", "JetEta_MetCut", "JetMuonPhi_MetCut", "MetJetPhi_MetCut", "MetMuonPhi_MetCut", 
                        "MetJetPt_MetCut", "MuonIsolation_MetCut", "JetMuonR_MetCut"};
  const char *outfiles[8] = {"./plots/variables/metcut/jetPt.png", "./plots/variables/metcut/JetEta.png", "./plots/variables/metcut/JetMuonPhi.png", 
                              "./plots/variables/metcut/MetJetPhi.png", "./plots/variables/metcut/MetMuonPhi.png", 
                              "./plots/variables/metcut/MetJetPt.png", "./plots/variables/metcut/MuIso.png", "./plots/variables/metcut/JetMuonR.png"};
  const char *titles[8] = {"Jet pT w 30 GeV Met cut", "Jet Eta w 30 GeV Met cut", "Phi between Jet and Muon w 30 GeV Met cut", "Phi between Jet and Met w 30 GeV Met cut", 
                            "Phi between Met and Muon w 30 GeV Met cut", "Pt of Sum of Met and Jet w 30 GeV Met cut", "Muon Isolation w 30 GeV Met cut", "Delta R between Jet and Muon w 30 GeV Met cut"};
  const char *xlab[8] = {"Jet pT [GeV]", "Jet Eta", "Angle btwn Jet and Muon", "Angle btwn Met and Jet", "Angle btwn Met and Muon", "Sum of Met and Jet pT", "Isolation pT", "delta R"};
  const char *plus[5] = {"tt", "bot", "charm", "bb", "cc"};
  double xmax[8] = {160, 2.5, M_PI, M_PI, M_PI, 180, 200, M_PI};
  
  for(int i = 0; i < 8; i++) {
    // Get the histograms
    // ==================
    TH1F *sum = new TH1F(titles[i], "pT", 60, 0, xmax[i]);
    TH1F *ttbar = new TH1F(plus[0], "pT", 60, 0, xmax[i]);
    TH1F *bottomonium = new TH1F(plus[1], "pT", 60, 0, xmax[i]);
    TH1F *charmonium = new TH1F(plus[2], "pT", 60, 0, xmax[i]);
    TH1F *bbbar = new TH1F(plus[3], "pT", 60, 0, xmax[i]);
    TH1F *ccbar = new TH1F(plus[4], "pT", 60, 0, xmax[i]);
    // Get the histograms
    // ==================
    TH1F *ttbar_di = (TH1F*)infile[0].Get(var[i]);
    TH1F *ttbar_semi = (TH1F*)infile[1].Get(var[i]);
    TH1F *wbos = (TH1F*)infile[2].Get(var[i]);
    TH1F *zbos = (TH1F*)infile[3].Get(var[i]);
    TH1F *gamma = (TH1F*)infile[4].Get(var[i]);
    TH1F *bottom2 = (TH1F*)infile[5].Get(var[i]);
    TH1F *bottom40 = (TH1F*)infile[6].Get(var[i]);
    TH1F *bottom60 = (TH1F*)infile[7].Get(var[i]);
    TH1F *charm2 = (TH1F*)infile[8].Get(var[i]);
    TH1F *charm20 = (TH1F*)infile[9].Get(var[i]);
    TH1F *charm40 = (TH1F*)infile[10].Get(var[i]);
    TH1F *charm60 = (TH1F*)infile[11].Get(var[i]);
    TH1F *bb2 = (TH1F*)infile[12].Get(var[i]);
    TH1F *bb40 = (TH1F*)infile[13].Get(var[i]);
    TH1F *bb60 = (TH1F*)infile[14].Get(var[i]);
    TH1F *bb120 = (TH1F*)infile[15].Get(var[i]);
    TH1F *cc2 = (TH1F*)infile[16].Get(var[i]);
    TH1F *cc40 = (TH1F*)infile[17].Get(var[i]);
    TH1F *cc60 = (TH1F*)infile[18].Get(var[i]);
    TH1F *cc120 = (TH1F*)infile[18].Get(var[i]);

    TCanvas *cx = new TCanvas("cx","cx", 800, 600);
    cx->cd();

    gStyle->SetOptStat(0);
    gStyle->SetTitleFont(132, "t");

    ttbar->Add(ttbar_di);
    ttbar->Add(ttbar_semi);

    bottomonium->Add(bottom2);
    bottomonium->Add(bottom40);
    bottomonium->Add(bottom60);

    charmonium->Add(charm2);
    charmonium->Add(charm20);
    charmonium->Add(charm40);
    charmonium->Add(charm60);

    ccbar->Add(cc2);
    ccbar->Add(cc40);
    ccbar->Add(cc60);
    ccbar->Add(cc120);

    bbbar->Add(bb2);
    bbbar->Add(bb40);
    bbbar->Add(bb60);
    bbbar->Add(bb120);

    sum->Add(bottomonium);
    sum->Add(charmonium);
    sum->Add(bbbar);
    sum->Add(ccbar);
    sum->Add(ttbar);
    sum->Add(wbos);
    sum->Add(zbos);

    sum->SetTitle(titles[i]);
    sum->SetTitleFont(132, "t");

    sum->GetXaxis()->SetTitle("Variable");
    sum->GetYaxis()->SetTitle("N_{events}");
    // sum->GetYaxis()->SetRangeUser(1,10000000);
    
    sum->GetXaxis()->SetTitleFont(132);
    sum->GetYaxis()->SetTitleFont(132);

    sum->SetLineColor(46);
    sum->SetLineWidth(3);
    sum->Draw("HIST");

    bottomonium->SetLineColor(42);
    bottomonium->SetLineWidth(3);
    bottomonium->Draw("HIST SAME");

    charmonium->SetLineColor(41);
    charmonium->SetLineWidth(3);
    charmonium->Draw("HIST SAME");

    bbbar->SetLineColor(30);
    bbbar->SetLineWidth(3);
    bbbar->Draw("HIST SAME");

    ccbar->SetLineColor(29);
    ccbar->SetLineWidth(3);
    ccbar->Draw("HIST SAME");

    ttbar->SetLineColor(38);
    ttbar->SetLineWidth(3);
    ttbar->Draw("HIST SAME");

    wbos->SetLineColor(36);
    wbos->SetLineWidth(3);
    wbos->Draw("HIST SAME");

    zbos->SetLineColor(48);
    zbos->SetLineWidth(3);
    zbos->Draw("HIST SAME");

    auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
    leg->AddEntry(sum, "All Events", "f");
    leg->AddEntry(bottomonium, "Bottomonium","f");
    leg->AddEntry(charmonium, "Charmonium", "f");
    leg->AddEntry(bbbar, "bbbar", "f");
    leg->AddEntry(ccbar, "ccbar", "f");
    leg->AddEntry(ttbar, "ttbar", "f");
    leg->AddEntry(wbos, "wbos", "f");
    leg->AddEntry(zbos, "zbos", "f");
    leg->SetTextSize(0.035);
    leg->Draw();

    TLatex *lumilabel = new TLatex(0.69, 0.58, "luminosity: 1pm^(-1)");
    lumilabel->SetNDC();
    lumilabel->SetTextSize(0.03);
    lumilabel->SetTextAlign(22); // Center align
    lumilabel->SetTextFont(132);
    lumilabel->Draw();
    cx->Update();

    cx->SetLogy();
    cx->Print(outfiles[i]);
    cx->Close();

    sum->Delete();
    ttbar->Delete();
    bottomonium->Delete();
    charmonium->Delete();
    bbbar->Delete();
    ccbar->Delete();
  }
}