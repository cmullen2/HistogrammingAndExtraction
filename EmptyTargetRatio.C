#include <stdlib.h>
#include "TSystem.h"


TH1F* MakeHisto(TString tempName,Double_t &fileCounter);

TH1F* LoadSaved(TString fname , TString hname );


void EmptyTargetRatio() {
		
/*
  TFile *infileEmp1Para = TFile::Open("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/AcquOutput/EmptyTarget/Para/Hist_CBTaggTAPS_15811.root");
  TFile *infileEmp1Perp = TFile::Open("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/AcquOutput/EmptyTarget/Perp/Hist_CBTaggTAPS_15837.root");
  TFile *infileDat1Perp = TFile::Open("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/AcquOutput/Perp/Hist_CBTaggTAPS_14979.root");
  TFile *infileDat1Para = TFile::Open("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/AcquOutput/Para/Hist_CBTaggTAPS_14956.root");
*/


Double_t empParaCount = 0;
Double_t empPerpCount = 0;
Double_t dataParaCount = 0;
Double_t dataPerpCount = 0;



TH1F* empParahist =  MakeHisto("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/AcquOutput/EmptyTarget/Para/Hist",empParaCount);
TH1F* empPerphist =  MakeHisto("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/AcquOutput/EmptyTarget/Perp/Hist",empPerpCount);
TH1F* dataParahist =  MakeHisto("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/AcquOutput/Para/Hist",dataParaCount);
TH1F* dataPerphist =  MakeHisto("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/AcquOutput/Perp/Hist",dataPerpCount);



cout << empParaCount << "   " << empPerpCount << "   "<< dataParaCount << "    "<< dataPerpCount << endl;

Double_t sumEmpty = empParaCount + empPerpCount;
Double_t sumData = dataParaCount + dataPerpCount;


TH1F *empTotalhist =  (TH1F*)empParahist->Clone("empTotalhist");
TH1F *dataTotalhist =  (TH1F*)dataParahist->Clone("dataTotalhist");
empTotalhist->Add(empPerphist);
dataTotalhist->Add(dataPerphist);

TH1F *ratioHist;

if (sumEmpty==sumData){
 
   ratioHist = (TH1F*)empTotalhist->Clone("ratioHist");
   ratioHist->Divide(dataTotalhist);

}
else{
  Double_t sumRatio = sumEmpty/sumData ;
  dataTotalhist->Scale(sumRatio);

  ratioHist =  (TH1F*)empTotalhist->Clone("ratioHist");
  ratioHist ->Divide(dataTotalhist);

cout <<" Ratio of empty target to data is: " << sumRatio << endl;
}



TFile *OutFile = new TFile("/scratch/chris/Emptyration.root","recreate");

ratioHist->Write();  
empTotalhist->Write();
dataTotalhist->Write();
empParahist->Write();
empPerphist->Write();
dataParahist->Write();
dataPerphist->Write();
OutFile->Close();

}




TH1F* MakeHisto(TString tempName, Double_t &fileCounter){

//  TH1F* totalhisto = new TH1F("totalhisto","totalhisto",352,0,352);

  TString dirName=gSystem->DirName(tempName);
  TH1F* totalhisto = new TH1F(dirName,dirName,352,0,352);
  TString prefix=gSystem->BaseName(tempName); //anything after directory in tempname
  if(prefix==TString("")) prefix="Weights";
  void *dir=gSystem->OpenDirectory(dirName);
  if(!dir) cout<<" No directory found : "<<dirName<<endl;
  else cout<<" Merging histos "<<prefix <<"* in directory "<<dirName<<endl;
  TString fileName;
  while( (fileName=(gSystem->GetDirEntry(dir)))){


    if(fileName==TString("")) break;
    if(fileName==TString("."))continue;
    if(fileName==TString(".."))continue;
    if(!fileName.Contains(prefix))continue;
    if(!fileName.Contains(".root"))continue;
    cout<<"THSWeights::Merge Adding file "<<fileName<<endl;

    TH1F* firsthist =  LoadSaved(dirName+"/"+fileName,"FPD_ScalerAcc");
//Add returned histo to total histo.
   totalhisto->Add(firsthist);

   fileCounter = fileCounter +1;

// Delete the returned histo
   delete firsthist;

}

return totalhisto;

}


TH1F* LoadSaved(TString fname,TString hname){

  TDirectory* savedir=gDirectory;
  TFile* hfile=new TFile(fname);
  cout<<fname<<" "<<hname<<endl;
  TH1F* scalerhist = (TH1F*)hfile->Get(hname);
  return scalerhist;





//  wfile->ls();
/*
//  THSWeights* file_wts=(THSWeights*)wfile->Get(wname);//read into memory
  temphisto 

  fName=file_wts->GetName();
  fTitle=file_wts->GetTitle();
  cout<<fName<<" "<<fTitle<<endl;
  savedir->cd();
  TTree* tempTree=0;
  tempTree=(TTree*)wfile->Get(wname+"_W");
  cout<<tempTree<<endl;
  fWTree=tempTree->CloneTree();
  delete tempTree;
  fWTree->SetDirectory(0);
  fSpecies=file_wts->GetSpecies();
  fWVals.ResizeTo(fSpecies.size());
  for(UInt_t i=0;i<fSpecies.size();i++)
    fWTree->SetBranchAddress(GetSpeciesName(i),&fWVals[i]); 

  tempTree=(TTree*)wfile->Get(wname+"_ID");
  fIDTree=tempTree->CloneTree();
  // fIDTree=(TTree*)file_wts->GetIDTree()->Clone();
  delete tempTree;
  fIDTree->SetDirectory(0);
  fIDTree->SetBranchAddress("WID",&fID);
 
  fCurrEntry=0;
  fIsSorted=kFALSE;
  fN=fWTree->GetEntries();
  delete file_wts;  
  wfile->Close();
  delete wfile;
*/
}




