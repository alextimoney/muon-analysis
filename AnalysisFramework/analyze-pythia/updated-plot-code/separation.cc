// AnglePlots.C
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================


  int option = 1;
  int num_bins = 60;

  TFile infile[28] = {"$PWD/histograms/updated/ttbar-dilep.root", "$PWD/histograms/updated/ttbar-semilep.root",
                      "$PWD/histograms/updated/wbos.root", "$PWD/histograms/updated/zbos.root", "$PWD/histograms/updated/gamma.root", 
                      "$PWD/histograms/updated/bottom2.root", "$PWD/histograms/updated/bottom20.root", "$PWD/histograms/updated/bottom40.root", "$PWD/histograms/updated/bottom60.root", "$PWD/histograms/updated/bottom120.root",
                      "$PWD/histograms/updated/charm2.root", "$PWD/histograms/updated/charm10.root","$PWD/histograms/updated/charm20.root", "$PWD/histograms/updated/charm40.root", "$PWD/histograms/updated/charm60.root", "$PWD/histograms/updated/charm120.root",
                      "$PWD/histograms/updated/bb2.root", "$PWD/histograms/updated/bb20.root","$PWD/histograms/updated/bb40.root", "$PWD/histograms/updated/bb60.root", "$PWD/histograms/updated/bb120.root","$PWD/histograms/updated/bb200.root", 
                      "$PWD/histograms/updated/cc2.root", "$PWD/histograms/updated/cc40.root", "$PWD/histograms/updated/cc40.root", "$PWD/histograms/updated/cc60.root", "$PWD/histograms/updated/cc120.root", "$PWD/histograms/updated/cc200.root"};

  const char *var[5][8] = {{"MetMuon_dPhi_1", "MetMuon_dPhi_2", "MetMuon_dPhi_3", "MetMuon_dPhi_4", "MetMuon_dPhi_5", "MetMuon_dPhi_6", "MetMuon_dPhi_7", "MetMuon_dPhi_8"},
                           {"JetMuon_dPhi_1", "JetMuon_dPhi_2", "JetMuon_dPhi_3", "JetMuon_dPhi_4", "JetMuon_dPhi_5", "JetMuon_dPhi_6", "JetMuon_dPhi_7", "JetMuon_dPhi_8"},
                           {"diMu_dPhi_1", "diMu_dPhi_2", "diMu_dPhi_3", "diMu_dPhi_4", "diMu_dPhi_5", "diMu_dPhi_6", "diMu_dPhi_7", "diMu_dPhi_8"},
                           {"JetMuon_dR_1", "JetMuon_dR_2", "JetMuon_dR_3", "JetMuon_dR_4", "JetMuon_dR_5", "JetMuon_dR_6", "JetMuon_dR_7", "JetMuon_dR_8"},
                           {"diMu_dR_1", "diMu_dR_2", "diMu_dR_3", "diMu_dR_4", "diMu_dR_5", "diMu_dR_6", "diMu_dR_7", "diMu_dR_8"}};
  const char *leg_lab[5][8] = {{"\\Delta \\phi < \\frac{\\pi}{8}", "\\frac{\\pi}{8} < \\Delta \\phi < \\frac{\\pi}{4}", "\\frac{\\pi}{4} < \\Delta \\phi < \\frac{3\\pi}{8}", "\\frac{3\\pi}{8} < \\Delta \\phi < \\frac{\\pi}{2}", "\\frac{\\pi}{2} < \\Delta \\phi < \\frac{5\\pi}{8}", "\\frac{5\\pi}{4} < \\Delta \\phi < \\frac{3\\pi}{4}", "\\frac{3\\pi}{4} < \\Delta \\phi < \\frac{7\\pi}{8}", "\\frac{7\\pi}{8} < \\Delta \\phi < \\pi"},
                           {"\\Delta \\phi < \\frac{\\pi}{8}", "\\frac{\\pi}{8} < \\Delta \\phi < \\frac{\\pi}{4}", "\\frac{\\pi}{4} < \\Delta \\phi < \\frac{3\\pi}{8}", "\\frac{3\\pi}{8} < \\Delta \\phi < \\frac{\\pi}{2}", "\\frac{\\pi}{2} < \\Delta \\phi < \\frac{5\\pi}{8}", "\\frac{5\\pi}{4} < \\Delta \\phi < \\frac{3\\pi}{4}", "\\frac{3\\pi}{4} < \\Delta \\phi < \\frac{7\\pi}{8}", "\\frac{7\\pi}{8} < \\Delta \\phi < \\pi"},
                           {"\\Delta \\phi < \\frac{\\pi}{8}", "\\frac{\\pi}{8} < \\Delta \\phi < \\frac{\\pi}{4}", "\\frac{\\pi}{4} < \\Delta \\phi < \\frac{3\\pi}{8}", "\\frac{3\\pi}{8} < \\Delta \\phi < \\frac{\\pi}{2}", "\\frac{\\pi}{2} < \\Delta \\phi < \\frac{5\\pi}{8}", "\\frac{5\\pi}{4} < \\Delta \\phi < \\frac{3\\pi}{4}", "\\frac{3\\pi}{4} < \\Delta \\phi < \\frac{7\\pi}{8}", "\\frac{7\\pi}{8} < \\Delta \\phi < \\pi"},
                           {"\\Delta R < 1", "1 < \\Delta R < 2", "2 < \\Delta R < 3", "3 < \\Delta R < 4", "4 < \\Delta R < 5", "5 < \\Delta R < 6", "6 < \\Delta R < 7", "\\Delta R > 7"},
                           {"\\Delta R < 1", "1 < \\Delta R < 2", "2 < \\Delta R < 3", "3 < \\Delta R < 4", "4 < \\Delta R < 5", "5 < \\Delta R < 6", "6 < \\Delta R < 7", "\\Delta R > 7"}};

  const char *outfiles[5] = {"./plots/separation/MetMuon_dPhi.png", "./plots/separation/JetMuon_dPhi.png", "./plots/separation/diMu_dPhi.png", 
                             "./plots/separation/JetMuon_dR.png", "./plots/separation/diMu_dR.png"};
  const char *titles[5] = {"\\mbox{Cuts on } \\Delta \\phi \\mbox{ between } E_T^{miss} \\mbox{ and Lead Muon}", "\\mbox{Cuts on }\\Delta \\phi \\mbox{ between Lead Jet and Lead Muon}", "\\mbox{Cuts on }\\Delta \\phi \\mbox{ between First Two Muons}", "\\mbox{Cuts on }\\Delta R \\mbox{ between Lead Jet and Lead Muon}", 
                           "\\mbox{Cuts on }\\Delta R \\mbox{ between First Two Muons}"};

  TH1F *all_muons = new TH1F("sum", "sum", num_bins, 0, 120);
  TH1F *hist1 = new TH1F("plot1", "plot1", num_bins, 0, 120);
  TH1F *hist2 = new TH1F("plot2", "plot2", num_bins, 0, 120);
  TH1F *hist3 = new TH1F("plot3", "plot3", num_bins, 0, 120);
  TH1F *hist4 = new TH1F("plot4", "plot4", num_bins, 0, 120);
  TH1F *hist5 = new TH1F("plot5", "plot5", num_bins, 0, 120);
  TH1F *hist6 = new TH1F("plot6", "plot6", num_bins, 0, 120);
  TH1F *hist7 = new TH1F("plot7", "plot7", num_bins, 0, 120);
  TH1F *hist8 = new TH1F("plot8", "plot8", num_bins, 0, 120);


  for (int i = 0; i < 5; i++) {
    // Get the histograms
    for (int j = 0; j < 28; j++) {
      TH1F *tempall = (TH1F*)infile[j].Get("Bare_Muon_pT");
      TH1F *temp1  = (TH1F*)infile[j].Get(var[i][0]);
      TH1F *temp2 = (TH1F*)infile[j].Get(var[i][1]);
      TH1F *temp3  = (TH1F*)infile[j].Get(var[i][2]);
      TH1F *temp4  = (TH1F*)infile[j].Get(var[i][3]);
      TH1F *temp5  = (TH1F*)infile[j].Get(var[i][4]);
      TH1F *temp6  = (TH1F*)infile[j].Get(var[i][5]);
      TH1F *temp7  = (TH1F*)infile[j].Get(var[i][6]);
      TH1F *temp8  = (TH1F*)infile[j].Get(var[i][7]);

      all_muons->Add(tempall);
      hist1->Add(temp1);
      hist2->Add(temp2);
      hist3->Add(temp3);
      hist4->Add(temp4);
      hist5->Add(temp5);
      hist6->Add(temp6);
      hist7->Add(temp7);
      hist8->Add(temp8);
    }

    gStyle->SetOptStat(0);
    gStyle->SetTitleFont(132, "t");

    TCanvas *cx = new TCanvas("cx","cx", 800, 600);
    cx->cd();

    all_muons->SetTitle(titles[i]);
    all_muons->SetTitleFont(132, "t");
    
    all_muons->GetXaxis()->SetTitle("Muon p_{T} [GeV]");
    all_muons->GetYaxis()->SetTitle("N_{muons}");
    
    all_muons->GetXaxis()->SetTitleFont(132);
    all_muons->GetYaxis()->SetTitleFont(132);
    all_muons->GetYaxis()->SetRangeUser(1, 10000000000);
    all_muons->GetXaxis()->SetRangeUser(5, 80);

    all_muons->SetLineColor(46);
    all_muons->SetLineWidth(3);
    all_muons->Draw("HIST");

    hist1->SetLineColor(42);
    hist1->SetLineWidth(3);
    hist1->Draw("HIST SAME");

    hist2->SetLineColor(41);
    hist2->SetLineWidth(3);
    hist2->Draw("HIST SAME");

    hist3->SetLineColor(30);
    hist3->SetLineWidth(3);
    hist3->Draw("HIST SAME");

    hist4->SetLineColor(29);
    hist4->SetLineWidth(3);
    hist4->Draw("HIST SAME");

    hist5->SetLineColor(38);
    hist5->SetLineWidth(3);
    hist5->Draw("HIST SAME");

    hist6->SetLineColor(36);
    hist6->SetLineWidth(3);
    hist6->Draw("HIST SAME");

    hist7->SetLineColor(40);
    hist7->SetLineWidth(3);
    hist7->Draw("HIST SAME");

    hist8->SetLineColor(48);
    hist8->SetLineWidth(3);
    hist8->Draw("HIST SAME");

    auto leg = new TLegend(0.45, 0.63, 0.9, 0.89);
    leg->SetNColumns(2);
    leg->AddEntry(all_muons, "All Events", "l");
    leg->AddEntry(hist5, leg_lab[i][4], "l");
    leg->AddEntry(hist1, leg_lab[i][0],"l");
    leg->AddEntry(hist6, leg_lab[i][5], "l");
    leg->AddEntry(hist2, leg_lab[i][1], "l");
    leg->AddEntry(hist7, leg_lab[i][6], "l");
    leg->AddEntry(hist3, leg_lab[i][2], "l");
    leg->AddEntry(hist8, leg_lab[i][7], "l");
    leg->AddEntry(hist4, leg_lab[i][3], "l");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.035);
    leg->Draw();

    cx->SetLogy();
    cx->Print(outfiles[i]);
    cx->Close();
  }
}
