#include <vector>
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/algorithm/string/join.hpp>
#include "TSystem.h"
#include "TMatrixD.h"
#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"
#include "RooFitResult.h"
#include "Analysis/Models/interface/HistContainer.h"
#include "Analysis/Models/interface/TreeContainer.h"
#include "Analysis/Models/interface/FitContainer.h"
#include "Analysis/Models/interface/ParamModifier.h"
#include "Analysis/Models/interface/Tools.h"
#include "Analysis/Models/interface/ProbabilityDensityFunctions.h"


namespace po = boost::program_options;
namespace ab = analysis::models;

int modelFit(ab::FitContainer&, po::variables_map&);


int main(int argc, char* argv[]) {
   const auto cmsswBase = static_cast<std::string>(gSystem->Getenv("CMSSW_BASE"));
 
 
   // general command line options
   po::options_description cmdLineOptions("Optional arguments");
   cmdLineOptions.add_options()
      ("help,h", "Produce help message.")
      ("verbose,v", po::value<int>()->default_value(0), "More verbose output.")
      ("profile,p", "Create profile likelihoods of the fit parameters.")
      ("list_parameters,l", "List parameters of the chosen fit models and exit.")
      ("input_file,i", po::value<std::string>(),"ROOT file from which input histograms are retrieved.")
      ("input_tree_file,t", po::value<std::string>(), "ROOT file from which input tree is retrieved. If this parameter is not given a binned fit is performed using 'input_file'.")
      ("input_data"  , po::value<std::string>(), "Name of data leaf in the input tree")
      ("input_weight", po::value<std::string>(), "Name of weight leaf in the input tree")
      ("input_tree", po::value<std::string>(), "Name of the input tree")
      ("output_directory,o", po::value<std::string>()->default_value("fitmodel_output/"),"Directory where the output is stored.")
      ("fit_min", po::value<float>(), "Lower bound of the fit range.")
      ("fit_max", po::value<float>(), "Upper bound of the fit range.")
      ("nbins", po::value<int>(), "Number of bins in the fit range.")
      ("weighted", "If events are weighted")
      ("modify_param,m", po::value<std::vector<std::string> >()->composing()->default_value(std::vector<std::string>(), ""),
       "Modify parameters as follows: \"name: [start=<value>,] [min=<value>,] [max=<value>,] [constant,] [floating]\"");
   po::variables_map vm;
   po::store(po::command_line_parser(argc, argv).options(cmdLineOptions).allow_unregistered().run(), vm);
   //po::store(po::command_line_parser( argc, argv ).options(cmdLineOptions).run(), vm);
 
   // now add required options
   po::options_description requiredOptions("Required arguments");
   requiredOptions.add_options()
      ("type"  , po::value<std::string>(), "signal or background")
      ("model", po::value<std::string>()->required(),("Name of the model (" + boost::algorithm::join(ab::ProbabilityDensityFunctions::getAvailableModels(), ", ") + ").").c_str());
   po::store(po::command_line_parser(argc, argv).options(requiredOptions).allow_unregistered().run(), vm);
   
   // now add all options 
   po::options_description allOptions("Allowed arguments");
   allOptions.add(cmdLineOptions).add(requiredOptions);

   // check for help flag before checking for required options
   if (vm.count("help"))
   {
       std::cout << allOptions << std::endl;
       return 0;
   }
   
   // options are notified!
   po::notify(vm);


   // check arguments parsed are valid
   try
   {
      po::notify(vm);
   }
   catch (const po::required_option& ex)
   {
      std::cerr << ex.what() << std::endl;
      return 1;
   }


   // check for required verbosity:
   //
   // ROOT error message levels:
   //    kUnset, kPrint, kInfo, kWarning, kError, kBreak, kSysError, kFatal
   // RooFit error message levels:
   //    DEBUG=0, INFO=1, PROGRESS=2, WARNING=3, ERROR=4, FATAL=5
   auto verbosity = vm["verbose"].as<int>();
   switch (verbosity)
   {
      case 0:
         gErrorIgnoreLevel = kError;
         RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
         break;
      case 1:
         gErrorIgnoreLevel = kInfo;
         RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);
         break;
      case 2:
         RooMsgService::instance().setGlobalKillBelow(RooFit::PROGRESS);
         break;
      case 3:
         gErrorIgnoreLevel = kPrint;
         RooMsgService::instance().setGlobalKillBelow(RooFit::INFO);
         break;
      default:
         if (verbosity < 0)
         {
            gErrorIgnoreLevel = kFatal;
            RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
         }
         else // highest level of verbosity reached
         {  
            gErrorIgnoreLevel = kUnset;
            RooMsgService::instance().setGlobalKillBelow(RooFit::DEBUG);
         }
   }

   std::cout << "Fitting Model " << vm["model"].as<std::string>() << "..." << std::endl;

   if (vm["input_tree_file"].empty())
   {
      // binned fit
      ab::HistContainer input(vm["input_file"].as<std::string>());
      input.show();
      ab::FitContainer fitter(input, vm["output_directory"].as<std::string>());
      fitter.verbosity(verbosity - 1);
      return modelFit(fitter, vm);
   }
   else // unbinned fit
   {  //  #### R.W. It needs to be improved #####
       if (!vm["input_tree"].empty() && !vm["input_data"].empty() && !vm["input_weight"].empty() )
       {
          ab::TreeContainer input(vm["input_tree_file"].as<std::string>(),vm["input_tree"].as<std::string>(),vm["input_data"].as<std::string>(),vm["input_weight"].as<std::string>());
          input.show();
          ab::FitContainer fitter(input, vm["output_directory"].as<std::string>());
          fitter.verbosity(verbosity - 1);
          return modelFit(fitter, vm);
       }        
       else // uses default, namely old hard-coded parameters - to be deprecated!?
       {
          ab::TreeContainer input(vm["input_tree_file"].as<std::string>());
          input.show();
          ab::FitContainer fitter(input, vm["output_directory"].as<std::string>());
          fitter.verbosity(verbosity - 1);
          return modelFit(fitter, vm);
       }
   }
}


int modelFit(ab::FitContainer& fitter, po::variables_map& vm)
{
   // setting limits and parameters for the fit
   if (!vm["fit_min"].empty()) fitter.fitRangeMin(vm["fit_min"].as<float>());
   if (!vm["fit_max"].empty()) fitter.fitRangeMax(vm["fit_max"].as<float>());
   if (!vm["nbins"].empty())   fitter.setNBins(vm["nbins"].as<int>());
   std::vector<ab::ParamModifier> modifiers = ab::parseModifiers(vm["modify_param"].as<std::vector<std::string> >());
   
   ab::FitContainer::Type type = ab::FitContainer::Type::background;
   if ( vm["type"].as<std::string>() == "signal" )
      type = ab::FitContainer::Type::signal;
   else
      type = ab::FitContainer::Type::background;
      
   fitter.setModel(type, vm["model"].as<std::string>(), modifiers);
   
   if (vm.count("list_parameters"))
   {
      fitter.showModels();
      return 0;
   }
   for (const auto& m : modifiers) m.show();


   int returnValue = 0;
   
   bool weighted = false;
   if (vm.count("weighted"))
      weighted = true;
   
   std::unique_ptr<RooFitResult> modelFit = fitter.modelFit(vm["model"].as<std::string>(),weighted);
   
   if (modelFit)
   {
      std::cout << "\nCorrelation matrix of model fit:" << std::endl;
      if (&(modelFit->correlationMatrix()) != nullptr)
      {
         modelFit->correlationMatrix().Print("v");
         TMatrixDSymEigen CM = modelFit->correlationMatrix();
         TMatrixD CM_eigen = CM.GetEigenVectors();
         std::cout << "Eigenvectors of Correlation Matrix" << std::endl;
         CM_eigen.Print("v");
      }
      else
      {
         std::cout << ">>> no correlation matrix available" << std::endl;
         returnValue = 1;
      }
    if (&(modelFit->covarianceMatrix()) != nullptr) {
      std::cout << "Covariance Matrix" << std::endl;
      modelFit->covarianceMatrix().Print("v");

      TMatrixDSymEigen VM = modelFit->covarianceMatrix();
      TMatrixD VM_eigen = VM.GetEigenVectors();
      std::cout << "Eigenvectors of Covariance Matrix" << std::endl;
      VM_eigen.Print("v");
    } else {
      std::cout << ">>> no covariance matrix available" << std::endl;
      returnValue = 1;
    }
  } else {
    returnValue = 1;
  }

  if (vm.count("profile")) {
    fitter.profileModel(ab::FitContainer::Type::background);
  }

  return returnValue;
}
