// nJets.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile[28] = {"$PWD/histograms/ttbar-dilep.root", "$PWD/histograms/ttbar-semilep.root",
                      "$PWD/histograms/wbos.root", "$PWD/histograms/zbos.root", "$PWD/histograms/gamma.root", 
                      "$PWD/histograms/bottom2.root", "$PWD/histograms/bottom20.root", "$PWD/histograms/bottom40.root", "$PWD/histograms/bottom60.root", "$PWD/histograms/bottom120.root",
                      "$PWD/histograms/charm2.root", "$PWD/histograms/charm10.root","$PWD/histograms/charm20.root", "$PWD/histograms/charm40.root", "$PWD/histograms/charm60.root", "$PWD/histograms/charm120.root",
                      "$PWD/histograms/bb2.root", "$PWD/histograms/bb20.root","$PWD/histograms/bb40.root", "$PWD/histograms/bb60.root", "$PWD/histograms/bb120.root","$PWD/histograms/bb200.root", 
                      "$PWD/histograms/cc2.root", "$PWD/histograms/cc40.root", "$PWD/histograms/cc40.root", "$PWD/histograms/cc60.root", "$PWD/histograms/cc120.root", "$PWD/histograms/cc200.root"};
  
  TH1F *all_muons = new TH1F("sum", "sum", 60, 0, 120);
  TH1F *one_muon = new TH1F("one_muon", "one_muon", 60, 0, 120);
  TH1F *cut_muons1 = new TH1F("muon cuts 1", "muon cuts 1", 60, 0, 120);
  TH1F *cut_muons2 = new TH1F("muon cuts 2", "muon cuts 2", 60, 0, 120);
  TH1F *cut_muons3 = new TH1F("muon cuts 3", "muon cuts 3", 60, 0, 120);
  TH1F *cut_muons4 = new TH1F("muon cuts 4", "muon cuts 4", 60, 0, 120);


  // Get the histograms
  // ==================

  for (int i = 0; i < 28; i++) {
    TH1F *tempall = (TH1F*)infile[i].Get("Bare_Muon_pT");
    TH1F *temp1 = (TH1F*)infile[i].Get("OneMuon");
    TH1F *tempcut1  = (TH1F*)infile[i].Get("ComboCuts1");
    TH1F *tempcut2  = (TH1F*)infile[i].Get("ComboCuts2");
    TH1F *tempcut3  = (TH1F*)infile[i].Get("ComboCuts3");
    TH1F *tempcut4  = (TH1F*)infile[i].Get("ComboCuts4");

    all_muons->Add(tempall);
    one_muon->Add(temp1);
    cut_muons1->Add(tempcut1);
    cut_muons2->Add(tempcut2);
    cut_muons3->Add(tempcut3);
    cut_muons4->Add(tempcut4);
  }

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  all_muons->SetTitle("Muon pT with Cuts");
  all_muons->SetTitleFont(132, "t");
  
  all_muons->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  all_muons->GetYaxis()->SetTitle("N_{muons}");
  
  all_muons->GetXaxis()->SetTitleFont(132);
  all_muons->GetYaxis()->SetTitleFont(132);

  all_muons->SetLineColor(46);
  all_muons->SetLineWidth(3);
  all_muons->Draw("HIST");

  cut_muons1->SetLineColor(42);
  cut_muons1->SetLineWidth(3);
  cut_muons1->Draw("HIST SAME");

  cut_muons2->SetLineColor(32);
  cut_muons2->SetLineWidth(3);
  cut_muons2->Draw("HIST SAME");

  cut_muons3->SetLineColor(38);
  cut_muons3->SetLineWidth(3);
  cut_muons3->Draw("HIST SAME");

  one_muon->SetLineColor(48);
  one_muon->SetLineWidth(3);
  one_muon->Draw("HIST SAME");

  // cut_muons4->SetLineColor(48);
  // cut_muons4->SetLineWidth(3);
  // cut_muons4->Draw("HIST SAME");

  auto leg = new TLegend(0.35, 0.60, 0.9, 0.89);
  leg->AddEntry(all_muons, "all events", "f");
  leg->AddEntry(one_muon, "Events with 1 muon", "f");
  leg->AddEntry(cut_muons1, "Met > 5, 1 muon","f");
  leg->AddEntry(cut_muons2, "Met > 10, 1 muon","f");
  leg->AddEntry(cut_muons3, "Met > 20, 1 muon","f");
  // leg->AddEntry(cut_muons4, "MET > 30 GeV || Jets > 0","f");

  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/combo_cuts.png");
  cx->Close();
}