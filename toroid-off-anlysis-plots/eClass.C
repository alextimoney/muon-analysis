#define eClass_cxx
#include "eClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void eClass::Loop()
{

   TH1F *L1MU20VFC_hist = new TH1F("L1MU20VFC_hist","L1MU20VFC and cumulative muon pt",8,0,8);
   TH1F *L1MU14FCH_hist = new TH1F("L1MU14FCH_hist","Trigger pass rate for L1MU14FCH",2,0,2);
   TH1F *lead_muon_cumulative_pt_hist = new TH1F("lead_muon_cumulative_pt_hist","Cumulative lead muon pt for each trigger level",7, 0, 7);
   TH1F *muon_pt_mu5_hist   = new TH1F("muon_pt_mu5_hist","muon pt for mu5 trigger",60,0,60000);
   TH1F *muon_pt_mu8_hist   = new TH1F("muon_pt_mu8_hist","muon pt for mu8 trigger",60,0,60000);
   TH1F *muon_pt_mu10_hist   = new TH1F("muon_pt_mu10_hist","muon pt for mu10 trigger",60,0,60000);
   TH1F *muon_pt_mu20_hist   = new TH1F("muon_pt_mu20_hist","muon pt for mu20 trigger",60,0,60000);
   TH1F *muon_pt_mu25_hist   = new TH1F("muon_pt_mu25_hist","muon pt for mu25 trigger",60,0,60000);
   TH1F *muon_pt_mu30_hist   = new TH1F("muon_pt_mu30_hist","muon pt for mu30 trigger",60,0,60000);
   TH1F *muon_pt_mu50_hist   = new TH1F("muon_pt_mu50_hist","muon pt for mu50 trigger",60,0,60000);


   if (fChain == 0) return;

   int nentries = fChain->GetEntriesFast();
   // int nentries = 200000;
   std::cout << "Looping over " << nentries << " events" << std::endl;

   for(int i=0; i<nentries; i++){
      fChain->GetEntry(i);



      // Fill hists

      // bool pass_cuts = false;
      bool pass_cuts = true;

      if (pass_cuts) 
      {
         // L1MU20VFC:
         // ---------
         if (HLT_mu5_mucombTag_L1MU20VFC_Passed == true) {
            L1MU20VFC_hist->AddBinContent(1);
         }
         if (HLT_mu8_mucombTag_L1MU20VFC_Passed == true) {
            L1MU20VFC_hist->AddBinContent(2);
         }
         if (HLT_mu10_mucombTag_L1MU20VFC_Passed == true) {
            L1MU20VFC_hist->AddBinContent(3);
         }
         if (HLT_mu20_mucombTag_L1MU20VFC_Passed == true) {
            L1MU20VFC_hist->AddBinContent(4);
         }
         if (HLT_mu25_mucombTag_L1MU20VFC_Passed == true) {
            L1MU20VFC_hist->AddBinContent(5);
         }
         if (HLT_mu30_mucombTag_L1MU20VFC_Passed == true) {
            L1MU20VFC_hist->AddBinContent(6);
         }
         if (HLT_mu50_mucombTag_L1MU20VFC_Passed == true) {
            L1MU20VFC_hist->AddBinContent(7);
         }

         // L1MU14FCH:
         // ---------
         if (HLT_mu24_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed == true) {
            L1MU14FCH_hist->AddBinContent(1);
         }
         if (HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed == true) {
            L1MU14FCH_hist->AddBinContent(2);
         }


      }


   }



   // I don't know what I'm doing
   double muon_pt;
   UInt_t mRunNumber;
   UInt_t mEventNumber;
   Float_t msegmentChi2OverDoF;
   UChar_t muon_numberOfPhiLayers;
   TFile *mfile = new TFile("/eos/user/j/jdegens/alignment/outputfiles/data_22_13p6TeV/outputfile.root");;
   TTree *mtree = (TTree*)mfile->Get("mtree");
   TBranch *muon_pt_branch = mtree->GetBranch("muon_pt");
   TBranch *mRunNumber_branch = mtree->GetBranch("mRunNumber");
   TBranch *mEventNumber_branch = mtree->GetBranch("mEventNumber");
   TBranch *msegmentChi2OverDoF_branch = mtree->GetBranch("msegmentChi2OverDoF");
   TBranch *muon_numberOfPhiLayers_branch = mtree->GetBranch("muon_numberOfPhiLayers");
   mtree->SetBranchAddress("muon_pt",&muon_pt, &muon_pt_branch);
   mtree->SetBranchAddress("mRunNumber",&mRunNumber, &mRunNumber_branch);
   mtree->SetBranchAddress("mEventNumber",&mEventNumber, &mEventNumber_branch);
   mtree->SetBranchAddress("msegmentChi2OverDoF",&msegmentChi2OverDoF, &msegmentChi2OverDoF_branch);
   mtree->SetBranchAddress("muon_numberOfPhiLayers",&muon_numberOfPhiLayers, &muon_numberOfPhiLayers_branch);

   int mentries=muon_pt_branch->GetEntries();
   double lead_muon_pt = 0.0;
   int run_number;
   int event_number;
   int thesh_5 = 0;
   int thesh_8 = 0;
   int thesh_10 = 0;
   int thesh_20 = 0;
   int thesh_25 = 0;
   int thesh_30 = 0;
   int thesh_50 = 0;
   int test_counter = 0;
   for(int i=0;i<mentries;i++) {
      muon_pt_branch->GetEntry(i);
      mRunNumber_branch->GetEntry(i);
      mEventNumber_branch->GetEntry(i);
      msegmentChi2OverDoF_branch->GetEntry(i);
      muon_numberOfPhiLayers_branch->GetEntry(i);

      if (i == 0) {
         run_number = mRunNumber;
         event_number = mEventNumber;
         std::cout << event_number<<std::endl;
      }
      // // Putting this check here to make sure that event number doesnt fuck up when running over the full sample
      else if (mRunNumber != run_number) {
         std::cout << "run number not constant!!" << std::endl;
         return;
      }
      
      // Cuts
      bool pass_cuts = true;
      // if (msegmentChi2OverDoF > 10.){
      //    pass_cuts = false;
      // }
      // if (muon_numberOfPhiLayers < 0.) {
      //    pass_cuts = false;
      // }
      // pass_cuts = true;


      if (mEventNumber != event_number) {
         test_counter++;

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

      // std::cout << "rune number: " << run_number << "       event number: "<< mEventNumber << std::endl;
      // std::cout << "lead muon pt: " << lead_muon_pt << std::endl;

   

      // if (lead_muon_pt >= 5000) {
      //    lead_muon_cumulative_pt_hist->AddBinContent(1);
      // }
      // if (lead_muon_pt >= 8000) {
      //    lead_muon_cumulative_pt_hist->AddBinContent(2);
      // }
      // if (lead_muon_pt >= 10000) {
      //    lead_muon_cumulative_pt_hist->AddBinContent(3);
      // }
      // if (lead_muon_pt >= 20000) {
      //    lead_muon_cumulative_pt_hist->AddBinContent(4);
      // }
      // if (lead_muon_pt >= 25000) {
      //    lead_muon_cumulative_pt_hist->AddBinContent(5);
      // }
      // if (lead_muon_pt >= 30000) {
      //    lead_muon_cumulative_pt_hist->AddBinContent(6);
      // }
      // if (lead_muon_pt >= 50000) {
      //    lead_muon_cumulative_pt_hist->AddBinContent(7);
      // }
   }
   std::cout << event_number<<std::endl;

   lead_muon_cumulative_pt_hist->SetBinContent(1, thesh_5);
   lead_muon_cumulative_pt_hist->SetBinContent(2, thesh_8);
   lead_muon_cumulative_pt_hist->SetBinContent(3, thesh_10);
   lead_muon_cumulative_pt_hist->SetBinContent(4, thesh_20);
   lead_muon_cumulative_pt_hist->SetBinContent(5, thesh_25);
   lead_muon_cumulative_pt_hist->SetBinContent(6, thesh_30);
   lead_muon_cumulative_pt_hist->SetBinContent(7, thesh_50);

   // comparing these two numbers will give number of leading muons that didn't pass the 5mev trigger
   std::cout << test_counter<< std::endl;
   std::cout<<thesh_5+thesh_8+thesh_10+thesh_20+thesh_25+thesh_30+thesh_50<<std::endl;

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


   TCanvas *c1 = new TCanvas("c1","L1MU20VFC",800,600);
   TCanvas *c2 = new TCanvas("c2","L1MU14FCH",800,600);
   gStyle->SetOptStat(0);


   c1->cd();
   L1MU20VFC_hist->Draw("HIST");
   L1MU20VFC_hist->GetXaxis()->SetBinLabel(1,"HLT_mu5");
   L1MU20VFC_hist->GetXaxis()->SetBinLabel(2,"HLT_mu8");
   L1MU20VFC_hist->GetXaxis()->SetBinLabel(3,"HLT_mu10");
   L1MU20VFC_hist->GetXaxis()->SetBinLabel(4,"HLT_mu20");
   L1MU20VFC_hist->GetXaxis()->SetBinLabel(5,"HLT_mu25");
   L1MU20VFC_hist->GetXaxis()->SetBinLabel(6,"HLT_mu30");
   L1MU20VFC_hist->GetXaxis()->SetBinLabel(7,"HLT_mu50");
   L1MU20VFC_hist->GetXaxis()->SetTitle("Triggers");
   // L1MU20VFC_hist->GetYaxis()->SetTitle("Percentage of events passing given trigger");
   L1MU20VFC_hist->GetYaxis()->SetTitle("Number of events passing given trigger");

   lead_muon_cumulative_pt_hist->SetLineColor(kRed);
   lead_muon_cumulative_pt_hist->Draw("SAME");

   auto legend = new TLegend(0.65,0.7,0.85,0.8);
   legend->AddEntry(L1MU20VFC_hist,"Trigger pass rate");
   legend->AddEntry(lead_muon_cumulative_pt_hist,"Cumulative muon pt");
   legend->Draw();


   c2->cd();
   L1MU14FCH_hist->Draw("HIST");
   L1MU14FCH_hist->GetXaxis()->SetBinLabel(1,"HLT_mu24");
   L1MU14FCH_hist->GetXaxis()->SetBinLabel(2,"HLT_mu28");
   L1MU14FCH_hist->GetXaxis()->SetTitle("Triggers");
   L1MU14FCH_hist->GetYaxis()->SetTitle("Percentage of events passing given trigger");


}