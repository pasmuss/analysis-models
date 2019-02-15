#include "TFile.h"
#include "TROOT.h"
#include "Analysis/Models/interface/TreeContainer.h"
#include "Analysis/Models/interface/Tools.h"


using namespace analysis::models;


TreeContainer::TreeContainer(const std::string& input) :
   treeFileName_(input),
   treename_("MssmHbb"),
   dataleaf_("mbb"),
   weightleaf_("weight"),
   data_(getTree_("data"))
{
//    std::string name = "data";  // change this
//    TFile file(treeFileName_.c_str(), "read");
//    TTree & intree = *static_cast<TTree*>(file.Get(treename_.c_str())->Clone(name.c_str()));
//    data_ = std::unique_ptr<TTree>(intree.CloneTree(0));
//    data_->SetDirectory(0);
//    data_->CopyEntries(&intree);
//    file.Close();
//    
}

TreeContainer::TreeContainer(const std::string& input, const std::string& tree, const std::string& data, const std::string& weight) :
   treeFileName_(input),
   treename_(tree),
   dataleaf_(data),
   weightleaf_(weight)
{
   std::string name = "data";  // change this
   TFile file(treeFileName_.c_str(), "read");
   TTree & intree = *static_cast<TTree*>(file.Get(treename_.c_str())->Clone(name.c_str()));
   data_ = std::unique_ptr<TTree>(intree.CloneTree(0));
   data_->SetDirectory(0);
   data_->CopyEntries(&intree);
   file.Close();
   
}



TreeContainer::~TreeContainer() = default;


std::unique_ptr<TTree> TreeContainer::data() const {
  return uniqueClone_(*data_);
}


void TreeContainer::show() const {
  std::cout << "Data events: " << data_->GetEntriesFast() << std::endl;
}


std::unique_ptr<TTree> TreeContainer::getTree_(const std::string& name) const {
  TFile file(treeFileName_.c_str(), "read");
  TTree& input = // FIXME: tree name currently hard-coded
    *static_cast<TTree*>(file.Get("MssmHbb")->Clone(name.c_str()));
  std::unique_ptr<TTree> tree(input.CloneTree(0));
  tree->SetDirectory(0);
  tree->CopyEntries(&input);
  file.Close();
  return tree;
}


std::unique_ptr<TTree> TreeContainer::uniqueClone_(const TTree& original) {
  std::unique_ptr<TTree> clone(static_cast<TTree*>(uniqueClone(&original)));
  if (clone != nullptr) clone->SetDirectory(0);
  return clone;
}
