#define mClass_cxx
#include "mClass.h"
#include <TH2.h>
#include <string> // for string and to_string()
#include <TStyle.h>
#include <TCanvas.h>

void mClass::Loop(int samplen)
{
   string outfile = "mtree_out/4510163/mtree_out_test_" + to_string(samplen) + ".root";
   const char * out = outfile.c_str();
   TFile outputFile(out,"RECREATE");
   // TFile *outputFile = TFile::Open("mtree_out/mtree_out_test.root", "recreate");
   // TFile *outputFile = new TFile("mtree_out/mtree_out_0pt_cut.root","RECREATE");
   // TFile *outputFile = new TFile("mtree_out/mtree_out_nocut.root","RECREATE");

   double muon_pt_cut = 0.;


   TH2F *etaphi_hist = new TH2F("etaphi_hist","eta vs phi",60,-3,3,60,-3,3);

   TH2F *etaphi_innerBothHits_hist   = new TH2F("etaphi_innerBothHits_hist","eta phi for inner small&large hits > 1",60,-3,3,60,-3.15,3.15);
   TH2F *etaphi_middleBothHits_hist   = new TH2F("etaphi_middleBothHits_hist","eta phi for middle small&large hits > 1",60,-3,3,60,-3.15,3.15);
   TH2F *etaphi_outerBothHits_hist   = new TH2F("etaphi_outerBothHits_hist","eta for outer small&large hits > 1",60,-3,3,60,-3.15,3.15);

   TH2F *etaphi_innerSmallHits_hist   = new TH2F("etaphi_innerSmallHits_hist","Inner small chambers eta phi",60,-3,3,60,-3.15,3.15);
   TH2F *etaphi_middleSmallHits_hist   = new TH2F("etaphi_middleSmallHits_hist","Middle small chambers eta phi",60,-3,3,60,-3.15,3.15);
   TH2F *etaphi_outerSmallHits_hist   = new TH2F("etaphi_outerSmallHits_hist","Outer small chambers eta phi",60,-3,3,60,-3.15,3.15);

   TH2F *etaphi_innerLargeHits_hist   = new TH2F("etaphi_innerLargeHits_hist","Inner large chambers eta phi",60,-3,3,60,-3.15,3.15);
   TH2F *etaphi_middleLargeHits_hist   = new TH2F("etaphi_middleLargeHits_hist","Middle large chambers eta phi",60,-3,3,60,-3.15,3.15);
   TH2F *etaphi_outerLargeHits_hist   = new TH2F("etaphi_outerLargeHits_hist","Outer large chambers eta phi",60,-3,3,60,-3.15,3.15);

   TH1F *muon_p_hist   = new TH1F("muon_p_hist","muon momentum",120,0,120000);
   TH1F *muon_p_HLT5_hist   = new TH1F("muon_p_HLT5_hist","muon momentum for HLT pt_8",120,0,120000);
   TH1F *muon_p_HLT10_hist   = new TH1F("muon_p_HLT10_hist","muon momentum for HLT pt_10",120,0,120000);
   TH1F *muon_p_HLT20_hist   = new TH1F("muon_p_HLT20_hist","muon momentum for HLT pt_20",120,0,120000);

   // TH1F *muon_p_selection_hist   = new TH1F("muon_p_hist","muon momentum",60,0,60000);
   // TH1F *muon_p_HLT5_selection_hist   = new TH1F("muon_p_HLT5_hist","muon momentum for HLT pt_8",60,0,60000);
   // TH1F *muon_p_HLT10_selection_hist   = new TH1F("muon_p_HLT10_hist","muon momentum for HLT pt_10",60,0,60000);
   // TH1F *muon_p_HLT20_selection_hist   = new TH1F("muon_p_HLT20_hist","muon momentum for HLT pt_20",60,0,60000);


   // trigger hists
   TH1F *L1MU20VFC_hist = new TH1F("L1MU20VFC_hist","L1MU20VFC and cumulative muon pt",8,0,8);
   TH1F *L1MU14FCH_hist = new TH1F("L1MU14FCH_hist","Trigger pass rate for L1MU14FCH",2,0,2);
   TH1F *lead_muon_cumulative_pt_hist = new TH1F("lead_muon_cumulative_pt_hist","Cumulative lead muon pt for each trigger level",7, 0, 7);
   TH1F *muon_pt_mu5_hist   = new TH1F("muon_pt_mu5_hist","muon pt for mu5 trigger",120,0,120000);
   TH1F *muon_pt_mu8_hist   = new TH1F("muon_pt_mu8_hist","muon pt for mu8 trigger",120,0,120000);
   TH1F *muon_pt_mu10_hist   = new TH1F("muon_pt_mu10_hist","muon pt for mu10 trigger",120,0,120000);
   TH1F *muon_pt_mu20_hist   = new TH1F("muon_pt_mu20_hist","muon pt for mu20 trigger",120,0,120000);
   TH1F *muon_pt_mu25_hist   = new TH1F("muon_pt_mu25_hist","muon pt for mu25 trigger",120,0,120000);
   TH1F *muon_pt_mu30_hist   = new TH1F("muon_pt_mu30_hist","muon pt for mu30 trigger",120,0,120000);
   TH1F *muon_pt_mu50_hist   = new TH1F("muon_pt_mu50_hist","muon pt for mu50 trigger",120,0,120000);


   // initialise some variables 

   int run_number;
   int event_number;
   int event_counter = 0;
   double lead_muon_pt = 0.0;
   int thesh_5 = 0;
   int thesh_8 = 0;
   int thesh_10 = 0;
   int thesh_20 = 0;
   int thesh_25 = 0;
   int thesh_30 = 0;
   int thesh_50 = 0;

   double missing_et = 0;





   if (fChain == 0) return;

   int nentries = fChain->GetEntriesFast();
   // int nentries = 200000;
   std::cout << "Looping over " << nentries << " events" << std::endl;


   int passed = 0;
   int failed = 0;

   int counter1 = 0;
   int counter2 = 0;
   int counter3 = 0;
   int counter4 = 0;

   
   for(int i=0; i<nentries; i++){
      fChain->GetEntry(i);

      if (i == 0) {
         run_number = mRunNumber;
         event_number = mEventNumber;
         std::cout << "Starting event number: " << event_number<<std::endl;
      }
      // // Putting this check here to make sure that event number doesnt fuck up when running over the full sample
      else if (mRunNumber != run_number) {
         std::cout << "run number not constant!!" << std::endl;
         return;
      }


      double muon_p = muon_pt*std::cosh(muon_eta);


      // Cuts



      bool pass_cuts = true;
      // pass_cuts = false;

      // Fit quality cuts
      if (msegmentChi2OverDoF > 10.) {
         // std::cout << "1" <<std::endl;
         pass_cuts = false;
      }




      if ((muon_innerSmallHits < 1) && (muon_innerLargeHits < 1)) {
         // std::cout << "2" <<std::endl;
         pass_cuts = false;
      }
      if ((muon_middleSmallHits < 1) && (muon_middleLargeHits < 1)) {
         // std::cout << "3" <<std::endl;
         pass_cuts = false;
      }
      if ((muon_outerSmallHits < 1) && (muon_outerLargeHits < 1)) {
         // std::cout << "4" <<std::endl;
         pass_cuts = false;
      }


      // // high p
      // if ( muon_p < 40000. ) {
      //    // std::cout << "5" <<std::endl;
      //    pass_cuts = false;
      // }




      if (muon_numberOfPhiLayers < 0.) {
         // std::cout << "6" <<std::endl;
         pass_cuts = false;
      }

      if ( muon_pt < muon_pt_cut ) {
         // std::cout << "7" <<std::endl;
         pass_cuts = false;
      }
      if (muon_author != 1) {
         // std::cout << "8" <<std::endl;
         pass_cuts = false;
      }

      // pass_cuts = false;
      // pass_cuts = true; 




      // Fill hists

      if (pass_cuts == true) {passed++;}
      if (pass_cuts == false) {failed++;}

      if (pass_cuts) 
      {
         etaphi_hist->Fill(muon_eta,muon_phi);

         if ( (muon_innerSmallHits > 1) && (muon_innerLargeHits > 1) ) {
            etaphi_innerBothHits_hist->Fill(muon_eta,muon_phi);
         }
         if ( (muon_middleSmallHits > 1) && (muon_middleLargeHits > 1) ) {
            etaphi_middleBothHits_hist->Fill(muon_eta,muon_phi);
         }
         if ( (muon_outerSmallHits > 1) && (muon_outerLargeHits > 1) ) {
            etaphi_outerBothHits_hist->Fill(muon_eta,muon_phi);
         }

         int hit_num = 1;
         if ( muon_innerSmallHits > hit_num ) {
            etaphi_innerSmallHits_hist->Fill(muon_eta,muon_phi);
         }
         if ( (muon_middleSmallHits > hit_num) ) {
            etaphi_middleSmallHits_hist->Fill(muon_eta,muon_phi);
         }
         if ( (muon_outerSmallHits > hit_num) ) {
            etaphi_outerSmallHits_hist->Fill(muon_eta,muon_phi);
         }

         if ( (muon_innerLargeHits > hit_num) ) {
            etaphi_innerLargeHits_hist->Fill(muon_eta,muon_phi);
         }
         if ( (muon_middleLargeHits > hit_num) ) {
            etaphi_middleLargeHits_hist->Fill(muon_eta,muon_phi);
         }
         if ( (muon_outerLargeHits > hit_num) ) {
            etaphi_outerLargeHits_hist->Fill(muon_eta,muon_phi);
         }


         // Muon p
         // -------
         
         muon_p_hist->Fill(muon_p);
         counter1++;
         if (HLT_mu5_mucombTag_L1MU20VFC_Passed == true) {
            muon_p_HLT5_hist->Fill(muon_p);
         }
         if (HLT_mu10_mucombTag_L1MU20VFC_Passed == true) {
            muon_p_HLT10_hist->Fill(muon_p);
         }
         if (HLT_mu20_mucombTag_L1MU20VFC_Passed == true) {
            muon_p_HLT20_hist->Fill(muon_p);
         }


         // L1MU20VFC:
         // ---------
         if (HLT_mu5_mucombTag_L1MU20VFC_Passed == true) {
            L1MU20VFC_hist->AddBinContent(1);
            muon_pt_mu5_hist->Fill(muon_pt);
         }
         if (HLT_mu8_mucombTag_L1MU20VFC_Passed == true) {
            L1MU20VFC_hist->AddBinContent(2);
            muon_pt_mu8_hist->Fill(muon_pt);
         }
         if (HLT_mu10_mucombTag_L1MU20VFC_Passed == true) {
            L1MU20VFC_hist->AddBinContent(3);
            muon_pt_mu10_hist->Fill(muon_pt);
         }
         if (HLT_mu20_mucombTag_L1MU20VFC_Passed == true) {
            L1MU20VFC_hist->AddBinContent(4);
            muon_pt_mu20_hist->Fill(muon_pt);
         }
         if (HLT_mu25_mucombTag_L1MU20VFC_Passed == true) {
            L1MU20VFC_hist->AddBinContent(5);
            muon_pt_mu25_hist->Fill(muon_pt);
         }
         if (HLT_mu30_mucombTag_L1MU20VFC_Passed == true) {
            L1MU20VFC_hist->AddBinContent(6);
            muon_pt_mu30_hist->Fill(muon_pt);
         }
         if (HLT_mu50_mucombTag_L1MU20VFC_Passed == true) {
            L1MU20VFC_hist->AddBinContent(7);
            muon_pt_mu50_hist->Fill(muon_pt);
         }

         // L1MU14FCH:
         // ---------
         if (HLT_mu24_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed == true) {
            L1MU14FCH_hist->AddBinContent(1);
         }
         if (HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed == true) {
            L1MU14FCH_hist->AddBinContent(2);
         }


         // Set trigger threshold values
         // ----------------------------

         // If we have reached a new event we increment the lead muon variables for the previous event 
         if (mEventNumber != event_number) {
            event_counter++;

            if (pass_cuts) {
               if (lead_muon_pt >= 5000) {
                  thesh_5++;
               }
               if (lead_muon_pt >= 8000) {
                  thesh_8++;
               }
               if (lead_muon_pt >= 10000) {
                  thesh_10++;
               }
               if (lead_muon_pt >= 20000) {
                  thesh_20++;
               }
               if (lead_muon_pt >= 25000) {
                  thesh_25++;
               }
               if (lead_muon_pt >= 30000) {
                  thesh_30++;
               }
               if (lead_muon_pt >= 50000) {
                  thesh_50++;
               }
            }

            lead_muon_pt = 0.0;
            event_number = mEventNumber;
         }

         if (muon_pt > lead_muon_pt) {
            lead_muon_pt = muon_pt;
         }

      } // end cuts

   } // end event loop

   // comparing these numbers will give number of leading muons that didn't pass the 5mev trigger
   std::cout << "event number: " << event_number<<std::endl;
   std::cout << "event counter: " << event_counter<< std::endl;
   std::cout<< "sum thresh passed: " << thesh_5+thesh_8+thesh_10+thesh_20+thesh_25+thesh_30+thesh_50<<std::endl;

   std::cout << "Passed: " << passed << "   Failed: " << failed << std::endl;
   // std::cout << "1: " << counter1 << std::endl;
   // std::cout << "2: " << counter2 << std::endl;
   // std::cout << "3: " << counter3 << std::endl;
   // std::cout << "4: " << counter4 << std::endl;


   lead_muon_cumulative_pt_hist->SetBinContent(1, thesh_5);
   lead_muon_cumulative_pt_hist->SetBinContent(2, thesh_8);
   lead_muon_cumulative_pt_hist->SetBinContent(3, thesh_10);
   lead_muon_cumulative_pt_hist->SetBinContent(4, thesh_20);
   lead_muon_cumulative_pt_hist->SetBinContent(5, thesh_25);
   lead_muon_cumulative_pt_hist->SetBinContent(6, thesh_30);
   lead_muon_cumulative_pt_hist->SetBinContent(7, thesh_50);

   // Scale trigger by 1/nentries*100 to get a percentage of events that passed each trigger
   // 1.0 so that we get a double instead of zero
   // L1MU20VFC_hist->Scale(1.0/nentries*100.0);
   // L1MU14FCH_hist->Scale(1.0/nentries*100.0);

   // Normalised 
   // L1MU20VFC_hist->Scale(1/L1MU20VFC_hist->Integral());
   // L1MU14FCH_hist->Scale(1/L1MU14FCH_hist->Integral());
   // lead_muon_cumulative_pt_hist->Scale(1/lead_muon_cumulative_pt_hist->Integral());

   // Scaling muon_pt first bin to be same as trigger hist bin
   // double factor = L1MU20VFC_hist->GetBinContent(1)/lead_muon_cumulative_pt_hist->GetBinContent(1);
   // lead_muon_cumulative_pt_hist->Scale(factor);




   // etaphi_hist->Write();
   // etaphi_innerBothHits_hist->Write();
   // etaphi_middleBothHits_hist->Write();
   // etaphi_outerBothHits_hist->Write();
   // etaphi_innerSmallHits_hist->Write();
   // etaphi_middleSmallHits_hist->Write();
   // etaphi_outerSmallHits_hist->Write();
   // etaphi_innerLargeHits_hist->Write();
   // etaphi_middleLargeHits_hist->Write();
   // etaphi_outerLargeHits_hist->Write();
   // muon_p_hist->Write();
   L1MU20VFC_hist->Write();
   muon_pt_mu5_hist->Write();
   muon_p_HLT5_hist->Write();

   muon_pt_mu8_hist->Write();
   muon_pt_mu10_hist->Write();
   muon_pt_mu20_hist->Write();
   muon_pt_mu25_hist->Write();
   muon_pt_mu30_hist->Write();
   muon_pt_mu50_hist->Write();
   // lead_muon_cumulative_pt_hist->Write(); 




   // // Draw to canvas

   // TCanvas *c1 = new TCanvas("c1","eta phi",800,600);
   // TCanvas *c2 = new TCanvas("c2","eta phi small&large hits",800,600);
   // TCanvas *c3 = new TCanvas("c3","eta phi small hits",800,600);
   // TCanvas *c4 = new TCanvas("c4","eta phi large hits",800,600);
   // TCanvas *c5 = new TCanvas("c5","L1MU20VFC",800,600);
   // TCanvas *c6 = new TCanvas("c6","L1MU14FCH",800,600);
   // TCanvas *c7 = new TCanvas("c7","muon pt",800,600);
   // TCanvas *c8 = new TCanvas("c8","muon pt normalised",800,600);

   // c2->Divide(2,2);
   // c3->Divide(2,2);
   // c4->Divide(2,2);
   // gStyle->SetOptStat(0);
   // // gStyle->SetOptStat(11);


   // c1->cd();
   // etaphi_hist->Draw("COLZ");
   // etaphi_hist->GetXaxis()->SetTitle("eta");
   // etaphi_hist->GetYaxis()->SetTitle("phi");


   // c2->cd(1);
   // etaphi_innerBothHits_hist->Draw("COLZ");
   // etaphi_innerBothHits_hist->GetXaxis()->SetTitle("eta");
   // etaphi_innerBothHits_hist->GetYaxis()->SetTitle("phi");

   // c2->cd(2);
   // etaphi_middleBothHits_hist->Draw("COLZ");
   // etaphi_middleBothHits_hist->GetXaxis()->SetTitle("eta");
   // etaphi_middleBothHits_hist->GetYaxis()->SetTitle("phi");

   // c2->cd(3);
   // etaphi_outerBothHits_hist->Draw("COLZ");
   // etaphi_outerBothHits_hist->GetXaxis()->SetTitle("eta");
   // etaphi_outerBothHits_hist->GetYaxis()->SetTitle("phi");



   // c3->cd(1);
   // etaphi_innerSmallHits_hist->Draw("COLZ");
   // etaphi_innerSmallHits_hist->GetXaxis()->SetTitle("eta");
   // etaphi_innerSmallHits_hist->GetYaxis()->SetTitle("phi");

   // c3->cd(2);
   // etaphi_middleSmallHits_hist->Draw("COLZ");
   // etaphi_middleSmallHits_hist->GetXaxis()->SetTitle("eta");
   // etaphi_middleSmallHits_hist->GetYaxis()->SetTitle("phi");

   // c3->cd(3);
   // etaphi_outerSmallHits_hist->Draw("COLZ");
   // etaphi_outerSmallHits_hist->GetXaxis()->SetTitle("eta");
   // etaphi_outerSmallHits_hist->GetYaxis()->SetTitle("phi");



   // c4->cd(1);
   // etaphi_innerLargeHits_hist->Draw("COLZ");
   // etaphi_innerLargeHits_hist->GetXaxis()->SetTitle("eta");
   // etaphi_innerLargeHits_hist->GetYaxis()->SetTitle("phi");

   // c4->cd(2);
   // etaphi_middleLargeHits_hist->Draw("COLZ");
   // etaphi_middleLargeHits_hist->GetXaxis()->SetTitle("eta");
   // etaphi_middleLargeHits_hist->GetYaxis()->SetTitle("phi");

   // c4->cd(3);
   // etaphi_outerLargeHits_hist->Draw("COLZ");
   // etaphi_outerLargeHits_hist->GetXaxis()->SetTitle("eta");
   // etaphi_outerLargeHits_hist->GetYaxis()->SetTitle("phi");

   // c5->cd();
   // L1MU20VFC_hist->Draw("HIST");
   // L1MU20VFC_hist->GetXaxis()->SetBinLabel(1,"HLT_mu5");
   // L1MU20VFC_hist->GetXaxis()->SetBinLabel(2,"HLT_mu8");
   // L1MU20VFC_hist->GetXaxis()->SetBinLabel(3,"HLT_mu10");
   // L1MU20VFC_hist->GetXaxis()->SetBinLabel(4,"HLT_mu20");
   // L1MU20VFC_hist->GetXaxis()->SetBinLabel(5,"HLT_mu25");
   // L1MU20VFC_hist->GetXaxis()->SetBinLabel(6,"HLT_mu30");
   // L1MU20VFC_hist->GetXaxis()->SetBinLabel(7,"HLT_mu50");
   // L1MU20VFC_hist->GetXaxis()->SetTitle("Trigger thresholds");
   // // L1MU20VFC_hist->GetYaxis()->SetTitle("Percentage of events passing given trigger");
   // L1MU20VFC_hist->GetYaxis()->SetTitle("Counts");

   // // c5->SetLogy();
   // // c5->Print("./mtree_out/L1MU20VFC.png");

   // // lead_muon_cumulative_pt_hist->SetLineColor(kRed);
   // // lead_muon_cumulative_pt_hist->Draw("SAME");

   // auto legend = new TLegend(0.65,0.7,0.85,0.8);
   // legend->AddEntry(L1MU20VFC_hist,"Trigger pass rate per muon");
   // // legend->AddEntry(lead_muon_cumulative_pt_hist,"Number of muons passing pT threshold");
   // legend->Draw();

   // c6->cd();
   // L1MU14FCH_hist->Draw("HIST");
   // L1MU14FCH_hist->GetXaxis()->SetBinLabel(1,"HLT_mu24");
   // L1MU14FCH_hist->GetXaxis()->SetBinLabel(2,"HLT_mu28");
   // L1MU14FCH_hist->GetXaxis()->SetTitle("Triggers");
   // L1MU14FCH_hist->GetYaxis()->SetTitle("Percentage of events passing given trigger");




   // c7->cd();
   // muon_p_hist->SetLineColor(kBlack);
   // muon_p_HLT5_hist->SetLineColor(kRed);
   // muon_p_HLT10_hist->SetLineColor(kBlue);
   // muon_p_HLT20_hist->SetLineColor(kGreen);

   // muon_p_hist->SetTitle("Muon momentum at different HLT chains");   
   // muon_p_hist->GetXaxis()->SetTitle("Muon p (MeV)");
   // muon_p_hist->GetYaxis()->SetTitle("Counts");
   // muon_p_hist->Draw("HIST");
   // muon_p_HLT5_hist->Draw("HIST SAME");
   // muon_p_HLT10_hist->Draw("HIST SAME");
   // muon_p_HLT20_hist->Draw("HIST SAME");

   // auto legend2 = new TLegend(0.65,0.7,0.85,0.8);
   // legend2->AddEntry(muon_p_hist,"Muon p: HLT_mu5");
   // legend2->AddEntry(muon_p_HLT5_hist,"Muon p: HLT_mu8");
   // legend2->AddEntry(muon_p_HLT10_hist,"Muon p: HLT_mu10");
   // legend2->AddEntry(muon_p_HLT20_hist,"Muon p: HLT_mu20");
   // legend2->Draw();


   // c8->cd();

   // TH1F *muon_p_hist_clone = (TH1F*)muon_p_hist->Clone("sag0_clone");
   // TH1F *muon_p_HLT5_hist_clone = (TH1F*)muon_p_HLT5_hist->Clone("sag5_clone");
   // TH1F *muon_p_HLT10_hist_clone = (TH1F*)muon_p_HLT10_hist->Clone("sag10_clone");
   // TH1F *muon_p_HLT20_hist_clone = (TH1F*)muon_p_HLT20_hist->Clone("sag15_clone");

   // muon_p_hist_clone->SetLineColor(kBlack);
   // muon_p_HLT5_hist_clone->SetLineColor(kRed);
   // muon_p_HLT10_hist_clone->SetLineColor(kBlue);
   // muon_p_HLT20_hist_clone->SetLineColor(kGreen);


   // muon_p_hist_clone->Scale(1/muon_p_hist_clone->Integral());
   // muon_p_HLT5_hist_clone->Scale(1/muon_p_HLT5_hist_clone->Integral());
   // muon_p_HLT10_hist_clone->Scale(1/muon_p_HLT10_hist_clone->Integral());
   // muon_p_HLT20_hist_clone->Scale(1/muon_p_HLT20_hist_clone->Integral());

   // muon_p_hist_clone->SetTitle("Muon momentum at different HLT chains: Normalised");   
   // muon_p_hist_clone->GetXaxis()->SetTitle("Muon p (MeV)");
   // muon_p_hist_clone->SetMaximum(muon_p_hist_clone->GetMaximum()*1.2);

   // muon_p_hist_clone->Draw("HIST");
   // muon_p_HLT5_hist_clone->Draw("HIST SAME");
   // muon_p_HLT10_hist_clone->Draw("HIST SAME");
   // muon_p_HLT20_hist_clone->Draw("HIST SAME");


   // auto legend3 = new TLegend(0.65,0.7,0.85,0.8);
   // legend3->AddEntry(muon_p_hist_clone,"Muon p: HLT_mu5");
   // legend3->AddEntry(muon_p_HLT5_hist_clone,"Muon p: HLT_mu8");
   // legend3->AddEntry(muon_p_HLT10_hist_clone,"Muon p: HLT_mu10");
   // legend3->AddEntry(muon_p_HLT20_hist_clone,"Muon p: HLT_mu20");
   // legend3->Draw();

   // c1->Close();
   // c2->Close();
   // c3->Close();
   // c4->Close();
   // c5->Close();
   // c6->Close();
   // c7->Close();
   // c8->Close();
}
