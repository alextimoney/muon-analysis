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
  
  TH1F *all_muons = new TH1F("sum", "sum", num_bins, 0, 120);
  TH1F *hist1 = new TH1F("Jet", "plot1", num_bins, 0, 120);
  TH1F *hist2 = new TH1F("Dimuon", "plot2", num_bins, 0, 120);
  TH1F *hist3 = new TH1F("Dimuon, Jet", "plot3", num_bins, 0, 120);
  TH1F *hist4 = new TH1F("dimujet", "plot4", num_bins, 0, 120);
  TH1F *met5 = new TH1F("sum met5", "sum met5", 60, 0, 120);

  // Get the histograms
  // ==================

  for (int i = 0; i < 28; i++) {
    TH1F *tempall = (TH1F*)infile[i].Get("Bare_Muon_pT");
    TH1F *tempdimujet  = (TH1F*)infile[i].Get("diMuJet");
    TH1F *tempdimu = (TH1F*)infile[i].Get("diMuon");
    TH1F *tempdimujetmet = (TH1F*)infile[i].Get("diMuJetMET");

    TH1F *temp1jet= (TH1F*)infile[i].Get("One_Jet");
    TH1F *temp2jet  = (TH1F*)infile[i].Get("Two_Jet");
    TH1F *tempmjet  = (TH1F*)infile[i].Get("Mult_Jet");

    TH1F *temp5 = (TH1F*)infile[i].Get("Met5");
    TH1F *temp6 = (TH1F*)infile[i].Get("Met6");
    TH1F *temp7 = (TH1F*)infile[i].Get("Met7");
    TH1F *temp8 = (TH1F*)infile[i].Get("Met8");

    met5->Add(temp5);
    met5->Add(temp6);
    met5->Add(temp7);
    met5->Add(temp8);

    all_muons->Add(tempall);
    
    hist1->Add(temp1jet);
    hist1->Add(temp2jet);
    hist1->Add(tempmjet);

    hist2->Add(tempdimu);
    hist3->Add(tempdimujet);
    hist4->Add(tempdimujetmet);
  }

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  all_muons->SetTitle("Muon p_{T} for Events with Jets and More than One Muon");
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

  // hist1->SetLineColor(42);
  // hist1->SetLineWidth(3);
  // hist1->Draw("HIST SAME");

  // hist2->SetLineColor(38);
  // hist2->SetLineWidth(3);
  // hist2->Draw("HIST SAME");

  hist3->SetLineColor(32);
  hist3->SetLineWidth(3);
  hist3->Draw("HIST SAME");

  hist4->SetLineColor(42);
  hist4->SetLineWidth(3);
  hist4->Draw("HIST SAME");

  met5->SetLineColor(38);
  met5->SetLineWidth(3);
  met5->Draw("HIST SAME");

  auto leg = new TLegend(0.55, 0.70, 0.9, 0.89);
  leg->AddEntry(all_muons, "All Events", "l");
  // leg->AddEntry(hist1, "nJets > 0","l");
  // leg->AddEntry(hist2, "nMuons > 1", "l");
  leg->AddEntry(hist3, "Dimuon or Jet", "l");
  leg->AddEntry(hist4, "Dimuon or Jet, MET < 30", "l");
  leg->AddEntry(met5, "MET > 30 GeV", "l");

  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/muon-pt/diMuJet.png");
  cx->Close();
}
