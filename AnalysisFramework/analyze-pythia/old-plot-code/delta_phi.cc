// AnglePlots.C
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================


  int option = 1;
  int num_bins = 60;
  string histo[3][8] = {
    {"MetJet1", "MetJet2", "MetJet3", "MetJet4", "MetJet5", "MetJet6", "MetJet7", "MetJet8"},
    {"MetMuon1", "MetMuon2", "MetMuon3", "MetMuon4", "MetMuon5", "MetMuon6", "MetMuon7", "MetMuon8"},
    {"JetMuon1", "JetMuon2", "JetMuon3", "JetMuon4", "JetMuon5", "JetMuon6", "JetMuon7", "JetMuon8"},
  };

  TFile infile[17] = {"$PWD/histograms/pTmin/bottom2.root", "$PWD/histograms/pTmin/charm2.root",
                     "$PWD/histograms/pTmin/bb2.root", "$PWD/histograms/pTmin/cc2.root", 
                     "$PWD/histograms/run1/ttbar-dilep.root", "$PWD/histograms/run1/ttbar-semilep.root",
                     "$PWD/histograms/run1/wbos.root", "$PWD/histograms/run1/zbos.root", "$PWD/histograms/run1/gamma.root",
                     "$PWD/histograms/pTmin/bottom40.root", "$PWD/histograms/pTmin/bottom60.root",
                     "$PWD/histograms/pTmin/charm40.root", "$PWD/histograms/pTmin/charm60.root", "$PWD/histograms/pTmin/bb40.root", 
                     "$PWD/histograms/pTmin/bb60.root", "$PWD/histograms/pTmin/cc40.root", "$PWD/histograms/pTmin/cc60.root"};

  TH1F *all_muons = new TH1F("sum", "sum", num_bins, 0, 120);
  TH1F *hist1 = new TH1F("plot1", "plot1", num_bins, 0, 120);
  TH1F *hist2 = new TH1F("plot2", "plot2", num_bins, 0, 120);
  TH1F *hist3 = new TH1F("plot3", "plot3", num_bins, 0, 120);
  TH1F *hist4 = new TH1F("plot4", "plot4", num_bins, 0, 120);
  TH1F *hist5 = new TH1F("plot5", "plot5", num_bins, 0, 120);
  TH1F *hist6 = new TH1F("plot6", "plot6", num_bins, 0, 120);
  TH1F *hist7 = new TH1F("plot7", "plot7", num_bins, 0, 120);
  TH1F *hist8 = new TH1F("plot8", "plot8", num_bins, 0, 120);
  TH1F *jetevents = new TH1F("jetevents", "jetevents", 60, 0, 120);

  // Get the histograms
  // ==================

  for (int i = 0; i < 17; i++) {
    TH1F *tempall = (TH1F*)infile[i].Get("Bare_Muon_pT");
    TH1F *temp1  = (TH1F*)infile[i].Get("MetMuon1");
    TH1F *temp2 = (TH1F*)infile[i].Get("MetMuon2");
    TH1F *temp3  = (TH1F*)infile[i].Get("MetMuon3");
    TH1F *temp4  = (TH1F*)infile[i].Get("MetMuon4");
    TH1F *temp5  = (TH1F*)infile[i].Get("MetMuon5");
    TH1F *temp6  = (TH1F*)infile[i].Get("MetMuon6");
    TH1F *temp7  = (TH1F*)infile[i].Get("MetMuon7");
    TH1F *temp8  = (TH1F*)infile[i].Get("MetMuon8");

    all_muons->Add(tempall);
    hist1->Add(temp1);
    hist2->Add(temp2);
    hist3->Add(temp3);
    hist4->Add(temp4);
    hist5->Add(temp5);
    hist6->Add(temp6);
    hist7->Add(temp7);
    hist8->Add(temp8);

    TH1F *temponejet = (TH1F*)infile[i].Get("One_Jet");
    TH1F *temptwojet = (TH1F*)infile[i].Get("Two_Jet");
    TH1F *tempmultjet = (TH1F*)infile[i].Get("Mult_Jet");
    jetevents->Add(temponejet);
    jetevents->Add(temptwojet);
    jetevents->Add(tempmultjet);
  }

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  all_muons->SetTitle("Muon pT for cuts on Angle Betwen Met and Muon");
  all_muons->SetTitleFont(132, "t");
  
  all_muons->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  all_muons->GetYaxis()->SetTitle("N_{events}");
  
  all_muons->GetXaxis()->SetTitleFont(132);
  all_muons->GetYaxis()->SetTitleFont(132);
  all_muons->GetYaxis()->SetRangeUser(1, 10000000000);

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

  // jetevents->SetLineColor(16);
  // jetevents->SetLineWidth(3);
  // jetevents->Draw("HIST SAME");

  auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg->AddEntry(all_muons, "all events", "f");
  // leg->AddEntry(jetevents, "events with a jet", "f");
  leg->AddEntry(hist1, "0 < |phi| < pi/8","f");
  leg->AddEntry(hist2, "pi/8 < |phi| < pi/4", "f");
  leg->AddEntry(hist3, "pi/4 < |phi| < 3pi/8", "f");
  leg->AddEntry(hist4, "3pi/8 < |phi| < pi/2", "f");
  leg->AddEntry(hist5, "pi/2 < |phi| < 5pi/8", "f");
  leg->AddEntry(hist6, "5pi/8 < |phi| < 3pi/4", "f");
  leg->AddEntry(hist7, "3pi/4 < |phi| < 7pi/8", "f");
  leg->AddEntry(hist8, "7pi/8 < |phi| < 0", "f");
  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/muon-pt/delta_phi/MetMuon.png");
  cx->Close();
}
