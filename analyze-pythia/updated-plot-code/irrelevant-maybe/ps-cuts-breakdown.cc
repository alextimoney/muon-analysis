// FinalCuts.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile[28] = {"$PWD/histograms/run1/ttbar-dilep.root", "$PWD/histograms/run1/ttbar-semilep.root",
                      "$PWD/histograms/run1/wbos.root", "$PWD/histograms/run1/zbos.root", "$PWD/histograms/run1/gamma.root", 
                      "$PWD/histograms/pTmin/bottom2.root", "$PWD/histograms/pTmin/bottom20.root", "$PWD/histograms/pTmin/bottom40.root", "$PWD/histograms/pTmin/bottom60.root", "$PWD/histograms/pTmin/bottom120.root",
                      "$PWD/histograms/pTmin/charm2.root", "$PWD/histograms/pTmin/charm10.root","$PWD/histograms/pTmin/charm20.root", "$PWD/histograms/pTmin/charm40.root", "$PWD/histograms/pTmin/charm60.root", "$PWD/histograms/pTmin/charm120.root",
                      "$PWD/histograms/pTmin/bb2.root", "$PWD/histograms/pTmin/bb20.root","$PWD/histograms/pTmin/bb40.root", "$PWD/histograms/pTmin/bb60.root", "$PWD/histograms/pTmin/bb120.root","$PWD/histograms/pTmin/bb200.root", 
                      "$PWD/histograms/pTmin/cc2.root", "$PWD/histograms/pTmin/cc40.root", "$PWD/histograms/pTmin/cc40.root", "$PWD/histograms/pTmin/cc60.root", "$PWD/histograms/pTmin/cc120.root", "$PWD/histograms/pTmin/cc200.root"};
  
  // Get the histograms
  // ==================

  TH1F *ttbar_di = (TH1F*)infile[0].Get("Bare_Muon_pT");
  TH1F *ttbar_semi = (TH1F*)infile[1].Get("Bare_Muon_pT");
  TH1F *wbos = (TH1F*)infile[2].Get("Bare_Muon_pT");
  TH1F *zbos = (TH1F*)infile[3].Get("Bare_Muon_pT");
  TH1F *gamma = (TH1F*)infile[4].Get("Bare_Muon_pT");
  TH1F *bottom2 = (TH1F*)infile[5].Get("Bare_Muon_pT");
  TH1F *bottom20 = (TH1F*)infile[6].Get("Bare_Muon_pT");
  TH1F *bottom40 = (TH1F*)infile[7].Get("Bare_Muon_pT");
  TH1F *bottom60 = (TH1F*)infile[8].Get("Bare_Muon_pT");
  TH1F *bottom120 = (TH1F*)infile[9].Get("Bare_Muon_pT");
  TH1F *charm2 = (TH1F*)infile[10].Get("Bare_Muon_pT");
  TH1F *charm10 = (TH1F*)infile[11].Get("Bare_Muon_pT");
  TH1F *charm20 = (TH1F*)infile[12].Get("Bare_Muon_pT");
  TH1F *charm40 = (TH1F*)infile[13].Get("Bare_Muon_pT");
  TH1F *charm60 = (TH1F*)infile[14].Get("Bare_Muon_pT");
  TH1F *charm120 = (TH1F*)infile[15].Get("Bare_Muon_pT");
  TH1F *bb2 = (TH1F*)infile[16].Get("Bare_Muon_pT");
  TH1F *bb20 = (TH1F*)infile[17].Get("Bare_Muon_pT");
  TH1F *bb40 = (TH1F*)infile[18].Get("Bare_Muon_pT");
  TH1F *bb60 = (TH1F*)infile[19].Get("Bare_Muon_pT");
  TH1F *bb120 = (TH1F*)infile[20].Get("Bare_Muon_pT");
  TH1F *bb200 = (TH1F*)infile[21].Get("Bare_Muon_pT");
  TH1F *cc2 = (TH1F*)infile[22].Get("Bare_Muon_pT");
  TH1F *cc20 = (TH1F*)infile[23].Get("Bare_Muon_pT");
  TH1F *cc40 = (TH1F*)infile[24].Get("Bare_Muon_pT");
  TH1F *cc60 = (TH1F*)infile[25].Get("Bare_Muon_pT");
  TH1F *cc120 = (TH1F*)infile[26].Get("Bare_Muon_pT");
  TH1F *cc200 = (TH1F*)infile[27].Get("Bare_Muon_pT");
  TH1F *ttbar = new TH1F("ttbar", "pT", 60, 0, 120);
  TH1F *bottomonium = new TH1F("bottomonium", "pT", 60, 0, 120);
  TH1F *charmonium = new TH1F("charmonium", "pT", 60, 0, 120);
  TH1F *bbbar = new TH1F("bbbar", "pT", 60, 0, 120);
  TH1F *ccbar = new TH1F("ccbar", "pT", 60, 0, 120);
  TH1F *sum = new TH1F("SumpT", "pT", 60, 0, 120);

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

  TCanvas *c1 = new TCanvas("c1","c1", 800, 600);
  c1->cd();

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  bottomonium->SetTitle("Bottomonium Muon Bare pT");
  bottomonium->SetTitleFont(132, "t");

  bottomonium->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  bottomonium->GetYaxis()->SetTitle("N_{events}");
  bottomonium->GetYaxis()->SetRangeUser(1,10000000000);
  bottomonium->GetXaxis()->SetRangeUser(0,120);
  
  bottomonium->GetXaxis()->SetTitleFont(132);
  bottomonium->GetYaxis()->SetTitleFont(132);

  bottomonium->SetLineColor(46);
  bottomonium->SetLineWidth(3);
  bottomonium->Draw("HIST");

  bottom2->SetLineColor(42);
  bottom2->SetLineWidth(3);
  bottom2->Draw("HIST SAME");

  bottom20->SetLineColor(41);
  bottom20->SetLineWidth(3);
  bottom20->Draw("HIST SAME");

  bottom40->SetLineColor(30);
  bottom40->SetLineWidth(3);
  bottom40->Draw("HIST SAME");

  bottom60->SetLineColor(38);
  bottom60->SetLineWidth(3);
  bottom60->Draw("HIST SAME");

  bottom120->SetLineColor(40);
  bottom120->SetLineWidth(3);
  bottom120->Draw("HIST SAME");

  auto leg1 = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg1->AddEntry(bottomonium, "All Bottomonium", "f");
  leg1->AddEntry(bottom2, "2-20 GeV","f");
  leg1->AddEntry(bottom20, "20-40 GeV","f");
  leg1->AddEntry(bottom40, "40-60 GeV", "f");
  leg1->AddEntry(bottom60, "60-120 GeV", "f");
  leg1->AddEntry(bottom120, "120+ GeV", "f");
  leg1->SetTextSize(0.035);
  leg1->Draw();

  c1->SetLogy();
  c1->Print("./plots/chop-comp/bottomonium.png");
  c1->Close();

  TCanvas *c2 = new TCanvas("c2","c2", 800, 600);
  c2->cd();

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  charmonium->SetTitle("Charmonium Muon Bare pT");
  charmonium->SetTitleFont(132, "t");

  charmonium->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  charmonium->GetYaxis()->SetTitle("N_{events}");
  charmonium->GetYaxis()->SetRangeUser(1,10000000000);
  charmonium->GetXaxis()->SetRangeUser(0,120);

  charmonium->GetXaxis()->SetTitleFont(132);
  charmonium->GetYaxis()->SetTitleFont(132);

  charmonium->SetLineColor(46);
  charmonium->SetLineWidth(3);
  charmonium->Draw("HIST");

  charm2->SetLineColor(42);
  charm2->SetLineWidth(3);
  charm2->Draw("HIST SAME");

  charm10->SetLineColor(41);
  charm10->SetLineWidth(3);
  charm10->Draw("HIST SAME");

  charm20->SetLineColor(30);
  charm20->SetLineWidth(3);
  charm20->Draw("HIST SAME");

  charm40->SetLineColor(38);
  charm40->SetLineWidth(3);
  charm40->Draw("HIST SAME");

  charm60->SetLineColor(40);
  charm60->SetLineWidth(3);
  charm60->Draw("HIST SAME");

  charm120->SetLineColor(kRed-9);
  charm120->SetLineWidth(3);
  charm120->Draw("HIST SAME");

  auto leg2 = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg2->AddEntry(charmonium, "All Charmonium", "f");
  leg2->AddEntry(charm2, "2-10 GeV","f");
  leg2->AddEntry(charm10, "10-20 GeV","f");
  leg2->AddEntry(charm20, "20-40 GeV","f");
  leg2->AddEntry(charm40, "40-60 GeV", "f");
  leg2->AddEntry(charm60, "60-120 GeV", "f");
  leg2->AddEntry(charm120, "120 GeV+", "f");
  leg2->SetTextSize(0.035);
  leg2->Draw();

  c2->SetLogy();
  c2->Print("./plots/chop-comp/charmonium.png");
  c2->Close();

  TCanvas *c3 = new TCanvas("c3","c3", 800, 600);
  c3->cd();

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  bbbar->SetTitle("bbbar Muon Bare pT");
  bbbar->SetTitleFont(132, "t");

  bbbar->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  bbbar->GetYaxis()->SetTitle("N_{events}");
  bbbar->GetYaxis()->SetRangeUser(1,10000000000);
  bbbar->GetXaxis()->SetRangeUser(0,120);

  bbbar->GetXaxis()->SetTitleFont(132);
  bbbar->GetYaxis()->SetTitleFont(132);

  bbbar->SetLineColor(46);
  bbbar->SetLineWidth(3);
  bbbar->Draw("HIST");

  bb2->SetLineColor(42);
  bb2->SetLineWidth(3);
  bb2->Draw("HIST SAME");

  bb20->SetLineColor(41);
  bb20->SetLineWidth(3);
  bb20->Draw("HIST SAME");

  bb40->SetLineColor(30);
  bb40->SetLineWidth(3);
  bb40->Draw("HIST SAME");

  bb60->SetLineColor(38);
  bb60->SetLineWidth(3);
  bb60->Draw("HIST SAME");

  bb120->SetLineColor(40);
  bb120->SetLineWidth(3);
  bb120->Draw("HIST SAME");

  bb200->SetLineColor(kRed-9);
  bb200->SetLineWidth(3);
  bb200->Draw("HIST SAME");

  auto leg3 = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg3->AddEntry(bbbar, "All bbbar", "f");
  leg3->AddEntry(bb2, "2-20 GeV","f");
  leg3->AddEntry(bb20, "20-40 GeV","f");
  leg3->AddEntry(bb40, "40-60 GeV", "f");
  leg3->AddEntry(bb60, "60-120 GeV", "f");
  leg3->AddEntry(bb120, "120-200 GeV", "f");
  leg3->AddEntry(bb200, "200+ GeV", "f");
  leg3->SetTextSize(0.035);
  leg3->Draw();

  c3->SetLogy();
  c3->Print("./plots/chop-comp/bbbar.png");
  c3->Close();

  TCanvas *c4 = new TCanvas("c4","c4", 800, 600);
  c4->cd();

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  ccbar->SetTitle("ccbar Muon Bare pT");
  ccbar->SetTitleFont(132, "t");

  ccbar->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  ccbar->GetYaxis()->SetTitle("N_{events}");
  ccbar->GetYaxis()->SetRangeUser(1,10000000000);
  ccbar->GetXaxis()->SetRangeUser(0,120);
  
  ccbar->GetXaxis()->SetTitleFont(132);
  ccbar->GetYaxis()->SetTitleFont(132);

  ccbar->SetLineColor(46);
  ccbar->SetLineWidth(3);
  ccbar->Draw("HIST");

  cc2->SetLineColor(42);
  cc2->SetLineWidth(3);
  cc2->Draw("HIST SAME");
  
  cc20->SetLineColor(41);
  cc20->SetLineWidth(3);
  cc20->Draw("HIST SAME");

  cc40->SetLineColor(30);
  cc40->SetLineWidth(3);
  cc40->Draw("HIST SAME");

  cc60->SetLineColor(38);
  cc60->SetLineWidth(3);
  cc60->Draw("HIST SAME");

  cc120->SetLineColor(40);
  cc120->SetLineWidth(3);
  cc120->Draw("HIST SAME");

  cc200->SetLineColor(kRed-9);
  cc200->SetLineWidth(3);
  cc200->Draw("HIST SAME");

  auto leg4 = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg4->AddEntry(ccbar, "All ccbar", "f");
  leg4->AddEntry(cc2, "2-20 GeV","f");
  leg4->AddEntry(cc20, "20-40 GeV","f");
  leg4->AddEntry(cc40, "40-60 GeV", "f");
  leg4->AddEntry(cc60, "60-120 GeV", "f");
  leg4->AddEntry(cc120, "120-200 GeV", "f");
  leg4->AddEntry(cc200, "200+ GeV", "f");
  leg4->SetTextSize(0.035);
  leg4->Draw();

  c4->SetLogy();
  c4->Print("./plots/chop-comp/ccbar.png");
  c4->Close();
}