/*
 * RooBackgroundModel.h
 *
 *  Created on: 20
 */

#ifndef Analysis_Models_RooBackgroundModel_h_
#define Analysis_Models_RooBackgroundModel_h_

#include "Analysis/Models/interface/RooDoubleCB.h"
#include "Analysis/Models/interface/RooExpGausExp.h"
#include "Analysis/Models/interface/RooGausExp.h"
#include "Analysis/Models/interface/RooExpBWExp.h"
#include "Analysis/Models/interface/RooPhaseSpace.h"
#include "Analysis/Models/interface/RooPhaseSpacePol4.h"
#include "Analysis/Models/interface/RooRelBreitWigner.h"
#include "Analysis/Models/interface/RooQuadGausExp.h"
#include "Analysis/Models/interface/RooMyNovosibirsk.h"
#include "Analysis/Models/interface/RooExtendNovosibirsk.h"
#include "Analysis/Models/interface/RooDoubleGausExp.h"
#include "Analysis/Models/interface/RooSuperNovosibirsk.h"
#include "Analysis/Models/interface/RooPolyDijet.h"
#include "Analysis/Models/interface/RooSuperDiJet.h"

namespace analysis {
namespace backgroundmodel {

   class RooDoubleCB          : public analysis::models::RooDoubleCB          {
      private:
            ClassDef(RooDoubleCB         ,1)
      };
   class RooExpGausExp        : public analysis::models::RooExpGausExp        {
      private:
            ClassDef(RooExpGausExp         ,1)
      };
   class RooGausExp           : public analysis::models::RooGausExp           {
      private:
            ClassDef(RooGausExp         ,1)
      };
   class RooExpBWExp          : public analysis::models::RooExpBWExp          {
      private:
            ClassDef(RooExpBWExp         ,1)
      };
   class RooPhaseSpace        : public analysis::models::RooPhaseSpace        {
      private:
            ClassDef(RooPhaseSpace         ,1)
      };
   class RooPhaseSpacePol4    : public analysis::models::RooPhaseSpacePol4    {
      private:
            ClassDef(RooPhaseSpacePol4         ,1)
      };
   class RooRelBreitWigner    : public analysis::models::RooRelBreitWigner    {
      private:
            ClassDef(RooRelBreitWigner         ,1)
      };
   class RooQuadGausExp       : public analysis::models::RooQuadGausExp       {
      private:
            ClassDef(RooQuadGausExp         ,1)
      };
   class RooMyNovosibirsk     : public analysis::models::RooMyNovosibirsk     {
      private:
            ClassDef(RooMyNovosibirsk         ,1)
      };
   class RooExtendNovosibirsk : public analysis::models::RooExtendNovosibirsk {
      private:
            ClassDef(RooExtendNovosibirsk         ,1)
      };
   class RooDoubleGausExp     : public analysis::models::RooDoubleGausExp     {
      private:
            ClassDef(RooDoubleGausExp         ,1)
      };
   class RooSuperNovosibirsk  : public analysis::models::RooSuperNovosibirsk  {
      private:
            ClassDef(RooSuperNovosibirsk         ,1)
      };
   class RooPolyDijet         : public analysis::models::RooPolyDijet         {
      private:
            ClassDef(RooPolyDijet         ,1)
      };
   class RooSuperDiJet        : public analysis::models::RooSuperDiJet        {
      private:
            ClassDef(RooSuperDiJet         ,1)
      };
   
   

} /* namespace backgroundmodel */
} /* namespace analysis */

#endif /* Analysis_Models_RooBackgroundModel_h_ */
