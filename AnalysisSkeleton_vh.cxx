#include "AnalysisSkeleton.hxx"
#include <iostream>
#include "TCanvas.h"
#include "TH2.h"

using namespace std;

void AnalysisSkeleton::Loop()
{
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0, NSide = 2 , NRoDID = 12, NTrgSec = 4;
  
  cerr << "NEvents_bcid ="<< fChain->GetEntries("tgcsl_tilecalobits0_bcid") << endl;
  cerr << "NEvents_bcid ="<< fChain->GetEntries("tgcsl_correspondingtile0_bcid") << endl;
  TCanvas *c1 = new TCanvas("c1","hist_TSN_BCIDdif", 1600, 1200);
  TH2D *hist_TSN_BCIDdif = new TH2D ("hist_TSN_BCIDdif", "RunNumber=", 96, 0, 96, 3, 0, 3);
  int RunNumber = 0;
  
  for (Long64_t jentry = 0; jentry < nentries ; jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    // Analysis code here
    //      for (Long64_t SideNum = 0; SideNum < NSide ; SideNum++){
      //	for (Long64_t TrgSecNum = 0; TrgSecNum < NTrgSec < 4; TrgSecNum++){
    /*
      if(){
      SideNum = 1;
      };
      else{
      SideNum = 2;
      };
    */
    //	  double TGCSec = SideNum * TrgSecNum * (tgcsl_rodid&0x000000FF);
    double TGCSec = 0.;
    //	  cerr << "test=100,entry="  << ientry << endl;
	  
    //Fill data
    //if(tgcsl_tilecalobits0_bcid - tgcsl_correspondingtile0_bcid != 0){
    //hist_TSN_BCIDdif->Fill(TGCSec,1.0);
    //}
    
    for (int iTgcSlRod=0,nTgcSlRods=tgcsl_rod_bcid->size(); iTgcSlRod<nTgcSlRods; iTgcSlRod++) {
      const unsigned int& rodid = tgcsl_rodid->at(iTgcSlRod);
      const unsigned int& bctiming = tgcsl_bctiming->at(iTgcSlRod);
      if (bctiming!=1) {continue;}
      const unsigned int sector   = (rodid&0x000000FF);
      const unsigned int sourceid = ((rodid&0x00FF0000)>>16);
      const bool isAside = (sourceid==0X67);
      
      const unsigned int& tilebcid0 = tgcsl_correspondingtile0_bcid->at(iTgcSlRod);
      const unsigned int& tgcbcid0  = tgcsl_tilecalobits0_bcid->at(iTgcSlRod);
      const unsigned int& tilebcid1 = tgcsl_correspondingtile1_bcid->at(iTgcSlRod);
      const unsigned int& tgcbcid1  = tgcsl_tilecalobits1_bcid->at(iTgcSlRod);
      const unsigned int& tilebcid2 = tgcsl_correspondingtile2_bcid->at(iTgcSlRod);
      const unsigned int& tgcbcid2  = tgcsl_tilecalobits2_bcid->at(iTgcSlRod);
      const unsigned int& tilebcid3 = tgcsl_correspondingtile3_bcid->at(iTgcSlRod);
      const unsigned int& tgcbcid3  = tgcsl_tilecalobits3_bcid->at(iTgcSlRod);
      const int dif0 = tilebcid0-tgcbcid0;
      const int dif1 = tilebcid1-tgcbcid1;
      const int dif2 = tilebcid2-tgcbcid2;
      const int dif3 = tilebcid3-tgcbcid3;
      // cout << "Event = " << jentry << ", sector =  " << sector
      // 	   << " " << Form("0x%08x", rodid) << " " << bctiming << " " << (isAside ? "A" : "C" )
      // 	   << " 0:" << dif0 << ",1:" << dif1 << ",2:" << dif2 << ",3:" << dif3 << endl;
      printf("Event=%2u Side=%s Sector=%2u [0:%2d, 1:%2d, 2:%2d, 3:%2d]\n",
	     jentry, (isAside ? "A" : "C" ), sector, dif0, dif1, dif2, dif3);
    }
    
    //Fill data
    //	}
    //    }
  }
  
  //
  c1->cd();
  hist_TSN_BCIDdif->Draw("colz");
  c1->Print();
  c1->SaveAs("hist_RunNumber.pdf");    
  //
}
