/*
 * JetAnalysisBase.h
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: rostyslav
 */

#ifndef ANALYSIS_MSSMHBB_SRC_JETANALYSISBASE_H_
#define ANALYSIS_MSSMHBB_SRC_JETANALYSISBASE_H_

#include "TFile.h"
#include "TH1.h"
#include "TH1D.h"
#include "TH2.h"
#include "TH2D.h"

// system include files
#include <memory>
#include <vector>
#include <string>
#include <type_traits>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/algorithm/string/join.hpp>
#include "TSystem.h"
//
// user include files

#include "Analysis/Tools/interface/Analysis.h"
#include "Analysis/Tools/interface/Collection.h"
#include "Analysis/Tools/interface/Jet.h"

#include "Analysis/MssmHbb/interface/Weights.h"
#include "Analysis/MssmHbb/interface/Histograms.h"
#include "Analysis/MssmHbb/interface/BTagCalibrationStandalone.h"


//TODO: Add template arguments to unique_ptr depending on the TH type
typedef std::unique_ptr<TH1D> pTH1D;
typedef std::unique_ptr<TH2D> pTH2D;
typedef std::unique_ptr<TFile> pTFile;
typedef std::unique_ptr<BTagCalibrationReader> pSFReader;

namespace analysis{
	namespace mssmhbb{
	class JetAnalysisBase : public analysis::tools::Analysis {
	public:

		//Default constructor
		JetAnalysisBase(const std::string & inputFilelist, const std::string & evtinfo = "MssmHbb/Events/EventInfo",const bool & lowM = true);
		virtual ~JetAnalysisBase();

        //Add trigger Object Trees
        void addTriggerObjects(const std::vector<std::string> & triggerObjectName = {"hltL1sL1DoubleJetC100",
                   																	"hltDoubleJetsC100",
                   																	"hltDoublePFJetsC100",
                   																	"hltDoubleBTagCSV0p9",
                   																	"hltDoublePFJetsC100MaxDeta1p6"},
     		   	   	   	   	  const std::string & path = "MssmHbb/Events/selectedPatTrigger/");

        void loadCorrections();
        void applySelection();
        void setupAnalysis(const std::string & json);
        virtual void makeHistograms(const int &size = 100);

        struct ScaleFactor{
        	ScaleFactor() : central(0), up(0), down (0) {};
        	ScaleFactor(const double & centr, const double & upper, const double & lower) :
        		central(centr),
        		up(upper),
        		down(lower) {};
        	~ScaleFactor(){};
        	double central;
        	double up;
        	double down;
        };

	protected:

        std::unique_ptr<Weights> pWeight_;
        bool lowM_;
        std::string triggerLogicName_;
        int nJets_;
        Histograms histo_;

        //Protected members
        std::vector<std::string> getTriggerObjectNames();
        virtual bool leadingJetSelection(const int & iJet, const tools::Jet & Jet);
        //Scale Factors calculation
        const ScaleFactor calculateBTagSF(const tools::Jet & Jet, const bool & thirdJ);
        //Trigger Selection
        virtual bool OnlineSelection(const analysis::tools::Jet &fLeadOfflineJet,const analysis::tools::Jet &sLeadOfflineJet);



	private:

        std::map<std::string, double > weight_;
        std::vector<std::string> triggerObjectName_;
        std::map<std::string,pTFile> fCorrections_;
        std::map<std::string,pTH1D>  hCorrections1D_;
        std::map<std::string,pTH2D>  hCorrections2D_;
        std::map<std::string,pSFReader > SFb_;
        std::unique_ptr<BTagCalibration> BTagCalibrationLib_;

        const double pt1_ = 80.;
        const double pt3_ = 30.;
        const double eta1_ = 2.4;
        const double dEta_ = 100.;
        const double dR_ = 1.;

	};

	inline std::vector<std::string> JetAnalysisBase::getTriggerObjectNames() {return triggerObjectName_;}

	}
}



#endif /* ANALYSIS_MSSMHBB_SRC_JETANALYSISBASE_H_ */
