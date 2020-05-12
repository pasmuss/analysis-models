#include "Analysis/Models/interface/RooGaussianErf.h"

using namespace analysis::models;

ClassImp(RooGaussianErf)

RooGaussianErf::RooGaussianErf(const char *name, const char *title,
			       RooAbsReal& x,
			       RooAbsReal& scale,
			       RooAbsReal& offset,
			       RooAbsReal& slope):
RooAbsPdf(name, title),
  x_("x", "x", this, x),
  scale_("scale", "scale", this, scale),
  offset_("offset", "offset", this, offset),
  slope_("slope", "slope", this, slope) {
}

RooGaussianErf::RooGaussianErf(const RooGaussianErf& other, const char* newname) :
  RooAbsPdf(other, newname),
  x_("x", this, other.x_),
  scale_("scale", this, other.scale_),
  offset_("offset", this, other.offset_),
  slope_("slope", this, other.slope_) {
}

TObject* RooGaussianErf::clone(const char* newname) const {
  return new RooGaussianErf(*this, newname);
}

double RooGaussianErf::evaluate() const {

  double arg = slope_ * (x_ - offset_);
  double res = scale_ * TMath::Erf(arg);

  return res;

}
