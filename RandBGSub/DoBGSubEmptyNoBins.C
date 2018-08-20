#include <stdlib.h>



//void MakeSigmaGraph(Double_t , Double_t,Double_t,Double_t,Int_t,TString);

void MakeSigmaGraph(vector<Double_t> sigma, vector<Double_t> error, vector<Double_t> plotVar, vector<Double_t> plotVarError, Int_t numBins, TString hTitle, TString hName );

void DoBGSubEmpty() {
		
//  TFile *infile = TFile::Open("/w/work1/home/chris/TestingFinalNoPolNewPhi20bins.root");
  TFile *infile = TFile::Open("/w/work1/home/chris/HistoSelector/RandBGMethod/EmptyCoplanBinnedBGSub.root");
  //TFile *infile = TFile::Open("/w/work1/home/chris/TestingFinalNoPolNoW995.root");

  TFile *outfile =new TFile("/w/work1/home/chris/HistoSelector/RandBGMethod/EmptyBinnedBGSubbedProtonChannel2.root","recreate");
  string dirs[2] = {"Prompt","Random"};
  vector<TString> histNames;
  vector<TString> phihistNames;
  vector<Double_t> VecSigma;
  vector<Double_t> VecSigmaErr;
  vector<Double_t> VecCosth;
  vector<Double_t> VecCosthErr;
  Int_t BinsCounter = 0;
	
  // all histograms for each bin
  for (int i=0; i<1; i++) {
					
    TDirectory *weightsDir = infile->GetDirectory(dirs[i].c_str());	//WeightsDir is top lev folder
    TIter	nextTbinDir(weightsDir->GetListOfKeys());
    TKey 	*tbinKey;
			
    while ((tbinKey=(TKey*)nextTbinDir())) {
			
      TDirectory *tbinDir = weightsDir->GetDirectory(tbinKey->GetName()); //tbinDir is my W var.
      TIter	nextPolbinDir(tbinDir->GetListOfKeys());
      TKey 	*polbinKey;
      
      // Making my new directory structure
      TDirectory *Wfold = outfile->mkdir(tbinKey->GetName());
      Wfold->cd();
	
	while ((polbinKey=(TKey*)nextPolbinDir())){   //Looping round my polarisation states - +

	  TDirectory *polbinDir = tbinDir->GetDirectory(polbinKey->GetName());
	  TIter	nextHist(polbinDir->GetListOfKeys());
	  TKey	*histKey;

	  TDirectory *Polfold = Wfold->mkdir(polbinKey->GetName());
	  Polfold->cd();
					
	  int histNum = 0;
	  while ((histKey=(TKey*)nextHist())) {
									
	    histNum++;
//	    TString IsPhi = (TString)histKey->GetName();
//	    TString IsPolPos = (TString)polbinDir->GetName();

	    TString RandName = "/" + dirs[i+1] + "/" + (TString)tbinDir->GetName() + "/" +  (TString)polbinDir->GetName()+"/" + histKey->GetName(); 
	    TH1F* histRand = (TH1F*)infile->Get(RandName);
	    TH1F* hist = (TH1F*) histKey->ReadObj();

	    hist->Add(histRand,-0.5);	    
	    hist->SetName(histKey->GetName());
	    hist->Write();

	  }  //Closing while hist key		
	}   //Closing while nextPolbin
          //Closing while nextEbindir costh
    }     //Closing while nextTbindir W
  }  //Closing For loop
  outfile->Close();
} //closing main function
	

void MakeSigmaGraph(vector<Double_t> sigma, vector<Double_t> error, vector<Double_t> plotVar, vector<Double_t> plotVarError, Int_t numBins, TString hTitle,TString hName ){


  TGraph* SigmaPlot = new TGraphErrors(numBins,&(plotVar[0]),&(sigma[0]),&(plotVarError[0]),&(error[0])); 
SigmaPlot->Draw("AP");
SigmaPlot->SetTitle(hTitle);
SigmaPlot->SetName(hName);
SigmaPlot->GetYaxis()->SetTitle("#Sigma");
SigmaPlot->GetXaxis()->SetTitle("Cos#theta_{CM} ");
SigmaPlot->GetXaxis()->CenterTitle();
SigmaPlot->Write();
}



