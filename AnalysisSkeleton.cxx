#include "AnalysisSkeleton.hxx"
#include "SetAtlasStyle.hxx"
#include <iostream>
#include <stdio.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <vector>
#include <string>
#include <THStack.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLatex.h>

TLatex GetAtlaslabel(const double x, const double y, std::string label);
void SetAtlasStyle();


void AnalysisSkeleton::Loop()
{
  SetAtlasStyle();
  
  TGraph a_Aside;
  TGraph b_Aside;
  TGraph c_Aside;
  TGraph total_Aside;

  TGraph a_Cside;
  TGraph b_Cside;
  TGraph c_Cside;
  TGraph total_Cside;

  a_Aside.SetMarkerColor(kBlack);// a_Aside.SetLineColor(kBlack);
  c_Aside.SetMarkerColor(kBlue);// b_Aside.SetLineColor(kBlue);
  b_Aside.SetMarkerColor(kRed);// c_Aside.SetLineColor(kRed);
  total_Aside.SetMarkerColor(kGreen);

  a_Aside.SetMarkerStyle(8);
  c_Aside.SetMarkerStyle(8);
  b_Aside.SetMarkerStyle(8);
  total_Aside.SetMarkerStyle(8);

  a_Aside.SetMarkerSize(0.7);
  b_Aside.SetMarkerSize(0.7);
  c_Aside.SetMarkerSize(0.7);
  total_Aside.SetMarkerSize(0.7);

//   a_Aside.SetLineStyle(2);
//   b_Aside.SetLineStyle(2);
//   c_Aside.SetLineStyle(2);
  

  a_Cside.SetMarkerColor(kBlack);// a_Cside.SetLineColor(kBlack);
  c_Cside.SetMarkerColor(kBlue);// b_Cside.SetLineColor(kBlue);
  b_Cside.SetMarkerColor(kRed);// c_Cside.SetLineColor(kRed);
  total_Cside.SetMarkerColor(kBlack);
  
  a_Cside.SetMarkerStyle(8);
  b_Cside.SetMarkerStyle(8);
  c_Cside.SetMarkerStyle(8);
  total_Cside.SetMarkerStyle(8);

  a_Cside.SetMarkerSize(0.7);
  b_Cside.SetMarkerSize(0.7);
  c_Cside.SetMarkerSize(0.7);
  total_Cside.SetMarkerSize(0.7);

//   a_Cside.SetLineStyle(2);
//   b_Cside.SetLineStyle(2);
//   c_Cside.SetLineStyle(2);

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  const int totalNumberOfSides=2;
  const int totalNumberOfRods=48;
  TH2D h2("TMDB-TGC","TMDB-TGC",96,0,96,140,-70,70);
  TH2D h2_0("TMDB_curr-TGC_prev","TMDB_curr-TGC_prev",96,0,96,140,-70,70);
  TH2D h2_2("TMDB_curr-TGC_next","TMDB_curr-TGC_next",96,0,96,140,-70,70);
  TH1D EC("title","title",96,-0.5,95.5);  

  TH1D *h1_0_A = new TH1D("title","title",48,-0.5,47.5);
  h1_0_A->SetFillColor(kRed);
  TH1D *h1_0_C = new TH1D("title","title",48,-0.5,47.5);
  h1_0_C->SetFillColor(kRed);
 
  TH1D *h1_1_A = new TH1D("title","title",48,-0.5,47.5);
  h1_1_A->SetFillColor(kBlack);
  TH1D *h1_1_C = new TH1D("title","title",48,-0.5,47.5);
  h1_1_C->SetFillColor(kBlack);
 
  TH1D *h1_2_A = new TH1D("title","title",48,-0.5,47.5);
  h1_2_A->SetFillColor(kBlue);
  TH1D *h1_2_C = new TH1D("title","title",48,-0.5,47.5);
  h1_2_C->SetFillColor(kBlue);

  TH1D *h1_other_A = new TH1D("title","title",48,-0.5,47.5);
  h1_other_A->SetFillColor(kYellow); 
  TH1D *h1_other_C = new TH1D("title","title",48,-0.5,47.5);
  h1_other_C->SetFillColor(kYellow); 
 
  std::vector<TH1D> hv;
  std::vector<TH1D> hv2;

  std::vector<double> numberOfdiff0_0Events(96,0);
  std::vector<double> numberOfdiff1_0Events(96,0);
  std::vector<double> numberOfdiff2_0Events(96,0);
  std::vector<double> numberOfdiff3_0Events(96,0);
  
  std::vector<double> numberOfcurr0_0Events(96,0);
  std::vector<double> numberOfcurr1_0Events(96,0);
  std::vector<double> numberOfcurr2_0Events(96,0);
  std::vector<double> numberOfcurr3_0Events(96,0);
  
  std::vector<double> numberOfprev0_0Events(96,0);
  std::vector<double> numberOfprev1_0Events(96,0);
  std::vector<double> numberOfprev2_0Events(96,0);
  std::vector<double> numberOfprev3_0Events(96,0);
    
  std::vector<double> numberOf0_0Event(96,0);    
  std::vector<double> numberOf1_0Event(96,0);
  std::vector<double> numberOf2_0Event(96,0);
  std::vector<double> numberOf3_0Event(96,0);
    
  std::vector<int> otherEvent0(96,0);
  std::vector<int> otherEvent1(96,0);
  std::vector<int> otherEvent2(96,0);
  std::vector<int> otherEvent3(96,0);

  

  for (int kk=0; kk<totalNumberOfSides; kk++) {
    for (int ii=0; ii<totalNumberOfRods; ii++) {
      std::string sideName = "A";
      if (kk==1) {sideName = "C";}
      const std::string name = Form("h_%s_%d", sideName.c_str(), ii);
      TH1D dummy1(name.c_str(), name.c_str(), 200, -100.5, 99.5);
      hv.push_back(dummy1);
    }
  }
  
  
  
  Long64_t nbytes = 0, nb = 0;
  // event loop
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    //    std::cout << Form("%2llu th event is being processed", jentry)<< std::endl;
    
    for (int iRod=0, nRods=tgcsl_rodid->size(); iRod<nRods; iRod++) {
      const unsigned int sector   = (tgcsl_rodid->at(iRod) & 0X000000FF);
      const unsigned int bctiming = tgcsl_bctiming->at(iRod);
      const bool isAside = ( ((tgcsl_rodid->at(iRod) & 0X00FF0000)>>16)==0X67);
      int offset = 0;
      if (!isAside) { offset = 48; }
      if(bctiming!=1){continue;}
       
      if(tgcsl_tilecalobits0_bcid->at(iRod)>4000000){tgcsl_tilecalobits0_bcid->at(iRod)=0;}       
      if(tgcsl_tilecalobits1_bcid->at(iRod)>4000000){tgcsl_tilecalobits1_bcid->at(iRod)=0;}       
      if(tgcsl_tilecalobits2_bcid->at(iRod)>4000000){tgcsl_tilecalobits2_bcid->at(iRod)=0;}       
      if(tgcsl_tilecalobits3_bcid->at(iRod)>4000000){tgcsl_tilecalobits3_bcid->at(iRod)=0;}
      
      if(tgcsl_tilecalobits0_bcid->at(iRod+1)>4000000){tgcsl_tilecalobits0_bcid->at(iRod+1)=0;}       
      if(tgcsl_tilecalobits1_bcid->at(iRod+1)>4000000){tgcsl_tilecalobits1_bcid->at(iRod+1)=0;}       
      if(tgcsl_tilecalobits2_bcid->at(iRod+1)>4000000){tgcsl_tilecalobits2_bcid->at(iRod+1)=0;}       
      if(tgcsl_tilecalobits3_bcid->at(iRod+1)>4000000){tgcsl_tilecalobits3_bcid->at(iRod+1)=0;}
      
      if(tgcsl_tilecalobits0_bcid->at(iRod-1)>4000000){tgcsl_tilecalobits0_bcid->at(iRod-1)=0;}       
      if(tgcsl_tilecalobits1_bcid->at(iRod-1)>4000000){tgcsl_tilecalobits1_bcid->at(iRod-1)=0;}       
      if(tgcsl_tilecalobits2_bcid->at(iRod-1)>4000000){tgcsl_tilecalobits2_bcid->at(iRod-1)=0;}       
      if(tgcsl_tilecalobits3_bcid->at(iRod-1)>4000000){tgcsl_tilecalobits3_bcid->at(iRod-1)=0;}
       

      int diff0 = (tgcsl_correspondingtile0_bcid->at(iRod)-tgcsl_tilecalobits0_bcid->at(iRod));
      int diff1 = (tgcsl_correspondingtile1_bcid->at(iRod)-tgcsl_tilecalobits1_bcid->at(iRod));
      int diff2 = (tgcsl_correspondingtile2_bcid->at(iRod)-tgcsl_tilecalobits2_bcid->at(iRod));
      int diff3 = (tgcsl_correspondingtile3_bcid->at(iRod)-tgcsl_tilecalobits3_bcid->at(iRod));
      
      int diff0_0 = (tgcsl_correspondingtile0_bcid->at(iRod)-tgcsl_tilecalobits0_bcid->at(iRod-1));
      int diff0_2 = (tgcsl_correspondingtile0_bcid->at(iRod)-tgcsl_tilecalobits0_bcid->at(iRod+1));      

      int diff1_0 = (tgcsl_correspondingtile1_bcid->at(iRod)-tgcsl_tilecalobits1_bcid->at(iRod-1));
      int diff1_2 = (tgcsl_correspondingtile1_bcid->at(iRod)-tgcsl_tilecalobits1_bcid->at(iRod+1));

      int diff2_0 = (tgcsl_correspondingtile2_bcid->at(iRod)-tgcsl_tilecalobits2_bcid->at(iRod-1));
      int diff2_2 = (tgcsl_correspondingtile2_bcid->at(iRod)-tgcsl_tilecalobits2_bcid->at(iRod+1));     

      int diff3_0 = (tgcsl_correspondingtile3_bcid->at(iRod)-tgcsl_tilecalobits3_bcid->at(iRod-1));
      int diff3_2 = (tgcsl_correspondingtile3_bcid->at(iRod)-tgcsl_tilecalobits3_bcid->at(iRod+1));     

      //       if(abs(diff0)==1 || abs(diff0)==2 || abs(diff0)==4 || abs(diff0)==8 || abs(diff0)==16 || abs(diff0)==32){
      //         diff0 = 0;
      //       }
      //       if(abs(diff1)==1 || abs(diff1)==2 || abs(diff1)==4 || abs(diff1)==8 || abs(diff1)==16 || abs(diff1)==32){
      //         diff1 = 0;
      //       }
      //       if(abs(diff2)==1 || abs(diff2)==2 || abs(diff2)==4 || abs(diff2)==8 || abs(diff2)==16 || abs(diff2)==32){
      //         diff2 = 0;
      //       }
      //       if(abs(diff3)==1 || abs(diff3)==2 || abs(diff3)==4 || abs(diff3)==8 || abs(diff3)==16 || abs(diff3)==32){
      //         diff3 = 0;
      //       }
      

      //
     
      const int index0 = offset + ((sector-1)*4) + 0;
      const int index1 = offset + ((sector-1)*4) + 1;
      const int index2 = offset + ((sector-1)*4) + 2;
      const int index3 = offset + ((sector-1)*4) + 3;

      const int subindex0 =   ((sector-1)*4) + 0;
      const int subindex1 =   ((sector-1)*4) + 1;
      const int subindex2 =   ((sector-1)*4) + 2;
      const int subindex3 =   ((sector-1)*4) + 3;
      


        if(tgcsl_correspondingtile0_bcid->at(iRod)!=0){
	  EC.Fill(index0);
	  hv.at(index0).Fill(diff0);
	  h2.Fill(index0,diff0);
	}
	
	if(tgcsl_correspondingtile1_bcid->at(iRod)!=0){ 
	  EC.Fill(index1);
	  hv.at(index1).Fill(diff1);
	  h2.Fill(index1,diff1);
 	}

	if(tgcsl_correspondingtile2_bcid->at(iRod)!=0){ 
	  EC.Fill(index2);
	  hv.at(index2).Fill(diff2);
	  h2.Fill(index2,diff2);
	}

	if(tgcsl_correspondingtile3_bcid->at(iRod)!=0){ 
	  EC.Fill(index3);
	  hv.at(index3).Fill(diff3);
	  h2.Fill(index3,diff3);
	}
	

	if(diff0!=0){
	  h2_0.Fill(index0,diff0_0);
	  if(diff0_0!=0){
	    h2_2.Fill(index0,diff0_2);
	  }     
	}
	
	if(diff1!=0){
	  h2_0.Fill(index1,diff1_0);
	  if(diff1_0!=0){	
	    h2_2.Fill(index1,diff1_2);
	  }          
	}         
	
	if(diff2!=0){
	  h2_0.Fill(index2,diff2_0);
	  if(diff2_0!=0){	
	    h2_2.Fill(index2,diff2_2);          
	  }
	}
	
	if(diff3!=0){
	  h2_0.Fill(index3,diff3_0);
	  if(diff3_0!=0){
	    h2_2.Fill(index3,diff3_2);          
	  }
	}
	
	


	if(tgcsl_correspondingtile0_bcid->at(iRod)!=0){
	  if(diff0==0){
	    numberOfdiff0_0Events.at(iRod)++;
	    if(isAside){
	      h1_1_A->Fill(subindex0);
	    }
	    if(!isAside){
	      h1_1_C->Fill(subindex0);
	    }
	    
	  }else if(diff0_0==0){
	    numberOfcurr0_0Events.at(iRod)++;
	    if(isAside){
	      h1_0_A->Fill(subindex0);
	    }
	    if(!isAside){
	      h1_0_C->Fill(subindex0);
	    }

	  }else if(diff0_2==0){
	    numberOfprev0_0Events.at(iRod)++;
	    if(isAside){
	      h1_2_A->Fill(subindex0);
	    }
	    if(!isAside){
	      h1_2_C->Fill(subindex0);
	    }
	    
	  }else{
	    otherEvent0.at(iRod)++;
	    if(isAside){
	      h1_other_A->Fill(subindex0);
	    }
	    if(!isAside){
	      h1_other_C->Fill(subindex0);
	    }
	    
	  }
	}
	
	if(tgcsl_correspondingtile1_bcid->at(iRod)!=0){
	  if(diff1==0){
	    numberOfdiff1_0Events.at(iRod)++;
	    if(isAside){
	      h1_1_A->Fill(subindex1);
	    }
	    if(!isAside){
	      h1_1_C->Fill(subindex1);
	    }
	    
	  }else if(diff1_0==0){
	    numberOfcurr1_0Events.at(iRod)++;
	    if(isAside){
	      h1_0_A->Fill(subindex1);
	    }
	    if(!isAside){
	      h1_0_C->Fill(subindex1);
	    }
	    
	  }else if(diff1_2==0){
	    numberOfprev1_0Events.at(iRod)++;
	    if(isAside){
	      h1_2_A->Fill(subindex1);
	    }
	    if(!isAside){
	      h1_2_C->Fill(subindex1);
	    }

	  }else{
	    otherEvent1.at(iRod)++;
	    if(isAside){
	      h1_other_A->Fill(subindex1);
	    }
	    if(!isAside){
	      h1_other_C->Fill(subindex1);
	    }
	    
	  }
	}
	
	if(tgcsl_correspondingtile2_bcid->at(iRod)!=0){
	  if(diff2==0){
	    numberOfdiff2_0Events.at(iRod)++;
	    if(isAside){
	      h1_1_A->Fill(subindex2);
	    }
	    if(!isAside){
	      h1_1_C->Fill(subindex2);
	    }
	    
	  }else if(diff2_0==0){
	    numberOfcurr2_0Events.at(iRod)++;
	    if(isAside){
	      h1_0_A->Fill(subindex2);
	    }
	    if(!isAside){
	      h1_0_C->Fill(subindex2);
	    }
	    
	  }else if(diff2_2==0){
	    numberOfprev2_0Events.at(iRod)++;
	    if(isAside){
	      h1_2_A->Fill(subindex2);
	    }
	    if(!isAside){
	      h1_2_C->Fill(subindex2);
	    }
	    
	  }else{
	    otherEvent2.at(iRod)++;
	    if(isAside){
	      h1_other_A->Fill(subindex2);
	    }
	    if(!isAside){
	      h1_other_C->Fill(subindex2);
	    }

	  }
	}
	
	if(tgcsl_correspondingtile3_bcid->at(iRod)!=0){      
	  if(diff3==0){
	    numberOfdiff3_0Events.at(iRod)++;
	    if(isAside){
	      h1_1_A->Fill(subindex3);
	    }
	    if(!isAside){
	      h1_1_C->Fill(subindex3);
	    }
	    
	  }else if(diff3_0==0){
	    numberOfcurr3_0Events.at(iRod)++;
	    if(isAside){
	      h1_0_A->Fill(subindex3);
	    }
	    if(!isAside){
	      h1_0_C->Fill(subindex3);
	    }

	  }else if(diff3_2==0){
	    numberOfprev3_0Events.at(iRod)++;
	    if(isAside){
	      h1_2_A->Fill(subindex3);
	    }
	    if(!isAside){
	      h1_2_C->Fill(subindex3);
	    }

	  }else{
	    otherEvent3.at(iRod)++;
	    if(isAside){
	      h1_other_A->Fill(subindex3);
	    }
	    if(!isAside){
	      h1_other_C->Fill(subindex3);
	    }

	  }
	}
		
	//	if(numberOfdiff0_0Events.at(iRod)+numberOfcurr0_0Events.at(iRod)+numberOfprev0_0Events.at(iRod)+otherEvent0.at(iRod)!=0){
	double curr0 = numberOfdiff0_0Events.at(iRod)/(numberOfdiff0_0Events.at(iRod)+numberOfcurr0_0Events.at(iRod)+numberOfprev0_0Events.at(iRod)+otherEvent0.at(iRod));
	double prev0 = numberOfcurr0_0Events.at(iRod)/(numberOfdiff0_0Events.at(iRod)+numberOfcurr0_0Events.at(iRod)+numberOfprev0_0Events.at(iRod)+otherEvent0.at(iRod));
	double next0 = numberOfprev0_0Events.at(iRod)/(numberOfdiff0_0Events.at(iRod)+numberOfcurr0_0Events.at(iRod)+numberOfprev0_0Events.at(iRod)+otherEvent0.at(iRod));
	double total0 = curr0+prev0+next0;    
	if(isAside){   
	  a_Aside.SetPoint(subindex0, subindex0, curr0);    
	  b_Aside.SetPoint(subindex0, subindex0, prev0);
	  c_Aside.SetPoint(subindex0, subindex0, next0);
	  total_Aside.SetPoint(subindex0, subindex0, total0);    
	}
	if(!isAside){
	  a_Cside.SetPoint(subindex0, subindex0, curr0);    
	  b_Cside.SetPoint(subindex0, subindex0, prev0);
	  c_Cside.SetPoint(subindex0, subindex0, next0);
	  total_Cside.SetPoint(subindex0, subindex0, total0);    
	}    
	//  }  
	
	  //	if(numberOfdiff1_0Events.at(iRod)+numberOfcurr1_0Events.at(iRod)+numberOfprev1_0Events.at(iRod)+otherEvent1.at(iRod)!=0){
	double curr1 = numberOfdiff1_0Events.at(iRod)/(numberOfdiff1_0Events.at(iRod)+numberOfcurr1_0Events.at(iRod)+numberOfprev1_0Events.at(iRod)+otherEvent1.at(iRod));
	double prev1 = numberOfcurr1_0Events.at(iRod)/(numberOfdiff1_0Events.at(iRod)+numberOfcurr1_0Events.at(iRod)+numberOfprev1_0Events.at(iRod)+otherEvent1.at(iRod));
	double next1 = numberOfprev1_0Events.at(iRod)/(numberOfdiff1_0Events.at(iRod)+numberOfcurr1_0Events.at(iRod)+numberOfprev1_0Events.at(iRod)+otherEvent1.at(iRod));
	double total1 = curr1+prev1+next1;    
	if(isAside){   
	  a_Aside.SetPoint(subindex1, subindex1, curr1);    
	  b_Aside.SetPoint(subindex1, subindex1, prev1);
	  c_Aside.SetPoint(subindex1, subindex1, next1);
	  total_Aside.SetPoint(subindex1, subindex1, total1);    
	}
	if(!isAside){
	  a_Cside.SetPoint(subindex1, subindex1, curr1);    
	  b_Cside.SetPoint(subindex1, subindex1, prev1);
	  c_Cside.SetPoint(subindex1, subindex1, next1);
	  total_Cside.SetPoint(subindex1, subindex1, total1);    
	}    
	//	}
	
	  //	if(numberOfdiff2_0Events.at(iRod)+numberOfcurr2_0Events.at(iRod)+numberOfprev2_0Events.at(iRod)+otherEvent2.at(iRod)!=0){
	double curr2 = numberOfdiff2_0Events.at(iRod)/(numberOfdiff2_0Events.at(iRod)+numberOfcurr2_0Events.at(iRod)+numberOfprev2_0Events.at(iRod)+otherEvent2.at(iRod));
	double prev2 = numberOfcurr2_0Events.at(iRod)/(numberOfdiff2_0Events.at(iRod)+numberOfcurr2_0Events.at(iRod)+numberOfprev2_0Events.at(iRod)+otherEvent2.at(iRod));
	double next2 = numberOfprev2_0Events.at(iRod)/(numberOfdiff2_0Events.at(iRod)+numberOfcurr2_0Events.at(iRod)+numberOfprev2_0Events.at(iRod)+otherEvent2.at(iRod));
	double total2 = curr2+prev2+next2;    
	if(isAside){   
	  a_Aside.SetPoint(subindex2, subindex2, curr2);    
	  b_Aside.SetPoint(subindex2, subindex2, prev2);
	  c_Aside.SetPoint(subindex2, subindex2, next2);
	  total_Aside.SetPoint(subindex2, subindex2, total2);    
	}
	if(!isAside){
	  a_Cside.SetPoint(subindex2, subindex2, curr2);    
	  b_Cside.SetPoint(subindex2, subindex2, prev2);
	  c_Cside.SetPoint(subindex2, subindex2, next2);
	  total_Cside.SetPoint(subindex2, subindex2, total2);    
	}    
	//	}
    
	  //	if(numberOfdiff3_0Events.at(iRod)+numberOfcurr3_0Events.at(iRod)+numberOfprev3_0Events.at(iRod)+otherEvent3.at(iRod)!=0){
	double curr3 = numberOfdiff3_0Events.at(iRod)/(numberOfdiff3_0Events.at(iRod)+numberOfcurr3_0Events.at(iRod)+numberOfprev3_0Events.at(iRod)+otherEvent3.at(iRod));
	double prev3 = numberOfcurr3_0Events.at(iRod)/(numberOfdiff3_0Events.at(iRod)+numberOfcurr3_0Events.at(iRod)+numberOfprev3_0Events.at(iRod)+otherEvent3.at(iRod));
	double next3 = numberOfprev3_0Events.at(iRod)/(numberOfdiff3_0Events.at(iRod)+numberOfcurr3_0Events.at(iRod)+numberOfprev3_0Events.at(iRod)+otherEvent3.at(iRod));
	double total3 = curr3+prev3+next3;    
	if(isAside){   
	  a_Aside.SetPoint(subindex3, subindex3, curr3);    
	  b_Aside.SetPoint(subindex3, subindex3, prev3);
	  c_Aside.SetPoint(subindex3, subindex3, next3);
	  total_Aside.SetPoint(subindex3, subindex3, total3);    
	}
	if(!isAside){
	  a_Cside.SetPoint(subindex3, subindex3, curr3);    
	  b_Cside.SetPoint(subindex3, subindex3, prev3);
	  c_Cside.SetPoint(subindex3, subindex3, next3);
	  total_Cside.SetPoint(subindex3, subindex3, total3);    
	}    
	
	  	
	  	 	
	
    }
    
  }
  
  // save
  TFile fout("fout.root", "RECREATE");
  for (int kk=0; kk<totalNumberOfSides; kk++) {
    for (int ii=0; ii<totalNumberOfRods; ii++) {  
      const int indexHist = kk*totalNumberOfRods+ii;
      hv.at(indexHist).Write();
    }
  }
  //test.Write();
  fout.Write();
  
  //save 2D
  TFile fout2("fout2.root","RECREATE");
  h2.Write();
  fout2.Write();  
  
  TCanvas c1;
  c1.Print("output.pdf[");
  for (int kk=0; kk<totalNumberOfSides; kk++) {
    for (int ii=0; ii<totalNumberOfRods; ii++) {  
      const int indexHist = kk*totalNumberOfRods+ii;
      hv.at(indexHist).Draw();
      hv.at(indexHist).SetStats(1);
      c1.Print("output.pdf");
    }
  }
  c1.Print("output.pdf]");
  
  TCanvas c2;
  h2.Draw("colz");
  h2.SetStats(0);  
  c2.Print("output2.pdf");

  TCanvas c2_0;
  h2_0.Draw("colz");
  h2_0.SetStats(0);    
  c2_0.Print("output2_0.pdf");
  
  TCanvas c2_2;
  h2_2.Draw("colz");
  h2_2.SetStats(0);
  c2_2.Print("output2_2.pdf");

  TCanvas cEC;
  EC.Draw();
  cEC.Print("output_EC.pdf");
  

  TCanvas c3_A;
  THStack *hs_A = new THStack("hs","test");
  hs_A->Add(h1_0_A);
  hs_A->Add(h1_1_A);
  hs_A->Add(h1_2_A);
  hs_A->Add(h1_other_A);
  hs_A->Draw();
  c3_A.Print("output3_A.pdf");  

  TCanvas c3_C;
  THStack *hs_C = new THStack("hs","test");
  hs_C->Add(h1_0_C);
  hs_C->Add(h1_1_C);
  hs_C->Add(h1_2_C);
  hs_C->Add(h1_other_C);
  hs_C->Draw();
  c3_C.Print("output3_C.pdf");  

  //count number of events
  
  

        
   
    
    
  
  //Aside
  
  TCanvas c5_Aside;
  
  TH2D waku_Aside("waku", "", 1, -0.5, 47.5, 1, 0, 1.1);
  waku_Aside.GetXaxis()->SetTitle("TGC Trigger Sector");
  waku_Aside.GetYaxis()->SetTitle("Good Event rate");

  waku_Aside.Draw();
  c_Aside.Draw("P");
  b_Aside.Draw("P");
  a_Aside.Draw("P");
  
  TLegend leg_Aside(0.77, 0.3, 0.97, 0.55);
  leg_Aside.SetLineWidth(0);
  leg_Aside.SetFillColor(0);
  leg_Aside.AddEntry(&a_Aside, "Current", "P");
  leg_Aside.AddEntry(&b_Aside, "Previous", "P");
  leg_Aside.AddEntry(&c_Aside, "Next", "P");
  leg_Aside.Draw();
  
  TLatex label_Aside = GetAtlaslabel(0.77, 0.55, "Internal");
  label_Aside.Draw();
  
  c5_Aside.Print("example_Aside.pdf");

  TCanvas c5_total_Aside;
  
  TH2D waku_total_Aside("waku", "", 1, -0.5, 47.5, 1, 0.9, 1.05);
  waku_total_Aside.GetXaxis()->SetTitle("TGC Trigger Sector");
  waku_total_Aside.GetYaxis()->SetTitle("Good Event rate");

  waku_total_Aside.Draw();
  total_Aside.Draw("P");
  
//   TLegend leg_total_Aside(0.77, 0.3, 0.97, 0.55);
//   leg_total_Aside.SetLineWidth(0);
//   leg_total_Aside.SetFillColor(0);
//   leg_total_Aside.AddEntry(&total_Aside, "total", "P");
//   leg_total_Aside.Draw();
  
//  TLatex label_total_Aside = GetAtlaslabel(0.77, 0.55, "Internal");
//  label_total_Aside.Draw();
  
  c5_total_Aside.Print("example_total_Aside.pdf");

  //Cside
  TCanvas c5_Cside;
  
  TH2D waku_Cside("waku", "", 1, -0.5, 47.5, 1, 0, 1.1);
  waku_Cside.GetXaxis()->SetTitle("TGC Trigger Sector");
  waku_Cside.GetYaxis()->SetTitle("Good Event rate");

  waku_Cside.Draw();
  c_Cside.Draw("P");
  b_Cside.Draw("P");
  a_Cside.Draw("P");
  
  TLegend leg_Cside(0.77, 0.3, 0.97, 0.55);
  leg_Cside.SetLineWidth(0);
  leg_Cside.SetFillColor(0);
  leg_Cside.AddEntry(&a_Cside, "Current", "P");
  leg_Cside.AddEntry(&b_Cside, "Previous", "P");
  leg_Cside.AddEntry(&c_Cside, "Next", "P");
  leg_Cside.Draw();
  
  TLatex label_Cside = GetAtlaslabel(0.77, 0.55, "Internal");
  label_Cside.Draw();
  
  c5_Cside.Print("example_Cside.pdf");

  TCanvas c5_total_Cside;
  
  TH2D waku_total_Cside("waku", "", 1, -0.5, 47.5, 1, 0.9, 1.05);
  waku_total_Cside.GetXaxis()->SetTitle("TGC Trigger Sector");
  waku_total_Cside.GetYaxis()->SetTitle("Good event rate");

  waku_total_Cside.Draw();
  total_Cside.Draw("P");
  
//   TLegend leg_total_Cside(0.77, 0.3, 0.97, 0.55);
//   leg_total_Cside.SetLineWidth(0);
//   leg_total_Cside.SetFillColor(0);
//   leg_total_Cside.AddEntry(&total_Cside, "total", "P");
//   leg_total_Cside.Draw();
  
//  TLatex label_total_Cside = GetAtlaslabel(0.77, 0.55, "Internal");
//  label_total_Cside.Draw();
  
  c5_total_Cside.Print("example_total_Cside.pdf");

}
  
