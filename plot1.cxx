#include <cstdlib>
#include <algorithm>                                     
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include "Riostream.h"
#include <fstream>
#include <istream>
#include <strstream>
#include <cstdlib>
#include "TH1D.h"
#include <math.h>


void plot1(){
  double TotalTimeCount = 15.;
  ifstream input_file;
 
  string file = "SCINT1_15s.dat"; 
  input_file.open(file, std::ios::in);
  

  if(!input_file){
    std::cout<<"Error!! Can not open the input file  " << file <<std::endl;
  }
 
  std::string s;
  int a = 0;
  std::vector<float> vthreshold;
  std::vector<float> vcountSr;
  std::vector<float> vcount0;
  while (getline(input_file, s)) {
    a++;
    std::stringstream line(s);
    float threshold;
    float count;
    float count0;
    line >> threshold >> count >> count0;
    vthreshold.push_back(-threshold);
    vcountSr.push_back(count);
    vcount0.push_back(count0);
  }
  float pthreshold[vthreshold.size()];
  float pcount[vthreshold.size()];
  float pcount0[vthreshold.size()];
  float epcount[vthreshold.size()];
  float epcount0[vthreshold.size()];
  float ratio[vthreshold.size()];
  for(int i=0; i<vthreshold.size(); i++){pthreshold[i]=100*vthreshold.at(i);pcount[i]=vcountSr.at(i);
    epcount[i] = sqrt(pcount[i]);pcount0[i]=vcount0.at(i);epcount0[i]=sqrt(pcount0[i]); ratio[i]=pcount0[i]/pcount[i];}
  TGraphErrors *gr1 = new TGraphErrors(vthreshold.size(),pthreshold,pcount,0,epcount);
  gr1->GetXaxis()->SetTitle("Threshold, [mV])");
  gr1->GetYaxis()->SetTitle("counts per sec");
  gr1->SetTitle("Threshold scan, SCINT1, PMT V = 908 mV ");
  
  gr1->SetFillColor(1);
  gr1->SetMarkerColor(2);
  gr1->SetMarkerStyle(22);
  gr1->SetName("gr1");
  gr1->Draw("AP");

  TGraphErrors *gr2 = new TGraphErrors(vthreshold.size(),pthreshold,pcount0,0,epcount);
  gr2->SetFillColor(1);
  gr2->SetMarkerColor(3);
  gr2->SetMarkerStyle(21);
  gr2->SetName("gr2");
  gr2->Draw("P SAME");

  auto legend = new TLegend(0.5,0.7,0.9,0.9);
  legend->AddEntry("gr2","Sr source","lep");
  legend->AddEntry("gr1","No Source","lep");
  legend->Draw();


  TCanvas *c = new TCanvas("c","c",100,100,400,400);
  TGraphErrors *gr3 = new TGraphErrors(vthreshold.size(),pthreshold,ratio,0,0);
  gr3->GetXaxis()->SetTitle("Threshold, [mV])");
  gr3->GetYaxis()->SetTitle("Noise/Signale rate");
  gr3->SetTitle("Threshold scan, SCINT1, PMT V = 908 mV ");
  gr3->GetXaxis()->SetRangeUser(0,2000);
  gr3->GetYaxis()->SetRangeUser(0,1);
  gr3->Draw("ACP");


}
