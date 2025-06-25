// combining.cc
// Purpose: to take all the toroid-off individual histograms and make one big file with histograms
#include <dirent.h>


void combining(){
  TFile *outFile = TFile::Open("run-data.root", "recreate");

  const char *directory[3] = {"/afs/cern.ch/user/a/atimoney/private/toroid-off-analysis-plots/mtree_out/4510137", 
                        "/afs/cern.ch/user/a/atimoney/private/toroid-off-analysis-plots/mtree_out/4510146", 
                        "/afs/cern.ch/user/a/atimoney/private/toroid-off-analysis-plots/mtree_out/4510163"};
  string run[3] = {"4510137/", "4510146/", "4510163/"};

  TH1F *muon_pT = new TH1F("muon_pT", "muon_pT", 120, 0, 120000);
  TH1F *muon_P = new TH1F("muon_P", "muon_P", 120, 0, 120000);

  for(int i = 0; i < 3; i++) {
    std::vector<string> samples;
    DIR *dir_ptr;
    struct dirent *diread;
    if ((dir_ptr = opendir(directory[i])) != nullptr) {
      while ((diread = readdir(dir_ptr)) != nullptr) {
            string sample = diread->d_name;
            if (sample.find(".root") != string::npos){
                samples.push_back(sample);
            }
        }
        closedir(dir_ptr);
      }

    for(int j = 0; j < samples.size(); j++) {
      string path = run[i] + samples[j];
      TFile inf = path.c_str();
      TH1F *temp_pT = (TH1F*)inf.Get("muon_pt_mu5_hist");
      TH1F *temp_P = (TH1F*)inf.Get("muon_p_HLT5_hist");

      muon_pT->Add(temp_pT);
      muon_P->Add(temp_P);
    }
  }
  
  outFile->cd();

  muon_pT->Rebin(2);
  // muon_P->Rebin(2);

  muon_pT->Write("muon_pT");
  muon_P->Write("muon_P_bin1");

  muon_P->Rebin(2);
  muon_P->Write("muon_P");

  outFile->Close();
}

