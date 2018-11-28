/*
 * RooFitQuality.h
 *
 *  Created on: 20 Apr 2017
 *      Author: shevchen
 */

#ifndef Analysis_Models_2016_RooFitQuality_h
#define Analysis_Models_2016_RooFitQuality_h

#include <utility>

#include "TMath.h"

#include "RooPlot.h"
#include "RooFitResult.h"

//User libs
#include "Analysis/Models/interface/RooFitUtils.h"

namespace analysis {
namespace backgroundmodel {

class Chi2Ndf{
public:
	Chi2Ndf(const double& chi2, const double& ndf) : chi2(chi2), ndf(ndf) {};
	Chi2Ndf() : chi2(0), ndf(0) {};
	double chi2;
	int ndf;
	double GetPValue(){return TMath::Prob(chi2,ndf);}
	void Print(){std::cout<<"chi2/ndf = "<<chi2<<"/"<<ndf<<" = "<<chi2/ndf<<"\n p = "<<GetPValue()<<std::endl;}
};

class RooFitQuality {
public:
	RooFitQuality() = default;
	virtual ~RooFitQuality() = default;

	Chi2Ndf chiSquare(RooPlot& frame,const std::string& curvename, const std::string& histname,const int& nFitParam, const double& blind_lowEdge = 1e+06, const double& blind_highEdge = -1e+06);
	void PrintParametersInfo(const RooFitResult& res);
//	int ndf

private:
	std::pair<double,double> CurveRange(const RooCurve &curve);
};

} /* namespace backgroundmodel */
} /* namespace analysis */

#endif /* Analysis_Models_2016_RooFitQuality_h */
