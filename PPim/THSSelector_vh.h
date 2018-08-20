//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue May 15 14:21:21 2018 by ROOT version 6.08/06
// from TTree HSParticles/A tree containing reconstructed particles
// found on file: /w/work1/home/chris/LatestAnalysisRuns/Data/DataDec17ChargedPion/HaspectOutput/PiMinusP/ProdData/Dev3.0Files20PhysicsAll.root
//////////////////////////////////////////////////////////

#ifndef THSSelector_vh_h
#define THSSelector_vh_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include "THSOutput.h"
#include "THSWeights.h"
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class THSSelector_vh : public TSelector, public THSOutput {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

  //data members for reading weights
   THSWeights* fWeights=0;
  //data members for new branches
   //you must define how they are processed for each event and set to 0 in constructor
   //e.g.   TLorentzVector  *fp1;
   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Double_t> MissMass = {fReader, "MissMass"};
   TTreeReaderValue<Double_t> Phi = {fReader, "Phi"};
   TTreeReaderValue<Double_t> Costh = {fReader, "Costh"};
   TTreeReaderValue<Double_t> SpecMom = {fReader, "SpecMom"};
   TTreeReaderValue<Double_t> Coplanarity = {fReader, "Coplanarity"};
   TTreeReaderValue<Double_t> BeamEnergy = {fReader, "BeamEnergy"};
   TTreeReaderValue<Double_t> W = {fReader, "W"};
   TTreeReaderValue<Double_t> InvMass = {fReader, "InvMass"};
   TTreeReaderValue<Double_t> Pol = {fReader, "Pol"};
   TTreeReaderValue<Double_t> TaggChannel = {fReader, "TaggChannel"};
   TTreeReaderValue<Double_t> ConeAngle = {fReader, "ConeAngle"};
   TTreeReaderValue<Double_t> DetErrs = {fReader, "DetErrs"};
   TTreeReaderValue<Double_t> PimTagDiffTime = {fReader, "PimTagDiffTime"};
   TTreeReaderValue<Double_t> AnyErrs = {fReader, "AnyErrs"};
   TTreeReaderValue<Int_t> Correct = {fReader, "Correct"};
   TTreeReaderValue<Double_t> DCorrect = {fReader, "DCorrect"};
   TTreeReaderValue<Double_t> SpecMass = {fReader, "SpecMass"};
   TTreeReaderValue<Double_t> WII = {fReader, "WII"};
   TTreeReaderValue<Double_t> CorrectedProtonEnergy = {fReader, "CorrectedProtonEnergy"};
   TTreeReaderValue<Double_t> TagTime = {fReader, "TagTime"};
   TTreeReaderValue<Double_t> PimTime = {fReader, "PimTime"};
   TTreeReaderValue<Double_t> ProtonTime = {fReader, "ProtonTime"};
   TTreeReaderValue<Double_t> ProtonTagTimeDiff = {fReader, "ProtonTagTimeDiff"};
   TTreeReaderValue<Double_t> NucleonRawEnergy = {fReader, "NucleonRawEnergy"};
   TTreeReaderValue<Double_t> NucleonEnergyFinal = {fReader, "NucleonEnergyFinal"};
   TTreeReaderValue<Double_t> PimRawEnergy = {fReader, "PimRawEnergy"};
   TTreeReaderValue<Double_t> PimMassDiff = {fReader, "PimMassDiff"};
   TTreeReaderValue<Double_t> ConePhi = {fReader, "ConePhi"};
   TTreeReaderValue<Double_t> ProtonPhi = {fReader, "ProtonPhi"};
   TTreeReaderValue<Double_t> ProtonTheta = {fReader, "ProtonTheta"};
   TTreeReaderValue<Double_t> PimPhi = {fReader, "PimPhi"};
   TTreeReaderValue<Double_t> PimTheta = {fReader, "PimTheta"};
   TTreeReaderValue<Double_t> ProtonDetector = {fReader, "ProtonDetector"};
   TTreeReaderValue<Double_t> PimDetector = {fReader, "PimDetector"};
   TTreeReaderValue<Int_t> PolState = {fReader, "PolState"};
   TTreeReaderValue<Double_t> PolStateD = {fReader, "PolStateD"};
   TTreeReaderValue<Double_t> PolErrs = {fReader, "PolErrs"};
   TTreeReaderValue<Double_t> UID = {fReader, "UID"};


   THSSelector_vh(TTree * /*tree*/ =0) { }
   virtual ~THSSelector_vh() {SafeDelete(fWeights); /*//SafeDelete(fp1);//If we add pointer ro classmust delete it*/  }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();
//Add THSHisto functions
   virtual void HistogramList(TString sLabel);
   virtual void FillHistograms(TString sCut);

   ClassDef(THSSelector_vh,0);

};

#endif

#ifdef THSSelector_vh_cxx
void THSSelector_vh::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t THSSelector_vh::Notify()
{
   fChain=fReader.GetTree();
   THSOutput::HSNotify(fChain);
  THSOutput::InitOutTree();
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef THSSelector_vh_cxx
