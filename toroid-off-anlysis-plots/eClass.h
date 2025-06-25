//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 28 17:06:49 2022 by ROOT version 6.24/08
// from TTree etree/etree
// found on file: output_new_triggers_03.root
//////////////////////////////////////////////////////////

#ifndef eClass_h
#define eClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class eClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           enMuons;
   UInt_t          eRunNumber;
   UInt_t          eEventNumber;
   UInt_t          eLumiBlock;
   Bool_t          L1_MU20VFC_Passed;
   Bool_t          HLT_mu5_mucombTag_L1MU20VFC_Passed;
   Bool_t          HLT_mu8_mucombTag_L1MU20VFC_Passed;
   Bool_t          HLT_mu10_mucombTag_L1MU20VFC_Passed;
   Bool_t          HLT_mu20_mucombTag_L1MU20VFC_Passed;
   Bool_t          HLT_mu25_mucombTag_L1MU20VFC_Passed;
   Bool_t          HLT_mu30_mucombTag_L1MU20VFC_Passed;
   Bool_t          HLT_mu50_mucombTag_L1MU20VFC_Passed;
   Bool_t          L1_MU14FCH_Passed;
   Bool_t          HLT_mu24_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed;
   Bool_t          HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed;
   Bool_t          HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU18VFCH_Passed;
   Double_t        vx_x;
   Double_t        vx_y;
   Double_t        vx_z;
   Double_t        vx_chiSquared;
   Double_t        vx_nDOF;

   // List of branches
   TBranch        *b_enMuons;   //!
   TBranch        *b_eRunNumber;   //!
   TBranch        *b_eEventNumber;   //!
   TBranch        *b_eLumiBlock;   //!
   TBranch        *b_L1_MU20VFC_Passed;   //!
   TBranch        *b_HLT_mu5_mucombTag_L1MU20VFC_Passed;   //!
   TBranch        *b_HLT_mu8_mucombTag_L1MU20VFC_Passed;   //!
   TBranch        *b_HLT_mu10_mucombTag_L1MU20VFC_Passed;   //!
   TBranch        *b_HLT_mu20_mucombTag_L1MU20VFC_Passed;   //!
   TBranch        *b_HLT_mu25_mucombTag_L1MU20VFC_Passed;   //!
   TBranch        *b_HLT_mu30_mucombTag_L1MU20VFC_Passed;   //!
   TBranch        *b_HLT_mu50_mucombTag_L1MU20VFC_Passed;   //!
   TBranch        *b_L1_MU14FCH_Passed;   //!
   TBranch        *b_HLT_mu24_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed;   //!
   TBranch        *b_HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed;   //!
   TBranch        *b_HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU18VFCH_Passed;   //!
   TBranch        *b_vx_x;   //!
   TBranch        *b_vx_y;   //!
   TBranch        *b_vx_z;   //!
   TBranch        *b_vx_chiSquared;   //!
   TBranch        *b_vx_nDOF;   //!

   eClass(TTree *tree=0);
   virtual ~eClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef eClass_cxx
eClass::eClass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("test_mtree_triggers_02.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("test_mtree_triggers_02.root");
      }
      f->GetObject("etree",tree);

   }
   Init(tree);
}

eClass::~eClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t eClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t eClass::LoadTree(Long64_t entry)
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

void eClass::Init(TTree *tree)
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

   fChain->SetBranchAddress("enMuons", &enMuons, &b_enMuons);
   fChain->SetBranchAddress("eRunNumber", &eRunNumber, &b_eRunNumber);
   fChain->SetBranchAddress("eEventNumber", &eEventNumber, &b_eEventNumber);
   fChain->SetBranchAddress("eLumiBlock", &eLumiBlock, &b_eLumiBlock);
   fChain->SetBranchAddress("L1_MU20VFC_Passed", &L1_MU20VFC_Passed, &b_L1_MU20VFC_Passed);
   fChain->SetBranchAddress("HLT_mu5_mucombTag_L1MU20VFC_Passed", &HLT_mu5_mucombTag_L1MU20VFC_Passed, &b_HLT_mu5_mucombTag_L1MU20VFC_Passed);
   fChain->SetBranchAddress("HLT_mu8_mucombTag_L1MU20VFC_Passed", &HLT_mu8_mucombTag_L1MU20VFC_Passed, &b_HLT_mu8_mucombTag_L1MU20VFC_Passed);
   fChain->SetBranchAddress("HLT_mu10_mucombTag_L1MU20VFC_Passed", &HLT_mu10_mucombTag_L1MU20VFC_Passed, &b_HLT_mu10_mucombTag_L1MU20VFC_Passed);
   fChain->SetBranchAddress("HLT_mu20_mucombTag_L1MU20VFC_Passed", &HLT_mu20_mucombTag_L1MU20VFC_Passed, &b_HLT_mu20_mucombTag_L1MU20VFC_Passed);
   fChain->SetBranchAddress("HLT_mu25_mucombTag_L1MU20VFC_Passed", &HLT_mu25_mucombTag_L1MU20VFC_Passed, &b_HLT_mu25_mucombTag_L1MU20VFC_Passed);
   fChain->SetBranchAddress("HLT_mu30_mucombTag_L1MU20VFC_Passed", &HLT_mu30_mucombTag_L1MU20VFC_Passed, &b_HLT_mu30_mucombTag_L1MU20VFC_Passed);
   fChain->SetBranchAddress("HLT_mu50_mucombTag_L1MU20VFC_Passed", &HLT_mu50_mucombTag_L1MU20VFC_Passed, &b_HLT_mu50_mucombTag_L1MU20VFC_Passed);
   fChain->SetBranchAddress("L1_MU14FCH_Passed", &L1_MU14FCH_Passed, &b_L1_MU14FCH_Passed);
   fChain->SetBranchAddress("HLT_mu24_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed", &HLT_mu24_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed, &b_HLT_mu24_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed);
   fChain->SetBranchAddress("HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed", &HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed, &b_HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU14FCH_Passed);
   fChain->SetBranchAddress("HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU18VFCH_Passed", &HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU18VFCH_Passed, &b_HLT_mu26_ivarmedium_mu14_idperf_probe_50invmAB130_L1MU18VFCH_Passed);
   fChain->SetBranchAddress("vx_x", &vx_x, &b_vx_x);
   fChain->SetBranchAddress("vx_y", &vx_y, &b_vx_y);
   fChain->SetBranchAddress("vx_z", &vx_z, &b_vx_z);
   fChain->SetBranchAddress("vx_chiSquared", &vx_chiSquared, &b_vx_chiSquared);
   fChain->SetBranchAddress("vx_nDOF", &vx_nDOF, &b_vx_nDOF);
   Notify();
}

Bool_t eClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void eClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t eClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef eClass_cxx
