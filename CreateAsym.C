void CreateAsym() {
	// Need to change to root file output and create histos for all plus asym. Then create another one of these that only does asym, pol and  

  //TFile *outfile =new TFile("/w/work1/home/chris/AsymsTesting.root","recreate");
  bool doBins = true;	
	
  if (doBins) {
		
    TFile *infile = TFile::Open("/w/work1/home/chris/TestingFinalNoPol.root");
    //TFile *infile = TFile::Open("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/TestMulti/Dev15.0Files20PhysicsAll.root");

    TFile *outfile =new TFile("/w/work1/home/chris/AsymsProtonChannel.root","recreate");
    string dirs[3] = {"BG","Sig", "Cut1"};
    vector<TString> histNames;
    vector<TString> phihistNames;
    bool storeHistNames = true;
		
    // all histograms for each bin
    for (int i=0; i<3; i++) {
					
      TDirectory *weightsDir = infile->GetDirectory(dirs[i].c_str());	//WeightsDir is top lev folder
      TIter	nextTbinDir(weightsDir->GetListOfKeys());
      TKey 	*tbinKey;
			
      while ((tbinKey=(TKey*)nextTbinDir())) {
			
	TDirectory *tbinDir = weightsDir->GetDirectory(tbinKey->GetName()); //tbinDir is my W var.
	TIter	nextEbinDir(tbinDir->GetListOfKeys());
	TKey 	*ebinKey;
				
	while ((ebinKey=(TKey*)nextEbinDir())) {
					
	  TDirectory *ebinDir = tbinDir->GetDirectory(ebinKey->GetName()); //ebinDir is my costh
	  TIter nextPolbinDir(ebinDir->GetListOfKeys());
	  TKey  *polbinKey;

	  while ((polbinKey=(TKey*)nextPolbinDir())){

	    TDirectory *polbinDir = ebinDir->GetDirectory(polbinKey->GetName());
	    TIter	nextHist(polbinDir->GetListOfKeys());
	    TKey	*histKey;
	   // TString heading = dirs[i]+" "+(TString)tbinDir->GetName()+" "+(TString)ebinDir->GetName()+" " + (TString)polbinDir->GetName();
					
	    int histNum = 0;
	    while ((histKey=(TKey*)nextHist())) {
									
	      histNum++;
						
	      TH1F* hist = (TH1F*) histKey->ReadObj();
	      hist->Draw();
	     // TString imFileName = dirs[i]+(TString)tbinDir->GetName()+(TString)ebinDir->GetName()+(TString)polbinDir->GetName()+histKey->GetName()+".gif";
	      //if (storeHistNames) histNames.push_back(histKey->GetName());
	      TString IsPhi = (TString)histKey->GetName();
	      TString IsPolPos = (TString)polbinDir->GetName();

	      if(IsPhi=="Phi" && IsPolPos=="PolStateD-0.50_"){
		//phihistNames.push_back(histKey->GetName());
		cout <<" Some manner of success " << endl;
		TString PolPosName ="/" + dirs[i]+"/" + (TString)tbinDir->GetName()+ "/"  +  (TString)ebinDir->GetName() + "/PolStateD0.50_/Phi";
		TH1F* PolPos = (TH1F*)infile->Get(PolPosName);
		TH1F* hist = (TH1F*) histKey->ReadObj();
		//Give Asym a proper name and heading
		TH1* Asym = PolPos->GetAsymmetry(hist);  //h1->GetAsym(h2)=> h1-h2
		TF1* fit=new TF1("cos2phi","[0]+[1]*cos(TMath::DegToRad()*(2*x+[2]))",-180,180);
		//fit->SetParLimits(2,80,100);
		Asym->Fit("cos2phi");
		Asym->Draw(); 
		Asym->Write();
		//TString imFileName = dirs[i]+(TString)tbinDir->GetName()+(TString)ebinDir->GetName()+(TString)histKey->GetName()+"Asym.gif";
		//TString histAsymName =(TString)histKey->GetName() + "Asym" ;
	      }

		hist->Write();
		

	    }		
	  }
	}
      }
    }
  }
}
	

