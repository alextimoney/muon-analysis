#define stree_cxx
#include "stree.h"

#include <fstream>

// #include "Math/GenVector/Cartesian3D.h"
// #include <Cartesian3D.h>

stree::stree(TTree *stree) : fChain(0)
{
   // if parameter tree is not specified (or zero), connect the file
   // used to generate this class and read the Tree.
   if (stree == 0)
   {
      std::cout << "not a tree" << std::endl;
      exit(1);
   }
   Init(stree);
   std::make_unique<Plotter>(850, 850);
}

stree::~stree()
{
   if (!fChain)
      return;
   delete fChain->GetCurrentFile();
}

Int_t stree::GetEntry(Long64_t entry)
{
   // Read contents of entry.
   if (!fChain)
      return 0;
   return fChain->GetEntry(entry);
}
Long64_t stree::LoadTree(Long64_t entry)
{
   // Set the environment to read one entry
   if (!fChain)
      return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0)
      return centry;
   if (fChain->GetTreeNumber() != fCurrent)
   {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void stree::Init(TTree *stree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   seg_name = 0;
   seg_name_short = 0;
   seg_vMB_x = 0;
   seg_vMB_y = 0;
   seg_vMB_z = 0;
   seg_hitshare = 0;
   // Set branch addresses and branch pointers
   if (!stree) return;
   fChain = stree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("sRunNumber", &sRunNumber, &b_sRunNumber);
   fChain->SetBranchAddress("sEventNumber", &sEventNumber, &b_sEventNumber);
   fChain->SetBranchAddress("sLumiBlock", &sLumiBlock, &b_sLumiBlock);
   fChain->SetBranchAddress("seg_muon_n", &seg_muon_n, &b_seg_muon_n);
   fChain->SetBranchAddress("seg_author", &seg_author, &b_seg_author);
   fChain->SetBranchAddress("seg_eta_index", &seg_eta_index, &b_seg_eta_index);
   fChain->SetBranchAddress("seg_tech", &seg_tech, &b_seg_tech);
   fChain->SetBranchAddress("seg_cham_index", &seg_cham_index, &b_seg_cham_index);
   fChain->SetBranchAddress("seg_name", &seg_name, &b_seg_name);
   fChain->SetBranchAddress("seg_name_short", &seg_name_short, &b_seg_name_short);
   fChain->SetBranchAddress("seg_haveTrkSeg", &seg_haveTrkSeg, &b_seg_haveTrkSeg);
   fChain->SetBranchAddress("seg_identifier", &seg_identifier, &b_seg_identifier);
   fChain->SetBranchAddress("seg_index", &seg_index, &b_seg_index);
   fChain->SetBranchAddress("seg_x", &seg_x, &b_seg_x);
   fChain->SetBranchAddress("seg_y", &seg_y, &b_seg_y);
   fChain->SetBranchAddress("seg_z", &seg_z, &b_seg_z);
   fChain->SetBranchAddress("seg_px", &seg_px, &b_seg_px);
   fChain->SetBranchAddress("seg_py", &seg_py, &b_seg_py);
   fChain->SetBranchAddress("seg_pz", &seg_pz, &b_seg_pz);
   fChain->SetBranchAddress("seg_t0", &seg_t0, &b_seg_t0);
   fChain->SetBranchAddress("seg_t0_error", &seg_t0_error, &b_seg_t0_error);
   fChain->SetBranchAddress("seg_chisquare", &seg_chisquare, &b_seg_chisquare);
   fChain->SetBranchAddress("seg_nDOF", &seg_nDOF, &b_seg_nDOF);
   fChain->SetBranchAddress("seg_nPrecisionHits", &seg_nPrecisionHits, &b_seg_nPrecisionHits);
   fChain->SetBranchAddress("seg_nTrigEtaLayers", &seg_nTrigEtaLayers, &b_seg_nTrigEtaLayers);
   fChain->SetBranchAddress("seg_nTrigPhiLayers", &seg_nTrigPhiLayers, &b_seg_nTrigPhiLayers);
   fChain->SetBranchAddress("seg_global_x", &seg_global_x, &b_seg_global_x);
   fChain->SetBranchAddress("seg_global_y", &seg_global_y, &b_seg_global_y);
   fChain->SetBranchAddress("seg_global_z", &seg_global_z, &b_seg_global_z);
   fChain->SetBranchAddress("seg_global_px", &seg_global_px, &b_seg_global_px);
   fChain->SetBranchAddress("seg_global_py", &seg_global_py, &b_seg_global_py);
   fChain->SetBranchAddress("seg_global_pz", &seg_global_pz, &b_seg_global_pz);
   fChain->SetBranchAddress("seg_local_x", &seg_local_x, &b_seg_local_x);
   fChain->SetBranchAddress("seg_local_y", &seg_local_y, &b_seg_local_y);
   fChain->SetBranchAddress("seg_local_z", &seg_local_z, &b_seg_local_z);
   fChain->SetBranchAddress("seg_local_px", &seg_local_px, &b_seg_local_px);
   fChain->SetBranchAddress("seg_local_py", &seg_local_py, &b_seg_local_py);
   fChain->SetBranchAddress("seg_local_pz", &seg_local_pz, &b_seg_local_pz);
   fChain->SetBranchAddress("seg_cham_x", &seg_cham_x, &b_seg_cham_x);
   fChain->SetBranchAddress("seg_cham_y", &seg_cham_y, &b_seg_cham_y);
   fChain->SetBranchAddress("seg_cham_z", &seg_cham_z, &b_seg_cham_z);
   fChain->SetBranchAddress("seg_vMB_x", &seg_vMB_x, &b_seg_vMB_x);
   fChain->SetBranchAddress("seg_vMB_y", &seg_vMB_y, &b_seg_vMB_y);
   fChain->SetBranchAddress("seg_vMB_z", &seg_vMB_z, &b_seg_vMB_z);
   fChain->SetBranchAddress("seg_nhits", &seg_nhits, &b_seg_nhits);
   fChain->SetBranchAddress("seg_ntrackhits", &seg_ntrackhits, &b_seg_ntrackhits);
   fChain->SetBranchAddress("seg_track_hitshare", &seg_track_hitshare, &b_seg_track_hitshare);
   fChain->SetBranchAddress("seg_hitshare", &seg_hitshare, &b_seg_hitshare);
   fChain->SetBranchAddress("seg_hitreq", &seg_hitreq, &b_seg_hitreq);
   fChain->SetBranchAddress("seg_fitqual", &seg_fitqual, &b_seg_fitqual);
   fChain->SetBranchAddress("seg_residual", &seg_residual, &b_seg_residual);
   fChain->SetBranchAddress("seg_pull", &seg_pull, &b_seg_pull);
   fChain->SetBranchAddress("seg_trk_match_id", &seg_trk_match_id, &b_seg_trk_match_id);
   fChain->SetBranchAddress("seg_trk_pos_global_x", &seg_trk_pos_global_x, &b_seg_trk_pos_global_x);
   fChain->SetBranchAddress("seg_trk_pos_global_y", &seg_trk_pos_global_y, &b_seg_trk_pos_global_y);
   fChain->SetBranchAddress("seg_trk_pos_global_z", &seg_trk_pos_global_z, &b_seg_trk_pos_global_z);
   fChain->SetBranchAddress("seg_trk_pos_local_x", &seg_trk_pos_local_x, &b_seg_trk_pos_local_x);
   fChain->SetBranchAddress("seg_trk_pos_local_y", &seg_trk_pos_local_y, &b_seg_trk_pos_local_y);
   fChain->SetBranchAddress("seg_trk_pos_local_z", &seg_trk_pos_local_z, &b_seg_trk_pos_local_z);
   fChain->SetBranchAddress("seg_trk_dir_global_x", &seg_trk_dir_global_x, &b_seg_trk_dir_global_x);
   fChain->SetBranchAddress("seg_trk_dir_global_y", &seg_trk_dir_global_y, &b_seg_trk_dir_global_y);
   fChain->SetBranchAddress("seg_trk_dir_global_z", &seg_trk_dir_global_z, &b_seg_trk_dir_global_z);
   fChain->SetBranchAddress("seg_trk_dir_local_x", &seg_trk_dir_local_x, &b_seg_trk_dir_local_x);
   fChain->SetBranchAddress("seg_trk_dir_local_y", &seg_trk_dir_local_y, &b_seg_trk_dir_local_y);
   fChain->SetBranchAddress("seg_trk_dir_local_z", &seg_trk_dir_local_z, &b_seg_trk_dir_local_z);
   fChain->SetBranchAddress("sILumiBlock", &sILumiBlock, &b_sILumiBlock);
   Notify();
}

Bool_t stree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void stree::Show(Long64_t entry)
{
   // Print contents of entry.
   // If entry is not specified, print current entry
   if (!fChain)
      return;
   fChain->Show(entry);
}
Int_t stree::Cut(Long64_t entry)
{
   // This function may be called from Loop.
   // returns  1 if entry is accepted.
   // returns -1 otherwise.
   return 1;
};


void stree::Initialize()
{
    int x=1;
    // make plots here

}

void stree::Loop()
{
   int nentries = fChain->GetEntries();
   std::cout << "Looping over " << nentries << " events" << std::endl;

   int passed = 0;
   int failed = 0;

   int progress = 0;

   for (int i = 0; i < nentries; i++)
   {
        fChain->GetEntry(i);



        // Cuts
        bool pass_cuts = true;
        // pass_cuts = false;


        if (!seg_hitreq)
        { 
            pass_cuts = false;
        }


        // Track hit share
        if ((seg_track_hitshare < 4) || (seg_track_hitshare < seg_nhits - 1))
        {
            pass_cuts = false;
        }


        // Muon author
        if (seg_author == -999999)
        {
            pass_cuts = false;
        }


        // End of cuts
        // -----------

        // pass_cuts = true;
        if (pass_cuts == true)
        {
        passed++;
        }
        if (pass_cuts == false)
        {
        failed++;
        }


        // Fill hists
        // ----------



        // Fill the rest of the hists
        if (pass_cuts)
        {
            std::cout << "Passed: " << passed << "   Failed: " << failed << std::endl;
        }


   } // end loop

}