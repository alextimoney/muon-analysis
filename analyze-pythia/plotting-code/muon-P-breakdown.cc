// FinalCuts.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile[24] = {"histograms/run1/ttbar-dilep.root", "histograms/run1/ttbar-semilep.root",
                        "histograms/run1/wbos.root", "histograms/run1/zbos.root", "histograms/run1/gamma.root", 
                        "histograms/pTmin/bottom2.root", "histograms/pTmin/bottom40.root", "histograms/pTmin/bottom60.root", "histograms/pTmin/bottom120.root",
                        "histograms/pTmin/charm2.root", "histograms/pTmin/charm20.root", "histograms/pTmin/charm40.root", "histograms/pTmin/charm60.root", "histograms/pTmin/charm120.root", 
                        "histograms/pTmin/bb2.root", "histograms/pTmin/bb40.root", "histograms/pTmin/bb60.root", "histograms/pTmin/bb120.root", "histograms/pTmin/bb200.root", 
                        "histograms/pTmin/cc2.root", "histograms/pTmin/cc40.root", "histograms/pTmin/cc60.root", "histograms/pTmin/cc120.root", "histograms/pTmin/cc200.root"};
  
  // Get the histograms
  // ==================

  TH1F *ttbar_di = (TH1F*)infile[0].Get("Muon_P");
  TH1F *ttbar_semi = (TH1F*)infile[1].Get("Muon_P");
  TH1F *wbos = (TH1F*)infile[2].Get("Muon_P");
  TH1F *zbos = (TH1F*)infile[3].Get("Muon_P");
  TH1F *gamma = (TH1F*)infile[4].Get("Muon_P");
  TH1F *bottom2 = (TH1F*)infile[5].Get("Muon_P");
  TH1F *bottom40 = (TH1F*)infile[6].Get("Muon_P");
  TH1F *bottom60 = (TH1F*)infile[7].Get("Muon_P");
  TH1F *bottom120 = (TH1F*)infile[8].Get("Muon_P");
  TH1F *charm2 = (TH1F*)infile[9].Get("Muon_P");
  TH1F *charm20 = (TH1F*)infile[10].Get("Muon_P");
  TH1F *charm40 = (TH1F*)infile[11].Get("Muon_P");
  TH1F *charm60 = (TH1F*)infile[12].Get("Muon_P");
  TH1F *charm120 = (TH1F*)infile[13].Get("Muon_P");
  TH1F *bb2 = (TH1F*)infile[14].Get("Muon_P");
  TH1F *bb40 = (TH1F*)infile[15].Get("Muon_P");
  TH1F *bb60 = (TH1F*)infile[16].Get("Muon_P");
  TH1F *bb120 = (TH1F*)infile[17].Get("Muon_P");
  TH1F *bb200 = (TH1F*)infile[18].Get("Muon_P");
  TH1F *cc2 = (TH1F*)infile[19].Get("Muon_P");
  TH1F *cc40 = (TH1F*)infile[20].Get("Muon_P");
  TH1F *cc60 = (TH1F*)infile[21].Get("Muon_P");
  TH1F *cc120 = (TH1F*)infile[22].Get("Muon_P");
  TH1F *cc200 = (TH1F*)infile[23].Get("Muon_P");
  TH1F *ttbar = new TH1F("ttbar", "pT", 60, 0, 120);
  TH1F *bottomonium = new TH1F("bottomonium", "pT", 60, 0, 120);
  TH1F *charmonium = new TH1F("charmonium", "pT", 60, 0, 120);
  TH1F *bbbar = new TH1F("bbbar", "pT", 60, 0, 120);
  TH1F *ccbar = new TH1F("ccbar", "pT", 60, 0, 120);
  TH1F *sum = new TH1F("SumpT", "pT", 60, 0, 120);

  bottomonium->Add(bottom2);
  bottomonium->Add(bottom40);
  bottomonium->Add(bottom60);
  bottomonium->Add(bottom120);

  charmonium->Add(charm2);
  charmonium->Add(charm20);
  charmonium->Add(charm40);
  charmonium->Add(charm60);
  charmonium->Add(charm120);

  ccbar->Add(cc2);
  ccbar->Add(cc40);
  ccbar->Add(cc60);
  ccbar->Add(cc120);
  ccbar->Add(cc200);

  bbbar->Add(bb2);
  bbbar->Add(bb40);
  bbbar->Add(bb60);
  bbbar->Add(bb120);
  bbbar->Add(bb200);

  TCanvas *c1 = new TCanvas("c1","c1", 800, 600);
  c1->cd();

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  bottomonium->SetTitle("Bottomonium Muon Bare P");
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

  bottom40->SetLineColor(41);
  bottom40->SetLineWidth(3);
  bottom40->Draw("HIST SAME");

  bottom60->SetLineColor(30);
  bottom60->SetLineWidth(3);
  bottom60->Draw("HIST SAME");

  bottom120->SetLineColor(38);
  bottom120->SetLineWidth(3);
  bottom120->Draw("HIST SAME");

  auto leg1 = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg1->AddEntry(bottomonium, "All Bottomonium", "f");
  leg1->AddEntry(bottom2, "2-40 GeV","f");
  leg1->AddEntry(bottom40, "40-60 GeV", "f");
  leg1->AddEntry(bottom60, "60-120 GeV", "f");
  leg1->AddEntry(bottom120, "120+ GeV", "f");
  leg1->SetTextSize(0.035);
  leg1->Draw();

  c1->SetLogy();
  c1->Print("./plots/chop-comp/muon-P/bottomonium.png");
  c1->Close();

  TCanvas *c2 = new TCanvas("c2","c2", 800, 600);
  c2->cd();

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  charmonium->SetTitle("Charmonium Muon Bare P");
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

  charm20->SetLineColor(41);
  charm20->SetLineWidth(3);
  charm20->Draw("HIST SAME");

  charm40->SetLineColor(30);
  charm40->SetLineWidth(3);
  charm40->Draw("HIST SAME");

  charm60->SetLineColor(38);
  charm60->SetLineWidth(3);
  charm60->Draw("HIST SAME");

  charm120->SetLineColor(40);
  charm120->SetLineWidth(3);
  charm120->Draw("HIST SAME");

  auto leg2 = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg2->AddEntry(charmonium, "All Charmonium", "f");
  leg2->AddEntry(charm2, "2-20 GeV","f");
  leg2->AddEntry(charm20, "20-40 GeV","f");
  leg2->AddEntry(charm40, "40-60 GeV", "f");
  leg2->AddEntry(charm60, "60-120 GeV", "f");
  leg2->AddEntry(charm120, "120 GeV+", "f");
  leg2->SetTextSize(0.035);
  leg2->Draw();

  c2->SetLogy();
  c2->Print("./plots/chop-comp/muon-P/charmonium.png");
  c2->Close();

  TCanvas *c3 = new TCanvas("c3","c3", 800, 600);
  c3->cd();

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  bbbar->SetTitle("bbbar Muon Bare P");
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

  bb40->SetLineColor(41);
  bb40->SetLineWidth(3);
  bb40->Draw("HIST SAME");

  bb60->SetLineColor(30);
  bb60->SetLineWidth(3);
  bb60->Draw("HIST SAME");

  bb120->SetLineColor(38);
  bb120->SetLineWidth(3);
  bb120->Draw("HIST SAME");

  bb200->SetLineColor(40);
  bb200->SetLineWidth(3);
  bb200->Draw("HIST SAME");

  auto leg3 = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg3->AddEntry(bbbar, "All bbbar", "f");
  leg3->AddEntry(bb2, "2-40 GeV","f");
  leg3->AddEntry(bb40, "40-60 GeV", "f");
  leg3->AddEntry(bb60, "60-120 GeV", "f");
  leg3->AddEntry(bb120, "120-200 GeV", "f");
  leg3->AddEntry(bb200, "200+ GeV", "f");
  leg3->SetTextSize(0.035);
  leg3->Draw();

  c3->SetLogy();
  c3->Print("./plots/chop-comp/muon-P/bbbar.png");
  c3->Close();

  TCanvas *c4 = new TCanvas("c4","c4", 800, 600);
  c4->cd();

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  ccbar->SetTitle("ccbar Muon Bare P");
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

  cc40->SetLineColor(41);
  cc40->SetLineWidth(3);
  cc40->Draw("HIST SAME");

  cc60->SetLineColor(30);
  cc60->SetLineWidth(3);
  cc60->Draw("HIST SAME");

  cc120->SetLineColor(38);
  cc120->SetLineWidth(3);
  cc120->Draw("HIST SAME");

  cc200->SetLineColor(40);
  cc200->SetLineWidth(3);
  cc200->Draw("HIST SAME");

  auto leg4 = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg4->AddEntry(ccbar, "All ccbar", "f");
  leg4->AddEntry(cc2, "2-40 GeV","f");
  leg4->AddEntry(cc40, "40-60 GeV", "f");
  leg4->AddEntry(cc60, "60-120 GeV", "f");
  leg4->AddEntry(cc120, "120-200 GeV", "f");
  leg4->AddEntry(cc200, "200+ GeV", "f");
  leg4->SetTextSize(0.035);
  leg4->Draw();

  c4->SetLogy();
  c4->Print("./plots/chop-comp/muon-P/ccbar.png");
  c4->Close();
}