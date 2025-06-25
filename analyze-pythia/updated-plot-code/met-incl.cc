// Met.cc
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
  
  TH1F *all_muons = new TH1F("sum", "sum", 60, 0, 120);
  TH1F *sum_met_muons = new TH1F("summ", "summ", 60, 0, 120);
  TH1F *met1 = new TH1F("sum met1", "sum met1", 60, 0, 120);
  TH1F *met2 = new TH1F("sum met2", "sum met2", 60, 0, 120);
  TH1F *met3 = new TH1F("sum met3", "sum met3", 60, 0, 120);
  TH1F *met4 = new TH1F("sum met4", "sum met4", 60, 0, 120);
  TH1F *met5 = new TH1F("sum met5", "sum met5", 60, 0, 120);
  TH1F *met6 = new TH1F("sum met6", "sum met6", 60, 0, 120);
  TH1F *met7 = new TH1F("sum met7", "sum met7", 60, 0, 120);
  TH1F *met8 = new TH1F("sum met8", "sum met8", 60, 0, 120);


  for (int i = 0; i < 28; i++) {
    TH1F *tempall = (TH1F*)infile[i].Get("Bare_Muon_pT");
    TH1F *temp1 = (TH1F*)infile[i].Get("Met1");
    TH1F *temp2 = (TH1F*)infile[i].Get("Met2");
    TH1F *temp3 = (TH1F*)infile[i].Get("Met3");
    TH1F *temp4 = (TH1F*)infile[i].Get("Met4");
    TH1F *temp5 = (TH1F*)infile[i].Get("Met5");
    TH1F *temp6 = (TH1F*)infile[i].Get("Met6");
    TH1F *temp7 = (TH1F*)infile[i].Get("Met7");
    TH1F *temp8 = (TH1F*)infile[i].Get("Met8");

    all_muons->Add(tempall);

    met6->Add(temp6);
    met6->Add(temp7);
    met6->Add(temp8);
    
    met5->Add(temp5);
    met5->Add(temp6);
    met5->Add(temp7);
    met5->Add(temp8);

    met4->Add(temp4);
    met4->Add(temp5);
    met4->Add(temp6);
    met4->Add(temp7);
    met4->Add(temp8);

    met3->Add(temp3);
    met3->Add(temp4);
    met3->Add(temp5);
    met3->Add(temp6);
    met3->Add(temp7);
    met3->Add(temp8);

    met2->Add(temp2);
    met2->Add(temp3);
    met2->Add(temp4);
    met2->Add(temp5);
    met2->Add(temp6);
    met2->Add(temp7);
    met2->Add(temp8);
  }

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  all_muons->SetTitle("Cuts on E_{T}^{miss}");
  all_muons->SetTitleFont(132, "t");

  all_muons->GetXaxis()->SetTitle("Muon p_{T} [GeV]");
  all_muons->GetYaxis()->SetTitle("N_{muons}");
  
  all_muons->GetXaxis()->SetTitleFont(132);
  all_muons->GetYaxis()->SetTitleFont(132);
  all_muons->GetXaxis()->SetRangeUser(5, 120);


  all_muons->SetLineColor(46);
  all_muons->SetLineWidth(3);
  all_muons->Draw("HIST");

  // met1->SetLineColor(42);
  // met1->SetLineWidth(3);
  // met1->Draw("HIST SAME");

  met2->SetLineColor(42);
  met2->SetLineWidth(3);
  met2->Draw("HIST SAME");

  met3->SetLineColor(30);
  met3->SetLineWidth(3);
  met3->Draw("HIST SAME");

  met4->SetLineColor(38);
  met4->SetLineWidth(3);
  met4->Draw("HIST SAME");

  met5->SetLineColor(36);
  met5->SetLineWidth(3);
  met5->Draw("HIST SAME");

  met6->SetLineColor(40);
  met6->SetLineWidth(3);
  met6->Draw("HIST SAME");

  // met7->SetLineColor(40);
  // met7->SetLineWidth(3);
  // met7->Draw("HIST SAME");

  // met8->SetLineColor(48);
  // met8->SetLineWidth(3);
  // met8->Draw("HIST SAME");

  cout << "All Muons: " << all_muons->Integral(0, 200) << endl;
  cout << "30 GeV threshold: " << met5->Integral(0, 200) << endl;
  cout << "All Muons (> 30 GeV): " << all_muons->Integral(30, 200) << endl;
  cout << "30 GeV threshold (> 30 GeV): " << met5->Integral(30, 200) << endl;

  auto leg = new TLegend(0.65, 0.62, 0.9, 0.89);
  leg->AddEntry(all_muons, "All Events", "l");
  // leg->AddEntry(met1, "0 < MET [GeV]","l");
  leg->AddEntry(met2, "5 < E_{T}^{miss} [GeV]", "l");
  leg->AddEntry(met3, "10 < E_{T}^{miss} [GeV]", "l");
  leg->AddEntry(met4, "20 < E_{T}^{miss} [GeV]", "l");
  leg->AddEntry(met5, "30 < E_{T}^{miss} [GeV]", "l");
  leg->AddEntry(met6, "40 < E_{T}^{miss} [GeV]", "l");
  leg->SetBorderSize(0);
  // leg->AddEntry(met7, "60 < MET [GeV] < 80", "l");
  // leg->AddEntry(met8, "80 < MET [GeV]", "l");
  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/muon-pt/met_incl.png");
  cx->Close();

}