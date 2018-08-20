//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar 16 13:56:18 2018 by ROOT version 6.08/06
// from TTree HSParticles/A tree containing reconstructed particles
// found on file: /w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/TestMulti/Dev19.0Files20PhysicsAll.root
//////////////////////////////////////////////////////////

#ifndef THSRandBG_vh_h
#define THSRandBG_vh_h

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


class THSRandBG_vh : public TSelector, public THSOutput {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

  //data members for reading weights
   THSWeights* fWeights=0;
  //data members for new branches
   //you must define how they are processed for each event and set to 0 in constructor
   //e.g.   TLorentzVector  *fp1;
   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Double_t> Topo = {fReader, "Topo"};
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
   TTreeReaderValue<Double_t> EnergyErrs = {fReader, "EnergyErrs"};
   TTreeReaderValue<Double_t> DetErrs = {fReader, "DetErrs"};
   TTreeReaderValue<Double_t> GammaAveTagDiffTime = {fReader, "GammaAveTagDiffTime"};
   TTreeReaderValue<Double_t> DomFuncErrs = {fReader, "DomFuncErrs"};
   TTreeReaderValue<Double_t> AnyErrs = {fReader, "AnyErrs"};
   TTreeReaderValue<Double_t> MissMass = {fReader, "MissMass"};
   TTreeReaderValue<Int_t> Correct = {fReader, "Correct"};
   TTreeReaderValue<Double_t> DCorrect = {fReader, "DCorrect"};
   TTreeReaderValue<Double_t> SpecMass = {fReader, "SpecMass"};
   TTreeReaderValue<Double_t> WII = {fReader, "WII"};
   TTreeReaderValue<Int_t> PolState = {fReader, "PolState"};
   TTreeReaderValue<Double_t> PolStateD = {fReader, "PolStateD"};
   TTreeReaderValue<Double_t> PolErrs = {fReader, "PolErrs"};
   TTreeReaderValue<Double_t> UID = {fReader, "UID"};


   THSRandBG_vh(TTree * /*tree*/ =0) { }
   virtual ~THSRandBG_vh() {SafeDelete(fWeights); /*//SafeDelete(fp1);//If we add pointer ro classmust delete it*/  }
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

   ClassDef(THSRandBG_vh,0);

};

#endif

#ifdef THSRandBG_vh_cxx
void THSRandBG_vh::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t THSRandBG_vh::Notify()
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


#endif // #ifdef THSRandBG_vh_cxx
