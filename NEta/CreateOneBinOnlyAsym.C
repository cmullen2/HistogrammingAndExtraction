#include <stdlib.h>



//void MakeSigmaGraph(Double_t , Double_t,Double_t,Double_t,Int_t,TString);

void MakeSigmaGraph(vector<Double_t> sigma, vector<Double_t> error, vector<Double_t> plotVar, vector<Double_t> plotVarError, Int_t numBins, TString hTitle, TString hName );

void CreateOneBinOnlyAsym() {
		
  //TFile *infile = TFile::Open("/w/work1/home/chris/TestingFinalNoPolNewPhi20bins.root");
  TFile *infile = TFile::Open("/w/work1/home/chris/HistoSelector/PEta/Coplan/TestPEtaSingleBin.root");
  //TFile *infile = TFile::Open("/w/work1/home/chris/TestingFinalNoPolNoW995.root");

  TFile *outfile =new TFile("/w/work1/home/chris/HistoSelector/PEta/Coplan/AsymsAllNoBins.root","recreate");
  string dirs[3] = {"BG","Sig", "Cut1"};
  vector<TString> histNames;
  vector<TString> phihistNames;
  vector<Double_t> VecSigma;
  vector<Double_t> VecSigmaErr;
  vector<Double_t> VecCosth;
  vector<Double_t> VecCosthErr;
  Int_t BinsCounter = 0;
	
  // all histograms for each bin
  for (int i=0; i<3; i++) {
					
    TDirectory *weightsDir = infile->GetDirectory(dirs[i].c_str());	//WeightsDir is top lev folder
//    TIter	nextTbinDir(weightsDir->GetListOfKeys());
//    TKey 	*tbinKey;
			
//    while ((tbinKey=(TKey*)nextTbinDir())) {
			
//      TDirectory *tbinDir = weightsDir->GetDirectory(tbinKey->GetName()); //tbinDir is my W var.
//      TIter	nextEbinDir(tbinDir->GetListOfKeys());
//      TKey 	*ebinKey;
				
//      while ((ebinKey=(TKey*)nextEbinDir())) {
					
//	TDirectory *ebinDir = tbinDir->GetDirectory(ebinKey->GetName()); //ebinDir is my costh
	TIter nextPolbinDir(weightsDir->GetListOfKeys());
	TKey  *polbinKey;

	while ((polbinKey=(TKey*)nextPolbinDir())){   //Looping round my polarisation states - +

	  TDirectory *polbinDir = weightsDir->GetDirectory(polbinKey->GetName());
	  TIter	nextHist(polbinDir->GetListOfKeys());
	  TKey	*histKey;
					
	  int histNum = 0;
	  while ((histKey=(TKey*)nextHist())) {
	cout << " HEllo" << endl;								
	    histNum++;
	    TString IsPhi = (TString)histKey->GetName();
	    TString IsPolPos = (TString)polbinDir->GetName();
cout << IsPhi << IsPolPos<< endl;
	    if(IsPhi=="Phi" && IsPolPos=="PolStateD-0.50_"){
	      TString PolPosName ="/" + dirs[i] +  "/PolStateD0.50_/Phi";
	      TString PolarPosName ="/" + dirs[i] + "/PolStateD0.50_/Polarisation";
	      TString PolarNegName ="/" + dirs[i]  + "/PolStateD-0.50_/Polarisation";
	      TH1F* PolarPos = (TH1F*)infile->Get(PolarPosName);
	      TH1F* PolarNeg = (TH1F*)infile->Get(PolarNegName);
		cout << PolPosName<< endl;
	      TH1F* PolPos = (TH1F*)infile->Get(PolPosName);
	      TH1F* hist = (TH1F*) histKey->ReadObj();
	      //Give Asym a proper name and heading
	      TH1* Asym = hist->GetAsymmetry(PolPos);
	      TF1* fit=new TF1("cos2phi","[0]+[1]*cos(TMath::DegToRad()*(2*x+[2]))",-180,180);
	      //fit->SetParLimits(2,80,100);
	      Asym->Fit("cos2phi");
	      Asym->Draw(); 
	      Double_t MeanPolPos =  PolarPos->GetMean();
	      Double_t MeanPolNeg =  PolarNeg->GetMean();
	      Double_t AvePol = (MeanPolPos + MeanPolNeg)/2;
	      Double_t Par1 = fit->GetParameter(1) ;
	      Double_t Err1 =fit->GetParError(1) ;
	      Double_t Sigma = Par1/AvePol;  //Need a histo for each W var. or store in an array and use a separate function to plot the sigma plots so that I can change the binning without rerunning selector.
	      Err1 = Sigma* (Err1/Par1) ;
	      BinsCounter = BinsCounter+1;
	      string thetabin ="0" ;
		cout << "MADE IT HERE " << endl;
	      //cout << thetabin << endl;
	      //Double_t thetalen = thetabin.size();
	      //string thetabin3 = thetabin.substr(5,thetalen -1 );
	      //cout << thetabin3 << endl;
	      //Double_t CosthBin = stod(thetabin3); //Can I cast straight to double here?
	      //cout << dirs[i]  << CosthBin << " Costh " <<"Sigma=Par1/AvePol  " << Sigma << "=" << Par1 << "/"<< AvePol  <<endl;
	      VecSigma.push_back(Sigma);
	cout << "DID WE MAKE IT HERE " << endl;
	      VecSigmaErr.push_back(Err1);
	      VecCosth.push_back(1);
	      VecCosthErr.push_back(0.1);
	      Asym->Write();
	     cout <<"ALSO HERE TOO " <<endl;
	      hist->Write();
	      PolPos->Write();
	      PolarPos->Write();
	      PolarNeg->Write();
	    } //Closing if 
	  }  //Closing while hist key		
	}   //Closing while nextPolbin
 //     }    //Closing while nextEbindir costh
	TString Wbin = "0";
	TString Wname = dirs[i] + "0";
	MakeSigmaGraph(VecSigma, VecSigmaErr, VecCosth, VecCosthErr, BinsCounter, Wbin, Wname); //Errors both wrong, costh is just the bin size might need changed. Sigma is the fit param error doesn't account for the division
	//MakeSigmaGraph(1, 2, 3, 4, 5, "h");
	VecSigmaErr.clear();
	VecSigma.clear();
	VecCosth.clear();
	VecCosthErr.clear();
	BinsCounter=0;
//    }     //Closing while nextTbindir W
  }  //Closing For loop
  //Can Make the function for drawing tgraph for sigma here and add simons code for adding sigma theory curves too.
  outfile->Close();
} //closing main function
	

void MakeSigmaGraph(vector<Double_t> sigma, vector<Double_t> error, vector<Double_t> plotVar, vector<Double_t> plotVarError, Int_t numBins, TString hTitle,TString hName ){

  //Use this function to plot the sigma variable wrt energy or costh. First do sigma on y and costh on x for an energy bin, then energy on x for a costh bin.
  //Make an array for all sigma for each bin variable. Also make an array which stores the energy and ones that stores the costh for each of these.
  //
  //   W loop
  //	Costh loop
  //		sigma formed(Pol loop too but ignore)
  //	so for each new W could call MakeSigmaGraph, then clear the vector. Plot it with the W range on it, can pass as a param via tbinkey->GetName
  //
  //
  //  To be able to do the opposite we need to store all sigma values in a vector that isn't cleared until the end of dobins
  //  Then can call after all W have looped a separate function or just split the vector into other vectors using a small for loop and pass these to the function 
  //  Would need counters for the number of bins for each method. For the first method using the W as each plot need it for each call of the makesigma function.
  //  For the second method need it to allow the splitting of the vectors correctly and to pass to the plotting function
  //
  // First get it working for method one!

  TGraph* SigmaPlot = new TGraphErrors(numBins,&(plotVar[0]),&(sigma[0]),&(plotVarError[0]),&(error[0])); 
  //TGraph* SigmaPlotCosth = new TGraphErrors(NumBins,costh,sigma,costherror,error); 



SigmaPlot->Draw("AP");
SigmaPlot->SetTitle(hTitle);
SigmaPlot->SetName(hName);
//SigmaPlot->GetXaxis()->SetTitle("#theta");
//SigmaPlot->GetXaxis()->SetTitleSize(0.09);
//SigmaPlot->GetXaxis()->SetTitleOffset(0.5);
//SigmaPlot->GetXaxis()->SetNdivisions(1,7,0);
//SigmaPlot->GetXaxis()->SetLabelSize(0.08);
//SigmaPlot->GetXaxis()->CenterTitle();
SigmaPlot->GetYaxis()->SetTitle("#Sigma");
//SigmaPlot->GetYaxis()->SetTitleSize(0.15);
//SigmaPlot->GetYaxis()->SetTitleOffset(0.18);
//SigmaPlot->GetYaxis()->SetLabelSize(0.08);
//SigmaPlot->GetYaxis()->SetNdivisions(0,7,0);
//SigmaPlot->GetYaxis()->SetRangeUser(-1,1);

SigmaPlot->GetXaxis()->SetTitle("Cos#theta_{CM} ");
//SigmaPlot->GetXaxis()->SetTitleSize(0.08);
//SigmaPlot->GetXaxis()->SetTitleOffset(0.5);
//SigmaPlot->GetXaxis()->SetNdivisions(1,5,0);
//SigmaPlot->GetXaxis()->SetLabelSize(0.08);
//SigmaPlot->GetXaxis()->SetLabelOffset(0.02);
SigmaPlot->GetXaxis()->CenterTitle();

//SigmaPlot->GetYaxis()->SetTitle("#Sigma");
//SigmaPlot->GetYaxis()->SetTitleSize(0.15);
//SigmaPlot->GetYaxis()->SetTitleOffset(0.24);
//SigmaPlot->GetYaxis()->SetLabelSize(0.08);
//SigmaPlot->GetYaxis()->SetNdivisions(2,5,0);
//SigmaPlot->GetYaxis()->SetRangeUser(-1,1);

  SigmaPlot->Write();
//Add in the new styles and axis labels etc. also name of the graphs. (Need to pass whether it is sig bg or cut1  )

}



