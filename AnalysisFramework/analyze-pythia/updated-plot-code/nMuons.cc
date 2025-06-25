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
  TH1F *hist1 = new TH1F("plot1", "plot1", num_bins, 0, 120);
  TH1F *hist2 = new TH1F("plot2", "plot2", num_bins, 0, 120);
  TH1F *hist3 = new TH1F("plot3", "plot3", num_bins, 0, 120);

  // Get the histograms
  // ==================

  for (int i = 0; i < 28; i++) {
    TH1F *tempall = (TH1F*)infile[i].Get("Bare_Muon_pT");
    TH1F *temp1  = (TH1F*)infile[i].Get("OneMuon");
    TH1F *temp2 = (TH1F*)infile[i].Get("TwoMuon");
    TH1F *temp3  = (TH1F*)infile[i].Get("ThreeMuon");

    all_muons->Add(tempall);
    hist1->Add(temp1);
    hist2->Add(temp2);
    hist3->Add(temp3);
  }

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  all_muons->SetTitle("Muon p_{T} Distribution for Number of Muons in Event");
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

  hist2->SetLineColor(38);
  hist2->SetLineWidth(3);
  hist2->Draw("HIST SAME");

  hist3->SetLineColor(30);
  hist3->SetLineWidth(3);
  hist3->Draw("HIST SAME");

  auto leg = new TLegend(0.72, 0.70, 0.9, 0.89);
  leg->AddEntry(all_muons, "All Events", "l");
  leg->AddEntry(hist1, "nMuons=1","l");
  leg->AddEntry(hist2, "nMuons=2", "l");
  leg->AddEntry(hist3, "nMuons=3", "l");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/muon-pt/nMuons.png");
  cx->Close();
}
