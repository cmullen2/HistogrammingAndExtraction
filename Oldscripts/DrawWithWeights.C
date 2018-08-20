{
  TString ParaPath ="outCoplanFromGammaTagDiffNeutronChannelNegPol6Files5BinsExcludeNoCBTAPSBifur/WeightsTopo-0.50_Pol-0.50_";
  TString PerpPath ="outCoplanFromGammaTagDiffNeutronChannelPosPol6Files5BinsExcludeNoCBTAPSBifur/WeightsTopo-0.50_Pol0.50_";
  TString ParaDir ="outCoplanFromGammaTagDiffNeutronChannelNegPol6Files5BinsExcludeNoCBTAPSBifur/";
  TString PerpDir ="outCoplanFromGammaTagDiffNeutronChannelPosPol6Files5BinsExcludeNoCBTAPSBifur/";

  // TString ParaPath ="outCoplanNeutronChannelNegPol6Files5Bins20ExcludeNoCBTAPS/WeightsTopo-0.50_Pol-0.50_";
  // TString PerpPath ="outCoplanNeutronChannelPosPol6Files5Bins20ExcludeNoCBTAPS/WeightsTopo-0.50_Pol0.50_";
  // TString ParaDir ="outCoplanNeutronChannelNegPol6Files5Bins20ExcludeNoCBTAPS/";
  // TString PerpDir ="outCoplanNeutronChannelPosPol6Files5Bins20ExcludeNoCBTAPS/";

std::string AFileName = "ResultsTopo0.50_BeamEnergy337.50_DetErrs0.00_.root";
std::size_t PositionB = AFileName.find("BeamEnergy");
cout <<PositionB << "   " << AFileName <<endl;
std::string EndName = AFileName.substr(PositionB );
cout << EndName << endl;
std::size_t EndingNo = EndName.find("_");
std::string Eggg= EndName.substr(0,EndingNo);
cout << Eggg << "   " << EndingNo << endl;
std::string Finalsss = Eggg.substr(10);
cout << Finalsss << endl;



  //Open the output file
  TDirectory *saveDir=gDirectory;
  TFile* outfile = new TFile("AsymFromGammaTagDiffNeutron6Files5BinsExcludeNoCBTAPSBifur.root","recreate");
  saveDir->cd();

  //SUM of weights squared still to be added but figure out binning first. Petey says root6 does it auto but should test this.

  //Here do the prefix stuff to determine the number of bins
  vector<TString>  BinNamesPos;
  vector<TString>  BinNamesNeg;
  DetermineBins(BinNamesPos,PerpPath);
  DetermineBins(BinNamesNeg,ParaPath);
 

  TChain chain("HSParticles");
  chain.Add("/w/work14/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/TestMulti/Dev9.0Files6PhysicsAll.root");
  Double_t ID,Phi,Pol;
  chain.SetBranchAddress("fUID",&ID);
  chain.SetBranchAddress("Phi",&Phi);
  chain.SetBranchAddress("Pol",&Pol);  //Pol is pos and neg depending on the state.
  
  //Loop for number of bins here and set up the names of the histos using the prefix names (array?)
  for(Int_t j=0; j<BinNamesNeg.size(); j++){
    //  for(Int_t j=0; j<1; j++){
 
    TString WNameNeg =ParaDir + BinNamesNeg[j];
    cout << WNameNeg<< "   WeightsName" <<endl;
    THSWeights* wtsNeg=new THSWeights("TotalWeightsNeg");
    wtsNeg->LoadSaved(WNameNeg,"HSsWeights"); 
    wtsNeg->PrintWeight();
    THSWeights* wtsPos=new THSWeights("TotalWeightsPos");

    TString WNamePos =PerpDir + BinNamesPos[j];
    wtsPos->LoadSaved(WNamePos,"HSsWeights");

    wtsPos->PrintWeight();
    TString hnameSPos="PhiSPos" + BinNamesPos[j] ;   
    TString hnameBPos="PhiBPos" + BinNamesPos[j] ;
    TString hnameSNeg="PhiSNeg" + BinNamesNeg[j] ;
    TString hnameBNeg="PhiBNeg" + BinNamesNeg[j] ;
    TString hnamePolSPos="PolSPos" + BinNamesPos[j] ;   
    TString hnamePolBPos="PolBPos" + BinNamesPos[j] ;   
    TString hnamePolSNeg="PolSNeg" + BinNamesPos[j] ;   
    TString hnamePolBNeg="PolBNeg" + BinNamesPos[j] ;   

    TH1F* histPhiSPos=new TH1F(hnameSPos,"PhiSPos",100,-180,180);
    TH1F* histPhiBPos=new TH1F(hnameBPos,"PhiBPos",100,-180,180);
    TH1F* histPhiSNeg=new TH1F(hnameSNeg,"PhiSNeg",100,-180,180);
    TH1F* histPhiBNeg=new TH1F(hnameBNeg,"PhiBNeg",100,-180,180);
    TH1F* histPolSPos=new TH1F(hnamePolSPos,"PolSPos",100,-1,1);
    TH1F* histPolBPos=new TH1F(hnamePolBPos,"PolBPos",100,-1,1);
    TH1F* histPolSNeg=new TH1F(hnamePolSNeg,"PolSNeg",100,-1,1);
    TH1F* histPolBNeg=new TH1F(hnamePolBNeg,"PolBNeg",100,-1,1);
    Double_t weight=0;
  
    for(Int_t i=0;i<chain.GetEntries();i++){
      chain.GetEntry(i);
      if(wtsPos->GetEntryBinarySearch(ID)){//find the weight for this event
	histPhiSPos->Fill(Phi,wtsPos->GetWeight("Signal"));
	histPhiBPos->Fill(Phi,wtsPos->GetWeight("BG"));
        histPolSPos->Fill(Pol,wtsPos->GetWeight("Signal"));
        histPolBPos->Fill(Pol,wtsPos->GetWeight("BG"));
      }
      else if(wtsNeg->GetEntryBinarySearch(ID)){//find the weight for this event   //Fill the linpol here too so can divide out(should this be mag or with sign)
	histPhiSNeg->Fill(Phi,wtsNeg->GetWeight("Signal"));
	histPhiBNeg->Fill(Phi,wtsNeg->GetWeight("BG"));
        histPolSNeg->Fill(Pol,wtsNeg->GetWeight("Signal"));
        histPolBNeg->Fill(Pol,wtsNeg->GetWeight("BG"));
      }
    }

    TH1* Asym = histPhiSNeg->GetAsymmetry(histPhiSPos); 
    TF1* fit=new TF1("cos2phi","[0]+[1]*cos(TMath::DegToRad()*(2*x+[2]))",-180,180); 
    fit->SetParLimits(2,80,100);
    Asym->Fit("cos2phi");


    //Write here
    outfile->cd();
    Asym->Write();
    histPhiSPos->Write();
    histPhiBPos->Write();
    histPhiSNeg->Write();
    histPhiBNeg->Write();
    histPolSPos->Write();
    histPolBPos->Write();
    histPolSNeg->Write();
    histPolBNeg->Write();
    saveDir->cd();


    //Delete "new" objects
    delete wtsNeg;
    delete wtsPos;
  }

  //Outside of the loop close the output file

}



void DetermineBins(vector<TString> & BinNames,TString tempName){
 
  Int_t Nbins =0 ;
  

  TString dirName=gSystem->DirName(tempName);
  cout << dirName << " THIS is the directory name" << endl;
  TString prefix=gSystem->BaseName(tempName); //anything after directory in tempname
  cout << "PRefix " << prefix << endl;
  if(prefix==TString("")) prefix="Weights";
  void *dir=gSystem->OpenDirectory(dirName);
  if(!dir) cout<<" No directory found : "<<dirName<<endl;
  else cout<<"It's alive "<<prefix <<"* in directory "<<dirName<<endl;
  TString fileName;
  while( (fileName=(gSystem->GetDirEntry(dir)))){
    if(fileName==TString("")) break;
    if(fileName==TString("."))continue;
    if(fileName==TString(".."))continue;
    if(!fileName.Contains(prefix))continue;
    if(!fileName.Contains(".root"))continue;
  
    Nbins = Nbins+1; //Nbins+=1;
    BinNames.push_back(fileName);

  }
  
  sort (BinNames.begin(), BinNames.end());
 
  cout << Nbins << "  Nbins hereA" << endl;
  cout << BinNames[0]<< endl;

}
