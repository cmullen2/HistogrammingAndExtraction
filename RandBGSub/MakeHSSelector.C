/** \file MakeHSSelector.C
 * 
 * Macro to generate a TSelector
 * using the THSSkeleton class
 * 
 * Usage:
 * root -l \<file containing tree> \--hssel '$HSANA/../MakeHSSelector/MakeHSSelector.C(\<treename>)'
 * 
 */

void MakeHSSelector(TString treeName = "tree"){
	
	THSSkeleton* sk = new THSSkeleton();
	
	sk->SetHisto();   //Going to make histograms
	sk->SetNewTree();   //Going to make new tree
	sk->SetWeights(); //Going to create weight structures
	
//	sk->SetLPS(3); //Add longitudinal phase space class
	
//	sk->SetFinalState("pKK");
	
//	sk->SetFinalStateTopo("proton:K+:K-"); //add topology where all three particles are detected
//	sk->SetFinalStateParts("Proton:proton,KPlus:K+,KMinus:K-"); //set final state particles <name:pdgname>
//	sk->CreateMyFinalState(); //create a project class
	
//	sk->SetFinalState("THSpKK"); //CreateMyFinalState() adds a THS in front of the name. To use the same class directly reset fFinalName here.
	
	sk->CreateSelector("THSRandBG_vh",_file0->GetName(),treeName,""); //create selector with all specifications
	
}
