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


void plot2(){
  double TotalTimeCount = 15.;
  ifstream input_file1;
  ifstream input_file2;
 
  string file_1 = "Counts_SCINT2_NoSource_15s.dat";  string file_2 = "Counts_SCINT2_SrSource_15s.dat";
  input_file1.open(file_1, std::ios::in);
  input_file2.open(file_2, std::ios::in);
  

  if(!input_file1){
    std::cout<<"Error!! Can not open the input file  " << file_1 <<std::endl;
  }
   if(!input_file2){
     std::cout<<"Error!! Can not open the input file  " <<  file_2<< std::endl;
  }
  
 
 
  std::string s1;
  int a1 = 0;
  // TVectorF vthreshold;  TVectorF vcount;
   std::vector<float> vthreshold1;
   std::vector<float> vcount1;
  while (getline(input_file1, s1)) {
    a1++;
    std::stringstream line(s1);
    float threshold;
    float count;
    line >> threshold >> count;
    //   std::cout<<" count  "<<count <<std::endl;
    vthreshold1.push_back(-threshold);
    vcount1.push_back(count);
  }
  std::string s2;
  int a2 = 0;
  // TVectorF vthreshold;  TVectorF vcount;
   std::vector<float> vthreshold2;
   std::vector<float> vcount2;
  while (getline(input_file2, s2)) {
    a2++;
    std::stringstream line(s2);
    float threshold;
    float count;
    line >> threshold >> count;
  
    vthreshold2.push_back(-threshold);
   
    vcount2.push_back(count);
  }
 
  int size1 = vthreshold1.size();

  float pthreshold1[size1];
  float pcount1[size1];
  float epcount1[size1];

  for(int i=0; i<size1; i++){pthreshold1[i]=vthreshold1.at(i);pcount1[i]=vcount1.at(i);epcount1[i] = sqrt(pcount1[i]);}
  TGraphErrors *gr1 = new TGraphErrors(size1,pthreshold1,pcount1,0,epcount1);
  gr1->GetXaxis()->SetTitle("Threshold, [mV])");
  gr1->GetYaxis()->SetTitle("counts per sec");
  gr1->SetTitle("Threshold scan, SCINT2, PMT V = 890 mV ");
  // gr1->GetXaxis()->SetRangeUser(-0.2,1.4);
  // gr1->GetYaxis()->SetRangeUser(0,20000);

  
  gr1->SetFillColor(1);
  gr1->SetMarkerColor(2);
  gr1->SetMarkerStyle(22);

  gr1->Draw("AP");

  int size2 = vthreshold2.size();
  
  float pthreshold2[size2];
  float pcount2[size2];
  float epcount2[size2];
  float ratio[size2];
  for(int i=0; i<size2; i++){pthreshold2[i]=vthreshold2.at(i);pcount2[i]=vcount2.at(i);epcount2[i] = sqrt(pcount2[i]);ratio[i] = pcount1[i]/pcount2[i];}
  TGraphErrors *gr2 = new TGraphErrors(size2,pthreshold2,pcount2,0,epcount2);
  //  gr2->GetYaxis()->SetRangeUser(0,1000);
  
  
  gr2->SetFillColor(1);
  gr2->SetMarkerColor(3);
  gr2->SetMarkerStyle(21);
  gr2->Draw("P SAME");


  auto legend = new TLegend(0.5,0.7,0.9,0.9);
  legend->AddEntry("gr2","Sr source","lep");
  legend->AddEntry("gr1","No Source","lep");
  legend->Draw();


  TCanvas *c = new TCanvas("c","c",100,100,400,400);
  TGraphErrors *gr3 = new TGraphErrors(size2,pthreshold2,ratio,0,0);
  gr3->GetXaxis()->SetTitle("Threshold, [mV])");
  gr3->GetYaxis()->SetTitle("Noise/Signale rate");
  gr3->SetTitle("Threshold scan, SCINT2, PMT V = 890 mV ");
  gr3->GetXaxis()->SetRangeUser(0,20);
  gr3->GetYaxis()->SetRangeUser(0,1);
  gr3->Draw("ACP");



  
}
