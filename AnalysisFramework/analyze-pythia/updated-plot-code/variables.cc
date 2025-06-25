// FinalCuts.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile[28] = {"$PWD/histograms/updated/ttbar-dilep.root", "$PWD/histograms/updated/ttbar-semilep.root",
    "$PWD/histograms/updated/wbos.root", "$PWD/histograms/updated/zbos.root", "$PWD/histograms/updated/gamma.root", 
    "$PWD/histograms/updated/bottom2.root", "$PWD/histograms/updated/bottom20.root", "$PWD/histograms/updated/bottom40.root", "$PWD/histograms/updated/bottom60.root", "$PWD/histograms/updated/bottom120.root",
    "$PWD/histograms/updated/charm2.root", "$PWD/histograms/updated/charm10.root","$PWD/histograms/updated/charm20.root", "$PWD/histograms/updated/charm40.root", "$PWD/histograms/updated/charm60.root", "$PWD/histograms/updated/charm120.root",
    "$PWD/histograms/updated/bb2.root", "$PWD/histograms/updated/bb20.root","$PWD/histograms/updated/bb40.root", "$PWD/histograms/updated/bb60.root", "$PWD/histograms/updated/bb120.root","$PWD/histograms/updated/bb200.root", 
    "$PWD/histograms/updated/cc2.root", "$PWD/histograms/updated/cc40.root", "$PWD/histograms/updated/cc40.root", "$PWD/histograms/updated/cc60.root", "$PWD/histograms/updated/cc120.root", "$PWD/histograms/updated/cc200.root"};

  const char *var[5] = {"MetMuon_dPhi", "JetMuon_dPhi", "diMu_dPhi", "JetMuon_dR", "diMu_dR"};
  const char *xlab[5] = {"\\Delta \\Phi", "\\Delta \\Phi", "\\Delta \\Phi", "\\Delta R", "\\Delta R"};
  const char *outfiles[5] = {"./plots/separation/process-breakdown/MetMuon_dPhi.png", "./plots/separation/process-breakdown/JetMuon_dPhi.png", "./plots/separation/process-breakdown/diMu_dPhi.png", 
                            "./plots/separation/process-breakdown/JetMuon_dR.png", "./plots/separation/process-breakdown/diMu_dR.png"};
  const char *titles[5] = {"\\Delta \\phi \\mbox{ between } E_T^{miss} \\mbox{ and Lead Muon}", "\\Delta \\phi \\mbox{ between Lead Jet and Lead Muon}", "\\Delta \\phi \\mbox{ between First Two Muons}", "\\Delta R \\mbox{ between Lead Jet and Lead Muon}", 
                            "\\Delta R \\mbox{ between First Two Muons}"};
  double xmax[5] = {M_PI, M_PI, M_PI, 10, 10};
  
  for(int i = 0; i < 5; i++) {
    TH1F *sum = new TH1F(titles[i], "pT", 60, 0, xmax[i]);
    TH1F *ttbar = new TH1F("tt", "pT", 60, 0, xmax[i]);
    TH1F *bottomonium = new TH1F("bot", "pT", 60, 0, xmax[i]);
    TH1F *charmonium = new TH1F("charm", "pT", 60, 0, xmax[i]);
    TH1F *bbbar = new TH1F("bb", "pT", 60, 0, xmax[i]);
    TH1F *ccbar = new TH1F("cc", "pT", 60, 0, xmax[i]);
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
    gStyle->SetTitleFont(122, "t");

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
    sum->SetTitleFont(122, "t");
    sum->GetYaxis()->SetRangeUser(1,100000000000);
    if (i == 4) {
      sum->GetXaxis()->SetRangeUser(0, 8);
    }

    sum->GetXaxis()->SetTitle(xlab[i]);
    sum->GetYaxis()->SetTitle("N_{muons}");
    
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

    auto leg = new TLegend(0.55, 0.7, 0.9, 0.89);
    leg->SetNColumns(2);
    leg->AddEntry(sum, "All Events", "l");
    leg->AddEntry(ttbar, "ttbar", "l");
    leg->AddEntry(bottomonium, "Bottomonium","l");
    leg->AddEntry(wbos, "W Boson", "l");
    leg->AddEntry(charmonium, "Charmonium", "l");
    leg->AddEntry(zbos, "Z Boson", "l");
    leg->AddEntry(bbbar, "b\\bar{b}", "l");
    leg->AddEntry(gamma, "\\gamma^*", "l");
    leg->AddEntry(ccbar, "c\\bar{c}", "l");
    leg->SetTextSize(0.035);
    leg->SetBorderSize(0);
    leg->Draw();

    cx->SetLogy();
    cx->Print(outfiles[i]);
    cx->Close();

    ttbar->Delete();
    bottomonium->Delete();
    charmonium->Delete();
    bbbar->Delete();
    ccbar->Delete();
  }
}