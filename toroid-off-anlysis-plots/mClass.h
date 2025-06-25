//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jan 25 14:46:49 2023 by ROOT version 6.24/06
// from TTree mtree/mtree
// found on file: test_mtree_triggers_01.root
//////////////////////////////////////////////////////////

#ifndef mClass_h
#define mClass_h

#include "TDirectory.h"

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <string> // for string and to_string()
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include <dirent.h>

// Header file for the classes stored in the TTree if any.

class mClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          mRunNumber;
   UInt_t          mEventNumber;
   UInt_t          mLumiBlock;
   Bool_t          L1_Passed;
   Bool_t          HLT_Passed;
   Bool_t          HLT_mu5_mucombTag_L1MU20VFC_Passed;
   Bool_t          HLT_mu8_mucombTag_L1MU20VFC_Passed;
   Bool_t          HLT_mu10_mucombTag_L1MU20VFC_Passed;
   Bool_t          HLT_mu15_mucombTag_L1MU20VFC_Passed;
   Bool_t          HLT_mu20_mucombTag_L1MU20VFC_Passed;
   Bool_t          HLT_mu25_mucombTag_L1MU20VFC_Passed;
   Bool_t          HLT_mu30_mucombTag_L1MU20VFC_Passed;
   Bool_t          HLT_mu50_mucombTag_L1MU20VFC_Passed;
   Bool_t          HLT_mu24_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed;
   Bool_t          HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed;
   Bool_t          HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU18VFCH_Passed;
   Int_t           muon_n;
   Double_t        muon_pt;
   Double_t        muon_eta;
   Double_t        muon_phi;
   Double_t        muon_m;
   Double_t        muon_e;
   Double_t        muon_charge;
   Int_t           muon_type;
   Int_t           muon_EnergyLossType;
   Int_t           muon_author;
   Bool_t          muon_quality;
   Bool_t          muon_pass_IDhits;
   Bool_t          muon_pass_HighPt;
   Int_t           muon_nSegments;
   Int_t           muon_trMatch;
   UShort_t        muon_allAuthors;
   Bool_t          isAuthorUnknown;
   Bool_t          isAuthorMuid;
   Bool_t          isAuthorStaco;
   Bool_t          isAuthorMuTag;
   Bool_t          isAuthorMuTagIMO;
   Bool_t          isAuthorMuidSA;
   Bool_t          isAuthorMuGirl;
   Bool_t          isAuthorMuGirlLowBeta;
   Bool_t          isAuthorCaloTag;
   Bool_t          isAuthorCaloLikelihood;
   Bool_t          isAuthorExtrapolateMuonToIP;
   Int_t           muon_nAuthors;
   UChar_t         muon_numberOfPrecisionLayers;
   UChar_t         muon_numberOfPrecisionHoleLayers;
   UChar_t         muon_numberOfPhiLayers;
   UChar_t         muon_numberOfPhiHoleLayers;
   UChar_t         muon_numberOfTriggerEtaLayers;
   UChar_t         muon_numberOfTriggerEtaHoleLayers;
   UChar_t         muon_primarySector;
   UChar_t         muon_secondarySector;
   UChar_t         muon_innerSmallHits;
   UChar_t         muon_innerLargeHits;
   UChar_t         muon_middleSmallHits;
   UChar_t         muon_middleLargeHits;
   UChar_t         muon_outerSmallHits;
   UChar_t         muon_outerLargeHits;
   UChar_t         muon_extendedSmallHits;
   UChar_t         muon_extendedLargeHits;
   UChar_t         muon_innerSmallHoles;
   UChar_t         muon_innerLargeHoles;
   UChar_t         muon_middleSmallHoles;
   UChar_t         muon_middleLargeHoles;
   UChar_t         muon_outerSmallHoles;
   UChar_t         muon_outerLargeHoles;
   UChar_t         muon_extendedSmallHoles;
   UChar_t         muon_extendedLargeHoles;
   Float_t         mspectrometerFieldIntegral;
   Float_t         mscatteringCurvatureSignificance;
   Float_t         mscatteringNeighbourSignificance;
   Float_t         mmomentumBalanceSignificance;
   Float_t         msegmentDeltaEta;
   Float_t         msegmentDeltaPhi;
   Float_t         msegmentChi2OverDoF;
   Float_t         mt0;
   Float_t         mbeta;
   Float_t         mannBarrel;
   Float_t         mannEndCap;
   Float_t         minnAngle;
   Float_t         mmidAngle;
   Float_t         mmsInnerMatchChi2;
   Float_t         mmsInnerMatchDOF;
   Float_t         mmsOuterMatchChi2;
   Float_t         mmsOuterMatchDOF;
   Float_t         mmeanDeltaADCCountsMDT;
   Float_t         mCaloLRLikelihood;
   Float_t         mCaloMuonIDTag;
   Float_t         mFSR_CandidateEnergy;
   Float_t         mEnergyLoss;
   Float_t         mParamEnergyLossmPara;
   Float_t         mMeasEnergyLoss;
   Float_t         mEnergyLossSigma;
   Float_t         mParamEnergyLossSigmaPlus;
   Float_t         mParamEnergyLossSigmaMinus;
   Float_t         mMeasEnergyLossSigma;

   // List of branches
   TBranch        *b_mRunNumber;   //!
   TBranch        *b_mEventNumber;   //!
   TBranch        *b_mLumiBlock;   //!
   TBranch        *b_L1_Passed;   //!
   TBranch        *b_HLT_Passed;   //!
   TBranch        *b_HLT_mu5_mucombTag_L1MU20VFC_Passed;   //!
   TBranch        *b_HLT_mu8_mucombTag_L1MU20VFC_Passed;   //!
   TBranch        *b_HLT_mu10_mucombTag_L1MU20VFC_Passed;   //!
   TBranch        *b_HLT_mu15_mucombTag_L1MU20VFC_Passed;   //!
   TBranch        *b_HLT_mu20_mucombTag_L1MU20VFC_Passed;   //!
   TBranch        *b_HLT_mu25_mucombTag_L1MU20VFC_Passed;   //!
   TBranch        *b_HLT_mu30_mucombTag_L1MU20VFC_Passed;   //!
   TBranch        *b_HLT_mu50_mucombTag_L1MU20VFC_Passed;   //!
   TBranch        *b_HLT_mu24_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed;   //!
   TBranch        *b_HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed;   //!
   TBranch        *b_HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU18VFCH_Passed;   //!
   TBranch        *b_muon_n;   //!
   TBranch        *b_muon_pt;   //!
   TBranch        *b_muon_eta;   //!
   TBranch        *b_muon_phi;   //!
   TBranch        *b_muon_m;   //!
   TBranch        *b_muon_e;   //!
   TBranch        *b_muon_charge;   //!
   TBranch        *b_muon_type;   //!
   TBranch        *b_muon_EnergyLossType;   //!
   TBranch        *b_muon_author;   //!
   TBranch        *b_muon_quality;   //!
   TBranch        *b_muon_pass_IDhits;   //!
   TBranch        *b_muon_pass_HighPt;   //!
   TBranch        *b_muon_nSegments;   //!
   TBranch        *b_muon_trMatch;   //!
   TBranch        *b_muon_allAuthors;   //!
   TBranch        *b_isAuthorUnknown;   //!
   TBranch        *b_isAuthorMuid;   //!
   TBranch        *b_isAuthorStaco;   //!
   TBranch        *b_isAuthorMuTag;   //!
   TBranch        *b_isAuthorMuTagIMO;   //!
   TBranch        *b_isAuthorMuidSA;   //!
   TBranch        *b_isAuthorMuGirl;   //!
   TBranch        *b_isAuthorMuGirlLowBeta;   //!
   TBranch        *b_isAuthorCaloTag;   //!
   TBranch        *b_isAuthorCaloLikelihood;   //!
   TBranch        *b_isAuthorExtrapolateMuonToIP;   //!
   TBranch        *b_muon_nAuthors;   //!
   TBranch        *b_muon_numberOfPrecisionLayers;   //!
   TBranch        *b_muon_numberOfPrecisionHoleLayers;   //!
   TBranch        *b_muon_numberOfPhiLayers;   //!
   TBranch        *b_muon_numberOfPhiHoleLayers;   //!
   TBranch        *b_muon_numberOfTriggerEtaLayers;   //!
   TBranch        *b_muon_numberOfTriggerEtaHoleLayers;   //!
   TBranch        *b_muon_primarySector;   //!
   TBranch        *b_muon_secondarySector;   //!
   TBranch        *b_muon_innerSmallHits;   //!
   TBranch        *b_muon_innerLargeHits;   //!
   TBranch        *b_muon_middleSmallHits;   //!
   TBranch        *b_muon_middleLargeHits;   //!
   TBranch        *b_muon_outerSmallHits;   //!
   TBranch        *b_muon_outerLargeHits;   //!
   TBranch        *b_muon_extendedSmallHits;   //!
   TBranch        *b_muon_extendedLargeHits;   //!
   TBranch        *b_muon_innerSmallHoles;   //!
   TBranch        *b_muon_innerLargeHoles;   //!
   TBranch        *b_muon_middleSmallHoles;   //!
   TBranch        *b_muon_middleLargeHoles;   //!
   TBranch        *b_muon_outerSmallHoles;   //!
   TBranch        *b_muon_outerLargeHoles;   //!
   TBranch        *b_muon_extendedSmallHoles;   //!
   TBranch        *b_muon_extendedLargeHoles;   //!
   TBranch        *b_mspectrometerFieldIntegral;   //!
   TBranch        *b_mscatteringCurvatureSignificance;   //!
   TBranch        *b_mscatteringNeighbourSignificance;   //!
   TBranch        *b_mmomentumBalanceSignificance;   //!
   TBranch        *b_msegmentDeltaEta;   //!
   TBranch        *b_msegmentDeltaPhi;   //!
   TBranch        *b_msegmentChi2OverDoF;   //!
   TBranch        *b_mt0;   //!
   TBranch        *b_mbeta;   //!
   TBranch        *b_mannBarrel;   //!
   TBranch        *b_mannEndCap;   //!
   TBranch        *b_minnAngle;   //!
   TBranch        *b_mmidAngle;   //!
   TBranch        *b_mmsInnerMatchChi2;   //!
   TBranch        *b_mmsInnerMatchDOF;   //!
   TBranch        *b_mmsOuterMatchChi2;   //!
   TBranch        *b_mmsOuterMatchDOF;   //!
   TBranch        *b_mmeanDeltaADCCountsMDT;   //!
   TBranch        *b_mCaloLRLikelihood;   //!
   TBranch        *b_mCaloMuonIDTag;   //!
   TBranch        *b_mFSR_CandidateEnergy;   //!
   TBranch        *b_mEnergyLoss;   //!
   TBranch        *b_mParamEnergyLossmPara;   //!
   TBranch        *b_mMeasEnergyLoss;   //!
   TBranch        *b_mEnergyLossSigma;   //!
   TBranch        *b_mParamEnergyLossSigmaPlus;   //!
   TBranch        *b_mParamEnergyLossSigmaMinus;   //!
   TBranch        *b_mMeasEnergyLossSigma;   //!

   mClass(TTree *tree=0);
   virtual ~mClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(int samplen);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef mClass_cxx
mClass::mClass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   // if (tree == 0) {
   //    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/user/n/ngarelli/ToroidOffBlines/alignment_toroid_off/alignment_rel22_v3/user.ngarelli.Blines_Athena24029_4510137_EXT1/user.ngarelli.37873434.EXT1._000440.outputfile.root");
   //    if (!f || !f->IsOpen()) {
   //       f = new TFile("/eos/user/n/ngarelli/ToroidOffBlines/alignment_toroid_off/alignment_rel22_v3/user.ngarelli.Blines_Athena24029_4510137_EXT1/user.ngarelli.37873434.EXT1._000440.outputfile.root");
   //    }
   //    f->GetObject("mtree",tree);
   // }
   // Init(tree);


   std::vector<string> samples;
   DIR *dir_ptr;
   struct dirent *diread;
   if ((dir_ptr = opendir("/eos/user/n/ngarelli/ToroidOffBlines/alignment_toroid_off/alignment_rel22_v3/user.ngarelli.Blines_Athena24029_4510163_EXT1")) != nullptr) {
      while ((diread = readdir(dir_ptr)) != nullptr) {
            string sample = diread->d_name;
            if (sample.find(".root") != string::npos){
               samples.push_back(sample);
            }
      }
      closedir(dir_ptr);
   }
   TFile *filearray[samples.size()];
   // TString tree = "mtree";
   // TChain *cc_tree = new TChain("mtree");
   if (tree == 0) {
      for(int i = 0; i < samples.size(); i++) {
         string inFile = "/eos/user/n/ngarelli/ToroidOffBlines/alignment_toroid_off/alignment_rel22_v3/user.ngarelli.Blines_Athena24029_4510163_EXT1/" + samples[i];
         // TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(inFile.c_str());
         // if (!f || !f->IsOpen() || f == nullptr) {
         TFile *f = new TFile(inFile.c_str());
         // }
         filearray[i] = f;
      }
      // Init(cc_tree);
   }
   for(int i = 0; i < samples.size(); i++) {
      cout << "Running on file #" << i << " of " << samples.size() << endl;
      string outfile_name = "./mtree_out/mtree_out_" + samples[i];
      filearray[i]->GetObject("mtree",tree);
      Init(tree);
      Loop(i);
      cout << endl;
   }
}

mClass::~mClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t mClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t mClass::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void mClass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mRunNumber", &mRunNumber, &b_mRunNumber);
   fChain->SetBranchAddress("mEventNumber", &mEventNumber, &b_mEventNumber);
   fChain->SetBranchAddress("mLumiBlock", &mLumiBlock, &b_mLumiBlock);
   fChain->SetBranchAddress("L1_Passed", &L1_Passed, &b_L1_Passed);
   fChain->SetBranchAddress("HLT_Passed", &HLT_Passed, &b_HLT_Passed);
   fChain->SetBranchAddress("HLT_mu5_mucombTag_L1MU20VFC_Passed", &HLT_mu5_mucombTag_L1MU20VFC_Passed, &b_HLT_mu5_mucombTag_L1MU20VFC_Passed);
   fChain->SetBranchAddress("HLT_mu8_mucombTag_L1MU20VFC_Passed", &HLT_mu8_mucombTag_L1MU20VFC_Passed, &b_HLT_mu8_mucombTag_L1MU20VFC_Passed);
   fChain->SetBranchAddress("HLT_mu10_mucombTag_L1MU20VFC_Passed", &HLT_mu10_mucombTag_L1MU20VFC_Passed, &b_HLT_mu10_mucombTag_L1MU20VFC_Passed);
   fChain->SetBranchAddress("HLT_mu15_mucombTag_L1MU20VFC_Passed", &HLT_mu15_mucombTag_L1MU20VFC_Passed, &b_HLT_mu15_mucombTag_L1MU20VFC_Passed);
   fChain->SetBranchAddress("HLT_mu20_mucombTag_L1MU20VFC_Passed", &HLT_mu20_mucombTag_L1MU20VFC_Passed, &b_HLT_mu20_mucombTag_L1MU20VFC_Passed);
   fChain->SetBranchAddress("HLT_mu25_mucombTag_L1MU20VFC_Passed", &HLT_mu25_mucombTag_L1MU20VFC_Passed, &b_HLT_mu25_mucombTag_L1MU20VFC_Passed);
   fChain->SetBranchAddress("HLT_mu30_mucombTag_L1MU20VFC_Passed", &HLT_mu30_mucombTag_L1MU20VFC_Passed, &b_HLT_mu30_mucombTag_L1MU20VFC_Passed);
   fChain->SetBranchAddress("HLT_mu50_mucombTag_L1MU20VFC_Passed", &HLT_mu50_mucombTag_L1MU20VFC_Passed, &b_HLT_mu50_mucombTag_L1MU20VFC_Passed);
   fChain->SetBranchAddress("HLT_mu24_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed", &HLT_mu24_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed, &b_HLT_mu24_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed);
   fChain->SetBranchAddress("HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed", &HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed, &b_HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed);
   fChain->SetBranchAddress("HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU18VFCH_Passed", &HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU18VFCH_Passed, &b_HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU18VFCH_Passed);
   fChain->SetBranchAddress("muon_n", &muon_n, &b_muon_n);
   fChain->SetBranchAddress("muon_pt", &muon_pt, &b_muon_pt);
   fChain->SetBranchAddress("muon_eta", &muon_eta, &b_muon_eta);
   fChain->SetBranchAddress("muon_phi", &muon_phi, &b_muon_phi);
   fChain->SetBranchAddress("muon_m", &muon_m, &b_muon_m);
   fChain->SetBranchAddress("muon_e", &muon_e, &b_muon_e);
   fChain->SetBranchAddress("muon_charge", &muon_charge, &b_muon_charge);
   fChain->SetBranchAddress("muon_type", &muon_type, &b_muon_type);
   fChain->SetBranchAddress("muon_EnergyLossType", &muon_EnergyLossType, &b_muon_EnergyLossType);
   fChain->SetBranchAddress("muon_author", &muon_author, &b_muon_author);
   fChain->SetBranchAddress("muon_quality", &muon_quality, &b_muon_quality);
   fChain->SetBranchAddress("muon_pass_IDhits", &muon_pass_IDhits, &b_muon_pass_IDhits);
   fChain->SetBranchAddress("muon_pass_HighPt", &muon_pass_HighPt, &b_muon_pass_HighPt);
   fChain->SetBranchAddress("muon_nSegments", &muon_nSegments, &b_muon_nSegments);
   fChain->SetBranchAddress("muon_trMatch", &muon_trMatch, &b_muon_trMatch);
   fChain->SetBranchAddress("muon_allAuthors", &muon_allAuthors, &b_muon_allAuthors);
   fChain->SetBranchAddress("isAuthorUnknown", &isAuthorUnknown, &b_isAuthorUnknown);
   fChain->SetBranchAddress("isAuthorMuid", &isAuthorMuid, &b_isAuthorMuid);
   fChain->SetBranchAddress("isAuthorStaco", &isAuthorStaco, &b_isAuthorStaco);
   fChain->SetBranchAddress("isAuthorMuTag", &isAuthorMuTag, &b_isAuthorMuTag);
   fChain->SetBranchAddress("isAuthorMuTagIMO", &isAuthorMuTagIMO, &b_isAuthorMuTagIMO);
   fChain->SetBranchAddress("isAuthorMuidSA", &isAuthorMuidSA, &b_isAuthorMuidSA);
   fChain->SetBranchAddress("isAuthorMuGirl", &isAuthorMuGirl, &b_isAuthorMuGirl);
   fChain->SetBranchAddress("isAuthorMuGirlLowBeta", &isAuthorMuGirlLowBeta, &b_isAuthorMuGirlLowBeta);
   fChain->SetBranchAddress("isAuthorCaloTag", &isAuthorCaloTag, &b_isAuthorCaloTag);
   fChain->SetBranchAddress("isAuthorCaloLikelihood", &isAuthorCaloLikelihood, &b_isAuthorCaloLikelihood);
   fChain->SetBranchAddress("isAuthorExtrapolateMuonToIP", &isAuthorExtrapolateMuonToIP, &b_isAuthorExtrapolateMuonToIP);
   fChain->SetBranchAddress("muon_nAuthors", &muon_nAuthors, &b_muon_nAuthors);
   fChain->SetBranchAddress("muon_numberOfPrecisionLayers", &muon_numberOfPrecisionLayers, &b_muon_numberOfPrecisionLayers);
   fChain->SetBranchAddress("muon_numberOfPrecisionHoleLayers", &muon_numberOfPrecisionHoleLayers, &b_muon_numberOfPrecisionHoleLayers);
   fChain->SetBranchAddress("muon_numberOfPhiLayers", &muon_numberOfPhiLayers, &b_muon_numberOfPhiLayers);
   fChain->SetBranchAddress("muon_numberOfPhiHoleLayers", &muon_numberOfPhiHoleLayers, &b_muon_numberOfPhiHoleLayers);
   fChain->SetBranchAddress("muon_numberOfTriggerEtaLayers", &muon_numberOfTriggerEtaLayers, &b_muon_numberOfTriggerEtaLayers);
   fChain->SetBranchAddress("muon_numberOfTriggerEtaHoleLayers", &muon_numberOfTriggerEtaHoleLayers, &b_muon_numberOfTriggerEtaHoleLayers);
   fChain->SetBranchAddress("muon_primarySector", &muon_primarySector, &b_muon_primarySector);
   fChain->SetBranchAddress("muon_secondarySector", &muon_secondarySector, &b_muon_secondarySector);
   fChain->SetBranchAddress("muon_innerSmallHits", &muon_innerSmallHits, &b_muon_innerSmallHits);
   fChain->SetBranchAddress("muon_innerLargeHits", &muon_innerLargeHits, &b_muon_innerLargeHits);
   fChain->SetBranchAddress("muon_middleSmallHits", &muon_middleSmallHits, &b_muon_middleSmallHits);
   fChain->SetBranchAddress("muon_middleLargeHits", &muon_middleLargeHits, &b_muon_middleLargeHits);
   fChain->SetBranchAddress("muon_outerSmallHits", &muon_outerSmallHits, &b_muon_outerSmallHits);
   fChain->SetBranchAddress("muon_outerLargeHits", &muon_outerLargeHits, &b_muon_outerLargeHits);
   fChain->SetBranchAddress("muon_extendedSmallHits", &muon_extendedSmallHits, &b_muon_extendedSmallHits);
   fChain->SetBranchAddress("muon_extendedLargeHits", &muon_extendedLargeHits, &b_muon_extendedLargeHits);
   fChain->SetBranchAddress("muon_innerSmallHoles", &muon_innerSmallHoles, &b_muon_innerSmallHoles);
   fChain->SetBranchAddress("muon_innerLargeHoles", &muon_innerLargeHoles, &b_muon_innerLargeHoles);
   fChain->SetBranchAddress("muon_middleSmallHoles", &muon_middleSmallHoles, &b_muon_middleSmallHoles);
   fChain->SetBranchAddress("muon_middleLargeHoles", &muon_middleLargeHoles, &b_muon_middleLargeHoles);
   fChain->SetBranchAddress("muon_outerSmallHoles", &muon_outerSmallHoles, &b_muon_outerSmallHoles);
   fChain->SetBranchAddress("muon_outerLargeHoles", &muon_outerLargeHoles, &b_muon_outerLargeHoles);
   fChain->SetBranchAddress("muon_extendedSmallHoles", &muon_extendedSmallHoles, &b_muon_extendedSmallHoles);
   fChain->SetBranchAddress("muon_extendedLargeHoles", &muon_extendedLargeHoles, &b_muon_extendedLargeHoles);
   fChain->SetBranchAddress("mspectrometerFieldIntegral", &mspectrometerFieldIntegral, &b_mspectrometerFieldIntegral);
   fChain->SetBranchAddress("mscatteringCurvatureSignificance", &mscatteringCurvatureSignificance, &b_mscatteringCurvatureSignificance);
   fChain->SetBranchAddress("mscatteringNeighbourSignificance", &mscatteringNeighbourSignificance, &b_mscatteringNeighbourSignificance);
   fChain->SetBranchAddress("mmomentumBalanceSignificance", &mmomentumBalanceSignificance, &b_mmomentumBalanceSignificance);
   fChain->SetBranchAddress("msegmentDeltaEta", &msegmentDeltaEta, &b_msegmentDeltaEta);
   fChain->SetBranchAddress("msegmentDeltaPhi", &msegmentDeltaPhi, &b_msegmentDeltaPhi);
   fChain->SetBranchAddress("msegmentChi2OverDoF", &msegmentChi2OverDoF, &b_msegmentChi2OverDoF);
   fChain->SetBranchAddress("mt0", &mt0, &b_mt0);
   fChain->SetBranchAddress("mbeta", &mbeta, &b_mbeta);
   fChain->SetBranchAddress("mannBarrel", &mannBarrel, &b_mannBarrel);
   fChain->SetBranchAddress("mannEndCap", &mannEndCap, &b_mannEndCap);
   fChain->SetBranchAddress("minnAngle", &minnAngle, &b_minnAngle);
   fChain->SetBranchAddress("mmidAngle", &mmidAngle, &b_mmidAngle);
   fChain->SetBranchAddress("mmsInnerMatchChi2", &mmsInnerMatchChi2, &b_mmsInnerMatchChi2);
   fChain->SetBranchAddress("mmsInnerMatchDOF", &mmsInnerMatchDOF, &b_mmsInnerMatchDOF);
   fChain->SetBranchAddress("mmsOuterMatchChi2", &mmsOuterMatchChi2, &b_mmsOuterMatchChi2);
   fChain->SetBranchAddress("mmsOuterMatchDOF", &mmsOuterMatchDOF, &b_mmsOuterMatchDOF);
   fChain->SetBranchAddress("mmeanDeltaADCCountsMDT", &mmeanDeltaADCCountsMDT, &b_mmeanDeltaADCCountsMDT);
   fChain->SetBranchAddress("mCaloLRLikelihood", &mCaloLRLikelihood, &b_mCaloLRLikelihood);
   fChain->SetBranchAddress("mCaloMuonIDTag", &mCaloMuonIDTag, &b_mCaloMuonIDTag);
   fChain->SetBranchAddress("mFSR_CandidateEnergy", &mFSR_CandidateEnergy, &b_mFSR_CandidateEnergy);
   fChain->SetBranchAddress("mEnergyLoss", &mEnergyLoss, &b_mEnergyLoss);
   fChain->SetBranchAddress("mParamEnergyLossmPara", &mParamEnergyLossmPara, &b_mParamEnergyLossmPara);
   fChain->SetBranchAddress("mMeasEnergyLoss", &mMeasEnergyLoss, &b_mMeasEnergyLoss);
   fChain->SetBranchAddress("mEnergyLossSigma", &mEnergyLossSigma, &b_mEnergyLossSigma);
   fChain->SetBranchAddress("mParamEnergyLossSigmaPlus", &mParamEnergyLossSigmaPlus, &b_mParamEnergyLossSigmaPlus);
   fChain->SetBranchAddress("mParamEnergyLossSigmaMinus", &mParamEnergyLossSigmaMinus, &b_mParamEnergyLossSigmaMinus);
   fChain->SetBranchAddress("mMeasEnergyLossSigma", &mMeasEnergyLossSigma, &b_mMeasEnergyLossSigma);
   Notify();
}

Bool_t mClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void mClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t mClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef mClass_cxx
