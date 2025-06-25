// FinalCuts.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile[28] = {"$PWD/histograms/jets/ttbar-dilep.root", "$PWD/histograms/jets/ttbar-semilep.root",
                      "$PWD/histograms/jets/wbos.root", "$PWD/histograms/jets/zbos.root", "$PWD/histograms/jets/gamma.root", 
                      "$PWD/histograms/jets/bottom2.root", "$PWD/histograms/jets/bottom20.root", "$PWD/histograms/jets/bottom40.root", "$PWD/histograms/jets/bottom60.root", "$PWD/histograms/jets/bottom120.root",
                      "$PWD/histograms/jets/charm2.root", "$PWD/histograms/jets/charm10.root","$PWD/histograms/jets/charm20.root", "$PWD/histograms/jets/charm40.root", "$PWD/histograms/jets/charm60.root", "$PWD/histograms/jets/charm120.root",
                      "$PWD/histograms/jets/bb2.root", "$PWD/histograms/jets/bb20.root","$PWD/histograms/jets/bb40.root", "$PWD/histograms/jets/bb60.root", "$PWD/histograms/jets/bb120.root","$PWD/histograms/jets/bb200.root", 
                      "$PWD/histograms/jets/cc2.root", "$PWD/histograms/jets/cc40.root", "$PWD/histograms/jets/cc40.root", "$PWD/histograms/jets/cc60.root", "$PWD/histograms/jets/cc120.root", "$PWD/histograms/jets/cc200.root"};
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

  ttbar->Add(ttbar_di);
  ttbar->Add(ttbar_semi);

  sum->Add(bottomonium);
  sum->Add(charmonium);
  sum->Add(bbbar);
  sum->Add(ccbar);
  sum->Add(ttbar);
  sum->Add(wbos);
  sum->Add(zbos);
  sum->Add(gamma);

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  sum->SetTitle("Muon Bare pT of Non-Jet Events");
  sum->SetTitleFont(132, "t");

  sum->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  sum->GetYaxis()->SetTitle("N_{events}");
  sum->GetYaxis()->SetRangeUser(1,100000000000);
  sum->GetXaxis()->SetRangeUser(0, 80);
  
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

  TLatex *lumilabel = new TLatex(0.69, 0.58, "luminosity: 100pb^(-1)");
  lumilabel->SetNDC();
  lumilabel->SetTextSize(0.03);
  lumilabel->SetTextAlign(22); // Center align
  lumilabel->SetTextFont(132);
  lumilabel->Draw();
  cx->Update();

  cx->SetLogy();
  cx->Print("./plots/no-jet-events.png");
  cx->Close();

}