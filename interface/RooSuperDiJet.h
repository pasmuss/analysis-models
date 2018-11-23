/*
 * RooSuperDiJet.h
 *
 *  Created on: 20 апр. 2017 г.
 *      Author: rostyslav
 */

#ifndef Analysis_Models_RooSuperDijet_h_
#define Analysis_Models_RooSuperDijet_h_

#include "RooAbsPdf.h"
#include "RooAbsArg.h"
#include "RooRealProxy.h"
#include "RooAbsReal.h"
#include "RooListProxy.h"
#include <string>
#include "TMath.h"

namespace analysis {
namespace models {

class RooSuperDiJet : public RooAbsPdf {
public:
	inline RooSuperDiJet() = default;
	RooSuperDiJet(const char *name, const char *title,
            RooAbsReal& x,
            RooAbsReal& mean,
            RooAbsReal& para,
            RooAbsReal& parb,
			const RooArgList& coefList);
	RooSuperDiJet(const RooSuperDiJet& other, const char* name=0) ;
	virtual TObject* clone(const char* newname) const;
	inline virtual ~RooSuperDiJet() = default;

protected:
	double evaluate() const;

    RooRealProxy x_ ;
    RooRealProxy mean_ ;
    RooRealProxy para_ ;
    RooRealProxy parb_ ;
    RooListProxy coefList_;

private:
    ClassDef(RooSuperDiJet,1)
};

} /* namespace models */
} /* namespace analysis */

#endif /* Analysis_Models_RooSuperDijet_h_ */
