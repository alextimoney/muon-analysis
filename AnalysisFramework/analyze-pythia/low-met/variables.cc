// FinalCuts.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile[28] = {"$PWD/../histograms/met-low/ttbar-dilep.root", "$PWD/../histograms/met-low/ttbar-semilep.root",
                      "$PWD/../histograms/met-low/wbos.root", "$PWD/../histograms/met-low/zbos.root", "$PWD/../histograms/met-low/gamma.root", 
                      "$PWD/../histograms/met-low/bottom2.root", "$PWD/../histograms/met-low/bottom20.root", "$PWD/../histograms/met-low/bottom40.root", "$PWD/../histograms/met-low/bottom60.root", "$PWD/../histograms/met-low/bottom120.root",
                      "$PWD/../histograms/met-low/charm2.root", "$PWD/../histograms/met-low/charm10.root","$PWD/../histograms/met-low/charm20.root", "$PWD/../histograms/met-low/charm40.root", "$PWD/../histograms/met-low/charm60.root", "$PWD/../histograms/met-low/charm120.root",
                      "$PWD/../histograms/met-low/bb2.root", "$PWD/../histograms/met-low/bb20.root","$PWD/../histograms/met-low/bb40.root", "$PWD/../histograms/met-low/bb60.root", "$PWD/../histograms/met-low/bb120.root","$PWD/../histograms/met-low/bb200.root", 
                      "$PWD/../histograms/met-low/cc2.root", "$PWD/../histograms/met-low/cc40.root", "$PWD/../histograms/met-low/cc40.root", "$PWD/../histograms/met-low/cc60.root", "$PWD/../histograms/met-low/cc120.root", "$PWD/../histograms/met-low/cc200.root"};
  
  const char *var[9] = {"JetPt", "JetEta", "JetMuonPhi", "MetJetPhi", "MetMuonPhi", "MetPt", "MetJetPt", "MuonIsolation", "JetMuonR"};
  const char *outfiles[9] = {"./plots/variables/jetPt.png", "./plots/variables/JetEta.png", "./plots/variables/JetMuonPhi.png", 
                              "./plots/variables/MetJetPhi.png", "./plots/variables/MetMuonPhi.png", "./plots/variables/MetPt.png", 
                              "./plots/variables/MetJetPt.png", "./plots/variables/MuIso.png", "./plots/variables/JetMuonR.png"};
  const char *outfiles_norm1[9] = {"./plots/variables/norm1/jetPt.png", "./plots/variables/norm1/JetEta.png", "./plots/variables/norm1/JetMuonPhi.png", 
                              "./plots/variables/norm1/MetJetPhi.png", "./plots/variables/norm1/MetMuonPhi.png", "./plots/variables/norm1/MetPt.png", 
                              "./plots/variables/norm1/MetJetPt.png", "./plots/variables/norm1/MuIso.png", "./plots/variables/norm1/JetMuonR.png"};
  const char *titles[9] = {"Jet pT", "Jet Eta", "Phi between Jet and Muon", "Phi between Jet and Met", 
                            "Phi between Met and Muon", "Pt of Met", "Pt of Sum of Met and Jet", "Muon Isolation", "Delta R between Jet and Muon"};
  const char *xlab[9] = {"Jet pT [GeV]", "Jet Eta", "Angle btwn Jet and Muon", "Angle between Jet and Met", "Angle between Met and muon", "Met pT", "Sum of Met and Jet pT", "Isolation pT", "delta R"};
  const char *plus[5] = {"tt", "bot", "charm", "bb", "cc"};
  double xmax[9] = {160, 2.5, M_PI, M_PI, M_PI, 140, 180, 200, 10};
  
  for(int i = 0; i < 9; i++) {
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
    TH1F *bottom20 = (TH1F*)infile[6].Get(var[i]);
    TH1F *bottom40 = (TH1F*)infile[7].Get(var[i]);
    TH1F *bottom60 = (TH1F*)infile[8].Get(var[i]);
    TH1F *bottom120 = (TH1F*)infile[9].Get(var[i]);
    TH1F *charm2 = (TH1F*)infile[10].Get(var[i]);
    TH1F *charm10 = (TH1F*)infile[11].Get(var[i]);
    TH1F *charm20 = (TH1F*)infile[12].Get(var[i]);
    TH1F *charm40 = (TH1F*)infile[13].Get(var[i]);
    TH1F *charm60 = (TH1F*)infile[14].Get(var[i]);
    TH1F *charm120 = (TH1F*)infile[15].Get(var[i]);
    TH1F *bb2 = (TH1F*)infile[16].Get(var[i]);
    TH1F *bb20 = (TH1F*)infile[17].Get(var[i]);
    TH1F *bb40 = (TH1F*)infile[18].Get(var[i]);
    TH1F *bb60 = (TH1F*)infile[19].Get(var[i]);
    TH1F *bb120 = (TH1F*)infile[20].Get(var[i]);
    TH1F *bb200 = (TH1F*)infile[21].Get(var[i]);
    TH1F *cc2 = (TH1F*)infile[22].Get(var[i]);
    TH1F *cc20 = (TH1F*)infile[23].Get(var[i]);
    TH1F *cc40 = (TH1F*)infile[24].Get(var[i]);
    TH1F *cc60 = (TH1F*)infile[25].Get(var[i]);
    TH1F *cc120 = (TH1F*)infile[26].Get(var[i]);
    TH1F *cc200 = (TH1F*)infile[27].Get(var[i]);

    TCanvas *cx = new TCanvas("cx","cx", 800, 600);
    cx->cd();

    gStyle->SetOptStat(0);
    gStyle->SetTitleFont(132, "t");

    ttbar->Add(ttbar_di);
    ttbar->Add(ttbar_semi);

    bottomonium->Add(bottom2);
    bottomonium->Add(bottom20);
    bottomonium->Add(bottom40);
    bottomonium->Add(bottom60);
    bottomonium->Add(bottom120);

    charmonium->Add(charm2);
    charmonium->Add(charm10);
    charmonium->Add(charm20);
    charmonium->Add(charm40);
    charmonium->Add(charm60);
    charmonium->Add(charm120);

    ccbar->Add(cc2);
    ccbar->Add(cc20);
    ccbar->Add(cc40);
    ccbar->Add(cc60);
    ccbar->Add(cc120);
    ccbar->Add(cc200);

    bbbar->Add(bb2);
    bbbar->Add(bb20);
    bbbar->Add(bb40);
    bbbar->Add(bb60);
    bbbar->Add(bb120);
    bbbar->Add(bb200);

    sum->Add(bottomonium);
    sum->Add(charmonium);
    sum->Add(bbbar);
    sum->Add(ccbar);
    sum->Add(ttbar);
    sum->Add(wbos);
    sum->Add(zbos);
    sum->Add(gamma);

    sum->SetTitle(titles[i]);
    sum->SetTitleFont(132, "t");
    sum->GetYaxis()->SetRangeUser(1,100000000000);
    if (i == 0 || i == 6) {
      sum->GetXaxis()->SetRangeUser(30, 180);
    }

    sum->GetXaxis()->SetTitle(xlab[i]);
    sum->GetYaxis()->SetTitle("N_{events}");
    
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

    gamma->SetLineColor(40);
    gamma->SetLineWidth(3);
    gamma->Draw("HIST SAME");

    auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
    leg->AddEntry(sum, "All Events", "f");
    leg->AddEntry(bottomonium, "Bottomonium","f");
    leg->AddEntry(charmonium, "Charmonium", "f");
    leg->AddEntry(bbbar, "bbbar", "f");
    leg->AddEntry(ccbar, "ccbar", "f");
    leg->AddEntry(ttbar, "ttbar", "f");
    leg->AddEntry(wbos, "wbos", "f");
    leg->AddEntry(zbos, "zbos", "f");
    leg->AddEntry(gamma, "gamma*", "f");
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


    TCanvas *cy = new TCanvas("cy","cy", 800, 600);
    cy->cd();

    gStyle->SetOptStat(0);
    gStyle->SetTitleFont(132, "t");

    sum->Scale(1/sum->GetSumOfWeights());
    bottomonium->Scale(1/bottomonium->GetSumOfWeights());
    charmonium->Scale(1/charmonium->GetSumOfWeights());
    bbbar->Scale(1/bbbar->GetSumOfWeights());
    ccbar->Scale(1/ccbar->GetSumOfWeights());
    ttbar->Scale(1/ttbar->GetSumOfWeights());
    wbos->Scale(1/wbos->GetSumOfWeights());
    zbos->Scale(1/zbos->GetSumOfWeights());
    gamma->Scale(1/gamma->GetSumOfWeights());

    sum->GetXaxis()->SetTitle(xlab[i]);
    sum->GetYaxis()->SetTitle("N_{events}");
    
    sum->GetXaxis()->SetTitleFont(132);
    sum->GetYaxis()->SetTitleFont(132);

    sum->Draw("HIST");
    bottomonium->Draw("HIST SAME");
    charmonium->Draw("HIST SAME");
    bbbar->Draw("HIST SAME");
    ccbar->Draw("HIST SAME");
    ttbar->Draw("HIST SAME");
    wbos->Draw("HIST SAME");
    zbos->Draw("HIST SAME");
    gamma->Draw("HIST SAME");

    leg->Draw();

    cy->SetLogy();
    cy->Print(outfiles_norm1[i]);
    cy->Close();

    sum->Delete();
    ttbar->Delete();
    bottomonium->Delete();
    charmonium->Delete();
    bbbar->Delete();
    ccbar->Delete();
  }
}