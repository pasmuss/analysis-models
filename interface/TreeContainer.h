#ifndef Analysis_Models_TreeContainer_h
#define Analysis_Models_TreeContainer_h 1

#include <string>
#include <vector>
#include <memory>
#include "TTree.h"


namespace analysis {
  namespace models {

    class TreeContainer {
    public:
      TreeContainer(const std::string& input);
      TreeContainer(const std::string&, const std::string&, const std::string&, const std::string&);
      virtual ~TreeContainer();

      std::unique_ptr<TTree> data() const;
      void show() const;
      
      void treeName(const std::string& );
      void dataLeaf(const std::string& );
      void weightLeaf(const std::string& );
      
      std::string treeName() const;
      std::string dataLeaf() const;
      std::string weightLeaf() const;


    private:
      std::unique_ptr<TTree> getTree_(const std::string& name) const;
      static std::unique_ptr<TTree> uniqueClone_(const TTree& original);

      std::string treeFileName_;
      std::string treename_;
      std::string dataleaf_;
      std::string weightleaf_;
      std::unique_ptr<TTree> data_;
      
    };
    
    /// Sets
    inline void TreeContainer::treeName  (const std::string& name)   { treename_   = name;   }
    inline void TreeContainer::dataLeaf  (const std::string& data)   { dataleaf_   = data;   }
    inline void TreeContainer::weightLeaf(const std::string& weight) { weightleaf_ = weight; }
    
    inline std::string TreeContainer::treeName  () const { return treename_;   }
    inline std::string TreeContainer::dataLeaf  () const { return dataleaf_;   }
    inline std::string TreeContainer::weightLeaf() const { return weightleaf_; }
    

  }
}

#endif  // Analysis_Models_TreeContainer_h
