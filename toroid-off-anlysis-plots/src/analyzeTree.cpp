#include "../TreeAnalyzers/tree.h"

#include "TChain.h"
#include "TFile.h"
#include "TKey.h"

#include <iostream>

int main(int argc, char **argv)
{
  // create an instance of the TChain class
  std::vector<std::string> inputFiles = {};
  const std::string treeName = "tree";
  // const std::string streeName = "stree";

  std::unique_ptr<TChain> treechain;
  treechain = std::make_unique<TChain>("tree");
  // std::unique_ptr<TChain> streechain;
  // streechain = std::make_unique<TChain>("tree");

  std::string steps = argv[1];
  std::unique_ptr<tree> m_data;

  bool create = (steps.find("c") != std::string::npos);
  bool plot   = (steps.find("p") != std::string::npos);

  // loop through the input files and add them to the chain
  for (int i = 2; i < argc; i++)
    {
      inputFiles.push_back(argv[i]);
      treechain->Add(argv[i]);

    }
  m_data = std::make_unique<tree>(treechain.get());
  

  if (create) {
    m_data->Initialize();
    m_data->Loop();
    m_data->WriteHistsToFile();
  }
  if (plot) {
    if (!create) {
      m_data->ReadHistsFromFile();
    }
    m_data->Plot();
  }

  return 0;
}
