#define tree_cxx
#include "tree.h"

#include <fstream>

// #include "Math/GenVector/Cartesian3D.h"
// #include <Cartesian3D.h>

tree::tree(TTree *tree) : fChain(0)
{
   // if parameter tree is not specified (or zero), connect the file
   // used to generate this class and read the Tree.
   if (tree == 0)
   {
      std::cout << "not a tree" << std::endl;
      exit(1);
   }
   Init(tree);
   std::make_unique<Plotter>(850, 850);
}

tree::~tree()
{
   if (!fChain)
      return;
   delete fChain->GetCurrentFile();
}

Int_t tree::GetEntry(Long64_t entry)
{
   // Read contents of entry.
   if (!fChain)
      return 0;
   return fChain->GetEntry(entry);
}
Long64_t tree::LoadTree(Long64_t entry)
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

void tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   if (!tree)
      return;
   fChain = tree;

   segger1_hitshare = 0;
   segger2_hitshare = 0;
   segger3_hitshare = 0;
   comb_type = 0;
   seg1_name = 0;
   seg1_name_short = 0;
   seg2_name = 0;
   seg2_name_short = 0;
   seg3_name = 0;
   seg3_name_short = 0;
   // Set branch addresses and branch pointers

   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("vx_x", &vx_x, &b_vx_x);
   fChain->SetBranchAddress("vx_y", &vx_y, &b_vx_y);
   fChain->SetBranchAddress("vx_z", &vx_z, &b_vx_z);
   fChain->SetBranchAddress("vx_chiSquared", &vx_chiSquared, &b_vx_chiSquared);
   fChain->SetBranchAddress("vx_nDOF", &vx_nDOF, &b_vx_nDOF);
   fChain->SetBranchAddress("seg1_index", &seg1_index, &b_seg1_index);
   fChain->SetBranchAddress("seg2_index", &seg2_index, &b_seg2_index);
   fChain->SetBranchAddress("seg3_index", &seg3_index, &b_seg3_index);
   fChain->SetBranchAddress("segger1_author", &segger1_author, &b_segger1_author);
   fChain->SetBranchAddress("segger1_muon_author", &segger1_muon_author, &b_segger1_muon_author);
   fChain->SetBranchAddress("segger1_hitsOnTrack", &segger1_hitsOnTrack, &b_segger1_hitsOnTrack);
   fChain->SetBranchAddress("segger1_muon_pt", &segger1_muon_pt, &b_segger1_muon_pt);
   fChain->SetBranchAddress("segger1_muon_eta", &segger1_muon_eta, &b_segger1_muon_eta);
   fChain->SetBranchAddress("segger1_muon_phi", &segger1_muon_phi, &b_segger1_muon_phi);
   fChain->SetBranchAddress("segger2_author", &segger2_author, &b_segger2_author);
   fChain->SetBranchAddress("segger2_muon_author", &segger2_muon_author, &b_segger2_muon_author);
   fChain->SetBranchAddress("segger2_hitsOnTrack", &segger2_hitsOnTrack, &b_segger2_hitsOnTrack);
   fChain->SetBranchAddress("segger2_muon_pt", &segger2_muon_pt, &b_segger2_muon_pt);
   fChain->SetBranchAddress("segger2_muon_eta", &segger2_muon_eta, &b_segger2_muon_eta);
   fChain->SetBranchAddress("segger2_muon_phi", &segger2_muon_phi, &b_segger2_muon_phi);
   fChain->SetBranchAddress("segger3_author", &segger3_author, &b_segger3_author);
   fChain->SetBranchAddress("segger3_muon_author", &segger3_muon_author, &b_segger3_muon_author);
   fChain->SetBranchAddress("segger3_hitsOnTrack", &segger3_hitsOnTrack, &b_segger3_hitsOnTrack);
   fChain->SetBranchAddress("segger3_muon_pt", &segger3_muon_pt, &b_segger3_muon_pt);
   fChain->SetBranchAddress("segger3_muon_eta", &segger3_muon_eta, &b_segger3_muon_eta);
   fChain->SetBranchAddress("segger3_muon_phi", &segger3_muon_phi, &b_segger3_muon_phi);
   fChain->SetBranchAddress("segger1_nhits", &segger1_nhits, &b_segger1_nhits);
   fChain->SetBranchAddress("segger1_ntrackhits", &segger1_ntrackhits, &b_segger1_ntrackhits);
   fChain->SetBranchAddress("segger1_track_hitshare", &segger1_track_hitshare, &b_segger1_track_hitshare);
   fChain->SetBranchAddress("segger1_hitshare", &segger1_hitshare, &b_segger1_hitshare);
   fChain->SetBranchAddress("segger2_nhits", &segger2_nhits, &b_segger2_nhits);
   fChain->SetBranchAddress("segger2_ntrackhits", &segger2_ntrackhits, &b_segger2_ntrackhits);
   fChain->SetBranchAddress("segger2_track_hitshare", &segger2_track_hitshare, &b_segger2_track_hitshare);
   fChain->SetBranchAddress("segger2_hitshare", &segger2_hitshare, &b_segger2_hitshare);
   fChain->SetBranchAddress("segger3_nhits", &segger3_nhits, &b_segger3_nhits);
   fChain->SetBranchAddress("segger3_ntrackhits", &segger3_ntrackhits, &b_segger3_ntrackhits);
   fChain->SetBranchAddress("segger3_track_hitshare", &segger3_track_hitshare, &b_segger3_track_hitshare);
   fChain->SetBranchAddress("segger3_hitshare", &segger3_hitshare, &b_segger3_hitshare);
   fChain->SetBranchAddress("cRunNumber", &cRunNumber, &b_cRunNumber);
   fChain->SetBranchAddress("cEventNumber", &cEventNumber, &b_cEventNumber);
   fChain->SetBranchAddress("cLumiBlock", &cLumiBlock, &b_cLumiBlock);
   fChain->SetBranchAddress("comb_muon_n", &comb_muon_n, &b_comb_muon_n);
   fChain->SetBranchAddress("comb_type", &comb_type, &b_comb_type);
   fChain->SetBranchAddress("comb_side", &comb_side, &b_comb_side);
   fChain->SetBranchAddress("comb_sector", &comb_sector, &b_comb_sector);
   fChain->SetBranchAddress("seg1_author", &seg1_author, &b_seg1_author);
   fChain->SetBranchAddress("seg1_eta_index", &seg1_eta_index, &b_seg1_eta_index);
   fChain->SetBranchAddress("seg1_tech", &seg1_tech, &b_seg1_tech);
   fChain->SetBranchAddress("seg1_cham_index", &seg1_cham_index, &b_seg1_cham_index);
   fChain->SetBranchAddress("seg1_name", &seg1_name, &b_seg1_name);
   fChain->SetBranchAddress("seg1_name_short", &seg1_name_short, &b_seg1_name_short);
   fChain->SetBranchAddress("seg1_x", &seg1_x, &b_seg1_x);
   fChain->SetBranchAddress("seg1_y", &seg1_y, &b_seg1_y);
   fChain->SetBranchAddress("seg1_z", &seg1_z, &b_seg1_z);
   fChain->SetBranchAddress("seg1_px", &seg1_px, &b_seg1_px);
   fChain->SetBranchAddress("seg1_py", &seg1_py, &b_seg1_py);
   fChain->SetBranchAddress("seg1_pz", &seg1_pz, &b_seg1_pz);
   fChain->SetBranchAddress("seg1_t0", &seg1_t0, &b_seg1_t0);
   fChain->SetBranchAddress("seg1_t0_error", &seg1_t0_error, &b_seg1_t0_error);
   fChain->SetBranchAddress("seg1_chisquare", &seg1_chisquare, &b_seg1_chisquare);
   fChain->SetBranchAddress("seg1_nDOF", &seg1_nDOF, &b_seg1_nDOF);
   fChain->SetBranchAddress("seg1_nPrecisionHits", &seg1_nPrecisionHits, &b_seg1_nPrecisionHits);
   fChain->SetBranchAddress("seg1_nTrigEtaLayers", &seg1_nTrigEtaLayers, &b_seg1_nTrigEtaLayers);
   fChain->SetBranchAddress("seg1_nTrigPhiLayers", &seg1_nTrigPhiLayers, &b_seg1_nTrigPhiLayers);
   fChain->SetBranchAddress("seg1_global_x", &seg1_global_x, &b_seg1_global_x);
   fChain->SetBranchAddress("seg1_global_y", &seg1_global_y, &b_seg1_global_y);
   fChain->SetBranchAddress("seg1_global_z", &seg1_global_z, &b_seg1_global_z);
   fChain->SetBranchAddress("seg1_global_px", &seg1_global_px, &b_seg1_global_px);
   fChain->SetBranchAddress("seg1_global_py", &seg1_global_py, &b_seg1_global_py);
   fChain->SetBranchAddress("seg1_global_pz", &seg1_global_pz, &b_seg1_global_pz);
   fChain->SetBranchAddress("seg1_local_x", &seg1_local_x, &b_seg1_local_x);
   fChain->SetBranchAddress("seg1_local_y", &seg1_local_y, &b_seg1_local_y);
   fChain->SetBranchAddress("seg1_local_z", &seg1_local_z, &b_seg1_local_z);
   fChain->SetBranchAddress("seg1_local_px", &seg1_local_px, &b_seg1_local_px);
   fChain->SetBranchAddress("seg1_local_py", &seg1_local_py, &b_seg1_local_py);
   fChain->SetBranchAddress("seg1_local_pz", &seg1_local_pz, &b_seg1_local_pz);
   fChain->SetBranchAddress("seg1_global_improved_x", &seg1_global_improved_x, &b_seg1_global_improved_x);
   fChain->SetBranchAddress("seg1_global_improved_y", &seg1_global_improved_y, &b_seg1_global_improved_y);
   fChain->SetBranchAddress("seg1_global_improved_z", &seg1_global_improved_z, &b_seg1_global_improved_z);
   fChain->SetBranchAddress("seg1_local_improved_x", &seg1_local_improved_x, &b_seg1_local_improved_x);
   fChain->SetBranchAddress("seg1_local_improved_y", &seg1_local_improved_y, &b_seg1_local_improved_y);
   fChain->SetBranchAddress("seg1_local_improved_z", &seg1_local_improved_z, &b_seg1_local_improved_z);
   fChain->SetBranchAddress("seg1_cham_x", &seg1_cham_x, &b_seg1_cham_x);
   fChain->SetBranchAddress("seg1_cham_y", &seg1_cham_y, &b_seg1_cham_y);
   fChain->SetBranchAddress("seg1_cham_z", &seg1_cham_z, &b_seg1_cham_z);
   fChain->SetBranchAddress("seg1_hitreq", &seg1_hitreq, &b_seg1_hitreq);
   fChain->SetBranchAddress("seg1_fitqual", &seg1_fitqual, &b_seg1_fitqual);
   fChain->SetBranchAddress("seg2_author", &seg2_author, &b_seg2_author);
   fChain->SetBranchAddress("seg2_eta_index", &seg2_eta_index, &b_seg2_eta_index);
   fChain->SetBranchAddress("seg2_tech", &seg2_tech, &b_seg2_tech);
   fChain->SetBranchAddress("seg2_cham_index", &seg2_cham_index, &b_seg2_cham_index);
   fChain->SetBranchAddress("seg2_name", &seg2_name, &b_seg2_name);
   fChain->SetBranchAddress("seg2_name_short", &seg2_name_short, &b_seg2_name_short);
   fChain->SetBranchAddress("seg2_x", &seg2_x, &b_seg2_x);
   fChain->SetBranchAddress("seg2_y", &seg2_y, &b_seg2_y);
   fChain->SetBranchAddress("seg2_z", &seg2_z, &b_seg2_z);
   fChain->SetBranchAddress("seg2_px", &seg2_px, &b_seg2_px);
   fChain->SetBranchAddress("seg2_py", &seg2_py, &b_seg2_py);
   fChain->SetBranchAddress("seg2_pz", &seg2_pz, &b_seg2_pz);
   fChain->SetBranchAddress("seg2_t0", &seg2_t0, &b_seg2_t0);
   fChain->SetBranchAddress("seg2_t0_error", &seg2_t0_error, &b_seg2_t0_error);
   fChain->SetBranchAddress("seg2_chisquare", &seg2_chisquare, &b_seg2_chisquare);
   fChain->SetBranchAddress("seg2_nDOF", &seg2_nDOF, &b_seg2_nDOF);
   fChain->SetBranchAddress("seg2_nPrecisionHits", &seg2_nPrecisionHits, &b_seg2_nPrecisionHits);
   fChain->SetBranchAddress("seg2_nTrigEtaLayers", &seg2_nTrigEtaLayers, &b_seg2_nTrigEtaLayers);
   fChain->SetBranchAddress("seg2_nTrigPhiLayers", &seg2_nTrigPhiLayers, &b_seg2_nTrigPhiLayers);
   fChain->SetBranchAddress("seg2_global_x", &seg2_global_x, &b_seg2_global_x);
   fChain->SetBranchAddress("seg2_global_y", &seg2_global_y, &b_seg2_global_y);
   fChain->SetBranchAddress("seg2_global_z", &seg2_global_z, &b_seg2_global_z);
   fChain->SetBranchAddress("seg2_global_px", &seg2_global_px, &b_seg2_global_px);
   fChain->SetBranchAddress("seg2_global_py", &seg2_global_py, &b_seg2_global_py);
   fChain->SetBranchAddress("seg2_global_pz", &seg2_global_pz, &b_seg2_global_pz);
   fChain->SetBranchAddress("seg2_local_x", &seg2_local_x, &b_seg2_local_x);
   fChain->SetBranchAddress("seg2_local_y", &seg2_local_y, &b_seg2_local_y);
   fChain->SetBranchAddress("seg2_local_z", &seg2_local_z, &b_seg2_local_z);
   fChain->SetBranchAddress("seg2_local_px", &seg2_local_px, &b_seg2_local_px);
   fChain->SetBranchAddress("seg2_local_py", &seg2_local_py, &b_seg2_local_py);
   fChain->SetBranchAddress("seg2_local_pz", &seg2_local_pz, &b_seg2_local_pz);
   fChain->SetBranchAddress("seg2_global_improved_x", &seg2_global_improved_x, &b_seg2_global_improved_x);
   fChain->SetBranchAddress("seg2_global_improved_y", &seg2_global_improved_y, &b_seg2_global_improved_y);
   fChain->SetBranchAddress("seg2_global_improved_z", &seg2_global_improved_z, &b_seg2_global_improved_z);
   fChain->SetBranchAddress("seg2_local_improved_x", &seg2_local_improved_x, &b_seg2_local_improved_x);
   fChain->SetBranchAddress("seg2_local_improved_y", &seg2_local_improved_y, &b_seg2_local_improved_y);
   fChain->SetBranchAddress("seg2_local_improved_z", &seg2_local_improved_z, &b_seg2_local_improved_z);
   fChain->SetBranchAddress("seg2_cham_x", &seg2_cham_x, &b_seg2_cham_x);
   fChain->SetBranchAddress("seg2_cham_y", &seg2_cham_y, &b_seg2_cham_y);
   fChain->SetBranchAddress("seg2_cham_z", &seg2_cham_z, &b_seg2_cham_z);
   fChain->SetBranchAddress("seg2_hitreq", &seg2_hitreq, &b_seg2_hitreq);
   fChain->SetBranchAddress("seg2_fitqual", &seg2_fitqual, &b_seg2_fitqual);
   fChain->SetBranchAddress("seg3_author", &seg3_author, &b_seg3_author);
   fChain->SetBranchAddress("seg3_eta_index", &seg3_eta_index, &b_seg3_eta_index);
   fChain->SetBranchAddress("seg3_tech", &seg3_tech, &b_seg3_tech);
   fChain->SetBranchAddress("seg3_cham_index", &seg3_cham_index, &b_seg3_cham_index);
   fChain->SetBranchAddress("seg3_name", &seg3_name, &b_seg3_name);
   fChain->SetBranchAddress("seg3_name_short", &seg3_name_short, &b_seg3_name_short);
   fChain->SetBranchAddress("seg3_x", &seg3_x, &b_seg3_x);
   fChain->SetBranchAddress("seg3_y", &seg3_y, &b_seg3_y);
   fChain->SetBranchAddress("seg3_z", &seg3_z, &b_seg3_z);
   fChain->SetBranchAddress("seg3_px", &seg3_px, &b_seg3_px);
   fChain->SetBranchAddress("seg3_py", &seg3_py, &b_seg3_py);
   fChain->SetBranchAddress("seg3_pz", &seg3_pz, &b_seg3_pz);
   fChain->SetBranchAddress("seg3_t0", &seg3_t0, &b_seg3_t0);
   fChain->SetBranchAddress("seg3_t0_error", &seg3_t0_error, &b_seg3_t0_error);
   fChain->SetBranchAddress("seg3_chisquare", &seg3_chisquare, &b_seg3_chisquare);
   fChain->SetBranchAddress("seg3_nDOF", &seg3_nDOF, &b_seg3_nDOF);
   fChain->SetBranchAddress("seg3_nPrecisionHits", &seg3_nPrecisionHits, &b_seg3_nPrecisionHits);
   fChain->SetBranchAddress("seg3_nTrigEtaLayers", &seg3_nTrigEtaLayers, &b_seg3_nTrigEtaLayers);
   fChain->SetBranchAddress("seg3_nTrigPhiLayers", &seg3_nTrigPhiLayers, &b_seg3_nTrigPhiLayers);
   fChain->SetBranchAddress("seg3_global_x", &seg3_global_x, &b_seg3_global_x);
   fChain->SetBranchAddress("seg3_global_y", &seg3_global_y, &b_seg3_global_y);
   fChain->SetBranchAddress("seg3_global_z", &seg3_global_z, &b_seg3_global_z);
   fChain->SetBranchAddress("seg3_global_px", &seg3_global_px, &b_seg3_global_px);
   fChain->SetBranchAddress("seg3_global_py", &seg3_global_py, &b_seg3_global_py);
   fChain->SetBranchAddress("seg3_global_pz", &seg3_global_pz, &b_seg3_global_pz);
   fChain->SetBranchAddress("seg3_local_x", &seg3_local_x, &b_seg3_local_x);
   fChain->SetBranchAddress("seg3_local_y", &seg3_local_y, &b_seg3_local_y);
   fChain->SetBranchAddress("seg3_local_z", &seg3_local_z, &b_seg3_local_z);
   fChain->SetBranchAddress("seg3_local_px", &seg3_local_px, &b_seg3_local_px);
   fChain->SetBranchAddress("seg3_local_py", &seg3_local_py, &b_seg3_local_py);
   fChain->SetBranchAddress("seg3_local_pz", &seg3_local_pz, &b_seg3_local_pz);
   fChain->SetBranchAddress("seg3_global_improved_x", &seg3_global_improved_x, &b_seg3_global_improved_x);
   fChain->SetBranchAddress("seg3_global_improved_y", &seg3_global_improved_y, &b_seg3_global_improved_y);
   fChain->SetBranchAddress("seg3_global_improved_z", &seg3_global_improved_z, &b_seg3_global_improved_z);
   fChain->SetBranchAddress("seg3_local_improved_x", &seg3_local_improved_x, &b_seg3_local_improved_x);
   fChain->SetBranchAddress("seg3_local_improved_y", &seg3_local_improved_y, &b_seg3_local_improved_y);
   fChain->SetBranchAddress("seg3_local_improved_z", &seg3_local_improved_z, &b_seg3_local_improved_z);
   fChain->SetBranchAddress("seg3_cham_x", &seg3_cham_x, &b_seg3_cham_x);
   fChain->SetBranchAddress("seg3_cham_y", &seg3_cham_y, &b_seg3_cham_y);
   fChain->SetBranchAddress("seg3_cham_z", &seg3_cham_z, &b_seg3_cham_z);
   fChain->SetBranchAddress("seg3_hitreq", &seg3_hitreq, &b_seg3_hitreq);
   fChain->SetBranchAddress("seg3_fitqual", &seg3_fitqual, &b_seg3_fitqual);
   fChain->SetBranchAddress("mm1_global_improved_x", &mm1_global_x, &b_mm1_global_x);
   fChain->SetBranchAddress("mm1_global_improved_y", &mm1_global_y, &b_mm1_global_y);
   fChain->SetBranchAddress("mm1_global_improved_z", &mm1_global_z, &b_mm1_global_z);
   fChain->SetBranchAddress("mm1_global_px", &mm1_global_px, &b_mm1_global_px);
   fChain->SetBranchAddress("mm1_global_py", &mm1_global_py, &b_mm1_global_py);
   fChain->SetBranchAddress("mm1_global_pz", &mm1_global_pz, &b_mm1_global_pz);
   fChain->SetBranchAddress("mm1_local_x", &mm1_local_x, &b_mm1_local_x);
   fChain->SetBranchAddress("mm1_local_y", &mm1_local_y, &b_mm1_local_y);
   fChain->SetBranchAddress("mm1_local_z", &mm1_local_z, &b_mm1_local_z);
   fChain->SetBranchAddress("mm1_local_px", &mm1_local_px, &b_mm1_local_px);
   fChain->SetBranchAddress("mm1_local_py", &mm1_local_py, &b_mm1_local_py);
   fChain->SetBranchAddress("mm1_local_pz", &mm1_local_pz, &b_mm1_local_pz);
   fChain->SetBranchAddress("mm1_cham_x", &mm1_cham_x, &b_mm1_cham_x);
   fChain->SetBranchAddress("mm1_cham_y", &mm1_cham_y, &b_mm1_cham_y);
   fChain->SetBranchAddress("mm1_cham_z", &mm1_cham_z, &b_mm1_cham_z);
   fChain->SetBranchAddress("mm1_eta_index", &mm1_eta_index, &b_mm1_eta_index);
   fChain->SetBranchAddress("mm2_global_improved_x", &mm2_global_x, &b_mm2_global_x);
   fChain->SetBranchAddress("mm2_global_improved_y", &mm2_global_y, &b_mm2_global_y);
   fChain->SetBranchAddress("mm2_global_improved_z", &mm2_global_z, &b_mm2_global_z);
   fChain->SetBranchAddress("mm2_global_px", &mm2_global_px, &b_mm2_global_px);
   fChain->SetBranchAddress("mm2_global_py", &mm2_global_py, &b_mm2_global_py);
   fChain->SetBranchAddress("mm2_global_pz", &mm2_global_pz, &b_mm2_global_pz);
   fChain->SetBranchAddress("mm2_local_x", &mm2_local_x, &b_mm2_local_x);
   fChain->SetBranchAddress("mm2_local_y", &mm2_local_y, &b_mm2_local_y);
   fChain->SetBranchAddress("mm2_local_z", &mm2_local_z, &b_mm2_local_z);
   fChain->SetBranchAddress("mm2_local_px", &mm2_local_px, &b_mm2_local_px);
   fChain->SetBranchAddress("mm2_local_py", &mm2_local_py, &b_mm2_local_py);
   fChain->SetBranchAddress("mm2_local_pz", &mm2_local_pz, &b_mm2_local_pz);
   fChain->SetBranchAddress("mm2_cham_x", &mm2_cham_x, &b_mm2_cham_x);
   fChain->SetBranchAddress("mm2_cham_y", &mm2_cham_y, &b_mm2_cham_y);
   fChain->SetBranchAddress("mm2_cham_z", &mm2_cham_z, &b_mm2_cham_z);
   fChain->SetBranchAddress("mm2_eta_index", &mm2_eta_index, &b_mm2_eta_index);
   fChain->SetBranchAddress("stgc1_global_improved_x", &stgc1_global_x, &b_stgc1_global_x);
   fChain->SetBranchAddress("stgc1_global_improved_y", &stgc1_global_y, &b_stgc1_global_y);
   fChain->SetBranchAddress("stgc1_global_improved_z", &stgc1_global_z, &b_stgc1_global_z);
   fChain->SetBranchAddress("stgc1_global_px", &stgc1_global_px, &b_stgc1_global_px);
   fChain->SetBranchAddress("stgc1_global_py", &stgc1_global_py, &b_stgc1_global_py);
   fChain->SetBranchAddress("stgc1_global_pz", &stgc1_global_pz, &b_stgc1_global_pz);
   fChain->SetBranchAddress("stgc1_local_x", &stgc1_local_x, &b_stgc1_local_x);
   fChain->SetBranchAddress("stgc1_local_y", &stgc1_local_y, &b_stgc1_local_y);
   fChain->SetBranchAddress("stgc1_local_z", &stgc1_local_z, &b_stgc1_local_z);
   fChain->SetBranchAddress("stgc1_local_px", &stgc1_local_px, &b_stgc1_local_px);
   fChain->SetBranchAddress("stgc1_local_py", &stgc1_local_py, &b_stgc1_local_py);
   fChain->SetBranchAddress("stgc1_local_pz", &stgc1_local_pz, &b_stgc1_local_pz);
   fChain->SetBranchAddress("stgc1_cham_x", &stgc1_cham_x, &b_stgc1_cham_x);
   fChain->SetBranchAddress("stgc1_cham_y", &stgc1_cham_y, &b_stgc1_cham_y);
   fChain->SetBranchAddress("stgc1_cham_z", &stgc1_cham_z, &b_stgc1_cham_z);
   fChain->SetBranchAddress("stgc1_eta_index", &stgc1_eta_index, &b_stgc1_eta_index);
   fChain->SetBranchAddress("stgc2_global_improved_x", &stgc2_global_x, &b_stgc2_global_x);
   fChain->SetBranchAddress("stgc2_global_improved_y", &stgc2_global_y, &b_stgc2_global_y);
   fChain->SetBranchAddress("stgc2_global_improved_z", &stgc2_global_z, &b_stgc2_global_z);
   fChain->SetBranchAddress("stgc2_global_px", &stgc2_global_px, &b_stgc2_global_px);
   fChain->SetBranchAddress("stgc2_global_py", &stgc2_global_py, &b_stgc2_global_py);
   fChain->SetBranchAddress("stgc2_global_pz", &stgc2_global_pz, &b_stgc2_global_pz);
   fChain->SetBranchAddress("stgc2_local_x", &stgc2_local_x, &b_stgc2_local_x);
   fChain->SetBranchAddress("stgc2_local_y", &stgc2_local_y, &b_stgc2_local_y);
   fChain->SetBranchAddress("stgc2_local_z", &stgc2_local_z, &b_stgc2_local_z);
   fChain->SetBranchAddress("stgc2_local_px", &stgc2_local_px, &b_stgc2_local_px);
   fChain->SetBranchAddress("stgc2_local_py", &stgc2_local_py, &b_stgc2_local_py);
   fChain->SetBranchAddress("stgc2_local_pz", &stgc2_local_pz, &b_stgc2_local_pz);
   fChain->SetBranchAddress("stgc2_cham_x", &stgc2_cham_x, &b_stgc2_cham_x);
   fChain->SetBranchAddress("stgc2_cham_y", &stgc2_cham_y, &b_stgc2_cham_y);
   fChain->SetBranchAddress("stgc2_cham_z", &stgc2_cham_z, &b_stgc2_cham_z);
   fChain->SetBranchAddress("stgc2_eta_index", &stgc2_eta_index, &b_stgc2_eta_index);
   fChain->SetBranchAddress("segger1_trk_match_id_count", &segger1_trk_match_id_count, &b_segger1_trk_match_id_count);
   fChain->SetBranchAddress("segger1_hitavg_global_x", &segger1_hitavg_global_x, &b_segger1_hitavg_global_x);
   fChain->SetBranchAddress("segger1_hitavg_global_y", &segger1_hitavg_global_y, &b_segger1_hitavg_global_y);
   fChain->SetBranchAddress("segger1_hitavg_global_z", &segger1_hitavg_global_z, &b_segger1_hitavg_global_z);
   fChain->SetBranchAddress("segger1_hitavg_local_x", &segger1_hitavg_local_x, &b_segger1_hitavg_local_x);
   fChain->SetBranchAddress("segger1_hitavg_local_y", &segger1_hitavg_local_y, &b_segger1_hitavg_local_y);
   fChain->SetBranchAddress("segger1_hitavg_local_z", &segger1_hitavg_local_z, &b_segger1_hitavg_local_z);
   fChain->SetBranchAddress("segger1_hitavg_global_px", &segger1_hitavg_global_px, &b_segger1_hitavg_global_px);
   fChain->SetBranchAddress("segger1_hitavg_global_py", &segger1_hitavg_global_py, &b_segger1_hitavg_global_py);
   fChain->SetBranchAddress("segger1_hitavg_global_pz", &segger1_hitavg_global_pz, &b_segger1_hitavg_global_pz);
   fChain->SetBranchAddress("segger1_hitavg_local_px", &segger1_hitavg_local_px, &b_segger1_hitavg_local_px);
   fChain->SetBranchAddress("segger1_hitavg_local_py", &segger1_hitavg_local_py, &b_segger1_hitavg_local_py);
   fChain->SetBranchAddress("segger1_hitavg_local_pz", &segger1_hitavg_local_pz, &b_segger1_hitavg_local_pz);
   fChain->SetBranchAddress("segger1_track_residual", &segger1_track_residual, &b_segger1_track_residual);
   fChain->SetBranchAddress("segger1_track_pull", &segger1_track_pull, &b_segger1_track_pull);
   fChain->SetBranchAddress("segger2_trk_match_id_count", &segger2_trk_match_id_count, &b_segger2_trk_match_id_count);
   fChain->SetBranchAddress("segger2_hitavg_global_x", &segger2_hitavg_global_x, &b_segger2_hitavg_global_x);
   fChain->SetBranchAddress("segger2_hitavg_global_y", &segger2_hitavg_global_y, &b_segger2_hitavg_global_y);
   fChain->SetBranchAddress("segger2_hitavg_global_z", &segger2_hitavg_global_z, &b_segger2_hitavg_global_z);
   fChain->SetBranchAddress("segger2_hitavg_local_x", &segger2_hitavg_local_x, &b_segger2_hitavg_local_x);
   fChain->SetBranchAddress("segger2_hitavg_local_y", &segger2_hitavg_local_y, &b_segger2_hitavg_local_y);
   fChain->SetBranchAddress("segger2_hitavg_local_z", &segger2_hitavg_local_z, &b_segger2_hitavg_local_z);
   fChain->SetBranchAddress("segger2_hitavg_global_px", &segger2_hitavg_global_px, &b_segger2_hitavg_global_px);
   fChain->SetBranchAddress("segger2_hitavg_global_py", &segger2_hitavg_global_py, &b_segger2_hitavg_global_py);
   fChain->SetBranchAddress("segger2_hitavg_global_pz", &segger2_hitavg_global_pz, &b_segger2_hitavg_global_pz);
   fChain->SetBranchAddress("segger2_hitavg_local_px", &segger2_hitavg_local_px, &b_segger2_hitavg_local_px);
   fChain->SetBranchAddress("segger2_hitavg_local_py", &segger2_hitavg_local_py, &b_segger2_hitavg_local_py);
   fChain->SetBranchAddress("segger2_hitavg_local_pz", &segger2_hitavg_local_pz, &b_segger2_hitavg_local_pz);
   fChain->SetBranchAddress("segger2_track_residual", &segger2_track_residual, &b_segger2_track_residual);
   fChain->SetBranchAddress("segger2_track_pull", &segger2_track_pull, &b_segger2_track_pull);
   fChain->SetBranchAddress("segger3_trk_match_id_count", &segger3_trk_match_id_count, &b_segger3_trk_match_id_count);
   fChain->SetBranchAddress("segger3_hitavg_global_x", &segger3_hitavg_global_x, &b_segger3_hitavg_global_x);
   fChain->SetBranchAddress("segger3_hitavg_global_y", &segger3_hitavg_global_y, &b_segger3_hitavg_global_y);
   fChain->SetBranchAddress("segger3_hitavg_global_z", &segger3_hitavg_global_z, &b_segger3_hitavg_global_z);
   fChain->SetBranchAddress("segger3_hitavg_local_x", &segger3_hitavg_local_x, &b_segger3_hitavg_local_x);
   fChain->SetBranchAddress("segger3_hitavg_local_y", &segger3_hitavg_local_y, &b_segger3_hitavg_local_y);
   fChain->SetBranchAddress("segger3_hitavg_local_z", &segger3_hitavg_local_z, &b_segger3_hitavg_local_z);
   fChain->SetBranchAddress("segger3_hitavg_global_px", &segger3_hitavg_global_px, &b_segger3_hitavg_global_px);
   fChain->SetBranchAddress("segger3_hitavg_global_py", &segger3_hitavg_global_py, &b_segger3_hitavg_global_py);
   fChain->SetBranchAddress("segger3_hitavg_global_pz", &segger3_hitavg_global_pz, &b_segger3_hitavg_global_pz);
   fChain->SetBranchAddress("segger3_hitavg_local_px", &segger3_hitavg_local_px, &b_segger3_hitavg_local_px);
   fChain->SetBranchAddress("segger3_hitavg_local_py", &segger3_hitavg_local_py, &b_segger3_hitavg_local_py);
   fChain->SetBranchAddress("segger3_hitavg_local_pz", &segger3_hitavg_local_pz, &b_segger3_hitavg_local_pz);
   fChain->SetBranchAddress("segger3_track_residual", &segger3_track_residual, &b_segger3_track_residual);
   fChain->SetBranchAddress("segger3_track_pull", &segger3_track_pull, &b_segger3_track_pull);
   Notify();
}

Bool_t tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tree::Show(Long64_t entry)
{
   // Print contents of entry.
   // If entry is not specified, print current entry
   if (!fChain)
      return;
   fChain->Show(entry);
}
Int_t tree::Cut(Long64_t entry)
{
   // This function may be called from Loop.
   // returns  1 if entry is accepted.
   // returns -1 otherwise.
   return 1;
};

void tree::CreateSagittaHist(std::vector< std::unique_ptr<TH1F> > &hist, int index, int momentum, std::string side) {
   auto name = "sagitta_"+std::to_string(momentum)+"p_hist_sec" + std::to_string(index) + "_" + side;
   auto title = "Sagitta constructed from segment positions for side-" + side + " sector " + std::to_string(index) + ": mu p > "+std::to_string(momentum);
   hist.emplace_back(new TH1F(name.c_str(), title.c_str(), sag_bins, sag_min, sag_max));
}

void tree::Initialize()
{
   

   // A-side plots

   seg1_xy_aside_hist = std::make_unique<TH2F>("seg1_xy_aside_hist", "seg1 x vs seg1 y for A-side", nbins, -7000, 7000, nbins, -7000, 7000);
   seg2_xy_aside_hist = std::make_unique<TH2F>("seg2_xy_aside_hist", "seg2 x vs seg2 y for A-side", nbins, -10000, 10000, nbins, -10000, 10000);
   seg3_xy_aside_hist = std::make_unique<TH2F>("seg3_xy_aside_hist", "seg3 x vs seg3 y for A-side", nbins, x_min, x_max, nbins, y_min, y_max);

   seg1x_seg2x_aside_hist = std::make_unique<TH2F>("seg1x_seg2x_aside_hist", "seg1 x vs seg2 x for A-side", nbins, x_min, x_max, nbins, y_min, y_max);
   seg1x_seg3x_aside_hist = std::make_unique<TH2F>("seg1x_seg3x_aside_hist", "seg1 x vs seg3 x for A-side", nbins, x_min, x_max, nbins, y_min, y_max);
   seg2x_seg3x_aside_hist = std::make_unique<TH2F>("seg2x_seg3x_aside_hist", "seg2 x vs seg3 x for A-side", nbins, x_min, x_max, nbins, y_min, y_max);

   seg1y_seg2y_aside_hist = std::make_unique<TH2F>("seg1y_seg2y_aside_hist", "seg1 y vs seg2 y for A-side", nbins, x_min, x_max, nbins, y_min, y_max);
   seg1y_seg3y_aside_hist = std::make_unique<TH2F>("seg1y_seg3y_aside_hist", "seg1 y vs seg3 y for A-side", nbins, x_min, x_max, nbins, y_min, y_max);
   seg2y_seg3y_aside_hist = std::make_unique<TH2F>("seg2y_seg3y_aside_hist", "seg2 y vs seg3 y for A-side", nbins, x_min, x_max, nbins, y_min, y_max);

   seg1z_seg2z_aside_hist = std::make_unique<TH2F>("seg1z_seg2z_aside_hist", "seg1 z vs seg2 z for A-side", nbins, -25000, 25000, nbins, -25000, 25000);
   seg1z_seg3z_aside_hist = std::make_unique<TH2F>("seg1z_seg3z_aside_hist", "seg1 z vs seg3 z for A-side", nbins, -25000, 25000, nbins, -25000, 25000);
   seg2z_seg3z_aside_hist = std::make_unique<TH2F>("seg2z_seg3z_aside_hist", "seg2 z vs seg3 z for A-side", nbins, -25000, 25000, nbins, -25000, 25000);

   // seg1_nhits_aside_hist = std::make_unique<TH1F>("seg1_nhits_aside_hist", "inner wheel nhits for A-side", 20, 0, 20);
   // seg2_nhits_aside_hist = std::make_unique<TH1F>("seg2_nhits_aside_hist", "middle wheel nhits for A-side", 20, 0, 20);
   // seg3_nhits_aside_hist = std::make_unique<TH1F>("seg3_nhits_aside_hist", "outer wheel nhits for A-side", 20, 0, 20);

   seg1_nhits_hist_per_sector_aside_hists.reserve(16);
   seg2_nhits_hist_per_sector_aside_hists.reserve(16);
   seg3_nhits_hist_per_sector_aside_hists.reserve(16);

   for (int i = 0; i < 16; i++)
   {
      auto name = "seg1_nhits_aside_sector"+ std::to_string(i+1);
      auto title = "seg1 nhits per sector for aside sector" + std::to_string(i+1);
      seg1_nhits_hist_per_sector_aside_hists.emplace_back(new TH1F(name.c_str(), title.c_str(), 20, 0, 20));  

      name = "seg2_nhits_aside_sector"+ std::to_string(i+1);
      title = "seg2 nhits per sector for aside sector" + std::to_string(i+1);
      seg2_nhits_hist_per_sector_aside_hists.emplace_back(new TH1F(name.c_str(), title.c_str(), 20, 0, 20));

      name = "seg3_nhits_aside_sector"+ std::to_string(i+1);
      title = "seg3 nhits per sector for aside sector" + std::to_string(i+1);
      seg3_nhits_hist_per_sector_aside_hists.emplace_back(new TH1F(name.c_str(), title.c_str(), 20, 0, 20));
   }

   // C-side plots
   seg1_xy_cside_hist = std::make_unique<TH2F>("seg1_xy_cside_hist", "seg1 x vs seg1 y for C-side", nbins, -7000, 7000, nbins, -7000, 7000);
   seg2_xy_cside_hist = std::make_unique<TH2F>("seg2_xy_cside_hist", "seg2 x vs seg2 y for C-side", nbins, -10000, 10000, nbins, -10000, 10000);
   seg3_xy_cside_hist = std::make_unique<TH2F>("seg3_xy_cside_hist", "seg3 x vs seg3 y for C-side", nbins, x_min, x_max, nbins, y_min, y_max);

   seg1x_seg2x_cside_hist = std::make_unique<TH2F>("seg1x_seg2x_cside_hist", "seg1 x vs seg2 x for C-side", nbins, x_min, x_max, nbins, y_min, y_max);
   seg1x_seg3x_cside_hist = std::make_unique<TH2F>("seg1x_seg3x_cside_hist", "seg1 x vs seg3 x for C-side", nbins, x_min, x_max, nbins, y_min, y_max);
   seg2x_seg3x_cside_hist = std::make_unique<TH2F>("seg2x_seg3x_cside_hist", "seg2 x vs seg3 x for C-side", nbins, x_min, x_max, nbins, y_min, y_max);

   seg1y_seg2y_cside_hist = std::make_unique<TH2F>("seg1y_seg2y_cside_hist", "seg1 y vs seg2 y for C-side", nbins, x_min, x_max, nbins, y_min, y_max);
   seg1y_seg3y_cside_hist = std::make_unique<TH2F>("seg1y_seg3y_cside_hist", "seg1 y vs seg3 y for C-side", nbins, x_min, x_max, nbins, y_min, y_max);
   seg2y_seg3y_cside_hist = std::make_unique<TH2F>("seg2y_seg3y_cside_hist", "seg2 y vs seg3 y for C-side", nbins, x_min, x_max, nbins, y_min, y_max);

   seg1z_seg2z_cside_hist = std::make_unique<TH2F>("seg1z_seg2z_cside_hist", "seg1 z vs seg2 z for C-side", nbins, -25000, 25000, nbins, -25000, 25000);
   seg1z_seg3z_cside_hist = std::make_unique<TH2F>("seg1z_seg3z_cside_hist", "seg1 z vs seg3 z for C-side", nbins, -25000, 25000, nbins, -25000, 25000);
   seg2z_seg3z_cside_hist = std::make_unique<TH2F>("seg2z_seg3z_cside_hist", "seg2 z vs seg3 z for C-side", nbins, -25000, 25000, nbins, -25000, 25000);

   // seg1_nhits_cside_hist = std::make_unique<TH1F>("seg1_nhits_cside_hist", "inner wheel nhits for C-side", 20, 0, 20);
   // seg2_nhits_cside_hist = std::make_unique<TH1F>("seg2_nhits_cside_hist", "middle wheel nhits for C-side", 20, 0, 20);
   // seg3_nhits_cside_hist = std::make_unique<TH1F>("seg3_nhits_cside_hist", "outer wheel nhits for C-side", 20, 0, 20);

   seg1_nhits_hist_per_sector_cside_hists.reserve(16);
   seg2_nhits_hist_per_sector_cside_hists.reserve(16);
   seg3_nhits_hist_per_sector_cside_hists.reserve(16);

   for (int i = 0; i < 16; i++)
   {
      auto name = "seg1_nhits_cside_sector"+ std::to_string(i+1);
      auto title = "seg1 nhits per sector for cside sector" + std::to_string(i+1);
      seg1_nhits_hist_per_sector_cside_hists.emplace_back(new TH1F(name.c_str(), title.c_str(), 20, 0, 20));  

      name = "seg2_nhits_cside_sector"+ std::to_string(i+1);
      title = "seg2 nhits per sector for cside sector" + std::to_string(i+1);
      seg2_nhits_hist_per_sector_cside_hists.emplace_back(new TH1F(name.c_str(), title.c_str(), 20, 0, 20));

      name = "seg3_nhits_cside_sector"+ std::to_string(i+1);
      title = "seg3 nhits per sector for cside sector" + std::to_string(i+1);
      seg3_nhits_hist_per_sector_cside_hists.emplace_back(new TH1F(name.c_str(), title.c_str(), 20, 0, 20));
   }


   seg1_eta_hist = std::make_unique<TH2F>("seg1_eta_hist", "seg1 eta vs muon eta", 60, -3, 3, 60, -3, 3);
   seg2_eta_hist = std::make_unique<TH2F>("seg2_eta_hist", "seg2 eta vs muon eta", 60, -3, 3, 60, -3, 3);
   seg3_eta_hist = std::make_unique<TH2F>("seg3_eta_hist", "seg3 eta vs muon eta", 60, -3, 3, 60, -3, 3);

   seg1_phi_hist = std::make_unique<TH2F>("seg1_phi_hist", "seg1 phi vs muon phi", 60, -3.5, 3.5, 60, -3.5, 3.5);
   seg2_phi_hist = std::make_unique<TH2F>("seg2_phi_hist", "seg2 phi vs muon phi", 60, -3.5, 3.5, 60, -3.5, 3.5);
   seg3_phi_hist = std::make_unique<TH2F>("seg3_phi_hist", "seg3 phi vs muon phi", 60, -3.5, 3.5, 60, -3.5, 3.5);

   seg1_seg2_eta_hist = std::make_unique<TH2F>("seg1_seg2_eta_hist", "seg1 eta vs seg2 eta", 60, -3, 3, 60, -3, 3);
   seg1_seg3_eta_hist = std::make_unique<TH2F>("seg1_seg3_eta_hist", "seg1 eta vs seg3 eta", 60, -3, 3, 60, -3, 3);
   seg2_seg3_eta_hist = std::make_unique<TH2F>("seg2_seg3_eta_hist", "seg2 eta vs seg3 eta", 60, -3, 3, 60, -3, 3);

   seg1_seg2_phi_hist = std::make_unique<TH2F>("seg1_seg2_phi_hist", "seg1 phi vs seg2 phi", 60, -3.5, 3.5, 60, -3.5, 3.5);
   seg1_seg3_phi_hist = std::make_unique<TH2F>("seg1_seg3_phi_hist", "seg1 phi vs seg3 phi", 60, -3.5, 3.5, 60, -3.5, 3.5);
   seg2_seg3_phi_hist = std::make_unique<TH2F>("seg2_seg3_phi_hist", "seg2 phi vs seg3 phi", 60, -3.5, 3.5, 60, -3.5, 3.5);


   sagitta_0p_hist = std::make_unique<TH1F>("sagitta_0p_hist", "Sagitta constructed from segment positions: mu p > 0", 80, sag_min, sag_max);
   sagitta_10p_hist = std::make_unique<TH1F>("sagitta_10p_hist", "Sagitta constructed from segment positions: mu p > 10", 80, sag_min, sag_max);
   sagitta_15p_hist = std::make_unique<TH1F>("sagitta_15p_hist", "Sagitta constructed from segment positions: mu p > 15", 80, sag_min, sag_max);
   sagitta_20p_hist = std::make_unique<TH1F>("sagitta_20p_hist", "Sagitta constructed from segment positions: mu p > 20", 80, sag_min, sag_max);
   sagitta_30p_hist = std::make_unique<TH1F>("sagitta_30p_hist", "Sagitta constructed from segment positions: mu p > 30", 80, sag_min, sag_max);
   sagitta_50p_hist = std::make_unique<TH1F>("sagitta_50p_hist", "Sagitta constructed from segment positions: mu p > 50", 80, sag_min, sag_max);


   muon_p_hist = std::make_unique<TH1F>("muon_p_hist", "muon momentum in MeV", 80, 0, 80000);
   muon_p_selection_hist = std::make_unique<TH1F>("muon_p_selection_hist", "muon momentum after selection in MeV", 80, 0, 80000);

   muon_pT_hist = std::make_unique<TH1F>("muon_pT_hist", "muon pT in MeV", 50, 0, 120000);
   muon_pT_selection_hist = std::make_unique<TH1F>("muon_pT_selection_hist", "muon transverse momentum after selection in MeV", 50, 0, 120000);

   /*   mm1_xy_aside_hist = std::make_unique<TH2F>("mm1_xy_aside_hist", "mm1_xy_aside", nbins, -7000, 7000, nbins, -7000, 7000);
   mm2_xy_aside_hist = std::make_unique<TH2F>("mm2_xy_aside_hist", "mm2_xy_aside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc1_xy_aside_hist = std::make_unique<TH2F>("stgc1_xy_aside_hist", "stgc1_xy_aside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc2_xy_aside_hist = std::make_unique<TH2F>("stgc2_xy_aside_hist", "stgc2_xy_aside", nbins, -7000, 7000, nbins, -7000, 7000);
   mm1_xy_cside_hist = std::make_unique<TH2F>("mm1_xy_cside_hist", "mm1_xy_cside", nbins, -7000, 7000, nbins, -7000, 7000);
   mm2_xy_cside_hist = std::make_unique<TH2F>("mm2_xy_cside_hist", "mm2_xy_cside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc1_xy_cside_hist = std::make_unique<TH2F>("stgc1_xy_cside_hist", "stgc1_xy_cside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc2_xy_cside_hist = std::make_unique<TH2F>("stgc2_xy_cside_hist", "stgc2_xy_cside", nbins, -7000, 7000, nbins, -7000, 7000);
High resolution
   */
   mm1_xy_aside_hist = std::make_unique<TH2F>("mm1_xy_aside_hist", "mm1_xy_aside", nbins*100, -7000, 7000, nbins*100, -7000, 7000);
   mm2_xy_aside_hist = std::make_unique<TH2F>("mm2_xy_aside_hist", "mm2_xy_aside", nbins*100, -7000, 7000, nbins*100, -7000, 7000);
   stgc1_xy_aside_hist = std::make_unique<TH2F>("stgc1_xy_aside_hist", "stgc1_xy_aside", nbins*100, -7000, 7000, nbins*100, -7000, 7000);
   stgc2_xy_aside_hist = std::make_unique<TH2F>("stgc2_xy_aside_hist", "stgc2_xy_aside", nbins*100, -7000, 7000, nbins*100, -7000, 7000);
   mm1_xy_cside_hist = std::make_unique<TH2F>("mm1_xy_cside_hist", "mm1_xy_cside", nbins*100, -7000, 7000, nbins*100, -7000, 7000);
   mm2_xy_cside_hist = std::make_unique<TH2F>("mm2_xy_cside_hist", "mm2_xy_cside", nbins*100, -7000, 7000, nbins*100, -7000, 7000);
   stgc1_xy_cside_hist = std::make_unique<TH2F>("stgc1_xy_cside_hist", "stgc1_xy_cside", nbins*100, -7000, 7000, nbins*100, -7000, 7000);
   stgc2_xy_cside_hist = std::make_unique<TH2F>("stgc2_xy_cside_hist", "stgc2_xy_cside", nbins*100, -7000, 7000, nbins*100, -7000, 7000);


   /*   mm1_xy_t1_aside_hist = std::make_unique<TH2F>("mm1_xy_t1_aside_hist", "mm1_xy_t1_aside", nbins, -7000, 7000, nbins, -7000, 7000);
   mm2_xy_t1_aside_hist = std::make_unique<TH2F>("mm2_xy_t1_aside_hist", "mm2_xy_t1_aside", nbins, -7000, 7000, nbins, -7000, 7000);
   mm1_xy_t2_aside_hist = std::make_unique<TH2F>("mm1_xy_t2_aside_hist", "mm1_xy_t2_aside", nbins, -7000, 7000, nbins, -7000, 7000);
   mm2_xy_t2_aside_hist = std::make_unique<TH2F>("mm2_xy_t2_aside_hist", "mm2_xy_t2_aside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc1_xy_t1_aside_hist = std::make_unique<TH2F>("stgc1_xy_t1_aside_hist", "stgc1_xy_t1_aside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc2_xy_t1_aside_hist = std::make_unique<TH2F>("stgc2_xy_t1_aside_hist", "stgc2_xy_t1_aside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc1_xy_t2_aside_hist = std::make_unique<TH2F>("stgc1_xy_t2_aside_hist", "stgc1_xy_t2_aside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc2_xy_t2_aside_hist = std::make_unique<TH2F>("stgc2_xy_t2_aside_hist", "stgc2_xy_t2_aside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc1_xy_t3_aside_hist = std::make_unique<TH2F>("stgc1_xy_t3_aside_hist", "stgc1_xy_t3_aside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc2_xy_t3_aside_hist = std::make_unique<TH2F>("stgc2_xy_t3_aside_hist", "stgc2_xy_t3_aside", nbins, -7000, 7000, nbins, -7000, 7000);


   mm1_xy_t1_cside_hist = std::make_unique<TH2F>("mm1_xy_t1_cside_hist", "mm1_xy_t1_cside", nbins, -7000, 7000, nbins, -7000, 7000);
   mm2_xy_t1_cside_hist = std::make_unique<TH2F>("mm2_xy_t1_cside_hist", "mm2_xy_t1_cside", nbins, -7000, 7000, nbins, -7000, 7000);
   mm1_xy_t2_cside_hist = std::make_unique<TH2F>("mm1_xy_t2_cside_hist", "mm1_xy_t2_cside", nbins, -7000, 7000, nbins, -7000, 7000);
   mm2_xy_t2_cside_hist = std::make_unique<TH2F>("mm2_xy_t2_cside_hist", "mm2_xy_t2_cside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc1_xy_t1_cside_hist = std::make_unique<TH2F>("stgc1_xy_t1_cside_hist", "stgc1_xy_t1_cside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc2_xy_t1_cside_hist = std::make_unique<TH2F>("stgc2_xy_t1_cside_hist", "stgc2_xy_t1_cside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc1_xy_t2_cside_hist = std::make_unique<TH2F>("stgc1_xy_t2_cside_hist", "stgc1_xy_t2_cside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc2_xy_t2_cside_hist = std::make_unique<TH2F>("stgc2_xy_t2_cside_hist", "stgc2_xy_t2_cside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc1_xy_t3_cside_hist = std::make_unique<TH2F>("stgc1_xy_t3_cside_hist", "stgc1_xy_t3_cside", nbins, -7000, 7000, nbins, -7000, 7000);
   stgc2_xy_t3_cside_hist = std::make_unique<TH2F>("stgc2_xy_t3_cside_hist", "stgc2_xy_t3_cside", nbins, -7000, 7000, nbins, -7000, 7000);
   */

   // mm1_zphi_aside_hist = std::make_unique<TH2F>("mm1_zphi_aside_hist", "mm1_zphi_aside", nbins, 5000, 10000, nbins, -3.5, 3.5);
   // mm2_zphi_aside_hist = std::make_unique<TH2F>("mm2_zphi_aside_hist", "mm2_zphi_aside", nbins, 5000, 10000, nbins, -3.5, 3.5);
   // stgc1_zphi_aside_hist = std::make_unique<TH2F>("stgc1_zphi_aside_hist", "stgc1_zphi_aside", nbins, 5000, 10000, nbins, -3.5, 3.5);
   // stgc2_zphi_aside_hist = std::make_unique<TH2F>("stgc2_zphi_aside_hist", "stgc2_zphi_aside", nbins, 5000, 10000, nbins, -3.5, 3.5);
   // mm1_zphi_cside_hist = std::make_unique<TH2F>("mm1_zphi_cside_hist", "mm1_zphi_cside", nbins, -5000, -10000, nbins, -3.5, 3.5);
   // mm2_zphi_cside_hist = std::make_unique<TH2F>("mm2_zphi_cside_hist", "mm2_zphi_cside", nbins, -5000, -10000, nbins, -3.5, 3.5);
   // stgc1_zphi_cside_hist = std::make_unique<TH2F>("stgc1_zphi_cside_hist", "stgc1_zphi_cside", nbins, -5000, -10000, nbins, -3.5, 3.5);
   // stgc2_zphi_cside_hist = std::make_unique<TH2F>("stgc2_zphi_cside_hist", "stgc2_zphi_cside", nbins, -5000, -10000, nbins, -3.5, 3.5);




// junk??????


   // seg1_chamber_xy = std::make_unique<TH2F>("seg1_chamber_xy", "seg1_chamber_xy", nbins, -7000, 7000, nbins, -7000, 7000);
   // seg1_chamber_phiz = std::make_unique<TH2F>("seg1_chamber_phiz", "seg1_chamber_phiz", nbins, -7000, 7000, nbins, -7000, 7000);

   // mm1_chamber_xy = std::make_unique<TH2F>("mm1_chamber_xy", "mm1_chamber_xy", nbins, -7000, 7000, nbins, -7000, 7000);
   // mm1_chamber_phiz = std::make_unique<TH2F>("mm1_chamber_phiz", "mm1_chamber_phiz", nbins, -7000, 7000, nbins, -7000, 7000);
   // mm2_chamber_xy = std::make_unique<TH2F>("mm2_chamber_xy", "mm2_chamber_xy", nbins, -7000, 7000, nbins, -7000, 7000);
   // mm2_chamber_phiz = std::make_unique<TH2F>("mm2_chamber_phiz", "mm2_chamber_phiz", nbins, -7000, 7000, nbins, -7000, 7000);
   // stgc1_chamber_xy = std::make_unique<TH2F>("stgc1_chamber_xy", "stgc1_chamber_xy", nbins, -7000, 7000, nbins, -7000, 7000);
   // stgc1_chamber_phiz = std::make_unique<TH2F>("stgc1_chamber_phiz", "stgc1_chamber_phiz", nbins, -7000, 7000, nbins, -7000, 7000);
   // stgc2_chamber_xy = std::make_unique<TH2F>("stgc2_chamber_xy", "stgc2_chamber_xy", nbins, -7000, 7000, nbins, -7000, 7000);
   // stgc2_chamber_phiz = std::make_unique<TH2F>("stgc2_chamber_phiz", "stgc2_chamber_phiz", nbins, -7000, 7000, nbins, -7000, 7000);

   // seg1_local_xy = std::make_unique<TH2F>("seg1_local_xy", "seg1_local_xy", nbins, -7000, 7000, nbins, -7000, 7000);
   // seg1_local_x = std::make_unique<TH1F>("seg1_local_x", "seg1_local_x", nbins, -7000, 7000);
   // seg1_local_y = std::make_unique<TH1F>("seg1_local_y", "seg1_local_y", nbins, -7000, 7000);
   // seg1_local_z = std::make_unique<TH1F>("seg1_local_y", "seg1_local_y", nbins, -7000, 7000);


   seg1_track_residual_hist = std::make_unique<TH1F>("seg1_track_residual_hist", "Seg1: Residuals between the segment and the track", 60, -1.5, 1.5);
   seg2_track_residual_hist = std::make_unique<TH1F>("seg2_track_residual_hist", "Seg2: Residuals between the segment and the track", 60, -1.5, 1.5);
   seg3_track_residual_hist = std::make_unique<TH1F>("seg3_track_residual_hist", "Seg3: Residuals between the segment and the track", 60, -1.5, 1.5);

   seg1_track_pull_hist = std::make_unique<TH1F>("seg1_track_pull_hist", "Seg1: Pulls between the segment and the track", 80, -50, 50);
   seg2_track_pull_hist = std::make_unique<TH1F>("seg2_track_pull_hist", "Seg2: Pulls between the segment and the track", 80, -50, 50);
   seg3_track_pull_hist = std::make_unique<TH1F>("seg3_track_pull_hist", "Seg3: Pulls between the segment and the track", 80, -50, 50);




   sagittas_a_0p_hist.reserve(16);
   sagittas_a_5p_hist.reserve(16);
   sagittas_a_10p_hist.reserve(16);
   sagittas_a_15p_hist.reserve(16);
   sagittas_a_20p_hist.reserve(16);
   sagittas_a_25p_hist.reserve(16);
   sagittas_a_30p_hist.reserve(16);
   sagittas_a_35p_hist.reserve(16);
   sagittas_a_40p_hist.reserve(16);
   sagittas_a_45p_hist.reserve(16);
   sagittas_a_50p_hist.reserve(16);

   sagittas_c_0p_hist.reserve(16);
   sagittas_c_5p_hist.reserve(16);
   sagittas_c_10p_hist.reserve(16);
   sagittas_c_15p_hist.reserve(16);
   sagittas_c_20p_hist.reserve(16);
   sagittas_c_25p_hist.reserve(16);
   sagittas_c_30p_hist.reserve(16);
   sagittas_c_35p_hist.reserve(16);
   sagittas_c_40p_hist.reserve(16);
   sagittas_c_45p_hist.reserve(16);
   sagittas_c_50p_hist.reserve(16);


   sagittas_a_0p_improved_hist.reserve(16);
   sagittas_a_5p_improved_hist.reserve(16);
   sagittas_a_10p_improved_hist.reserve(16);
   sagittas_a_15p_improved_hist.reserve(16);
   sagittas_a_20p_improved_hist.reserve(16);
   sagittas_a_25p_improved_hist.reserve(16);
   sagittas_a_30p_improved_hist.reserve(16);
   sagittas_a_35p_improved_hist.reserve(16);
   sagittas_a_40p_improved_hist.reserve(16);
   sagittas_a_45p_improved_hist.reserve(16);
   sagittas_a_50p_improved_hist.reserve(16);
   sagittas_a_100p_improved_hist.reserve(16);
   sagittas_a_200p_improved_hist.reserve(16);
   sagittas_a_300p_improved_hist.reserve(16);

   sagittas_a_0p_mm1_improved_hist.reserve(16);
   sagittas_a_10p_mm1_improved_hist.reserve(16);
   sagittas_a_20p_mm1_improved_hist.reserve(16);
   sagittas_a_30p_mm1_improved_hist.reserve(16);
   sagittas_a_40p_mm1_improved_hist.reserve(16);
   sagittas_a_50p_mm1_improved_hist.reserve(16);
   sagittas_a_100p_mm1_improved_hist.reserve(16);

   sagittas_a_0p_mm2_improved_hist.reserve(16);
   sagittas_a_10p_mm2_improved_hist.reserve(16);
   sagittas_a_20p_mm2_improved_hist.reserve(16);
   sagittas_a_30p_mm2_improved_hist.reserve(16);
   sagittas_a_40p_mm2_improved_hist.reserve(16);
   sagittas_a_50p_mm2_improved_hist.reserve(16);
   sagittas_a_100p_mm2_improved_hist.reserve(16);

   sagittas_a_0p_stgc1_improved_hist.reserve(16);
   sagittas_a_10p_stgc1_improved_hist.reserve(16);
   sagittas_a_20p_stgc1_improved_hist.reserve(16);
   sagittas_a_30p_stgc1_improved_hist.reserve(16);
   sagittas_a_40p_stgc1_improved_hist.reserve(16);
   sagittas_a_50p_stgc1_improved_hist.reserve(16);
   sagittas_a_100p_stgc1_improved_hist.reserve(16);

   sagittas_a_0p_stgc2_improved_hist.reserve(16);
   sagittas_a_10p_stgc2_improved_hist.reserve(16);
   sagittas_a_20p_stgc2_improved_hist.reserve(16);
   sagittas_a_30p_stgc2_improved_hist.reserve(16);
   sagittas_a_40p_stgc2_improved_hist.reserve(16);
   sagittas_a_50p_stgc2_improved_hist.reserve(16);
   sagittas_a_100p_stgc2_improved_hist.reserve(16);   


   //t1 t2 t3
   sagittas_a_0p_mm1_t_improved_hist.reserve(48);
   sagittas_a_10p_mm1_t_improved_hist.reserve(48);
   sagittas_a_20p_mm1_t_improved_hist.reserve(48);
   sagittas_a_30p_mm1_t_improved_hist.reserve(48);
   sagittas_a_40p_mm1_t_improved_hist.reserve(48);
   sagittas_a_50p_mm1_t_improved_hist.reserve(48);
   sagittas_a_100p_mm1_t_improved_hist.reserve(48);

   sagittas_a_0p_mm2_t_improved_hist.reserve(48);
   sagittas_a_10p_mm2_t_improved_hist.reserve(48);
   sagittas_a_20p_mm2_t_improved_hist.reserve(48);
   sagittas_a_30p_mm2_t_improved_hist.reserve(48);
   sagittas_a_40p_mm2_t_improved_hist.reserve(48);
   sagittas_a_50p_mm2_t_improved_hist.reserve(48);
   sagittas_a_100p_mm2_t_improved_hist.reserve(48);

   /*sagittas_a_0p_mm1_t2_improved_hist.reserve(16);
   sagittas_a_10p_mm1_t2_improved_hist.reserve(16);
   sagittas_a_20p_mm1_t2_improved_hist.reserve(16);
   sagittas_a_30p_mm1_t2_improved_hist.reserve(16);
   sagittas_a_40p_mm1_t2_improved_hist.reserve(16);
   sagittas_a_50p_mm1_t2_improved_hist.reserve(16);
   sagittas_a_100p_mm1_t2_improved_hist.reserve(16);

   sagittas_a_0p_mm2_t2_improved_hist.reserve(16);
   sagittas_a_10p_mm2_t2_improved_hist.reserve(16);
   sagittas_a_20p_mm2_t2_improved_hist.reserve(16);
   sagittas_a_30p_mm2_t2_improved_hist.reserve(16);
   sagittas_a_40p_mm2_t2_improved_hist.reserve(16);
   sagittas_a_50p_mm2_t2_improved_hist.reserve(16);
   sagittas_a_100p_mm2_t2_improved_hist.reserve(16);
   */
   sagittas_a_0p_stgc1_t_improved_hist.reserve(48);
   sagittas_a_10p_stgc1_t_improved_hist.reserve(48);
   sagittas_a_20p_stgc1_t_improved_hist.reserve(48);
   sagittas_a_30p_stgc1_t_improved_hist.reserve(48);
   sagittas_a_40p_stgc1_t_improved_hist.reserve(48);
   sagittas_a_50p_stgc1_t_improved_hist.reserve(48);
   sagittas_a_100p_stgc1_t_improved_hist.reserve(48);

   sagittas_a_0p_stgc2_t_improved_hist.reserve(48);
   sagittas_a_10p_stgc2_t_improved_hist.reserve(48);
   sagittas_a_20p_stgc2_t_improved_hist.reserve(48);
   sagittas_a_30p_stgc2_t_improved_hist.reserve(48);
   sagittas_a_40p_stgc2_t_improved_hist.reserve(48);
   sagittas_a_50p_stgc2_t_improved_hist.reserve(48);
   sagittas_a_100p_stgc2_t_improved_hist.reserve(48);   
   /*
   sagittas_a_0p_stgc1_t2_improved_hist.reserve(16);
   sagittas_a_10p_stgc1_t2_improved_hist.reserve(16);
   sagittas_a_20p_stgc1_t2_improved_hist.reserve(16);
   sagittas_a_30p_stgc1_t2_improved_hist.reserve(16);
   sagittas_a_40p_stgc1_t2_improved_hist.reserve(16);
   sagittas_a_50p_stgc1_t2_improved_hist.reserve(16);
   sagittas_a_100p_stgc1_t2_improved_hist.reserve(16);

   sagittas_a_0p_stgc2_t2_improved_hist.reserve(16);
   sagittas_a_10p_stgc2_t2_improved_hist.reserve(16);
   sagittas_a_20p_stgc2_t2_improved_hist.reserve(16);
   sagittas_a_30p_stgc2_t2_improved_hist.reserve(16);
   sagittas_a_40p_stgc2_t2_improved_hist.reserve(16);
   sagittas_a_50p_stgc2_t2_improved_hist.reserve(16);
   sagittas_a_100p_stgc2_t2_improved_hist.reserve(16);   

   sagittas_a_0p_stgc1_t3_improved_hist.reserve(16);
   sagittas_a_10p_stgc1_t3_improved_hist.reserve(16);
   sagittas_a_20p_stgc1_t3_improved_hist.reserve(16);
   sagittas_a_30p_stgc1_t3_improved_hist.reserve(16);
   sagittas_a_40p_stgc1_t3_improved_hist.reserve(16);
   sagittas_a_50p_stgc1_t3_improved_hist.reserve(16);
   sagittas_a_100p_stgc1_t3_improved_hist.reserve(16);

   sagittas_a_0p_stgc2_t3_improved_hist.reserve(16);
   sagittas_a_10p_stgc2_t3_improved_hist.reserve(16);
   sagittas_a_20p_stgc2_t3_improved_hist.reserve(16);
   sagittas_a_30p_stgc2_t3_improved_hist.reserve(16);
   sagittas_a_40p_stgc2_t3_improved_hist.reserve(16);
   sagittas_a_50p_stgc2_t3_improved_hist.reserve(16);
   sagittas_a_100p_stgc2_t3_improved_hist.reserve(16);   
   */

   sagittas_c_0p_improved_hist.reserve(16);
   sagittas_c_5p_improved_hist.reserve(16);
   sagittas_c_10p_improved_hist.reserve(16);
   sagittas_c_15p_improved_hist.reserve(16);
   sagittas_c_20p_improved_hist.reserve(16);
   sagittas_c_25p_improved_hist.reserve(16);
   sagittas_c_30p_improved_hist.reserve(16);
   sagittas_c_35p_improved_hist.reserve(16);
   sagittas_c_40p_improved_hist.reserve(16);
   sagittas_c_45p_improved_hist.reserve(16);
   sagittas_c_50p_improved_hist.reserve(16);
   sagittas_c_100p_improved_hist.reserve(16);
   sagittas_c_200p_improved_hist.reserve(16);
   sagittas_c_300p_improved_hist.reserve(16);

   sagittas_c_0p_mm1_improved_hist.reserve(16);
   sagittas_c_10p_mm1_improved_hist.reserve(16);
   sagittas_c_20p_mm1_improved_hist.reserve(16);
   sagittas_c_30p_mm1_improved_hist.reserve(16);
   sagittas_c_40p_mm1_improved_hist.reserve(16);
   sagittas_c_50p_mm1_improved_hist.reserve(16);
   sagittas_c_100p_mm1_improved_hist.reserve(16);

   sagittas_c_0p_mm2_improved_hist.reserve(16);
   sagittas_c_10p_mm2_improved_hist.reserve(16);
   sagittas_c_20p_mm2_improved_hist.reserve(16);
   sagittas_c_30p_mm2_improved_hist.reserve(16);
   sagittas_c_40p_mm2_improved_hist.reserve(16);
   sagittas_c_50p_mm2_improved_hist.reserve(16);
   sagittas_c_100p_mm2_improved_hist.reserve(16);

   sagittas_c_0p_stgc1_improved_hist.reserve(16);
   sagittas_c_10p_stgc1_improved_hist.reserve(16);
   sagittas_c_20p_stgc1_improved_hist.reserve(16);
   sagittas_c_30p_stgc1_improved_hist.reserve(16);
   sagittas_c_40p_stgc1_improved_hist.reserve(16);
   sagittas_c_50p_stgc1_improved_hist.reserve(16);
   sagittas_c_100p_stgc1_improved_hist.reserve(16);

   sagittas_c_0p_stgc2_improved_hist.reserve(16);
   sagittas_c_10p_stgc2_improved_hist.reserve(16);
   sagittas_c_20p_stgc2_improved_hist.reserve(16);
   sagittas_c_30p_stgc2_improved_hist.reserve(16);
   sagittas_c_40p_stgc2_improved_hist.reserve(16);
   sagittas_c_50p_stgc2_improved_hist.reserve(16);
   sagittas_c_100p_stgc2_improved_hist.reserve(16);
   
   // t1 t2 t3
   sagittas_c_0p_mm1_t_improved_hist.reserve(48);
   sagittas_c_10p_mm1_t_improved_hist.reserve(48);
   sagittas_c_20p_mm1_t_improved_hist.reserve(48);
   sagittas_c_30p_mm1_t_improved_hist.reserve(48);
   sagittas_c_40p_mm1_t_improved_hist.reserve(48);
   sagittas_c_50p_mm1_t_improved_hist.reserve(48);
   sagittas_c_100p_mm1_t_improved_hist.reserve(48);

   sagittas_c_0p_mm2_t_improved_hist.reserve(48);
   sagittas_c_10p_mm2_t_improved_hist.reserve(48);
   sagittas_c_20p_mm2_t_improved_hist.reserve(48);
   sagittas_c_30p_mm2_t_improved_hist.reserve(48);
   sagittas_c_40p_mm2_t_improved_hist.reserve(48);
   sagittas_c_50p_mm2_t_improved_hist.reserve(48);
   sagittas_c_100p_mm2_t_improved_hist.reserve(48);

   /*   sagittas_c_0p_mm1_t2_improved_hist.reserve(16);
   sagittas_c_10p_mm1_t2_improved_hist.reserve(16);
   sagittas_c_20p_mm1_t2_improved_hist.reserve(16);
   sagittas_c_30p_mm1_t2_improved_hist.reserve(16);
   sagittas_c_40p_mm1_t2_improved_hist.reserve(16);
   sagittas_c_50p_mm1_t2_improved_hist.reserve(16);
   sagittas_c_100p_mm1_t2_improved_hist.reserve(16);

   sagittas_c_0p_mm2_t2_improved_hist.reserve(16);
   sagittas_c_10p_mm2_t2_improved_hist.reserve(16);
   sagittas_c_20p_mm2_t2_improved_hist.reserve(16);
   sagittas_c_30p_mm2_t2_improved_hist.reserve(16);
   sagittas_c_40p_mm2_t2_improved_hist.reserve(16);
   sagittas_c_50p_mm2_t2_improved_hist.reserve(16);
   sagittas_c_100p_mm2_t2_improved_hist.reserve(16);
   */
   sagittas_c_0p_stgc1_t_improved_hist.reserve(48);
   sagittas_c_10p_stgc1_t_improved_hist.reserve(48);
   sagittas_c_20p_stgc1_t_improved_hist.reserve(48);
   sagittas_c_30p_stgc1_t_improved_hist.reserve(48);
   sagittas_c_40p_stgc1_t_improved_hist.reserve(48);
   sagittas_c_50p_stgc1_t_improved_hist.reserve(48);
   sagittas_c_100p_stgc1_t_improved_hist.reserve(48);

   sagittas_c_0p_stgc2_t_improved_hist.reserve(48);
   sagittas_c_10p_stgc2_t_improved_hist.reserve(48);
   sagittas_c_20p_stgc2_t_improved_hist.reserve(48);
   sagittas_c_30p_stgc2_t_improved_hist.reserve(48);
   sagittas_c_40p_stgc2_t_improved_hist.reserve(48);
   sagittas_c_50p_stgc2_t_improved_hist.reserve(48);
   sagittas_c_100p_stgc2_t_improved_hist.reserve(48);   
   /*
   sagittas_c_0p_stgc1_t2_improved_hist.reserve(16);
   sagittas_c_10p_stgc1_t2_improved_hist.reserve(16);
   sagittas_c_20p_stgc1_t2_improved_hist.reserve(16);
   sagittas_c_30p_stgc1_t2_improved_hist.reserve(16);
   sagittas_c_40p_stgc1_t2_improved_hist.reserve(16);
   sagittas_c_50p_stgc1_t2_improved_hist.reserve(16);
   sagittas_c_100p_stgc1_t2_improved_hist.reserve(16);

   sagittas_c_0p_stgc2_t2_improved_hist.reserve(16);
   sagittas_c_10p_stgc2_t2_improved_hist.reserve(16);
   sagittas_c_20p_stgc2_t2_improved_hist.reserve(16);
   sagittas_c_30p_stgc2_t2_improved_hist.reserve(16);
   sagittas_c_40p_stgc2_t2_improved_hist.reserve(16);
   sagittas_c_50p_stgc2_t2_improved_hist.reserve(16);
   sagittas_c_100p_stgc2_t2_improved_hist.reserve(16);   

   sagittas_c_0p_stgc1_t3_improved_hist.reserve(16);
   sagittas_c_10p_stgc1_t3_improved_hist.reserve(16);
   sagittas_c_20p_stgc1_t3_improved_hist.reserve(16);
   sagittas_c_30p_stgc1_t3_improved_hist.reserve(16);
   sagittas_c_40p_stgc1_t3_improved_hist.reserve(16);
   sagittas_c_50p_stgc1_t3_improved_hist.reserve(16);
   sagittas_c_100p_stgc1_t3_improved_hist.reserve(16);

   sagittas_c_0p_stgc2_t3_improved_hist.reserve(16);
   sagittas_c_10p_stgc2_t3_improved_hist.reserve(16);
   sagittas_c_20p_stgc2_t3_improved_hist.reserve(16);
   sagittas_c_30p_stgc2_t3_improved_hist.reserve(16);
   sagittas_c_40p_stgc2_t3_improved_hist.reserve(16);
   sagittas_c_50p_stgc2_t3_improved_hist.reserve(16);
   sagittas_c_100p_stgc2_t3_improved_hist.reserve(16);   
   */

   sagitta_a_2nd_coord_0p_hist.reserve(16);
   sagitta_a_2nd_coord_30p_hist.reserve(16);
   sagitta_c_2nd_coord_0p_hist.reserve(16);
   sagitta_c_2nd_coord_30p_hist.reserve(16);

   sagitta_a_2nd_coord_0p_improved_hist.reserve(16);
   sagitta_a_2nd_coord_30p_improved_hist.reserve(16);
   sagitta_c_2nd_coord_0p_improved_hist.reserve(16);
   sagitta_c_2nd_coord_30p_improved_hist.reserve(16);


   sagitta_a_t223_30p_hist.reserve(16);

   for (int i = 1; i < 17; ++i)
   {
      CreateSagittaHist(sagittas_a_0p_hist, i, 0, "a");
      CreateSagittaHist(sagittas_a_5p_hist, i, 5, "a");
      CreateSagittaHist(sagittas_a_10p_hist, i, 10, "a");
      CreateSagittaHist(sagittas_a_15p_hist, i, 15, "a");
      CreateSagittaHist(sagittas_a_20p_hist, i, 20, "a");
      CreateSagittaHist(sagittas_a_25p_hist, i, 25, "a");
      CreateSagittaHist(sagittas_a_30p_hist, i, 30, "a");
      CreateSagittaHist(sagittas_a_35p_hist, i, 35, "a");
      CreateSagittaHist(sagittas_a_40p_hist, i, 40, "a");
      CreateSagittaHist(sagittas_a_45p_hist, i, 45, "a");
      CreateSagittaHist(sagittas_a_50p_hist, i, 50, "a");

      CreateSagittaHist(sagittas_c_0p_hist, i, 0, "c");
      CreateSagittaHist(sagittas_c_5p_hist, i, 5, "c");
      CreateSagittaHist(sagittas_c_10p_hist, i, 10, "c");
      CreateSagittaHist(sagittas_c_15p_hist, i, 15, "c");
      CreateSagittaHist(sagittas_c_20p_hist, i, 20, "c");
      CreateSagittaHist(sagittas_c_25p_hist, i, 25, "c");
      CreateSagittaHist(sagittas_c_30p_hist, i, 30, "c");
      CreateSagittaHist(sagittas_c_35p_hist, i, 35, "c");
      CreateSagittaHist(sagittas_c_40p_hist, i, 40, "c");
      CreateSagittaHist(sagittas_c_45p_hist, i, 45, "c");
      CreateSagittaHist(sagittas_c_50p_hist, i, 50, "c");



      CreateSagittaHist(sagittas_a_0p_improved_hist, i, 0, "A");
      CreateSagittaHist(sagittas_a_5p_improved_hist, i, 5, "A");
      CreateSagittaHist(sagittas_a_10p_improved_hist, i, 10, "A");
      CreateSagittaHist(sagittas_a_15p_improved_hist, i, 15, "A");
      CreateSagittaHist(sagittas_a_20p_improved_hist, i, 20, "A");
      CreateSagittaHist(sagittas_a_25p_improved_hist, i, 25, "A");
      CreateSagittaHist(sagittas_a_30p_improved_hist, i, 30, "A");
      CreateSagittaHist(sagittas_a_35p_improved_hist, i, 35, "A");
      CreateSagittaHist(sagittas_a_40p_improved_hist, i, 40, "A");
      CreateSagittaHist(sagittas_a_45p_improved_hist, i, 45, "A");
      CreateSagittaHist(sagittas_a_50p_improved_hist, i, 50, "A");
      CreateSagittaHist(sagittas_a_100p_improved_hist, i, 100, "A");
      CreateSagittaHist(sagittas_a_200p_improved_hist, i, 200, "A");
      CreateSagittaHist(sagittas_a_300p_improved_hist, i, 300, "A");


      CreateSagittaHist(sagittas_a_0p_mm1_improved_hist, i, 0, "A MM-IP");
      CreateSagittaHist(sagittas_a_10p_mm1_improved_hist, i, 10, "A MM-IP");
      CreateSagittaHist(sagittas_a_20p_mm1_improved_hist, i, 20, "A MM-IP");  
      CreateSagittaHist(sagittas_a_30p_mm1_improved_hist, i, 30, "A MM-IP");
      CreateSagittaHist(sagittas_a_40p_mm1_improved_hist, i, 40, "A MM-IP");
      CreateSagittaHist(sagittas_a_50p_mm1_improved_hist, i, 50, "A MM-IP");
      CreateSagittaHist(sagittas_a_100p_mm1_improved_hist, i, 100, "A MM-IP");

      CreateSagittaHist(sagittas_a_0p_mm2_improved_hist, i, 0, "A MM-HO");
      CreateSagittaHist(sagittas_a_10p_mm2_improved_hist, i, 10, "A MM-HO");
      CreateSagittaHist(sagittas_a_20p_mm2_improved_hist, i, 20, "A MM-HO");
      CreateSagittaHist(sagittas_a_30p_mm2_improved_hist, i, 30, "A MM-HO");
      CreateSagittaHist(sagittas_a_40p_mm2_improved_hist, i, 40, "A MM-HO");
      CreateSagittaHist(sagittas_a_50p_mm2_improved_hist, i, 50, "A MM-HO");
      CreateSagittaHist(sagittas_a_100p_mm2_improved_hist, i, 100, "A MM-HO");

      CreateSagittaHist(sagittas_a_0p_stgc1_improved_hist, i, 0, "A sTGC-IP");
      CreateSagittaHist(sagittas_a_10p_stgc1_improved_hist, i, 10, "A sTGC-IP");
      CreateSagittaHist(sagittas_a_20p_stgc1_improved_hist, i, 20, "A sTGC-IP");
      CreateSagittaHist(sagittas_a_30p_stgc1_improved_hist, i, 30, "A sTGC-IP");
      CreateSagittaHist(sagittas_a_40p_stgc1_improved_hist, i, 40, "A sTGC-IP");
      CreateSagittaHist(sagittas_a_50p_stgc1_improved_hist, i, 50, "A sTGC-IP");
      CreateSagittaHist(sagittas_a_100p_stgc1_improved_hist, i, 100, "A sTGC-IP");

      CreateSagittaHist(sagittas_a_0p_stgc2_improved_hist, i, 0, "A sTGC-HO");
      CreateSagittaHist(sagittas_a_10p_stgc2_improved_hist, i, 10, "A sTGC-HO");
      CreateSagittaHist(sagittas_a_20p_stgc2_improved_hist, i, 20, "A sTGC-HO");
      CreateSagittaHist(sagittas_a_30p_stgc2_improved_hist, i, 30, "A sTGC-HO");
      CreateSagittaHist(sagittas_a_40p_stgc2_improved_hist, i, 40, "A sTGC-HO");
      CreateSagittaHist(sagittas_a_50p_stgc2_improved_hist, i, 50, "A sTGC-HO");
      CreateSagittaHist(sagittas_a_100p_stgc2_improved_hist, i, 100, "A sTGC-HO");

      // t1 t2 t3
      for (int n_tower=1;n_tower < 4; ++n_tower)
      {
	CreateSagittaHist(sagittas_a_0p_mm1_t_improved_hist, i+(n_tower-1)*16, 0, "A T MM-IP");
	CreateSagittaHist(sagittas_a_10p_mm1_t_improved_hist, i+(n_tower-1)*16, 10, "A T MM-IP");
	CreateSagittaHist(sagittas_a_20p_mm1_t_improved_hist, i+(n_tower-1)*16, 20, "A T MM-IP");  
	CreateSagittaHist(sagittas_a_30p_mm1_t_improved_hist, i+(n_tower-1)*16, 30, "A T MM-IP");
	CreateSagittaHist(sagittas_a_40p_mm1_t_improved_hist, i+(n_tower-1)*16, 40, "A T MM-IP");
	CreateSagittaHist(sagittas_a_50p_mm1_t_improved_hist, i+(n_tower-1)*16, 50, "A T MM-IP");
	CreateSagittaHist(sagittas_a_100p_mm1_t_improved_hist, i+(n_tower-1)*16, 100, "A T MM-IP");

	CreateSagittaHist(sagittas_a_0p_mm2_t_improved_hist, i+(n_tower-1)*16, 0, "A T MM-HO");
	CreateSagittaHist(sagittas_a_10p_mm2_t_improved_hist, i+(n_tower-1)*16, 10, "A T MM-HO");
	CreateSagittaHist(sagittas_a_20p_mm2_t_improved_hist, i+(n_tower-1)*16, 20, "A T MM-HO");
	CreateSagittaHist(sagittas_a_30p_mm2_t_improved_hist, i+(n_tower-1)*16, 30, "A T MM-HO");
	CreateSagittaHist(sagittas_a_40p_mm2_t_improved_hist, i+(n_tower-1)*16, 40, "A T MM-HO");
	CreateSagittaHist(sagittas_a_50p_mm2_t_improved_hist, i+(n_tower-1)*16, 50, "A T MM-HO");
	CreateSagittaHist(sagittas_a_100p_mm2_t_improved_hist, i+(n_tower-1)*16, 100, "A T MM-HO");

	CreateSagittaHist(sagittas_a_0p_stgc1_t_improved_hist, i+(n_tower-1)*16, 0, "A T sTGC-IP");
	CreateSagittaHist(sagittas_a_10p_stgc1_t_improved_hist, i+(n_tower-1)*16, 10, "A T sTGC-IP");
	CreateSagittaHist(sagittas_a_20p_stgc1_t_improved_hist, i+(n_tower-1)*16, 20, "A T sTGC-IP");
	CreateSagittaHist(sagittas_a_30p_stgc1_t_improved_hist, i+(n_tower-1)*16, 30, "A T sTGC-IP");
	CreateSagittaHist(sagittas_a_40p_stgc1_t_improved_hist, i+(n_tower-1)*16, 40, "A T sTGC-IP");
	CreateSagittaHist(sagittas_a_50p_stgc1_t_improved_hist, i+(n_tower-1)*16, 50, "A T sTGC-IP");
	CreateSagittaHist(sagittas_a_100p_stgc1_t_improved_hist, i+(n_tower-1)*16, 100, "A T sTGC-IP");

	CreateSagittaHist(sagittas_a_0p_stgc2_t_improved_hist, i+(n_tower-1)*16, 0, "A T sTGC-HO");
	CreateSagittaHist(sagittas_a_10p_stgc2_t_improved_hist, i+(n_tower-1)*16, 10, "A T sTGC-HO");
	CreateSagittaHist(sagittas_a_20p_stgc2_t_improved_hist, i+(n_tower-1)*16, 20, "A T sTGC-HO");
	CreateSagittaHist(sagittas_a_30p_stgc2_t_improved_hist, i+(n_tower-1)*16, 30, "A T sTGC-HO");
	CreateSagittaHist(sagittas_a_40p_stgc2_t_improved_hist, i+(n_tower-1)*16, 40, "A T sTGC-HO");
	CreateSagittaHist(sagittas_a_50p_stgc2_t_improved_hist, i+(n_tower-1)*16, 50, "A T sTGC-HO");
	CreateSagittaHist(sagittas_a_100p_stgc2_t_improved_hist, i+(n_tower-1)*16, 100, "A T sTGC-HO");
      }
      
      CreateSagittaHist(sagittas_c_0p_improved_hist, i, 0, "C");
      CreateSagittaHist(sagittas_c_5p_improved_hist, i, 5, "C");
      CreateSagittaHist(sagittas_c_10p_improved_hist, i, 10, "C");
      CreateSagittaHist(sagittas_c_15p_improved_hist, i, 15, "C");
      CreateSagittaHist(sagittas_c_20p_improved_hist, i, 20, "C");
      CreateSagittaHist(sagittas_c_25p_improved_hist, i, 25, "C");
      CreateSagittaHist(sagittas_c_30p_improved_hist, i, 30, "C");
      CreateSagittaHist(sagittas_c_35p_improved_hist, i, 35, "C");
      CreateSagittaHist(sagittas_c_40p_improved_hist, i, 40, "C");
      CreateSagittaHist(sagittas_c_45p_improved_hist, i, 45, "C");
      CreateSagittaHist(sagittas_c_50p_improved_hist, i, 50, "C");
      CreateSagittaHist(sagittas_c_100p_improved_hist, i, 100, "C");
      CreateSagittaHist(sagittas_c_200p_improved_hist, i, 200, "C");
      CreateSagittaHist(sagittas_c_300p_improved_hist, i, 300, "C");

      CreateSagittaHist(sagittas_c_0p_mm1_improved_hist, i, 0, "C MM-IP");
      CreateSagittaHist(sagittas_c_10p_mm1_improved_hist, i, 10, "C MM-IP");
      CreateSagittaHist(sagittas_c_20p_mm1_improved_hist, i, 20, "C MM-IP");  
      CreateSagittaHist(sagittas_c_30p_mm1_improved_hist, i, 30, "C MM-IP");
      CreateSagittaHist(sagittas_c_40p_mm1_improved_hist, i, 40, "C MM-IP");
      CreateSagittaHist(sagittas_c_50p_mm1_improved_hist, i, 50, "C MM-IP");
      CreateSagittaHist(sagittas_c_100p_mm1_improved_hist, i, 100, "C MM-IP");

      CreateSagittaHist(sagittas_c_0p_mm2_improved_hist, i, 0, "C MM-HO");
      CreateSagittaHist(sagittas_c_10p_mm2_improved_hist, i, 10, "C MM-HO");
      CreateSagittaHist(sagittas_c_20p_mm2_improved_hist, i, 20, "C MM-HO");
      CreateSagittaHist(sagittas_c_30p_mm2_improved_hist, i, 30, "C MM-HO");
      CreateSagittaHist(sagittas_c_40p_mm2_improved_hist, i, 40, "C MM-HO");
      CreateSagittaHist(sagittas_c_50p_mm2_improved_hist, i, 50, "C MM-HO");
      CreateSagittaHist(sagittas_c_100p_mm2_improved_hist, i, 100, "C MM-HO");

      CreateSagittaHist(sagittas_c_0p_stgc1_improved_hist, i, 0, "C sTGC-IP");
      CreateSagittaHist(sagittas_c_10p_stgc1_improved_hist, i, 10, "C sTGC-IP");
      CreateSagittaHist(sagittas_c_20p_stgc1_improved_hist, i, 20, "C sTGC-IP");
      CreateSagittaHist(sagittas_c_30p_stgc1_improved_hist, i, 30, "C sTGC-IP");
      CreateSagittaHist(sagittas_c_40p_stgc1_improved_hist, i, 40, "C sTGC-IP");
      CreateSagittaHist(sagittas_c_50p_stgc1_improved_hist, i, 50, "C sTGC-IP");
      CreateSagittaHist(sagittas_c_100p_stgc1_improved_hist, i, 100, "C sTGC-IP");

      CreateSagittaHist(sagittas_c_0p_stgc2_improved_hist, i, 0, "C sTGC-HO");
      CreateSagittaHist(sagittas_c_10p_stgc2_improved_hist, i, 10, "C sTGC-HO");
      CreateSagittaHist(sagittas_c_20p_stgc2_improved_hist, i, 20, "C sTGC-HO");
      CreateSagittaHist(sagittas_c_30p_stgc2_improved_hist, i, 30, "C sTGC-HO");
      CreateSagittaHist(sagittas_c_40p_stgc2_improved_hist, i, 40, "C sTGC-HO");
      CreateSagittaHist(sagittas_c_50p_stgc2_improved_hist, i, 50, "C sTGC-HO");
      CreateSagittaHist(sagittas_c_100p_stgc2_improved_hist, i, 100, "C sTGC-HO");

      // t1 t2 t3
      for (int n_tower=1;n_tower < 4; ++n_tower)
      {
	CreateSagittaHist(sagittas_c_0p_mm1_t_improved_hist, i+(n_tower-1)*16, 0, "C T MM-IP");
	CreateSagittaHist(sagittas_c_10p_mm1_t_improved_hist, i+(n_tower-1)*16, 10, "C T MM-IP");
	CreateSagittaHist(sagittas_c_20p_mm1_t_improved_hist, i+(n_tower-1)*16, 20, "C T MM-IP");  
	CreateSagittaHist(sagittas_c_30p_mm1_t_improved_hist, i+(n_tower-1)*16, 30, "C T MM-IP");
	CreateSagittaHist(sagittas_c_40p_mm1_t_improved_hist, i+(n_tower-1)*16, 40, "C T MM-IP");
	CreateSagittaHist(sagittas_c_50p_mm1_t_improved_hist, i+(n_tower-1)*16, 50, "C T MM-IP");
	CreateSagittaHist(sagittas_c_100p_mm1_t_improved_hist, i+(n_tower-1)*16, 100, "C T MM-IP");

	CreateSagittaHist(sagittas_c_0p_mm2_t_improved_hist, i+(n_tower-1)*16, 0, "C T MM-HO");
	CreateSagittaHist(sagittas_c_10p_mm2_t_improved_hist, i+(n_tower-1)*16, 10, "C T MM-HO");
	CreateSagittaHist(sagittas_c_20p_mm2_t_improved_hist, i+(n_tower-1)*16, 20, "C T MM-HO");
	CreateSagittaHist(sagittas_c_30p_mm2_t_improved_hist, i+(n_tower-1)*16, 30, "C T MM-HO");
	CreateSagittaHist(sagittas_c_40p_mm2_t_improved_hist, i+(n_tower-1)*16, 40, "C T MM-HO");
	CreateSagittaHist(sagittas_c_50p_mm2_t_improved_hist, i+(n_tower-1)*16, 50, "C T MM-HO");
	CreateSagittaHist(sagittas_c_100p_mm2_t_improved_hist, i+(n_tower-1)*16, 100, "C T MM-HO");

	CreateSagittaHist(sagittas_c_0p_stgc1_t_improved_hist, i+(n_tower-1)*16, 0, "C T sTGC-IP");
	CreateSagittaHist(sagittas_c_10p_stgc1_t_improved_hist, i+(n_tower-1)*16, 10, "C T sTGC-IP");
	CreateSagittaHist(sagittas_c_20p_stgc1_t_improved_hist, i+(n_tower-1)*16, 20, "C T sTGC-IP");
	CreateSagittaHist(sagittas_c_30p_stgc1_t_improved_hist, i+(n_tower-1)*16, 30, "C T sTGC-IP");
	CreateSagittaHist(sagittas_c_40p_stgc1_t_improved_hist, i+(n_tower-1)*16, 40, "C T sTGC-IP");
	CreateSagittaHist(sagittas_c_50p_stgc1_t_improved_hist, i+(n_tower-1)*16, 50, "C T sTGC-IP");
	CreateSagittaHist(sagittas_c_100p_stgc1_t_improved_hist, i+(n_tower-1)*16, 100, "C T sTGC-IP");

	CreateSagittaHist(sagittas_c_0p_stgc2_t_improved_hist, i+(n_tower-1)*16, 0, "C T sTGC-HO");
	CreateSagittaHist(sagittas_c_10p_stgc2_t_improved_hist, i+(n_tower-1)*16, 10, "C T sTGC-HO");
	CreateSagittaHist(sagittas_c_20p_stgc2_t_improved_hist, i+(n_tower-1)*16, 20, "C T sTGC-HO");
	CreateSagittaHist(sagittas_c_30p_stgc2_t_improved_hist, i+(n_tower-1)*16, 30, "C T sTGC-HO");
	CreateSagittaHist(sagittas_c_40p_stgc2_t_improved_hist, i+(n_tower-1)*16, 40, "C T sTGC-HO");
	CreateSagittaHist(sagittas_c_50p_stgc2_t_improved_hist, i+(n_tower-1)*16, 50, "C T sTGC-HO");
	CreateSagittaHist(sagittas_c_100p_stgc2_t_improved_hist, i+(n_tower-1)*16, 100, "C T sTGC-HO");
      }

      CreateSagittaHist(sagitta_a_2nd_coord_0p_hist, i, 0, "a_2nd_coord");
      CreateSagittaHist(sagitta_a_2nd_coord_30p_hist, i, 30, "a_2nd_coord");
      CreateSagittaHist(sagitta_c_2nd_coord_0p_hist, i, 0, "c_2nd_coord");
      CreateSagittaHist(sagitta_c_2nd_coord_30p_hist, i, 30, "c_2nd_coord");

      CreateSagittaHist(sagitta_a_2nd_coord_0p_improved_hist, i, 0, "a_2nd_coord_improved");
      CreateSagittaHist(sagitta_a_2nd_coord_30p_improved_hist, i, 30, "a_2nd_coord_improved");
      CreateSagittaHist(sagitta_c_2nd_coord_0p_improved_hist, i, 0, "c_2nd_coord_improved");
      CreateSagittaHist(sagitta_c_2nd_coord_30p_improved_hist, i, 30, "c_2nd_coord_improved");


      CreateSagittaHist(sagitta_a_t223_30p_hist, i, 30, "a_t223");
   }
}


void tree::Loop()
{
   int nentries = fChain->GetEntries();
   // int nentries = 1000000;
   std::cout << "Looping over " << nentries << " events" << std::endl;

   int passed = 0;
   int failed = 0;

   int progress = 0;

   for (int i = 0; i < nentries; i++)
   {
      fChain->GetEntry(i);

      if(i % 10000==0) std::cout << i << std::endl;

   // std::cout << segger1_hitavg_local_x << "   " <<segger1_hitavg_local_y << "   " <<segger1_hitavg_local_z << "   " <<std::endl; 
   // std::cout << segger2_hitavg_local_x << "   " <<segger2_hitavg_local_y << "   " <<segger2_hitavg_local_z << "   " <<std::endl; 
   // std::cout << segger3_hitavg_local_x << "   " <<segger3_hitavg_local_y << "   " <<segger3_hitavg_local_z << std::endl; 

   // if (seg1_eta_index > 0)
   // {
   //    std::cout << "A-side " <<std::endl; 
   // }
   // else
   // {
   //    std::cout << "C-side " <<std::endl; 
   // }
   // std::cout << "seg1 track hitavg local " << segger1_hitavg_local_x <<std::endl; 
   // std::cout << "seg2 track hitavg local " << segger2_hitavg_local_x << std::endl; 
   // std::cout << "seg3 track hitavg local " << segger3_hitavg_local_x << std::endl; 

   // std::cout << "regular global seg1" << "   " <<seg1_global_x << "   " <<seg1_global_y << "   " <<seg1_global_z << std::endl;
   // std::cout << "improved global seg1" << "   " <<seg1_global_improved_x << "   " <<seg1_global_improved_y << "   " <<seg1_global_improved_z << std::endl; 
   // std::cout << "regular global seg2" << "   " <<seg2_global_x << "   " <<seg2_global_y << "   " <<seg2_global_z << std::endl;
   // std::cout << "improved global seg2" << "   " <<seg2_global_improved_x << "   " <<seg2_global_improved_y << "   " <<seg2_global_improved_z << std::endl; 
   // std::cout << "regular global seg3" << "   " <<seg3_global_x << "   " <<seg3_global_y << "   " <<seg3_global_z << std::endl;
   // std::cout << "improved global seg3" << "   " <<seg3_global_improved_x << "   " <<seg3_global_improved_y << "   " <<seg3_global_improved_z << std::endl; 

   // std::cout << "regular local seg1" << "   " <<seg1_local_x << "   " <<seg1_local_y << "   " <<seg1_local_z << std::endl;
   // std::cout << "improved local seg1" << "   " <<seg1_local_improved_x << "   " <<seg1_local_improved_y << "   " <<seg1_local_improved_z << std::endl; 
   // std::cout << "regular local seg2" << "   " <<seg2_local_x << "   " <<seg2_local_y << "   " <<seg2_local_z << std::endl;
   // std::cout << "improved local seg2" << "   " <<seg2_local_improved_x << "   " <<seg2_local_improved_y << "   " <<seg2_local_improved_z << std::endl; 
   // std::cout << "regular local seg3" << "   " <<seg3_local_x << "   " <<seg3_local_y << "   " <<seg3_local_z << std::endl;
   // std::cout << "improved local seg3" << "   " <<seg3_local_improved_x << "   " <<seg3_local_improved_y << "   " <<seg3_local_improved_z << std::endl<< std::endl<< std::endl; 




      // Define comb_id 

      int comb_id;
      std::string s1 = *seg1_name_short;
      std::string s2 = *seg2_name_short;
      std::string s3 = *seg3_name_short;
      std::string name = s1 + s2 + s3;
      if (name == "eiemeo")
      {
         comb_id = 1;
      }
      else if (name == "eeemeo")
      {
         comb_id = 2;
      }
      else if (name == "eieeem")
      {
         comb_id = 3;
      }
      else if (name == "eibeem")
      {
         comb_id = 4;
      }
      else if (name == "bieeem")
      {
         comb_id = 5;
      }

      // Calculate values
   
      TVector3 seg1_vec(seg1_global_x, seg1_global_y, seg1_global_z);
      TVector3 seg2_vec(seg2_global_x, seg2_global_y, seg2_global_z);
      TVector3 seg3_vec(seg3_global_x, seg3_global_y, seg3_global_z);

      TVector3 seg1_improved_vec(seg1_global_improved_x, seg1_global_improved_y, seg1_global_improved_z);
      TVector3 seg2_improved_vec(seg2_global_improved_x, seg2_global_improved_y, seg2_global_improved_z);
      TVector3 seg3_improved_vec(seg3_global_improved_x, seg3_global_improved_y, seg3_global_improved_z);

      /*      if(std::abs(mm1_eta_index) >2 || std::abs(mm2_eta_index) >2 || std::abs(stgc1_eta_index) >3 || std::abs(stgc2_eta_index) >3){
	std::cout << "mm1 eta " << mm1_eta_index << std::endl;
	std::cout << "mm2 eta " << mm2_eta_index << std::endl;
	std::cout << "stgc1 eta " << stgc1_eta_index << std::endl;
	std::cout << "stgc2 eta " << stgc2_eta_index << std::endl;
	}*/
      TVector3 mm1_vec(mm1_global_x, mm1_global_y, mm1_global_z);
      TVector3 mm2_vec(mm2_global_x, mm2_global_y, mm2_global_z);
      TVector3 stgc1_vec(stgc1_global_x, stgc1_global_y, stgc1_global_z);
      TVector3 stgc2_vec(stgc2_global_x, stgc2_global_y, stgc2_global_z);

      // std::cout << "regular " << std::endl << seg1_global_x << std::endl << seg1_global_y << std::endl << seg1_global_z << std::endl;
      // std::cout << "improved " << std::endl << seg1_global_improved_x << std::endl << seg1_global_improved_y << std::endl << seg1_global_improved_z << std::endl; 

      // TVector3 seg3_local_vec(seg3_local_x, seg3_local_y, seg3_local_z);

      // TVector3 seg1_vec(stgc1_global_x, stgc1_global_y, stgc1_global_z);
      // TVector3 seg2_vec(seg2_global_x, seg2_global_y, seg2_global_z);
      // TVector3 seg3_vec(seg3_global_x, seg3_global_y, seg3_global_z);

      double seg1_eta = seg1_vec.Eta();
      double seg2_eta = seg2_vec.Eta();
      double seg3_eta = seg3_vec.Eta();

      double seg1_phi = seg1_vec.Phi();
      double seg2_phi = seg2_vec.Phi();
      double seg3_phi = seg3_vec.Phi();

      double seg1_improved_eta = seg1_improved_vec.Eta();
      double seg2_improved_eta = seg2_improved_vec.Eta();
      double seg3_improved_eta = seg3_improved_vec.Eta();

      double seg1_improved_phi = seg1_improved_vec.Phi();
      double seg2_improved_phi = seg2_improved_vec.Phi();
      double seg3_improved_phi = seg3_improved_vec.Phi();

      // Sagitta

      TVector3 IM_vec = seg2_vec - seg1_vec;
      TVector3 IO_vec = seg3_vec - seg1_vec;

      TVector3 IM_improved_vec = seg2_improved_vec - seg1_improved_vec;
      TVector3 IO_improved_vec = seg3_improved_vec - seg1_improved_vec;

      TVector3 w = wire_vec[comb_sector - 1];
      // TVector3 w_perp = w.Cross(IO_vec);
      double sagitta_sign = (seg1_eta_index > 0? 1:-1);

      double sagitta = sagitta_sign * IM_vec * (w.Cross(IO_vec) * (1 / (w.Cross(IO_vec)).Mag()));
      double sagitta_improved = sagitta_sign * IM_improved_vec * (w.Cross(IO_improved_vec) * (1 / (w.Cross(IO_improved_vec)).Mag()));

      // double sec_coord_sagitta = sagitta_sign * IM_vec * (w.Unit());
      double sec_coord_sagitta =  IM_vec * (IO_vec.Cross(w.Cross(IO_vec)) * (1 / (IO_vec.Cross(w.Cross(IO_vec))).Mag()));
      double sec_coord_improved_sagitta = IM_improved_vec * (IO_improved_vec.Cross(w.Cross(IO_improved_vec)) * (1 / (IO_improved_vec.Cross(w.Cross(IO_improved_vec))).Mag()));

   //    if(i < 10){
	// std::cout << "seg1_global_x  " << seg1_global_x << ", seg1_global_y  " << seg1_global_y << ", seg1_global_z  "<< seg1_global_z << std::endl; 
	// std::cout << "seg2_global_x  " << seg2_global_x << ", seg2_global_y  " << seg2_global_y << ", seg2_global_z  "<< seg2_global_z << std::endl; 
	// std::cout << "seg3_global_x  " << seg3_global_x << ", seg3_global_y  " << seg3_global_y << ", seg3_global_z  "<< seg3_global_z << std::endl; 
	// std::cout << "sagitta  " << sagitta << std::endl << "2nd coord sagitta  " << sec_coord_sagitta << std::endl;
      
	// std::cout << "seg1_global_improved_x  " << seg1_global_improved_x << ", seg1_global_improved_y  " << seg1_global_improved_y << ", seg1_global_improved_z  "<< seg1_global_improved_z << std::endl;
	// std::cout << "seg2_global_improved_x  " << seg2_global_improved_x << ", seg2_global_improved_y  " << seg2_global_improved_y << ", seg2_global_improved_z  "<< seg2_global_improved_z << std::endl;
	// std::cout << "seg3_global_improved_x  " << seg3_global_improved_x << ", seg3_global_improved_y  " << seg3_global_improved_y << ", seg3_global_improved_z  "<< seg3_global_improved_z << std::endl;
	// std::cout << "sagitta improved  " << sagitta_improved << std::endl << "2nd coord sagitta improved   " << sec_coord_improved_sagitta << std::endl;
   //    }

      TVector3 IM_mm1_vec = seg2_improved_vec - mm1_vec;
      TVector3 IO_mm1_vec = seg3_improved_vec - mm1_vec;
      TVector3 IM_mm2_vec = seg2_improved_vec - mm2_vec;
      TVector3 IO_mm2_vec = seg3_improved_vec - mm2_vec;
      TVector3 IM_stgc1_vec = seg2_improved_vec - stgc1_vec;
      TVector3 IO_stgc1_vec = seg3_improved_vec - stgc1_vec;
      TVector3 IM_stgc2_vec = seg2_improved_vec - stgc2_vec;
      TVector3 IO_stgc2_vec = seg3_improved_vec - stgc2_vec;

      double sagitta_mm1 = sagitta_sign * IM_mm1_vec * (w.Cross(IO_mm1_vec) * (1 / (w.Cross(IO_mm1_vec)).Mag()));
      double sagitta_mm2 = sagitta_sign * IM_mm2_vec * (w.Cross(IO_mm2_vec) * (1 / (w.Cross(IO_mm2_vec)).Mag()));
      double sagitta_stgc1 = sagitta_sign * IM_stgc1_vec * (w.Cross(IO_stgc1_vec) * (1 / (w.Cross(IO_stgc1_vec)).Mag()));
      double sagitta_stgc2 = sagitta_sign * IM_stgc2_vec * (w.Cross(IO_stgc2_vec) * (1 / (w.Cross(IO_stgc2_vec)).Mag()));
   
      
      
      
      // Getting p from pT

      double muon_p = segger1_muon_pt * std::cosh(segger1_muon_eta);
      double muon_pT = segger1_muon_pt;

      
      

      // Cuts
      bool pass_cuts = true;
      // pass_cuts = false;

      // Fit quality cuts
      if (seg1_chisquare / seg1_nDOF > 10. && seg2_chisquare / seg2_nDOF > 10. && seg3_chisquare / seg3_nDOF > 10.)
      {
         pass_cuts = false;
      }

      // Precision cuts

      // I think the idea is to allow in more stats by relaxing the nhits cuts for certan stations
      // eg for comb, reduce the hit cut for EI to get more stats for that comb
      // I'm sure Christoph will play around with these cuts depending on how many stats he needs
      // Note for NSW at the moment, the hitreq is set to zero. Need to change this eventually once our NSW problems are sorted out
      if (comb_id == 1 || comb_id == 2 || comb_id == 3)
      {
         if (!seg1_hitreq || !seg2_hitreq || !seg3_hitreq)
         { 
            pass_cuts = false;
         }
      }
      else if (comb_id == 4) // EI-BEE-EM
      {
         if (seg1_nPrecisionHits < 2 || !seg2_hitreq || !seg3_hitreq)
         {
            pass_cuts = false;
         }
      }
      else if (comb_id == 5) // BIS-EE-EM
      {
         if (seg1_nPrecisionHits < 2 || !seg2_hitreq || !seg3_hitreq)
         {
            pass_cuts = false;
         }
      }

      // TGC phi hit cuts:
      if (comb_id == 1 || comb_id == 2)
      {
         if (seg2_nTrigPhiLayers < 0)
         {
            pass_cuts = false;
         }
      }
      else if (comb_id == 3 || comb_id == 4 || comb_id == 5)
      {
         if (seg3_nTrigPhiLayers < 0)
         {
            pass_cuts = false;
         }
      }

      // Track hit pointing
      if ((segger1_muon_pt == -999999) || (segger2_muon_pt == -999999) || (segger3_muon_pt == -999999))
      {
         pass_cuts = false;
      }
      else if ((segger1_muon_pt != segger2_muon_pt) || (segger1_muon_eta != segger2_muon_eta) || (segger1_muon_phi != segger2_muon_phi))
      {
         pass_cuts = false;
      }
      else if ((segger1_muon_pt != segger3_muon_pt) || (segger1_muon_eta != segger3_muon_eta) || (segger1_muon_phi != segger3_muon_phi))
      {
         pass_cuts = false;
      }

      // Track hit share
      if ((segger1_track_hitshare < 4) || (segger1_track_hitshare < segger1_nhits - 1))
      {
         pass_cuts = false;
      }
      if ((segger2_track_hitshare < 4) || (segger2_track_hitshare < segger2_nhits - 1))
      {
         pass_cuts = false;
      }
      if ((segger3_track_hitshare < 4) || (segger3_track_hitshare < segger3_nhits - 1))
      {
         pass_cuts = false;
      }



      // Segment pointing

      double seg1_seg2_deta = seg1_eta - seg2_eta;
      double seg1_seg3_deta = seg1_eta - seg3_eta;
      double seg2_seg3_deta = seg2_eta - seg3_eta;

      double seg1_seg2_dphi = seg1_vec.DeltaPhi(seg2_vec);
      double seg1_seg3_dphi = seg1_vec.DeltaPhi(seg2_vec);
      double seg2_seg3_dphi = seg2_vec.DeltaPhi(seg2_vec);

      if (fabs(seg1_seg2_deta) > 0.05 || fabs(seg1_seg2_dphi) > 0.5)
      {
         pass_cuts = false;
      }
      if (fabs(seg1_seg3_deta) > 0.05 || fabs(seg1_seg3_dphi) > 0.5)
      {
         pass_cuts = false;
      }
      if (fabs(seg2_seg3_deta) > 0.05 || fabs(seg2_seg3_dphi) > 0.5)
      {
         pass_cuts = false;
      }

      // Segment hit sharing
      // If the hitshare is non-zero then it fail, unless the hitshare count is 1 for seg 1, 2 and 3.

      int s1_count = 0;
      int s2_count = 0;
      int s3_count = 0;
      bool pass_hitshare = true;

      for (int track = 0; track < segger1_hitshare->size(); ++track)
      {
         if (track > 0)
         {
            pass_hitshare = false;
            s1_count += 1;
         }
      }
      for (int track = 0; track < segger2_hitshare->size(); ++track)
      {
         if (track > 0)
         {
            pass_hitshare = false;
            s2_count += 1;
         }
      }
      for (int track = 0; track < segger3_hitshare->size(); ++track)
      {
         if (track > 0)
         {
            pass_hitshare = false;
            s3_count += 1;
         }
      }
      if (!pass_hitshare && s1_count == 1 && s2_count == 1 && s3_count == 1)
      {
         pass_hitshare = true;
      }
      if (pass_hitshare == false)
      {
         pass_cuts = false;
      }


      // Muon author
      if ((segger1_muon_author == -999999) || (segger1_muon_author != segger2_muon_author) || (segger1_muon_author != segger3_muon_author))
      {
         pass_cuts = false;
      }

   // dont need this cut i think
      // if ( (segger1_hitavg_global_x == -999999) || (segger2_hitavg_global_x == -999999) || (segger3_hitavg_global_x == -999999) ) 
      // {
      //    pass_cuts = false;
      // }

      // High pt / forward
      // It's weird to cut on both p and pT. Just have a p cut.
      // if ((segger1_muon_pt < 0) && (muon_p < 40000.)))
      // {
      //   pass_cuts = false;
      // }

      // Segs bounded within chambers
      // big stuff


      // Running over the first half million events or so
      // std::cout << cEventNumber << std::endl;
      // int start_event;
      // int end_event;
      // if (i == 0) 
      // {
      //    start_event = cEventNumber;
      //    end_event = start_event + 800000;
      // }
      // if (cEventNumber > end_event)
      // {
      //    pass_cuts = false;
      // }

      
      
      // pass_cuts = true;

      // bayley: neaten this up / do it properly
      seg1_global_x = seg1_global_improved_x;
      seg1_global_y = seg1_global_improved_y;
      seg1_global_z = seg1_global_improved_z;

      seg2_global_x = seg2_global_improved_x;
      seg2_global_y = seg2_global_improved_y;
      seg2_global_z = seg2_global_improved_z;

      seg3_global_x = seg3_global_improved_x;
      seg3_global_y = seg3_global_improved_y;
      seg3_global_z = seg3_global_improved_z;


      int comb_selection = 1; // select only 1 type of combinations
      if (comb_id != comb_selection) 
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

      // Want to fill this hist with only the cuts for the combination selection. 
      if (comb_id == comb_selection) 
      {
         muon_p_hist->Fill(muon_p);
         muon_pT_hist->Fill(muon_pT);
      }

      // Fill the rest of the hists
      if (pass_cuts)
      {
         muon_p_selection_hist->Fill(muon_p);
         muon_pT_selection_hist->Fill(muon_pT);

         if (seg1_eta_index > 0)
         {
            seg1_xy_aside_hist->Fill(seg1_global_x, seg1_global_y);
            seg2_xy_aside_hist->Fill(seg2_global_x, seg2_global_y);
            seg3_xy_aside_hist->Fill(seg3_global_x, seg3_global_y);

            seg1x_seg2x_aside_hist->Fill(seg1_global_x, seg2_global_x);
            seg1x_seg3x_aside_hist->Fill(seg1_global_x, seg3_global_x);
            seg2x_seg3x_aside_hist->Fill(seg2_global_x, seg3_global_x);

            seg1y_seg2y_aside_hist->Fill(seg1_global_y, seg2_global_y);
            seg1y_seg3y_aside_hist->Fill(seg1_global_y, seg3_global_y);
            seg2y_seg3y_aside_hist->Fill(seg2_global_y, seg3_global_y);

            seg1z_seg2z_aside_hist->Fill(seg1_global_z, seg2_global_z);
            seg1z_seg3z_aside_hist->Fill(seg1_global_z, seg3_global_z);
            seg2z_seg3z_aside_hist->Fill(seg2_global_z, seg3_global_z);

            seg1_nhits_hist_per_sector_aside_hists[comb_sector - 1]->Fill(seg1_nPrecisionHits);
            seg2_nhits_hist_per_sector_aside_hists[comb_sector - 1]->Fill(seg2_nPrecisionHits);
            seg3_nhits_hist_per_sector_aside_hists[comb_sector - 1]->Fill(seg3_nPrecisionHits);

            mm1_xy_aside_hist->Fill(mm1_global_x, mm1_global_y);
            mm2_xy_aside_hist->Fill(mm2_global_x, mm2_global_y);
            stgc1_xy_aside_hist->Fill(stgc1_global_x, stgc1_global_y);
            stgc2_xy_aside_hist->Fill(stgc2_global_x, stgc2_global_y);

            // junk for now

            // seg1_chamber_xy->Fill(seg1_cham_x, seg1_cham_y);
            // seg1_chamber_phiz->Fill(segger1_muon_phi, seg1_cham_z);

            // mm1_chamber_xy->Fill(mm1_cham_x, mm1_cham_y);
            // mm1_chamber_phiz->Fill(segger1_muon_phi, mm1_cham_z);
            // mm2_chamber_xy->Fill(mm2_cham_x, mm2_cham_y);
            // mm2_chamber_phiz->Fill(segger1_muon_phi, mm2_cham_z);
            // stgc1_chamber_xy->Fill(stgc1_cham_x, stgc1_cham_y);
            // stgc1_chamber_phiz->Fill(segger1_muon_phi, stgc1_cham_z);
            // stgc2_chamber_xy->Fill(stgc2_cham_x, stgc2_cham_y);
            // stgc2_chamber_phiz->Fill(segger1_muon_phi, stgc2_cham_z);
         }

         if (seg1_eta_index < 0)
         {
            seg1_xy_cside_hist->Fill(seg1_global_x, seg1_global_y);
            seg2_xy_cside_hist->Fill(seg2_global_x, seg2_global_y);
            seg3_xy_cside_hist->Fill(seg3_global_x, seg3_global_y);

            seg1x_seg2x_cside_hist->Fill(seg1_global_x, seg2_global_x);
            seg1x_seg3x_cside_hist->Fill(seg1_global_x, seg3_global_x);
            seg2x_seg3x_cside_hist->Fill(seg2_global_x, seg3_global_x);

            seg1y_seg2y_cside_hist->Fill(seg1_global_y, seg2_global_y);
            seg1y_seg3y_cside_hist->Fill(seg1_global_y, seg3_global_y);
            seg2y_seg3y_cside_hist->Fill(seg2_global_y, seg3_global_y);

            seg1z_seg2z_cside_hist->Fill(seg1_global_z, seg2_global_z);
            seg1z_seg3z_cside_hist->Fill(seg1_global_z, seg3_global_z);
            seg2z_seg3z_cside_hist->Fill(seg2_global_z, seg3_global_z);

            seg1_nhits_hist_per_sector_cside_hists[comb_sector - 1]->Fill(seg1_nPrecisionHits);
            seg2_nhits_hist_per_sector_cside_hists[comb_sector - 1]->Fill(seg2_nPrecisionHits);
            seg3_nhits_hist_per_sector_cside_hists[comb_sector - 1]->Fill(seg3_nPrecisionHits);

            mm1_xy_cside_hist->Fill(mm1_global_x, mm1_global_y);
            mm2_xy_cside_hist->Fill(mm2_global_x, mm2_global_y);
            stgc1_xy_cside_hist->Fill(stgc1_global_x, stgc1_global_y);
            stgc2_xy_cside_hist->Fill(stgc2_global_x, stgc2_global_y);
         }

         // Eta phi plots

         seg1_eta_hist->Fill(seg1_eta, segger1_muon_eta);
         seg2_eta_hist->Fill(seg2_eta, segger2_muon_eta);
         seg3_eta_hist->Fill(seg3_eta, segger3_muon_eta);

         seg1_phi_hist->Fill(seg1_phi, segger1_muon_phi);
         seg2_phi_hist->Fill(seg2_phi, segger2_muon_phi);
         seg3_phi_hist->Fill(seg3_phi, segger3_muon_phi);

         seg1_seg2_eta_hist->Fill(seg1_eta, seg2_eta);
         seg1_seg3_eta_hist->Fill(seg1_eta, seg3_eta);
         seg2_seg3_eta_hist->Fill(seg2_eta, seg3_eta);

         seg1_seg2_phi_hist->Fill(seg1_phi, seg2_phi);
         seg1_seg3_phi_hist->Fill(seg1_phi, seg3_phi);
         seg2_seg3_phi_hist->Fill(seg2_phi, seg3_phi);


         seg1_track_residual_hist->Fill(segger1_track_residual);
         seg2_track_residual_hist->Fill(segger2_track_residual);
         seg3_track_residual_hist->Fill(segger3_track_residual);

         seg1_track_pull_hist->Fill(segger1_track_pull);
         seg2_track_pull_hist->Fill(segger2_track_pull);
         seg3_track_pull_hist->Fill(segger3_track_pull);




         // Sagitta Plots

         if (muon_p > 0.)
         {
            sagitta_0p_hist->Fill(sagitta);
            if (seg1_eta_index > 0)
            {
               sagittas_a_0p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_a_0p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
               sagitta_a_2nd_coord_0p_hist.at(comb_sector - 1)->Fill(sec_coord_sagitta);
               sagitta_a_2nd_coord_0p_improved_hist.at(comb_sector - 1)->Fill(sec_coord_improved_sagitta);

               sagittas_a_0p_mm1_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm1);
               sagittas_a_0p_mm2_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm2);
               sagittas_a_0p_stgc1_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc1);
               sagittas_a_0p_stgc2_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc2);

	       if(std::abs(mm1_eta_index)==1 || std::abs(mm1_eta_index)==2) sagittas_a_0p_mm1_t_improved_hist.at(comb_sector - 1 + (std::abs(mm1_eta_index)-1)*16)->Fill(sagitta_mm1);
               if(std::abs(mm2_eta_index)==1 || std::abs(mm2_eta_index)==2) sagittas_a_0p_mm2_t_improved_hist.at(comb_sector - 1 + (std::abs(mm2_eta_index)-1)*16)->Fill(sagitta_mm2);
               if(std::abs(stgc1_eta_index)==1 || std::abs(stgc1_eta_index)==2 || std::abs(stgc1_eta_index)==3) sagittas_a_0p_stgc1_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc1_eta_index)-1)*16)->Fill(sagitta_stgc1);
	       if(std::abs(stgc2_eta_index)==1 || std::abs(stgc2_eta_index)==2 || std::abs(stgc2_eta_index)==3) sagittas_a_0p_stgc2_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc2_eta_index)-1)*16)->Fill(sagitta_stgc2);

            }
            else
            {
               sagittas_c_0p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_c_0p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
               sagitta_c_2nd_coord_0p_hist.at(comb_sector - 1)->Fill(sec_coord_sagitta);
               sagitta_c_2nd_coord_0p_improved_hist.at(comb_sector - 1)->Fill(sec_coord_improved_sagitta);

	       sagittas_c_0p_mm1_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm1);
               sagittas_c_0p_mm2_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm2);
               sagittas_c_0p_stgc1_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc1);
               sagittas_c_0p_stgc2_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc2);

	       if(std::abs(mm1_eta_index)==1 || std::abs(mm1_eta_index)==2) sagittas_c_0p_mm1_t_improved_hist.at(comb_sector - 1 + (std::abs(mm1_eta_index)-1)*16)->Fill(sagitta_mm1);
	       if(std::abs(mm2_eta_index)==1 || std::abs(mm2_eta_index)==2) sagittas_c_0p_mm2_t_improved_hist.at(comb_sector - 1 + (std::abs(mm2_eta_index)-1)*16)->Fill(sagitta_mm2);
               if(std::abs(stgc1_eta_index)==1 || std::abs(stgc1_eta_index)==2 || std::abs(stgc1_eta_index)==3) sagittas_c_0p_stgc1_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc1_eta_index)-1)*16)->Fill(sagitta_stgc1);
               if(std::abs(stgc2_eta_index)==1 || std::abs(stgc2_eta_index)==2 || std::abs(stgc2_eta_index)==3) sagittas_c_0p_stgc2_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc2_eta_index)-1)*16)->Fill(sagitta_stgc2);

            }
         }
         if (muon_p > 5000.)
         {
            if (seg1_eta_index > 0)
            {
               sagittas_a_5p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_a_5p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
            }
            else
            {
               sagittas_c_5p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_c_5p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
            }
         }
         if (muon_p > 10000.)
         {
            sagitta_10p_hist->Fill(sagitta);
            if (seg1_eta_index > 0)
            {
               sagittas_a_10p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_a_10p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);

	       sagittas_a_10p_mm1_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm1);
               sagittas_a_10p_mm2_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm2);
               sagittas_a_10p_stgc1_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc1);
               sagittas_a_10p_stgc2_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc2);

	       if(std::abs(mm1_eta_index)==1 || std::abs(mm1_eta_index)==2) sagittas_a_10p_mm1_t_improved_hist.at(comb_sector - 1 + (std::abs(mm1_eta_index)-1)*16)->Fill(sagitta_mm1);
	       if(std::abs(mm2_eta_index)==1 || std::abs(mm2_eta_index)==2) sagittas_a_10p_mm2_t_improved_hist.at(comb_sector - 1 + (std::abs(mm2_eta_index)-1)*16)->Fill(sagitta_mm2);
               if(std::abs(stgc1_eta_index)==1 || std::abs(stgc1_eta_index)==2 || std::abs(stgc1_eta_index)==3) sagittas_a_10p_stgc1_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc1_eta_index)-1)*16)->Fill(sagitta_stgc1);
               if(std::abs(stgc2_eta_index)==1 || std::abs(stgc2_eta_index)==2 || std::abs(stgc2_eta_index)==3) sagittas_a_10p_stgc2_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc2_eta_index)-1)*16)->Fill(sagitta_stgc2);
}
            else
            {
               sagittas_c_10p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_c_10p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);

	       sagittas_c_10p_mm1_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm1);
               sagittas_c_10p_mm2_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm2);
               sagittas_c_10p_stgc1_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc1);
               sagittas_c_10p_stgc2_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc2);

	       if(std::abs(mm1_eta_index)==1 || std::abs(mm1_eta_index)==2) sagittas_c_10p_mm1_t_improved_hist.at(comb_sector - 1 + (std::abs(mm1_eta_index)-1)*16)->Fill(sagitta_mm1);
               if(std::abs(mm2_eta_index)==1 || std::abs(mm2_eta_index)==2) sagittas_c_10p_mm2_t_improved_hist.at(comb_sector - 1 + (std::abs(mm2_eta_index)-1)*16)->Fill(sagitta_mm2);
               if(std::abs(stgc1_eta_index)==1 || std::abs(stgc1_eta_index)==2 || std::abs(stgc1_eta_index)==3) sagittas_c_10p_stgc1_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc1_eta_index)-1)*16)->Fill(sagitta_stgc1);
               if(std::abs(stgc2_eta_index)==1 || std::abs(stgc2_eta_index)==2 || std::abs(stgc2_eta_index)==3) sagittas_c_10p_stgc2_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc2_eta_index)-1)*16)->Fill(sagitta_stgc2);

            }
         }
         if (muon_p > 15000.)
         {
            sagitta_15p_hist->Fill(sagitta);
            if (seg1_eta_index > 0)
            {
               sagittas_a_15p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_a_15p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
            }
            else
            {
               sagittas_c_15p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_c_15p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
            }
         }
         if (muon_p > 20000.)
         {
            sagitta_20p_hist->Fill(sagitta);
            if (seg1_eta_index > 0)
            {
               sagittas_a_20p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_a_20p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);

	       sagittas_a_20p_mm1_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm1);
               sagittas_a_20p_mm2_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm2);
               sagittas_a_20p_stgc1_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc1);
               sagittas_a_20p_stgc2_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc2);

	       if(std::abs(mm1_eta_index)==1 || std::abs(mm1_eta_index)==2) sagittas_a_20p_mm1_t_improved_hist.at(comb_sector - 1 + (std::abs(mm1_eta_index)-1)*16)->Fill(sagitta_mm1);
	       if(std::abs(mm2_eta_index)==1 || std::abs(mm2_eta_index)==2) sagittas_a_20p_mm2_t_improved_hist.at(comb_sector - 1 + (std::abs(mm2_eta_index)-1)*16)->Fill(sagitta_mm2);
               if(std::abs(stgc1_eta_index)==1 || std::abs(stgc1_eta_index)==2 || std::abs(stgc1_eta_index)==3) sagittas_a_20p_stgc1_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc1_eta_index)-1)*16)->Fill(sagitta_stgc1);
               if(std::abs(stgc2_eta_index)==1 || std::abs(stgc2_eta_index)==2 || std::abs(stgc2_eta_index)==3) sagittas_a_20p_stgc2_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc2_eta_index)-1)*16)->Fill(sagitta_stgc2);
	    }
            else
            {
               sagittas_c_20p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_c_20p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);

	       sagittas_c_20p_mm1_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm1);
	       sagittas_c_20p_mm2_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm2);
               sagittas_c_20p_stgc1_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc1);
               sagittas_c_20p_stgc2_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc2);

	       if(std::abs(mm1_eta_index)==1 || std::abs(mm1_eta_index)==2) sagittas_c_20p_mm1_t_improved_hist.at(comb_sector - 1 + (std::abs(mm1_eta_index)-1)*16)->Fill(sagitta_mm1);
	       if(std::abs(mm2_eta_index)==1 || std::abs(mm2_eta_index)==2) sagittas_c_20p_mm2_t_improved_hist.at(comb_sector - 1 + (std::abs(mm2_eta_index)-1)*16)->Fill(sagitta_mm2);
               if(std::abs(stgc1_eta_index)==1 || std::abs(stgc1_eta_index)==2 || std::abs(stgc1_eta_index)==3) sagittas_c_20p_stgc1_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc1_eta_index)-1)*16)->Fill(sagitta_stgc1);
               if(std::abs(stgc2_eta_index)==1 || std::abs(stgc2_eta_index)==2 || std::abs(stgc2_eta_index)==3) sagittas_c_20p_stgc2_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc2_eta_index)-1)*16)->Fill(sagitta_stgc2);

            }
         }
         if (muon_p > 25000.)
         {
            if (seg1_eta_index > 0)
            {
               sagittas_a_25p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_a_25p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
            }
            else
            {
               sagittas_c_25p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_c_25p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
            }
         }
         if (muon_p > 30000.)
         {
            sagitta_30p_hist->Fill(sagitta);
            if (seg1_eta_index > 0)
            {
               sagittas_a_30p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_a_30p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
               sagitta_a_2nd_coord_30p_hist.at(comb_sector - 1)->Fill(sec_coord_sagitta);
               sagitta_a_2nd_coord_30p_improved_hist.at(comb_sector - 1)->Fill(sec_coord_improved_sagitta);
               
               sagittas_a_30p_mm1_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm1);
               sagittas_a_30p_mm2_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm2);
               sagittas_a_30p_stgc1_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc1);
               sagittas_a_30p_stgc2_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc2);

	       if(std::abs(mm1_eta_index)==1 || std::abs(mm1_eta_index)==2) sagittas_a_30p_mm1_t_improved_hist.at(comb_sector - 1 + (std::abs(mm1_eta_index)-1)*16)->Fill(sagitta_mm1);
	       if(std::abs(mm2_eta_index)==1 || std::abs(mm2_eta_index)==2) sagittas_a_30p_mm2_t_improved_hist.at(comb_sector - 1 + (std::abs(mm2_eta_index)-1)*16)->Fill(sagitta_mm2);
               if(std::abs(stgc1_eta_index)==1 || std::abs(stgc1_eta_index)==2 || std::abs(stgc1_eta_index)==3) sagittas_a_30p_stgc1_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc1_eta_index)-1)*16)->Fill(sagitta_stgc1);
               if(std::abs(stgc2_eta_index)==1 || std::abs(stgc2_eta_index)==2 || std::abs(stgc2_eta_index)==3) sagittas_a_30p_stgc2_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc2_eta_index)-1)*16)->Fill(sagitta_stgc2);

               if (seg1_eta_index == 2 && seg2_eta_index == 2 && seg3_eta_index == 3)
               {
                  sagitta_a_t223_30p_hist.at(comb_sector - 1)->Fill(sagitta_improved);
               }

            }
            else
            {
               sagittas_c_30p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_c_30p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
               sagitta_c_2nd_coord_30p_hist.at(comb_sector - 1)->Fill(sec_coord_sagitta);
               sagitta_c_2nd_coord_30p_improved_hist.at(comb_sector - 1)->Fill(sec_coord_improved_sagitta);

               sagittas_c_30p_mm1_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm1);
               sagittas_c_30p_mm2_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm2);
               sagittas_c_30p_stgc1_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc1);
               sagittas_c_30p_stgc2_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc2);

	       if(std::abs(mm1_eta_index)==1 || std::abs(mm1_eta_index)==2) sagittas_c_30p_mm1_t_improved_hist.at(comb_sector - 1 + (std::abs(mm1_eta_index)-1)*16)->Fill(sagitta_mm1);
	       if(std::abs(mm2_eta_index)==1 || std::abs(mm2_eta_index)==2) sagittas_c_30p_mm2_t_improved_hist.at(comb_sector - 1 + (std::abs(mm2_eta_index)-1)*16)->Fill(sagitta_mm2);
               if(std::abs(stgc1_eta_index)==1 || std::abs(stgc1_eta_index)==2 || std::abs(stgc1_eta_index)==3) sagittas_c_30p_stgc1_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc1_eta_index)-1)*16)->Fill(sagitta_stgc1);
               if(std::abs(stgc2_eta_index)==1 || std::abs(stgc2_eta_index)==2 || std::abs(stgc2_eta_index)==3) sagittas_c_30p_stgc2_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc2_eta_index)-1)*16)->Fill(sagitta_stgc2);
	       
	    }
         }
         if (muon_p > 35000.)
         {
            if (seg1_eta_index > 0)
            {
               sagittas_a_35p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_a_35p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
            }
            else
            {
               sagittas_c_35p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_c_35p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
            }
         }
         if (muon_p > 40000.)
         {
            if (seg1_eta_index > 0)
            {
               sagittas_a_40p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_a_40p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);

	       sagittas_a_40p_mm1_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm1);
               sagittas_a_40p_mm2_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm2);
               sagittas_a_40p_stgc1_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc1);
               sagittas_a_40p_stgc2_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc2);

	       if(std::abs(mm1_eta_index)==1 || std::abs(mm1_eta_index)==2) sagittas_a_40p_mm1_t_improved_hist.at(comb_sector - 1 + (std::abs(mm1_eta_index)-1)*16)->Fill(sagitta_mm1);
	       if(std::abs(mm2_eta_index)==1 || std::abs(mm2_eta_index)==2) sagittas_a_40p_mm2_t_improved_hist.at(comb_sector - 1 + (std::abs(mm2_eta_index)-1)*16)->Fill(sagitta_mm2);
               if(std::abs(stgc1_eta_index)==1 || std::abs(stgc1_eta_index)==2 || std::abs(stgc1_eta_index)==3) sagittas_a_40p_stgc1_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc1_eta_index)-1)*16)->Fill(sagitta_stgc1);
               if(std::abs(stgc2_eta_index)==1 || std::abs(stgc2_eta_index)==2 || std::abs(stgc2_eta_index)==3) sagittas_a_40p_stgc2_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc2_eta_index)-1)*16)->Fill(sagitta_stgc2);

            }
            else
            {
               sagittas_c_40p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_c_40p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);

	       sagittas_c_40p_mm1_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm1);
               sagittas_c_40p_mm2_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm2);
               sagittas_c_40p_stgc1_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc1);
               sagittas_c_40p_stgc2_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc2);

	       if(std::abs(mm1_eta_index)==1 || std::abs(mm1_eta_index)==2) sagittas_c_40p_mm1_t_improved_hist.at(comb_sector - 1 + (std::abs(mm1_eta_index)-1)*16)->Fill(sagitta_mm1);
	       if(std::abs(mm2_eta_index)==1 || std::abs(mm2_eta_index)==2) sagittas_c_40p_mm2_t_improved_hist.at(comb_sector - 1 + (std::abs(mm2_eta_index)-1)*16)->Fill(sagitta_mm2);
               if(std::abs(stgc1_eta_index)==1 || std::abs(stgc1_eta_index)==2 || std::abs(stgc1_eta_index)==3) sagittas_c_40p_stgc1_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc1_eta_index)-1)*16)->Fill(sagitta_stgc1);
               if(std::abs(stgc2_eta_index)==1 || std::abs(stgc2_eta_index)==2 || std::abs(stgc2_eta_index)==3) sagittas_c_40p_stgc2_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc2_eta_index)-1)*16)->Fill(sagitta_stgc2);
            }
         }
         if (muon_p > 45000.)
         {
            if (seg1_eta_index > 0)
            {
               sagittas_a_45p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_a_45p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
            }
            else
            {
               sagittas_c_45p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_c_45p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
            }
         }
         if (muon_p > 50000.)
         {
            sagitta_50p_hist->Fill(sagitta);
            if (seg1_eta_index > 0)
            {
               sagittas_a_50p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_a_50p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);

               sagittas_a_50p_mm1_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm1);
               sagittas_a_50p_mm2_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm2);
               sagittas_a_50p_stgc1_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc1);
               sagittas_a_50p_stgc2_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc2);

	       if(std::abs(mm1_eta_index)==1 || std::abs(mm1_eta_index)==2) sagittas_a_50p_mm1_t_improved_hist.at(comb_sector - 1 + (std::abs(mm1_eta_index)-1)*16)->Fill(sagitta_mm1);
	       if(std::abs(mm2_eta_index)==1 || std::abs(mm2_eta_index)==2) sagittas_a_50p_mm2_t_improved_hist.at(comb_sector - 1 + (std::abs(mm2_eta_index)-1)*16)->Fill(sagitta_mm2);
               if(std::abs(stgc1_eta_index)==1 || std::abs(stgc1_eta_index)==2 || std::abs(stgc1_eta_index)==3) sagittas_a_50p_stgc1_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc1_eta_index)-1)*16)->Fill(sagitta_stgc1);
               if(std::abs(stgc2_eta_index)==1 || std::abs(stgc2_eta_index)==2 || std::abs(stgc2_eta_index)==3) sagittas_a_50p_stgc2_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc2_eta_index)-1)*16)->Fill(sagitta_stgc2);

            }
            else
            {
               sagittas_c_50p_hist.at(comb_sector - 1)->Fill(sagitta);
               sagittas_c_50p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);

               sagittas_c_50p_mm1_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm1);
               sagittas_c_50p_mm2_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm2);
               sagittas_c_50p_stgc1_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc1);
               sagittas_c_50p_stgc2_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc2);

	       if(std::abs(mm1_eta_index)==1 || std::abs(mm1_eta_index)==2) sagittas_c_50p_mm1_t_improved_hist.at(comb_sector - 1 + (std::abs(mm1_eta_index)-1)*16)->Fill(sagitta_mm1);
	       if(std::abs(mm2_eta_index)==1 || std::abs(mm2_eta_index)==2) sagittas_c_50p_mm2_t_improved_hist.at(comb_sector - 1 + (std::abs(mm2_eta_index)-1)*16)->Fill(sagitta_mm2);
               if(std::abs(stgc1_eta_index)==1 || std::abs(stgc1_eta_index)==2 || std::abs(stgc1_eta_index)==3) sagittas_c_50p_stgc1_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc1_eta_index)-1)*16)->Fill(sagitta_stgc1);
               if(std::abs(stgc2_eta_index)==1 || std::abs(stgc2_eta_index)==2 || std::abs(stgc2_eta_index)==3) sagittas_c_50p_stgc2_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc2_eta_index)-1)*16)->Fill(sagitta_stgc2);

	    }
         }
         if (muon_p > 100000.)
         {
            if (seg1_eta_index > 0)
            {
               sagittas_a_100p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);

               sagittas_a_100p_mm1_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm1);
               sagittas_a_100p_mm2_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm2);
               sagittas_a_100p_stgc1_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc1);
               sagittas_a_100p_stgc2_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc2);

	       if(std::abs(mm1_eta_index)==1 || std::abs(mm1_eta_index)==2) sagittas_a_100p_mm1_t_improved_hist.at(comb_sector - 1 + (std::abs(mm1_eta_index)-1)*16)->Fill(sagitta_mm1);
	       if(std::abs(mm2_eta_index)==1 || std::abs(mm2_eta_index)==2) sagittas_a_100p_mm2_t_improved_hist.at(comb_sector - 1 + (std::abs(mm2_eta_index)-1)*16)->Fill(sagitta_mm2);
               if(std::abs(stgc1_eta_index)==1 || std::abs(stgc1_eta_index)==2 || std::abs(stgc1_eta_index)==3) sagittas_a_100p_stgc1_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc1_eta_index)-1)*16)->Fill(sagitta_stgc1);
               if(std::abs(stgc2_eta_index)==1 || std::abs(stgc2_eta_index)==2 || std::abs(stgc2_eta_index)==3) sagittas_a_100p_stgc2_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc2_eta_index)-1)*16)->Fill(sagitta_stgc2);

            }
            else
            {
               sagittas_c_100p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);

               sagittas_c_100p_mm1_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm1);
               sagittas_c_100p_mm2_improved_hist.at(comb_sector - 1)->Fill(sagitta_mm2);
               sagittas_c_100p_stgc1_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc1);
               sagittas_c_100p_stgc2_improved_hist.at(comb_sector - 1)->Fill(sagitta_stgc2);

	       if(std::abs(mm1_eta_index)==1 || std::abs(mm1_eta_index)==2) sagittas_c_100p_mm1_t_improved_hist.at(comb_sector - 1 + (std::abs(mm1_eta_index)-1)*16)->Fill(sagitta_mm1);
	       if(std::abs(mm2_eta_index)==1 || std::abs(mm2_eta_index)==2) sagittas_c_100p_mm2_t_improved_hist.at(comb_sector - 1 + (std::abs(mm2_eta_index)-1)*16)->Fill(sagitta_mm2);
               if(std::abs(stgc1_eta_index)==1 || std::abs(stgc1_eta_index)==2 || std::abs(stgc1_eta_index)==3) sagittas_c_100p_stgc1_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc1_eta_index)-1)*16)->Fill(sagitta_stgc1);
               if(std::abs(stgc2_eta_index)==1 || std::abs(stgc2_eta_index)==2 || std::abs(stgc2_eta_index)==3) sagittas_c_100p_stgc2_t_improved_hist.at(comb_sector - 1 + (std::abs(stgc2_eta_index)-1)*16)->Fill(sagitta_stgc2);
	    }
         }
         if (muon_p > 200000.)
         {
            if (seg1_eta_index > 0)
            {
               sagittas_a_200p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
            }
            else
            {
               sagittas_c_200p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
            }
         }
         if (muon_p > 300000.)
         {
            if (seg1_eta_index > 0)
            {
               sagittas_a_300p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
            }
            else
            {
               sagittas_c_300p_improved_hist.at(comb_sector - 1)->Fill(sagitta_improved);
            }
         }

         

      }
   }

   std::cout << "Passed: " << passed << "   Failed: " << failed << std::endl;
};

void tree::WriteHistsToFile()
{

   // Output file for hists
   std::cout << "Save hists to file" << std::endl;
   std::unique_ptr<TFile> outputFile(TFile::Open("Loop_out/tree_out.root", "RECREATE"));

   // seg1_xy_aside_hist.get()->Write();
   // seg2_xy_aside_hist.get()->Write();
   // seg3_xy_aside_hist.get()->Write();
   // seg1x_seg2x_aside_hist.get()->Write();
   // seg1x_seg3x_aside_hist.get()->Write();
   // seg2x_seg3x_aside_hist.get()->Write();
   // seg1y_seg3y_aside_hist.get()->Write();
   // seg1y_seg2y_aside_hist.get()->Write();
   // seg2y_seg3y_aside_hist.get()->Write();
   // seg1z_seg2z_aside_hist.get()->Write();
   // seg1z_seg3z_aside_hist.get()->Write();
   // seg2z_seg3z_aside_hist.get()->Write();

   // for (int i = 0; i < 16; ++i)
   // {
   //    seg1_nhits_hist_per_sector_aside_hists.at(i).get()->Write();
   //    seg2_nhits_hist_per_sector_aside_hists.at(i).get()->Write();
   //    seg3_nhits_hist_per_sector_aside_hists.at(i).get()->Write();
   // }

   // seg1_xy_cside_hist.get()->Write();
   // seg2_xy_cside_hist.get()->Write();
   // seg3_xy_cside_hist.get()->Write();
   // seg1x_seg2x_cside_hist.get()->Write();
   // seg1x_seg3x_cside_hist.get()->Write();
   // seg2x_seg3x_cside_hist.get()->Write();
   // seg1y_seg2y_cside_hist.get()->Write();
   // seg1y_seg3y_cside_hist.get()->Write();
   // seg2y_seg3y_cside_hist.get()->Write();
   // seg1z_seg2z_cside_hist.get()->Write();
   // seg1z_seg3z_cside_hist.get()->Write();
   // seg2z_seg3z_cside_hist.get()->Write();

   // for (int i = 0; i < 16; ++i)
   // {
   //    seg1_nhits_hist_per_sector_cside_hists.at(i).get()->Write();
   //    seg2_nhits_hist_per_sector_cside_hists.at(i).get()->Write();
   //    seg3_nhits_hist_per_sector_cside_hists.at(i).get()->Write();
   // }

   // seg1_eta_hist.get()->Write();
   // seg2_eta_hist.get()->Write();
   // seg3_eta_hist.get()->Write();
   // seg1_phi_hist.get()->Write();
   // seg2_phi_hist.get()->Write();
   // seg3_phi_hist.get()->Write();
   // seg1_seg2_eta_hist.get()->Write();
   // seg1_seg3_eta_hist.get()->Write();
   // seg2_seg3_eta_hist.get()->Write();
   // seg1_seg2_phi_hist.get()->Write();
   // seg1_seg3_phi_hist.get()->Write();
   // seg2_seg3_phi_hist.get()->Write();

   // seg1_track_residual_hist.get()->Write();
   // seg2_track_residual_hist.get()->Write();
   // seg3_track_residual_hist.get()->Write();

   // seg1_track_pull_hist.get()->Write();
   // seg2_track_pull_hist.get()->Write();
   // seg3_track_pull_hist.get()->Write();

   // Bayley: Also need to write nhits plots at some point (need to get mtree in to do this)

   // sagitta_0p_hist.get()->Write();
   // sagitta_10p_hist.get()->Write();
   // sagitta_15p_hist.get()->Write();
   // sagitta_20p_hist.get()->Write();
   // sagitta_30p_hist.get()->Write();
   // sagitta_50p_hist.get()->Write();

   // sagitta_2nd_coord_0p_hist.get()->Write();
   // sagitta_2nd_coord_30p_hist.get()->Write();


   // Muon Momentum histogram
   muon_p_hist.get()->Write();
   muon_p_selection_hist.get()->Write();
   muon_pT_hist.get()->Write();
   muon_pT_selection_hist.get()->Write();


   // for (int i = 0; i < 16; ++i)
   // {
   //    sagittas_a_0p_hist.at(i).get()->Write();
   //    sagittas_a_5p_hist.at(i).get()->Write();
   //    sagittas_a_10p_hist.at(i).get()->Write();
   //    sagittas_a_15p_hist.at(i).get()->Write();
   //    sagittas_a_20p_hist.at(i).get()->Write();
   //    sagittas_a_25p_hist.at(i).get()->Write();
   //    sagittas_a_30p_hist.at(i).get()->Write();
   //    sagittas_a_35p_hist.at(i).get()->Write();
   //    sagittas_a_40p_hist.at(i).get()->Write();
   //    sagittas_a_45p_hist.at(i).get()->Write();
   //    sagittas_a_50p_hist.at(i).get()->Write();

   //    sagittas_c_0p_hist.at(i).get()->Write();
   //    sagittas_c_5p_hist.at(i).get()->Write();
   //    sagittas_c_10p_hist.at(i).get()->Write();
   //    sagittas_c_15p_hist.at(i).get()->Write();
   //    sagittas_c_20p_hist.at(i).get()->Write();
   //    sagittas_c_25p_hist.at(i).get()->Write();
   //    sagittas_c_30p_hist.at(i).get()->Write();
   //    sagittas_c_35p_hist.at(i).get()->Write();
   //    sagittas_c_40p_hist.at(i).get()->Write();
   //    sagittas_c_45p_hist.at(i).get()->Write();
   //    sagittas_c_50p_hist.at(i).get()->Write();

   //    sagittas_a_0p_improved_hist.at(i).get()->Write();
   //    sagittas_a_5p_improved_hist.at(i).get()->Write();
   //    sagittas_a_10p_improved_hist.at(i).get()->Write();
   //    sagittas_a_15p_improved_hist.at(i).get()->Write();
   //    sagittas_a_20p_improved_hist.at(i).get()->Write();
   //    sagittas_a_25p_improved_hist.at(i).get()->Write();
   //    sagittas_a_30p_improved_hist.at(i).get()->Write();
   //    sagittas_a_35p_improved_hist.at(i).get()->Write();
   //    sagittas_a_40p_improved_hist.at(i).get()->Write();
   //    sagittas_a_45p_improved_hist.at(i).get()->Write();
   //    sagittas_a_50p_improved_hist.at(i).get()->Write();
   //    sagittas_a_100p_improved_hist.at(i).get()->Write();
   //    sagittas_a_200p_improved_hist.at(i).get()->Write();
   //    sagittas_a_300p_improved_hist.at(i).get()->Write();


   //    sagittas_a_0p_mm1_improved_hist.at(i).get()->Write();
   //    sagittas_a_10p_mm1_improved_hist.at(i).get()->Write();
   //    sagittas_a_20p_mm1_improved_hist.at(i).get()->Write();
   //    sagittas_a_30p_mm1_improved_hist.at(i).get()->Write();
   //    sagittas_a_40p_mm1_improved_hist.at(i).get()->Write();
   //    sagittas_a_50p_mm1_improved_hist.at(i).get()->Write();
   //    sagittas_a_100p_mm1_improved_hist.at(i).get()->Write();
      
   //    sagittas_a_0p_mm2_improved_hist.at(i).get()->Write();
   //    sagittas_a_10p_mm2_improved_hist.at(i).get()->Write();
   //    sagittas_a_20p_mm2_improved_hist.at(i).get()->Write();
   //    sagittas_a_30p_mm2_improved_hist.at(i).get()->Write();
   //    sagittas_a_40p_mm2_improved_hist.at(i).get()->Write();
   //    sagittas_a_50p_mm2_improved_hist.at(i).get()->Write();
   //    sagittas_a_100p_mm2_improved_hist.at(i).get()->Write();

   //    sagittas_a_0p_stgc1_improved_hist.at(i).get()->Write();
   //    sagittas_a_10p_stgc1_improved_hist.at(i).get()->Write();
   //    sagittas_a_20p_stgc1_improved_hist.at(i).get()->Write();
   //    sagittas_a_30p_stgc1_improved_hist.at(i).get()->Write();
   //    sagittas_a_40p_stgc1_improved_hist.at(i).get()->Write();
   //    sagittas_a_50p_stgc1_improved_hist.at(i).get()->Write();
   //    sagittas_a_100p_stgc1_improved_hist.at(i).get()->Write();

   //    sagittas_a_0p_stgc2_improved_hist.at(i).get()->Write();
   //    sagittas_a_10p_stgc2_improved_hist.at(i).get()->Write();
   //    sagittas_a_20p_stgc2_improved_hist.at(i).get()->Write();
   //    sagittas_a_30p_stgc2_improved_hist.at(i).get()->Write();
   //    sagittas_a_40p_stgc2_improved_hist.at(i).get()->Write();
   //    sagittas_a_50p_stgc2_improved_hist.at(i).get()->Write();
   //    sagittas_a_100p_stgc2_improved_hist.at(i).get()->Write();
      
   //    sagittas_c_0p_improved_hist.at(i).get()->Write(); 
   //    sagittas_c_5p_improved_hist.at(i).get()->Write();
   //    sagittas_c_10p_improved_hist.at(i).get()->Write();
   //    sagittas_c_15p_improved_hist.at(i).get()->Write();
   //    sagittas_c_20p_improved_hist.at(i).get()->Write();
   //    sagittas_c_25p_improved_hist.at(i).get()->Write();
   //    sagittas_c_30p_improved_hist.at(i).get()->Write();
   //    sagittas_c_35p_improved_hist.at(i).get()->Write();
   //    sagittas_c_40p_improved_hist.at(i).get()->Write();
   //    sagittas_c_45p_improved_hist.at(i).get()->Write();
   //    sagittas_c_50p_improved_hist.at(i).get()->Write();
   //    sagittas_c_100p_improved_hist.at(i).get()->Write();
   //    sagittas_c_200p_improved_hist.at(i).get()->Write();
   //    sagittas_c_300p_improved_hist.at(i).get()->Write();


   //    sagittas_c_0p_mm1_improved_hist.at(i).get()->Write();
   //    sagittas_c_10p_mm1_improved_hist.at(i).get()->Write();
   //    sagittas_c_20p_mm1_improved_hist.at(i).get()->Write();
   //    sagittas_c_30p_mm1_improved_hist.at(i).get()->Write();
   //    sagittas_c_40p_mm1_improved_hist.at(i).get()->Write();
   //    sagittas_c_50p_mm1_improved_hist.at(i).get()->Write();
   //    sagittas_c_100p_mm1_improved_hist.at(i).get()->Write();
      
   //    sagittas_c_0p_mm2_improved_hist.at(i).get()->Write();
   //    sagittas_c_10p_mm2_improved_hist.at(i).get()->Write();
   //    sagittas_c_20p_mm2_improved_hist.at(i).get()->Write();
   //    sagittas_c_30p_mm2_improved_hist.at(i).get()->Write();
   //    sagittas_c_40p_mm2_improved_hist.at(i).get()->Write();
   //    sagittas_c_50p_mm2_improved_hist.at(i).get()->Write();
   //    sagittas_c_100p_mm2_improved_hist.at(i).get()->Write();

   //    sagittas_c_0p_stgc1_improved_hist.at(i).get()->Write();
   //    sagittas_c_10p_stgc1_improved_hist.at(i).get()->Write();
   //    sagittas_c_20p_stgc1_improved_hist.at(i).get()->Write();
   //    sagittas_c_30p_stgc1_improved_hist.at(i).get()->Write();
   //    sagittas_c_40p_stgc1_improved_hist.at(i).get()->Write();
   //    sagittas_c_50p_stgc1_improved_hist.at(i).get()->Write();
   //    sagittas_c_100p_stgc1_improved_hist.at(i).get()->Write();

   //    sagittas_c_0p_stgc2_improved_hist.at(i).get()->Write();
   //    sagittas_c_10p_stgc2_improved_hist.at(i).get()->Write();
   //    sagittas_c_20p_stgc2_improved_hist.at(i).get()->Write();
   //    sagittas_c_30p_stgc2_improved_hist.at(i).get()->Write();
   //    sagittas_c_40p_stgc2_improved_hist.at(i).get()->Write();
   //    sagittas_c_50p_stgc2_improved_hist.at(i).get()->Write();
   //    sagittas_c_100p_stgc2_improved_hist.at(i).get()->Write();

   //    sagitta_a_2nd_coord_0p_hist.at(i).get()->Write(); 
   //    sagitta_a_2nd_coord_30p_hist.at(i).get()->Write(); 
   //    sagitta_c_2nd_coord_0p_hist.at(i).get()->Write(); 
   //    sagitta_c_2nd_coord_30p_hist.at(i).get()->Write(); 

   //    sagitta_a_2nd_coord_0p_improved_hist.at(i).get()->Write(); 
   //    sagitta_a_2nd_coord_30p_improved_hist.at(i).get()->Write(); 
   //    sagitta_c_2nd_coord_0p_improved_hist.at(i).get()->Write(); 
   //    sagitta_c_2nd_coord_30p_improved_hist.at(i).get()->Write(); 

   //    sagitta_a_t223_30p_hist.at(i).get()->Write(); 
   // }

   // for(int i =0; i<48; ++i){
   //    sagittas_a_0p_mm1_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_10p_mm1_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_20p_mm1_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_30p_mm1_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_40p_mm1_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_50p_mm1_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_100p_mm1_t_improved_hist.at(i).get()->Write();
      
   //    sagittas_a_0p_mm2_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_10p_mm2_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_20p_mm2_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_30p_mm2_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_40p_mm2_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_50p_mm2_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_100p_mm2_t_improved_hist.at(i).get()->Write();

   //    sagittas_a_0p_stgc1_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_10p_stgc1_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_20p_stgc1_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_30p_stgc1_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_40p_stgc1_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_50p_stgc1_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_100p_stgc1_t_improved_hist.at(i).get()->Write();

   //    sagittas_a_0p_stgc2_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_10p_stgc2_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_20p_stgc2_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_30p_stgc2_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_40p_stgc2_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_50p_stgc2_t_improved_hist.at(i).get()->Write();
   //    sagittas_a_100p_stgc2_t_improved_hist.at(i).get()->Write();

   //    sagittas_c_0p_mm1_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_10p_mm1_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_20p_mm1_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_30p_mm1_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_40p_mm1_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_50p_mm1_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_100p_mm1_t_improved_hist.at(i).get()->Write();
      
   //    sagittas_c_0p_mm2_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_10p_mm2_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_20p_mm2_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_30p_mm2_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_40p_mm2_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_50p_mm2_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_100p_mm2_t_improved_hist.at(i).get()->Write();

   //    sagittas_c_0p_stgc1_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_10p_stgc1_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_20p_stgc1_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_30p_stgc1_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_40p_stgc1_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_50p_stgc1_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_100p_stgc1_t_improved_hist.at(i).get()->Write();

   //    sagittas_c_0p_stgc2_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_10p_stgc2_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_20p_stgc2_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_30p_stgc2_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_40p_stgc2_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_50p_stgc2_t_improved_hist.at(i).get()->Write();
   //    sagittas_c_100p_stgc2_t_improved_hist.at(i).get()->Write();

   // }
   outputFile->Close();
};

void tree::Plot()
{
   std::cout << "Begin plotting" << std::endl;
   
   std::string outputdir = "Plots/";
   std::string name;
   
   
   if (seg1_xy_aside_hist == NULL)
   {
      std::cout << "nullpointer" << std::endl;
   }
   else
   {
      std::cout << "nooo" << std::endl;
   }
   seg1_xy_aside_hist->Print();
   
   
   
   // plotter->Create2DPlot("seg1_xy_aside_hist", "x  (mm)", "y  (mm)", seg1_xy_aside_hist.get(), outputdir);
   // std::cout << "plot 1 made" << std::endl;

   // plotter->Create2DPlot("seg2_xy_aside_hist", "x  (mm)", "y  (mm)", seg2_xy_aside_hist.get(), outputdir);
   // plotter->Create2DPlot("seg3_xy_aside_hist", "x  (mm)", "y  (mm)", seg3_xy_aside_hist.get(), outputdir);

   // plotter->Create2DPlot("seg1x_seg2x_aside_hist", "seg1 x  (mm)", "seg2 x  (mm)", seg1x_seg2x_aside_hist.get(), outputdir);
   // plotter->Create2DPlot("seg1x_seg3x_aside_hist", "seg1 x  (mm)", "seg3 x  (mm)", seg1x_seg3x_aside_hist.get(), outputdir);
   // plotter->Create2DPlot("seg2x_seg3x_aside_hist", "seg2 x  (mm)", "seg3 x  (mm)", seg2x_seg3x_aside_hist.get(), outputdir);

   // plotter->Create2DPlot("seg1y_seg2y_aside_hist", "seg1 y  (mm)", "seg2 y  (mm)", seg1y_seg2y_aside_hist.get(), outputdir);
   // plotter->Create2DPlot("seg1y_seg3y_aside_hist", "seg1 y  (mm)", "seg3 y  (mm)", seg1y_seg3y_aside_hist.get(), outputdir);
   // plotter->Create2DPlot("seg2y_seg3y_aside_hist", "seg2 y  (mm)", "seg3 y  (mm)", seg2y_seg3y_aside_hist.get(), outputdir);

   // plotter->Create2DPlot("seg1z_seg2z_aside_hist", "seg1 z  (mm)", "seg2z  (mm)", seg1z_seg2z_aside_hist.get(), outputdir);
   // plotter->Create2DPlot("seg1z_seg3z_aside_hist", "seg1 z  (mm)", "seg3z  (mm)", seg1z_seg3z_aside_hist.get(), outputdir);
   // plotter->Create2DPlot("seg2z_seg3z_aside_hist", "seg2 z  (mm)", "seg3z  (mm)", seg2z_seg3z_aside_hist.get(), outputdir);

   // for (int i = 0; i < 16; ++i)
   // {
   //    name = "seg1_nhits_aside_sector" + std::to_string(i+1) + "";
   //    plotter->Create1DPlot(name, "nhits", "", seg1_nhits_hist_per_sector_aside_hists.at(i).get(), outputdir);

   //    name = "seg2_nhits_aside_sector" + std::to_string(i+1) + "";
   //    plotter->Create1DPlot(name, "nhits", "", seg2_nhits_hist_per_sector_aside_hists.at(i).get(), outputdir);
      
   //    name = "seg3_nhits_aside_sector" + std::to_string(i+1) + "";
   //    plotter->Create1DPlot(name, "nhits", "", seg3_nhits_hist_per_sector_aside_hists.at(i).get(), outputdir);
   // }

   // std::cout << "block1 made" << std::endl;


   // plotter->Create2DPlot("seg1_xy_cside_hist", "x  (mm)", "y  (mm)", seg1_xy_cside_hist.get(), outputdir);
   // plotter->Create2DPlot("seg2_xy_cside_hist", "x  (mm)", "y  (mm)", seg2_xy_cside_hist.get(), outputdir);
   // plotter->Create2DPlot("seg3_xy_cside_hist", "x  (mm)", "y  (mm)", seg3_xy_cside_hist.get(), outputdir);

   // plotter->Create2DPlot("seg1x_seg2x_cside_hist", "seg1 x  (mm)", "seg2 x  (mm)", seg1x_seg2x_cside_hist.get(), outputdir);
   // plotter->Create2DPlot("seg1x_seg3x_cside_hist", "seg1 x  (mm)", "seg3 x  (mm)", seg1x_seg3x_cside_hist.get(), outputdir);
   // plotter->Create2DPlot("seg2x_seg3x_cside_hist", "seg2 x  (mm)", "seg3 x  (mm)", seg2x_seg3x_cside_hist.get(), outputdir);

   // plotter->Create2DPlot("seg1y_seg2y_cside_hist", "seg1 y  (mm)", "seg2 y  (mm)", seg1y_seg2y_cside_hist.get(), outputdir);
   // plotter->Create2DPlot("seg1y_seg3y_cside_hist", "seg1 y  (mm)", "seg3 y  (mm)", seg1y_seg3y_cside_hist.get(), outputdir);
   // plotter->Create2DPlot("seg2y_seg3y_cside_hist", "seg2 y  (mm)", "seg3 y  (mm)", seg2y_seg3y_cside_hist.get(), outputdir);

   // plotter->Create2DPlot("seg1z_seg2z_cside_hist", "seg1 z  (mm)", "seg2 z  (mm)", seg1z_seg2z_cside_hist.get(), outputdir);
   // plotter->Create2DPlot("seg1z_seg3z_cside_hist", "seg1 z  (mm)", "seg3 z  (mm)", seg1z_seg3z_cside_hist.get(), outputdir);
   // plotter->Create2DPlot("seg2z_seg3z_cside_hist", "seg2 z  (mm)", "seg3 z  (mm)", seg2z_seg3z_cside_hist.get(), outputdir);

   // for (int i = 0; i < 16; ++i)
   // {
   //    name = "seg1_nhits_cside_sector" + std::to_string(i+1) + "";
   //    plotter->Create1DPlot(name, "nhits", "", seg1_nhits_hist_per_sector_cside_hists.at(i).get(), outputdir);

   //    name = "seg2_nhits_cside_sector" + std::to_string(i+1) + "";
   //    plotter->Create1DPlot(name, "nhits", "", seg2_nhits_hist_per_sector_cside_hists.at(i).get(), outputdir);
      
   //    name = "seg3_nhits_cside_sector" + std::to_string(i+1) + "";
   //    plotter->Create1DPlot(name, "nhits", "", seg3_nhits_hist_per_sector_cside_hists.at(i).get(), outputdir);
   // }

   // std::cout << "block2 made" << std::endl;


   // plotter->Create2DPlot("seg1_eta_hist", "seg1 eta", "muon eta", seg1_eta_hist.get(), outputdir);
   // plotter->Create2DPlot("seg2_eta_hist", "seg2 eta", "muon eta", seg2_eta_hist.get(), outputdir);
   // plotter->Create2DPlot("seg3_eta_hist", "seg3 eta", "muon eta", seg3_eta_hist.get(), outputdir);
   // plotter->Create2DPlot("seg1_phi_hist", "seg1 phi", "muon phi", seg1_phi_hist.get(), outputdir);
   // plotter->Create2DPlot("seg2_phi_hist", "seg2 phi", "muon phi", seg2_phi_hist.get(), outputdir);
   // plotter->Create2DPlot("seg3_phi_hist", "seg3 phi", "muon phi", seg3_phi_hist.get(), outputdir);

   // plotter->Create2DPlot("seg1_seg2_eta_hist", "seg1 eta", "seg2 eta", seg1_seg2_eta_hist.get(), outputdir);
   // plotter->Create2DPlot("seg1_seg3_eta_hist", "seg1 eta", "seg3 eta", seg1_seg3_eta_hist.get(), outputdir);
   // plotter->Create2DPlot("seg2_seg3_eta_hist", "seg2 eta", "seg3 eta", seg2_seg3_eta_hist.get(), outputdir);
   // plotter->Create2DPlot("seg1_seg2_phi_hist", "seg1 phi", "seg2 phi", seg1_seg2_phi_hist.get(), outputdir);
   // plotter->Create2DPlot("seg1_seg3_phi_hist", "seg1 phi", "seg3 phi", seg1_seg3_phi_hist.get(), outputdir);
   // plotter->Create2DPlot("seg2_seg3_phi_hist", "seg2 phi", "seg3 phi", seg2_seg3_phi_hist.get(), outputdir);

   // std::cout << "eta phi plots made" << std::endl;


   // plotter->Create1DPlot("seg1_residuals_hist", "Residual (mm)", "", seg1_track_residual_hist.get(), outputdir);
   // plotter->Create1DPlot("seg2_residuals_hist", "Residual (mm)", "", seg2_track_residual_hist.get(), outputdir);
   // plotter->Create1DPlot("seg3_residuals_hist", "Residual (mm)", "", seg3_track_residual_hist.get(), outputdir);

   plotter->CreateMuonSelectionPlot("muon_p_comp_hist", muon_p_hist.get(), muon_p_selection_hist.get(), outputdir);
   plotter->CreateMuonSelectionPlot("muon_pT_comp_hist", muon_pT_hist.get(), muon_pT_selection_hist.get(), outputdir);



   // plotter->Create2DPlot("mm1_xy_aside_hist", "mm1 x  (mm)", "mm1 y  (mm)", mm1_xy_aside_hist.get(), outputdir);
   // plotter->Create2DPlot("mm2_xy_aside_hist", "mm2 x  (mm)", "mm2 y  (mm)", mm2_xy_aside_hist.get(), outputdir);
   // plotter->Create2DPlot("stgc1_xy_aside_hist", "stgc1 x  (mm)", "stgc1 y  (mm)", stgc1_xy_aside_hist.get(), outputdir);
   // plotter->Create2DPlot("stgc2_xy_aside_hist", "stgc2 x  (mm)", "stgc2 y  (mm)", stgc2_xy_aside_hist.get(), outputdir);

   // plotter->Create2DPlot("mm1_xy_cside_hist", "mm1 x  (mm)", "mm1 y  (mm)", mm1_xy_cside_hist.get(), outputdir);
   // plotter->Create2DPlot("mm2_xy_cside_hist", "mm2 x  (mm)", "mm2 y  (mm)", mm2_xy_cside_hist.get(), outputdir);
   // plotter->Create2DPlot("stgc1_xy_cside_hist", "stgc1 x  (mm)", "stgc1 y  (mm)", stgc1_xy_cside_hist.get(), outputdir);
   // plotter->Create2DPlot("stgc2_xy_cside_hist", "stgc2 x  (mm)", "stgc2 y  (mm)", stgc2_xy_cside_hist.get(), outputdir);



   // name = "Sagitta_0gev";
   // FitInfo f = plotter->CreateSagPlot(name, sagitta_0p_hist.get(), outputdir);
   // name = "Sagitta_10gev";
   // f = plotter->CreateSagPlot(name, sagitta_10p_hist.get(), outputdir);
   // name = "Sagitta_15gev";
   // f = plotter->CreateSagPlot(name, sagitta_15p_hist.get(), outputdir);
   // name = "Sagitta_20gev";
   // f = plotter->CreateSagPlot(name, sagitta_20p_hist.get(), outputdir);
   // name = "Sagitta_30gev";
   // f = plotter->CreateSagPlot(name, sagitta_30p_hist.get(), outputdir);
   // name = "Sagitta_50gev";
   // f = plotter->CreateSagPlot(name, sagitta_50p_hist.get(), outputdir);





   // for (int i = 0; i < 16; ++i)
   // {
   //    std::cout << "making per sector per side plots \t" << i << std::endl;
   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_0p_hist";
   //    std::ofstream myfile_a;

   //    myfile_a.open("csv/sagittas_a_sector_" + std::to_string(i+1) + "_hist.csv");

   //    myfile_a << "Nentries;"
   //           << "x0;"
   //           << "sigma_x0;"
   //           << "m;"
   //           << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_a_0p_hist.at(i).get(), outputdir);
   //    myfile_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_5p_hist.at(i).get(), outputdir);
   //    myfile_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_10p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_10p_hist.at(i).get(), outputdir);
   //    myfile_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_15p_hist.at(i).get(), outputdir);
   //    myfile_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_20p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_20p_hist.at(i).get(), outputdir);
   //    myfile_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_25p_hist.at(i).get(), outputdir);
   //    myfile_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_30p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_30p_hist.at(i).get(), outputdir);
   //    myfile_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_35p_hist.at(i).get(), outputdir);
   //    myfile_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_40p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_40p_hist.at(i).get(), outputdir);
   //    myfile_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_45p_hist.at(i).get(), outputdir);
   //    myfile_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_50p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_50p_hist.at(i).get(), outputdir);
   //    myfile_a << f << std::endl;



   //    std::vector<TH1*> thehists {sagittas_a_10p_hist.at(i).get(), sagittas_a_20p_hist.at(i).get(), sagittas_a_30p_hist.at(i).get()};
   //    std::vector<std::string> names {"p > 10 GeV", "p > 20 GeV", "p > 30 GeV"};
   //    std::vector<std::string> colors = {"#000000", "#bc0031", "#228b22"};
   //    std::string filename = "sagittas_a_sector_"+std::to_string(i+1)+"_momenta";

   //    plotter->Create1DPlotMomenta( names, thehists, colors, "Sagitta (mm)", "Entries", outputdir, filename);
   //    plotter->Create1DPlotMomenta( names, thehists, colors, "Sagitta (mm)", "A.U.", outputdir, filename+"_norm", 1000, 800, true);

      

   //    ////////c-side
   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_0p_hist";
   //    std::ofstream myfile_c;
   //    myfile_c.open("csv/sagittas_c_sector_" + std::to_string(i+1) + "_hist.csv");
   //    myfile_c << "Nentries;"
   //             << "x0;"
   //             << "sigma_x0;"
   //             << "m;"
   //             << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_c_0p_hist.at(i).get(), outputdir);
   //    myfile_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_5p_hist.at(i).get(), outputdir);
   //    myfile_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_10p_hist";

   //    f = plotter->CreateSagPlot(name, sagittas_c_10p_hist.at(i).get(), outputdir);
   //    myfile_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_15p_hist.at(i).get(), outputdir);
   //    myfile_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_20p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_20p_hist.at(i).get(), outputdir);
   //    myfile_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_25p_hist.at(i).get(), outputdir);
   //    myfile_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_30p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_30p_hist.at(i).get(), outputdir);
   //    myfile_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_35p_hist.at(i).get(), outputdir);
   //    myfile_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_40p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_40p_hist.at(i).get(), outputdir);
   //    myfile_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_45p_hist.at(i).get(), outputdir);
   //    myfile_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_50p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_50p_hist.at(i).get(), outputdir);
   //    myfile_c << f << std::endl;





   //    // plots using the 'improved' second coordinate

   //    std::cout << "making per sector per side plots with improved second coordinate \t" << i << std::endl;
   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_0p_improved_hist";
   //    std::ofstream myfile_a_improved;

   //    myfile_a_improved.open("csv/sagittas_a_sector_" + std::to_string(i+1) + "_improved_hist.csv");

   //    myfile_a_improved << "Nentries;"
   //           << "x0;"
   //           << "sigma_x0;"
   //           << "m;"
   //           << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_a_0p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_5p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_5p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_10p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_10p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_15p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_15p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_20p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_20p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_25p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_25p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_30p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_30p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_35p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_35p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_40p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_40p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_45p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_45p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_50p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_50p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;
      
   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_100p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_100p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_200p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_200p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_300p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_300p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_30p_mm1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_30p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_50p_mm1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_50p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_100p_mm1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_100p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_30p_mm2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_30p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_50p_mm2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_50p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_100p_mm2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_100p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_30p_stgc1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_30p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_50p_stgc1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_50p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_100p_stgc1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_100p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_30p_stgc2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_30p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_50p_stgc2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_50p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_100p_stgc2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_100p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_a_improved << f << std::endl;

   //    ////////c-side
   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_0p_improved_hist";
   //    std::ofstream myfile_c_improved;
   //    myfile_c_improved.open("csv/sagittas_c_sector_" + std::to_string(i+1) + "_improved_hist.csv");
   //    myfile_c_improved << "Nentries;"
   //             << "x0;"
   //             << "sigma_x0;"
   //             << "m;"
   //             << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_c_0p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_5p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_5p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_10p_improved_hist";

   //    f = plotter->CreateSagPlot(name, sagittas_c_10p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_15p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_15p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_20p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_20p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_25p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_25p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_30p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_30p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_35p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_35p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_40p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_40p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_45p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_45p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_50p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_50p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_100p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_100p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_200p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_200p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_300p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_300p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_30p_mm1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_30p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_50p_mm1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_50p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_100p_mm1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_100p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_30p_mm2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_30p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_50p_mm2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_50p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_100p_mm2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_100p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_30p_stgc1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_30p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_50p_stgc1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_50p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_100p_stgc1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_100p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_30p_stgc2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_30p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_50p_stgc2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_50p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_100p_stgc2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_100p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_c_improved << f << std::endl;



   //    // 2nd coord sagitta plots

   //    std::cout << "making 2nd coord sagitta plots  \t" << i << std::endl;
   //    name = "sagittas_a_2nd_coord_sector" + std::to_string(i+1) + "_0p_hist";
   //    std::ofstream myfile_a_2nd_coord;

   //    myfile_a_2nd_coord.open("csv/sagittas_a_2nd_coord_sector_" + std::to_string(i+1) + "_hist.csv");

   //    myfile_a_2nd_coord << "Nentries;"
   //           << "x0;"
   //           << "sigma_x0;"
   //           << "m;"
   //           << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagitta_a_2nd_coord_0p_hist.at(i).get(), outputdir);
   //    myfile_a_2nd_coord << f << std::endl;

   //    name = "sagittas_a_2nd_coord_sector" + std::to_string(i+1) + "_30p_hist";
   //    f = plotter->CreateSagPlot(name, sagitta_a_2nd_coord_30p_hist.at(i).get(), outputdir);
   //    myfile_a_2nd_coord << f << std::endl;


   //    name = "sagittas_c_2nd_coord_sector" + std::to_string(i+1) + "_0p_hist";
   //    std::ofstream myfile_c_2nd_coord;

   //    myfile_c_2nd_coord.open("csv/sagittas_c_2nd_coord_sector_" + std::to_string(i+1) + "_hist.csv");

   //    myfile_c_2nd_coord << "Nentries;"
   //           << "x0;"
   //           << "sigma_x0;"
   //           << "m;"
   //           << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagitta_c_2nd_coord_0p_hist.at(i).get(), outputdir);
   //    myfile_c_2nd_coord << f << std::endl;

   //    name = "sagittas_c_2nd_coord_sector" + std::to_string(i+1) + "_30p_hist";
   //    f = plotter->CreateSagPlot(name, sagitta_c_2nd_coord_30p_hist.at(i).get(), outputdir);
   //    myfile_c_2nd_coord << f << std::endl;



   //    // 2nd coord sagitta plots using the improved 2nd coordinate

   //    std::cout << "making 2nd coord sagitta plots with improved 2nd coordinate  \t" << i << std::endl;
   //    name = "sagittas_a_2nd_coord_sector" + std::to_string(i+1) + "_0p_improved_hist";
   //    std::ofstream myfile_a_2nd_coord_improved;

   //    myfile_a_2nd_coord_improved.open("csv/sagittas_a_2nd_coord_sector_" + std::to_string(i+1) + "_improved_hist.csv");

   //    myfile_a_2nd_coord_improved << "Nentries;"
   //           << "x0;"
   //           << "sigma_x0;"
   //           << "m;"
   //           << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagitta_a_2nd_coord_0p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_2nd_coord_improved << f << std::endl;

   //    name = "sagittas_a_2nd_coord_sector" + std::to_string(i+1) + "_30p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagitta_a_2nd_coord_30p_improved_hist.at(i).get(), outputdir);
   //    myfile_a_2nd_coord_improved << f << std::endl;


   //    name = "sagittas_c_2nd_coord_sector" + std::to_string(i+1) + "_0p_improved_hist";
   //    std::ofstream myfile_c_2nd_coord_improved;

   //    myfile_c_2nd_coord_improved.open("csv/sagittas_c_2nd_coord_sector_" + std::to_string(i+1) + "_improved_hist.csv");

   //    myfile_c_2nd_coord_improved << "Nentries;"
   //           << "x0;"
   //           << "sigma_x0;"
   //           << "m;"
   //           << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagitta_c_2nd_coord_0p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_2nd_coord_improved << f << std::endl;

   //    name = "sagittas_c_2nd_coord_sector" + std::to_string(i+1) + "_30p_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagitta_c_2nd_coord_30p_improved_hist.at(i).get(), outputdir);
   //    myfile_c_2nd_coord_improved << f << std::endl;


   //    // Sagittas for tower indices
   //    std::cout << "making per sector per side plots with improved second coordinate for different tower indices \t" << std::endl;
   //    name = "sagittas_t223_a_30p_improved sector_" + std::to_string(i+1) + "hist";
   //    std::ofstream myfile_t223_a_improved;
   //    myfile_t223_a_improved.open("csv/sagittas_t223_a_improved_sector" + std::to_string(i+1) + "_improved_hist.csv");

   //    myfile_t223_a_improved << "Nentries;"
   //             << "x0;"
   //             << "sigma_x0;"
   //             << "m;"
   //             << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagitta_a_t223_30p_hist.at(i).get(), outputdir);
   //    myfile_t223_a_improved << f << std::endl;



   //    myfile_a.close();
   //    myfile_c.close();
   //    myfile_a_improved.close();
   //    myfile_c_improved.close();
   //    myfile_a_2nd_coord.close();
   //    myfile_c_2nd_coord.close();
   //    myfile_a_2nd_coord_improved.close();
   //    myfile_c_2nd_coord_improved.close();
   //    myfile_t223_a_improved.close();
   // }


   // for (int i = 0; i < 16; ++i)
   // {
   //    //MM1
   //    outputdir="PlotsQ/";
   //    std::cout << "making per sector mm1 per side plots \t" << i << std::endl;
   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_0p_mm1_improved_hist";
   //    std::ofstream myfile_mm1_a;

   //    myfile_mm1_a.open("csv/sagittas_a_sector_" + std::to_string(i+1) + "_mm1_hist.csv");

   //    myfile_mm1_a << "Nentries;"
   //           << "x0;"
   //           << "sigma_x0;"
   //           << "m;"
   //           << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_a_0p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_5p_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_10p_mm1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_10p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_15p_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_20p_mm1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_20p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_25p_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_30p_mm1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_30p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_35p_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_40p_mm1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_40p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_45p_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_50p_mm1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_50p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;



   //    ////////c-side
   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_0p_mm1_improved_hist";
   //    std::ofstream myfile_mm1_c;
   //    myfile_mm1_c.open("csv/sagittas_c_sector_" + std::to_string(i+1) + "_mm1_hist.csv");
   //    myfile_mm1_c << "Nentries;"
   //             << "x0;"
   //             << "sigma_x0;"
   //             << "m;"
   //             << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_c_0p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_5p_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_10p_mm1_improved_hist";

   //    f = plotter->CreateSagPlot(name, sagittas_c_10p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_15p_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_20p_mm1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_20p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_25p_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_30p_mm1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_30p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_35p_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_40p_mm1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_40p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_45p_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_50p_mm1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_50p_mm1_improved_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    myfile_mm1_a.close();
   //    myfile_mm1_c.close();

   //      //MM2
   //    std::cout << "making per sector mm2 per side plots \t" << i << std::endl;
   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_0p_mm2_improved_hist";
   //    std::ofstream myfile_mm2_a;

   //    myfile_mm2_a.open("csv/sagittas_a_sector_" + std::to_string(i+1) + "_mm2_hist.csv");

   //    myfile_mm2_a << "Nentries;"
   //           << "x0;"
   //           << "sigma_x0;"
   //           << "m;"
   //           << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_a_0p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_5p_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_10p_mm2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_10p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_15p_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_20p_mm2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_20p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_25p_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_30p_mm2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_30p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_35p_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_40p_mm2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_40p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_45p_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_50p_mm2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_50p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;



   //    ////////c-side
   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_0p_mm2_improved_hist";
   //    std::ofstream myfile_mm2_c;
   //    myfile_mm2_c.open("csv/sagittas_c_sector_" + std::to_string(i+1) + "_mm2_hist.csv");
   //    myfile_mm2_c << "Nentries;"
   //             << "x0;"
   //             << "sigma_x0;"
   //             << "m;"
   //             << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_c_0p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_5p_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_10p_mm2_improved_hist";

   //    f = plotter->CreateSagPlot(name, sagittas_c_10p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_15p_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_20p_mm2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_20p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_25p_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_30p_mm2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_30p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_35p_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_40p_mm2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_40p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_45p_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_50p_mm2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_50p_mm2_improved_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    myfile_mm2_a.close();
   //    myfile_mm2_c.close();

   //         //STGC1
   //    std::cout << "making per sector stgc1 per side plots \t" << i << std::endl;
   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_0p_stgc1_improved_hist";
   //    std::ofstream myfile_stgc1_a;

   //    myfile_stgc1_a.open("csv/sagittas_a_sector_" + std::to_string(i+1) + "_stgc1_hist.csv");

   //    myfile_stgc1_a << "Nentries;"
   //           << "x0;"
   //           << "sigma_x0;"
   //           << "m;"
   //           << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_a_0p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_5p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_10p_stgc1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_10p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_15p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_20p_stgc1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_20p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_25p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_30p_stgc1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_30p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_35p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_40p_stgc1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_40p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_45p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_50p_stgc1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_50p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;



   //    ////////c-side
   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_0p_stgc1_improved_hist";
   //    std::ofstream myfile_stgc1_c;
   //    myfile_stgc1_c.open("csv/sagittas_c_sector_" + std::to_string(i+1) + "_stgc1_hist.csv");
   //    myfile_stgc1_c << "Nentries;"
   //             << "x0;"
   //             << "sigma_x0;"
   //             << "m;"
   //             << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_c_0p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_5p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_10p_stgc1_improved_hist";

   //    f = plotter->CreateSagPlot(name, sagittas_c_10p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_15p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_20p_stgc1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_20p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_25p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_30p_stgc1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_30p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_35p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_40p_stgc1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_40p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_45p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_50p_stgc1_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_50p_stgc1_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    myfile_stgc1_a.close();
   //    myfile_stgc1_c.close();

   //         //STGC2
   //    std::cout << "making per sector stgc2 per side plots \t" << i << std::endl;
   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_0p_stgc2_improved_hist";
   //    std::ofstream myfile_stgc2_a;

   //    myfile_stgc2_a.open("csv/sagittas_a_sector_" + std::to_string(i+1) + "_stgc2_hist.csv");

   //    myfile_stgc2_a << "Nentries;"
   //           << "x0;"
   //           << "sigma_x0;"
   //           << "m;"
   //           << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_a_0p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_5p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_10p_stgc2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_10p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_15p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_20p_stgc2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_20p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_25p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_30p_stgc2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_30p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_35p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_40p_stgc2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_40p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_45p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_50p_stgc2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_50p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;



   //    ////////c-side
   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_0p_stgc2_improved_hist";
   //    std::ofstream myfile_stgc2_c;
   //    myfile_stgc2_c.open("csv/sagittas_c_sector_" + std::to_string(i+1) + "_stgc2_hist.csv");
   //    myfile_stgc2_c << "Nentries;"
   //             << "x0;"
   //             << "sigma_x0;"
   //             << "m;"
   //             << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_c_0p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_5p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_10p_stgc2_improved_hist";

   //    f = plotter->CreateSagPlot(name, sagittas_c_10p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_15p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_20p_stgc2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_20p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_25p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_30p_stgc2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_30p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_35p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_40p_stgc2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_40p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_45p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_50p_stgc2_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_50p_stgc2_improved_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    myfile_stgc2_a.close();
   //    myfile_stgc2_c.close();

   //    outputdir="Plots/";

   // }
   


   //t1 t2 t3
   // for(int twr = 0; twr <3; ++twr)
   // {
   //  for (int i = 0; i < 16; ++i)
   //  {
   //    //MM1
   //    outputdir="PlotsTower/";
   //    std::cout << "making per sector mm1 per side plots \t" << i << std::endl;
   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_0p_mm1_t_improved_hist";
   //    std::ofstream myfile_mm1_a;

   //    myfile_mm1_a.open("csv/sagittas_a_sector_" + std::to_string(i+1) + "_mm1_t" + std::to_string(twr+1) + "_hist.csv");

   //    myfile_mm1_a << "Nentries;"
   //           << "x0;"
   //           << "sigma_x0;"
   //           << "m;"
   //           << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_a_0p_mm1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_5p_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_10p_mm1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_10p_mm1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_15p_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_20p_mm1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_20p_mm1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_25p_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_30p_mm1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_30p_mm1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_35p_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_40p_mm1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_40p_mm1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_45p_hist.at(i).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_50p_mm1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_50p_mm1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm1_a << f << std::endl;



   //    ////////c-side
   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_0p_mm1_t_improved_hist";
   //    std::ofstream myfile_mm1_c;
   //    myfile_mm1_c.open("csv/sagittas_c_sector_" + std::to_string(i+1) + "_mm1_t" + std::to_string(twr+1) + "_hist.csv");
   //    myfile_mm1_c << "Nentries;"
   //             << "x0;"
   //             << "sigma_x0;"
   //             << "m;"
   //             << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_c_0p_mm1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_5p_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_10p_mm1_t_improved_hist";

   //    f = plotter->CreateSagPlot(name, sagittas_c_10p_mm1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_15p_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_20p_mm1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_20p_mm1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_25p_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_30p_mm1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_30p_mm1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_35p_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_40p_mm1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_40p_mm1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_45p_hist.at(i).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_50p_mm1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_50p_mm1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm1_c << f << std::endl;

   //    myfile_mm1_a.close();
   //    myfile_mm1_c.close();

   //      //MM2
   //    std::cout << "making per sector mm2 per side plots \t" << i << std::endl;
   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_0p_mm2_t_improved_hist";
   //    std::ofstream myfile_mm2_a;

   //    myfile_mm2_a.open("csv/sagittas_a_sector_" + std::to_string(i+1) + "_mm2_t" + std::to_string(twr+1) + "_hist.csv");

   //    myfile_mm2_a << "Nentries;"
   //           << "x0;"
   //           << "sigma_x0;"
   //           << "m;"
   //           << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_a_0p_mm2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_5p_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_10p_mm2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_10p_mm2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_15p_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_20p_mm2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_20p_mm2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_25p_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_30p_mm2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_30p_mm2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_35p_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_40p_mm2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_40p_mm2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_45p_hist.at(i).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_50p_mm2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_50p_mm2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm2_a << f << std::endl;



   //    ////////c-side
   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_0p_mm2_t_improved_hist";
   //    std::ofstream myfile_mm2_c;
   //    myfile_mm2_c.open("csv/sagittas_c_sector_" + std::to_string(i+1) + "_mm2_t" + std::to_string(twr+1) + "_hist.csv");
   //    myfile_mm2_c << "Nentries;"
   //             << "x0;"
   //             << "sigma_x0;"
   //             << "m;"
   //             << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_c_0p_mm2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_5p_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_10p_mm2_t_improved_hist";

   //    f = plotter->CreateSagPlot(name, sagittas_c_10p_mm2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_15p_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_20p_mm2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_20p_mm2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_25p_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_30p_mm2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_30p_mm2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_35p_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_40p_mm2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_40p_mm2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_45p_hist.at(i).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_50p_mm2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_50p_mm2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_mm2_c << f << std::endl;

   //    myfile_mm2_a.close();
   //    myfile_mm2_c.close();

   //         //STGC1
   //    std::cout << "making per sector stgc1 per side plots \t" << i << std::endl;
   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_0p_stgc1_t_improved_hist";
   //    std::ofstream myfile_stgc1_a;

   //    myfile_stgc1_a.open("csv/sagittas_a_sector_" + std::to_string(i+1) + "_stgc1_t" + std::to_string(twr+1) + "_hist.csv");

   //    myfile_stgc1_a << "Nentries;"
   //           << "x0;"
   //           << "sigma_x0;"
   //           << "m;"
   //           << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_a_0p_stgc1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_5p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_10p_stgc1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_10p_stgc1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_15p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_20p_stgc1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_20p_stgc1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_25p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_30p_stgc1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_30p_stgc1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_35p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_40p_stgc1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_40p_stgc1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_45p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_50p_stgc1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_50p_stgc1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc1_a << f << std::endl;



   //    ////////c-side
   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_0p_stgc1_t_improved_hist";
   //    std::ofstream myfile_stgc1_c;
   //    myfile_stgc1_c.open("csv/sagittas_c_sector_" + std::to_string(i+1) + "_stgc1_t" + std::to_string(twr+1) + "_hist.csv");
   //    myfile_stgc1_c << "Nentries;"
   //             << "x0;"
   //             << "sigma_x0;"
   //             << "m;"
   //             << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_c_0p_stgc1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_5p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_10p_stgc1_t_improved_hist";

   //    f = plotter->CreateSagPlot(name, sagittas_c_10p_stgc1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_15p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_20p_stgc1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_20p_stgc1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_25p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_30p_stgc1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_30p_stgc1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_35p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_40p_stgc1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_40p_stgc1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_45p_hist.at(i).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_50p_stgc1_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_50p_stgc1_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc1_c << f << std::endl;

   //    myfile_stgc1_a.close();
   //    myfile_stgc1_c.close();

   //         //STGC2
   //    std::cout << "making per sector stgc2 per side plots \t" << i << std::endl;
   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_0p_stgc2_t_improved_hist";
   //    std::ofstream myfile_stgc2_a;

   //    myfile_stgc2_a.open("csv/sagittas_a_sector_" + std::to_string(i+1) + "_stgc2_t" + std::to_string(twr+1) + "_hist.csv");

   //    myfile_stgc2_a << "Nentries;"
   //           << "x0;"
   //           << "sigma_x0;"
   //           << "m;"
   //           << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_a_0p_stgc2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_5p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_10p_stgc2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_10p_stgc2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_15p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_20p_stgc2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_20p_stgc2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_25p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_30p_stgc2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_30p_stgc2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_35p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_40p_stgc2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_40p_stgc2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_45p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;

   //    name = "sagittas_a_sector" + std::to_string(i+1) + "_50p_stgc2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_a_50p_stgc2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc2_a << f << std::endl;



   //    ////////c-side
   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_0p_stgc2_t_improved_hist";
   //    std::ofstream myfile_stgc2_c;
   //    myfile_stgc2_c.open("csv/sagittas_c_sector_" + std::to_string(i+1) + "_stgc2_t" + std::to_string(twr+1) + "_hist.csv");
   //    myfile_stgc2_c << "Nentries;"
   //             << "x0;"
   //             << "sigma_x0;"
   //             << "m;"
   //             << "sigma_m;" << std::endl;

   //    f = plotter->CreateSagPlot(name, sagittas_c_0p_stgc2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_5p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_5p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_10p_stgc2_t_improved_hist";

   //    f = plotter->CreateSagPlot(name, sagittas_c_10p_stgc2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_15p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_15p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_20p_stgc2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_20p_stgc2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_25p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_25p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_30p_stgc2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_30p_stgc2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_35p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_35p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_40p_stgc2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_40p_stgc2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_45p_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_45p_hist.at(i).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    name = "sagittas_c_sector" + std::to_string(i+1) + "_50p_stgc2_t_improved_hist";
   //    f = plotter->CreateSagPlot(name, sagittas_c_50p_stgc2_t_improved_hist.at(i+twr*16).get(), outputdir);
   //    myfile_stgc2_c << f << std::endl;

   //    myfile_stgc2_a.close();
   //    myfile_stgc2_c.close();

   //    outputdir="Plots/";
   //  }
   // }
   
   std::cout << "finished plotting" << std::endl;
}

void tree::ReadHistsFromFile()
{

   std::cout << "reading hists" << std::endl;

   std::unique_ptr<TFile> myFile(TFile::Open("Loop_out/tree_out.root"));

   // seg1_xy_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1_xy_aside_hist"));
   // seg1_xy_aside_hist->SetDirectory(nullptr);

   // seg2_xy_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg2_xy_aside_hist"));
   // seg2_xy_aside_hist->SetDirectory(nullptr);

   // seg3_xy_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg3_xy_aside_hist"));
   // seg3_xy_aside_hist->SetDirectory(nullptr);

   // seg1x_seg2x_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1x_seg2x_aside_hist"));
   // seg1x_seg2x_aside_hist->SetDirectory(nullptr);

   // seg1x_seg3x_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1x_seg3x_aside_hist"));
   // seg1x_seg3x_aside_hist->SetDirectory(nullptr);

   // seg2x_seg3x_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg2x_seg3x_aside_hist"));
   // seg2x_seg3x_aside_hist->SetDirectory(nullptr);

   // seg1y_seg2y_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1y_seg2y_aside_hist"));
   // seg1y_seg2y_aside_hist->SetDirectory(nullptr);

   // seg1y_seg3y_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1y_seg3y_aside_hist"));
   // seg1y_seg3y_aside_hist->SetDirectory(nullptr);

   // seg2y_seg3y_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg2y_seg3y_aside_hist"));
   // seg2y_seg3y_aside_hist->SetDirectory(nullptr);

   // seg1z_seg2z_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1z_seg2z_aside_hist"));
   // seg1z_seg2z_aside_hist->SetDirectory(nullptr);

   // seg1z_seg3z_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1z_seg3z_aside_hist"));
   // seg1z_seg3z_aside_hist->SetDirectory(nullptr);

   // seg2z_seg3z_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg2z_seg3z_aside_hist"));
   // seg2z_seg3z_aside_hist->SetDirectory(nullptr);

   // seg1_xy_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1_xy_cside_hist"));
   // seg1_xy_cside_hist->SetDirectory(nullptr);

   // seg2_xy_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg2_xy_cside_hist"));
   // seg2_xy_cside_hist->SetDirectory(nullptr);

   // seg3_xy_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg3_xy_cside_hist"));
   // seg3_xy_cside_hist->SetDirectory(nullptr);

   // seg1x_seg2x_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1x_seg2x_cside_hist"));
   // seg1x_seg2x_cside_hist->SetDirectory(nullptr);

   // seg1x_seg3x_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1x_seg3x_cside_hist"));
   // seg1x_seg3x_cside_hist->SetDirectory(nullptr);

   // seg2x_seg3x_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg2x_seg3x_cside_hist"));
   // seg2x_seg3x_cside_hist->SetDirectory(nullptr);

   // seg1y_seg2y_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1y_seg2y_cside_hist"));
   // seg1y_seg2y_cside_hist->SetDirectory(nullptr);

   // seg1y_seg3y_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1y_seg2y_cside_hist"));
   // seg1y_seg3y_cside_hist->SetDirectory(nullptr);

   // seg2y_seg3y_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg2y_seg3y_cside_hist"));
   // seg2y_seg3y_cside_hist->SetDirectory(nullptr);

   // seg1z_seg2z_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1z_seg2z_cside_hist"));
   // seg1z_seg2z_cside_hist->SetDirectory(nullptr);

   // seg1z_seg3z_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1z_seg3z_cside_hist"));
   // seg1z_seg3z_cside_hist->SetDirectory(nullptr);

   // seg2z_seg3z_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg2z_seg3z_cside_hist"));
   // seg2z_seg3z_cside_hist->SetDirectory(nullptr);

   // std::cout << "block 1" << std::endl;

   // seg1_eta_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1_eta_hist"));
   // seg1_eta_hist->SetDirectory(nullptr);

   // seg2_eta_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg2_eta_hist"));
   // seg2_eta_hist->SetDirectory(nullptr);

   // seg3_eta_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg3_eta_hist"));
   // seg3_eta_hist->SetDirectory(nullptr);

   // seg1_phi_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1_phi_hist"));
   // seg1_phi_hist->SetDirectory(nullptr);

   // seg2_phi_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg2_phi_hist"));
   // seg2_phi_hist->SetDirectory(nullptr);

   // seg3_phi_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg3_phi_hist"));
   // seg3_phi_hist->SetDirectory(nullptr);

   // seg1_seg2_eta_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1_seg2_eta_hist"));
   // seg1_seg2_eta_hist->SetDirectory(nullptr);

   // seg1_seg3_eta_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1_seg3_eta_hist"));
   // seg1_seg3_eta_hist->SetDirectory(nullptr);

   // seg2_seg3_eta_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg2_seg3_eta_hist"));
   // seg2_seg3_eta_hist->SetDirectory(nullptr);

   // seg1_seg2_phi_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1_seg2_phi_hist"));
   // seg1_seg2_phi_hist->SetDirectory(nullptr);

   // seg1_seg3_phi_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg1_seg3_phi_hist"));
   // seg1_seg3_phi_hist->SetDirectory(nullptr);

   // seg2_seg3_phi_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("seg2_seg3_phi_hist"));
   // seg2_seg3_phi_hist->SetDirectory(nullptr);

   // sagitta_0p_hist = std::unique_ptr<TH1F>(myFile->Get<TH1F>("sagitta_0p_hist"));
   // sagitta_0p_hist->SetDirectory(nullptr);

   // sagitta_10p_hist = std::unique_ptr<TH1F>(myFile->Get<TH1F>("sagitta_10p_hist"));
   // sagitta_10p_hist->SetDirectory(nullptr);

   // sagitta_15p_hist = std::unique_ptr<TH1F>(myFile->Get<TH1F>("sagitta_15p_hist"));
   // sagitta_15p_hist->SetDirectory(nullptr);

   // sagitta_20p_hist = std::unique_ptr<TH1F>(myFile->Get<TH1F>("sagitta_20p_hist"));
   // sagitta_20p_hist->SetDirectory(nullptr);

   // sagitta_30p_hist = std::unique_ptr<TH1F>(myFile->Get<TH1F>("sagitta_30p_hist"));
   // sagitta_30p_hist->SetDirectory(nullptr);

   // sagitta_50p_hist = std::unique_ptr<TH1F>(myFile->Get<TH1F>("sagitta_50p_hist"));
   // sagitta_50p_hist->SetDirectory(nullptr);


   // std::cout << "block 2" << std::endl;

   // sagitta_2nd_coord_0p_hist = std::unique_ptr<TH1F>(myFile->Get<TH1F>("sagitta_2nd_coord_0p_hist"));
   // sagitta_2nd_coord_0p_hist->SetDirectory(nullptr);

   // sagitta_2nd_coord_30p_hist = std::unique_ptr<TH1F>(myFile->Get<TH1F>("sagitta_2nd_coord_30p_hist"));
   // sagitta_2nd_coord_30p_hist->SetDirectory(nullptr);


   muon_p_hist = std::unique_ptr<TH1F>(myFile->Get<TH1F>("muon_p_hist"));
   muon_p_hist->SetDirectory(nullptr);
   muon_p_selection_hist = std::unique_ptr<TH1F>(myFile->Get<TH1F>("muon_p_selection_hist"));
   muon_p_selection_hist->SetDirectory(nullptr);

   muon_pT_hist = std::unique_ptr<TH1F>(myFile->Get<TH1F>("muon_pT_hist"));
   muon_pT_hist->SetDirectory(nullptr);
   muon_pT_selection_hist = std::unique_ptr<TH1F>(myFile->Get<TH1F>("muon_pT_selection_hist"));
   muon_pT_selection_hist->SetDirectory(nullptr);

   // std::cout << "block 2 a" << std::endl;

   // mm1_xy_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("mm1_xy_aside_hist"));
   // mm1_xy_aside_hist->SetDirectory(nullptr);
   // mm2_xy_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("mm2_xy_aside_hist"));
   // mm2_xy_aside_hist->SetDirectory(nullptr);
   // stgc1_xy_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("stgc1_xy_aside_hist"));
   // stgc1_xy_aside_hist->SetDirectory(nullptr);
   // stgc2_xy_aside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("stgc2_xy_aside_hist"));
   // stgc2_xy_aside_hist->SetDirectory(nullptr);

   // std::cout << "block 2 b" << std::endl;

   // mm1_xy_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("mm1_xy_cside_hist"));
   // mm1_xy_cside_hist->SetDirectory(nullptr);
   // mm2_xy_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("mm2_xy_cside_hist"));
   // mm2_xy_cside_hist->SetDirectory(nullptr);
   // stgc1_xy_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("stgc1_xy_cside_hist"));
   // stgc1_xy_cside_hist->SetDirectory(nullptr);
   // stgc2_xy_cside_hist = std::unique_ptr<TH2F>(myFile->Get<TH2F>("stgc2_xy_cside_hist"));
   // stgc2_xy_cside_hist->SetDirectory(nullptr);
   
   // std::cout << "block 3" << std::endl;
   
   // sagittas_a_0p_hist.reserve(16);
   // sagittas_a_5p_hist.reserve(16);
   // sagittas_a_10p_hist.reserve(16);
   // sagittas_a_15p_hist.reserve(16);
   // sagittas_a_20p_hist.reserve(16);
   // sagittas_a_25p_hist.reserve(16);
   // sagittas_a_30p_hist.reserve(16);
   // sagittas_a_35p_hist.reserve(16);
   // sagittas_a_40p_hist.reserve(16);
   // sagittas_a_45p_hist.reserve(16);
   // sagittas_a_50p_hist.reserve(16);

   // sagittas_c_0p_hist.reserve(16);
   // sagittas_c_5p_hist.reserve(16);
   // sagittas_c_10p_hist.reserve(16);
   // sagittas_c_15p_hist.reserve(16);
   // sagittas_c_20p_hist.reserve(16);
   // sagittas_c_25p_hist.reserve(16);
   // sagittas_c_30p_hist.reserve(16);
   // sagittas_c_35p_hist.reserve(16);
   // sagittas_c_40p_hist.reserve(16);
   // sagittas_c_45p_hist.reserve(16);
   // sagittas_c_50p_hist.reserve(16);

   // sagittas_a_0p_improved_hist.reserve(16);
   // sagittas_a_5p_improved_hist.reserve(16);
   // sagittas_a_10p_improved_hist.reserve(16);
   // sagittas_a_15p_improved_hist.reserve(16);
   // sagittas_a_20p_improved_hist.reserve(16);
   // sagittas_a_25p_improved_hist.reserve(16);
   // sagittas_a_30p_improved_hist.reserve(16);
   // sagittas_a_35p_improved_hist.reserve(16);
   // sagittas_a_40p_improved_hist.reserve(16);
   // sagittas_a_45p_improved_hist.reserve(16);
   // sagittas_a_50p_improved_hist.reserve(16);
   // sagittas_a_100p_improved_hist.reserve(16);
   // sagittas_a_200p_improved_hist.reserve(16);
   // sagittas_a_300p_improved_hist.reserve(16);

   // sagittas_a_0p_mm1_improved_hist.reserve(16);
   // sagittas_a_10p_mm1_improved_hist.reserve(16);
   // sagittas_a_20p_mm1_improved_hist.reserve(16);
   // sagittas_a_30p_mm1_improved_hist.reserve(16);
   // sagittas_a_40p_mm1_improved_hist.reserve(16);
   // sagittas_a_50p_mm1_improved_hist.reserve(16);
   // sagittas_a_100p_mm1_improved_hist.reserve(16);

   // sagittas_a_0p_mm2_improved_hist.reserve(16);
   // sagittas_a_10p_mm2_improved_hist.reserve(16);
   // sagittas_a_20p_mm2_improved_hist.reserve(16);
   // sagittas_a_30p_mm2_improved_hist.reserve(16);
   // sagittas_a_40p_mm2_improved_hist.reserve(16);
   // sagittas_a_50p_mm2_improved_hist.reserve(16);
   // sagittas_a_100p_mm2_improved_hist.reserve(16);

   // sagittas_a_0p_stgc1_improved_hist.reserve(16);
   // sagittas_a_10p_stgc1_improved_hist.reserve(16);
   // sagittas_a_20p_stgc1_improved_hist.reserve(16);
   // sagittas_a_30p_stgc1_improved_hist.reserve(16);
   // sagittas_a_40p_stgc1_improved_hist.reserve(16);
   // sagittas_a_50p_stgc1_improved_hist.reserve(16);
   // sagittas_a_100p_stgc1_improved_hist.reserve(16);

   // sagittas_a_0p_stgc2_improved_hist.reserve(16);
   // sagittas_a_10p_stgc2_improved_hist.reserve(16);
   // sagittas_a_20p_stgc2_improved_hist.reserve(16);
   // sagittas_a_30p_stgc2_improved_hist.reserve(16);
   // sagittas_a_40p_stgc2_improved_hist.reserve(16);
   // sagittas_a_50p_stgc2_improved_hist.reserve(16);
   // sagittas_a_100p_stgc2_improved_hist.reserve(16);   

   // sagittas_c_0p_improved_hist.reserve(16);
   // sagittas_c_5p_improved_hist.reserve(16);
   // sagittas_c_10p_improved_hist.reserve(16);
   // sagittas_c_15p_improved_hist.reserve(16);
   // sagittas_c_20p_improved_hist.reserve(16);
   // sagittas_c_25p_improved_hist.reserve(16);
   // sagittas_c_30p_improved_hist.reserve(16);
   // sagittas_c_35p_improved_hist.reserve(16);
   // sagittas_c_40p_improved_hist.reserve(16);
   // sagittas_c_45p_improved_hist.reserve(16);
   // sagittas_c_50p_improved_hist.reserve(16);
   // sagittas_c_100p_improved_hist.reserve(16);
   // sagittas_c_200p_improved_hist.reserve(16);
   // sagittas_c_300p_improved_hist.reserve(16);

   // sagittas_c_0p_mm1_improved_hist.reserve(16);
   // sagittas_c_10p_mm1_improved_hist.reserve(16);
   // sagittas_c_20p_mm1_improved_hist.reserve(16);
   // sagittas_c_30p_mm1_improved_hist.reserve(16);
   // sagittas_c_40p_mm1_improved_hist.reserve(16);
   // sagittas_c_50p_mm1_improved_hist.reserve(16);
   // sagittas_c_100p_mm1_improved_hist.reserve(16);

   // sagittas_c_0p_mm2_improved_hist.reserve(16);
   // sagittas_c_10p_mm2_improved_hist.reserve(16);
   // sagittas_c_20p_mm2_improved_hist.reserve(16);
   // sagittas_c_30p_mm2_improved_hist.reserve(16);
   // sagittas_c_40p_mm2_improved_hist.reserve(16);
   // sagittas_c_50p_mm2_improved_hist.reserve(16);
   // sagittas_c_100p_mm2_improved_hist.reserve(16);

   // sagittas_c_0p_stgc1_improved_hist.reserve(16);
   // sagittas_c_10p_stgc1_improved_hist.reserve(16);
   // sagittas_c_20p_stgc1_improved_hist.reserve(16);
   // sagittas_c_30p_stgc1_improved_hist.reserve(16);
   // sagittas_c_40p_stgc1_improved_hist.reserve(16);
   // sagittas_c_50p_stgc1_improved_hist.reserve(16);
   // sagittas_c_100p_stgc1_improved_hist.reserve(16);

   // sagittas_c_0p_stgc2_improved_hist.reserve(16);
   // sagittas_c_10p_stgc2_improved_hist.reserve(16);
   // sagittas_c_20p_stgc2_improved_hist.reserve(16);
   // sagittas_c_30p_stgc2_improved_hist.reserve(16);
   // sagittas_c_40p_stgc2_improved_hist.reserve(16);
   // sagittas_c_50p_stgc2_improved_hist.reserve(16);
   // sagittas_c_100p_stgc2_improved_hist.reserve(16);   


   // sagitta_a_2nd_coord_0p_hist.reserve(16);
   // sagitta_a_2nd_coord_30p_hist.reserve(16);
   // sagitta_c_2nd_coord_0p_hist.reserve(16);
   // sagitta_c_2nd_coord_30p_hist.reserve(16);

   // sagitta_a_2nd_coord_0p_improved_hist.reserve(16);
   // sagitta_a_2nd_coord_30p_improved_hist.reserve(16);
   // sagitta_c_2nd_coord_0p_improved_hist.reserve(16);
   // sagitta_c_2nd_coord_30p_improved_hist.reserve(16);


   // sagitta_a_t223_30p_hist.reserve(16);
   

   for (int i = 0; i < 16; ++i)
   {
      std::cout << i << std::endl;

      std::string name;

      // name = "sagitta_0p_hist_sec" + std::to_string(i+1);
      // sagittas_a_0p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_0p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_5p_hist_sec" + std::to_string(i+1);
      // sagittas_a_5p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_5p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_10p_hist_sec" + std::to_string(i+1);
      // sagittas_a_10p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_10p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_15p_hist_sec" + std::to_string(i+1);
      // sagittas_a_15p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_15p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_20p_hist_sec" + std::to_string(i+1);
      // sagittas_a_20p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_20p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_25p_hist_sec" + std::to_string(i+1);
      // sagittas_a_25p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_25p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_30p_hist_sec" + std::to_string(i+1);
      // sagittas_a_30p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_30p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_35p_hist_sec" + std::to_string(i+1);
      // sagittas_a_35p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_35p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_40p_hist_sec" + std::to_string(i+1);
      // sagittas_a_40p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_40p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_45p_hist_sec" + std::to_string(i+1);
      // sagittas_a_45p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_45p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_50p_hist_sec" + std::to_string(i+1);
      // sagittas_a_50p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_50p_hist.at(i)->SetDirectory(nullptr);

      // std::cout << "c-side" << std::endl;

      // name = "sagitta_0p_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_0p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_0p_hist.at(i)->SetDirectory(nullptr);

      // std::cout << "first" << std::endl;

      // name = "sagitta_5p_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_5p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_5p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_10p_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_10p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_10p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_15p_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_15p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_15p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_20p_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_20p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_20p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_25p_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_25p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_25p_hist.at(i)->SetDirectory(nullptr);

      // std::cout << "25" << std::endl;

      // name = "sagitta_30p_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_30p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_30p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_35p_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_35p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_35p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_40p_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_40p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_40p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_45p_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_45p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_45p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_50p_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_50p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_50p_hist.at(i)->SetDirectory(nullptr);



      // // 'improved' second coordinate hists

      // // bayley : these don't work because they dont include the "side suffix" to retrieve the hists

      // name = "sagitta_0p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_a_0p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_0p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_5p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_a_5p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_5p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_10p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_a_10p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_10p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_15p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_a_15p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_15p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_20p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_a_20p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_20p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_25p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_a_25p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_25p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_30p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_a_30p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_30p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_35p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_a_35p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_35p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_40p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_a_40p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_40p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_45p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_a_45p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_45p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_50p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_a_50p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_50p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_100p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_a_100p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_100p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_200p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_a_200p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_200p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_300p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_a_300p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_a_300p_improved_hist.at(i)->SetDirectory(nullptr);



      // // name = "sagitta_30p_improved_hist_sec" + std::to_string(i+1);
      // // sagittas_a_30p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // // sagittas_a_30p_improved_hist.at(i)->SetDirectory(nullptr);

      // // name = "sagitta_30p_improved_hist_sec" + std::to_string(i+1);
      // // sagittas_a_30p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // // sagittas_a_30p_improved_hist.at(i)->SetDirectory(nullptr);

      // // name = "sagitta_30p_improved_hist_sec" + std::to_string(i+1);
      // // sagittas_a_30p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // // sagittas_a_30p_improved_hist.at(i)->SetDirectory(nullptr);

      // std::cout << "c-side" << std::endl;

      // name = "sagitta_0p_improved_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_0p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_0p_improved_hist.at(i)->SetDirectory(nullptr);

      // std::cout << "first" << std::endl;

      // name = "sagitta_5p_improved_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_5p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_5p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_10p_improved_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_10p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_10p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_15p_improved_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_15p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_15p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_20p_improved_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_20p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_20p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_25p_improved_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_25p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_25p_improved_hist.at(i)->SetDirectory(nullptr);

      // std::cout << "25" << std::endl;

      // name = "sagitta_30p_improved_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_30p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_30p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_35p_improved_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_35p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_35p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_40p_improved_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_40p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_40p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_45p_improved_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_45p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_45p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_50p_improved_hist_sec" + std::to_string(i+1) + "_c";
      // sagittas_c_50p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_50p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_30p_improved_hist_sec" + std::to_string(i+1) + "_a_t223";
      // sagitta_a_t223_30p_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagitta_a_t223_30p_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_100p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_c_100p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_100p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_200p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_c_200p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_200p_improved_hist.at(i)->SetDirectory(nullptr);

      // name = "sagitta_300p_improved_hist_sec" + std::to_string(i+1);
      // sagittas_c_300p_improved_hist.emplace_back(std::unique_ptr<TH1F>(myFile->Get<TH1F>(name.c_str())));
      // sagittas_c_300p_improved_hist.at(i)->SetDirectory(nullptr);
   }

   std::cout << "finished reading hists" << std::endl;
};
