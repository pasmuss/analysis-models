#ifndef Analysis_Models_RooGaussianErf_h_
#define Analysis_Models_RooGaussianErf_h_ 1

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooAbsReal.h"
#include "RooListProxy.h"
#include <string>
#include "TMath.h"

namespace analysis {
  namespace models {
    class RooGaussianErf: public RooAbsPdf {
    public:
      inline RooGaussianErf() = default;
      RooGaussianErf(const char *name, const char *title,
		     RooAbsReal& x,
		     RooAbsReal& scale,
		     RooAbsReal& offset,
		     RooAbsReal& slope);
      RooGaussianErf(const RooGaussianErf& other, const char* name=0) ;
      virtual TObject* clone(const char* newname) const;
      inline virtual ~RooGaussianErf() = default;

    protected:
      double evaluate() const;

      RooRealProxy x_ ;
      RooRealProxy scale_ ;
      RooRealProxy offset_ ;
      RooRealProxy slope_ ;

    private:
      ClassDef(RooGaussianErf,1)
	};

  } /* namespace models */
} /* namespace analysis */

#endif /* Analysis_Models_RooGaussianErf_h_ */
