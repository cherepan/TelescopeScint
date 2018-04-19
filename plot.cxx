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


void plot(){

  ifstream input_file;
  string file_ = "values.dat";
  input_file.open(file_, std::ios::in);
  

  if(!input_file){
    std::cout<<"Error!! Can not open the inputi file" << std::endl;
  }
  
  std::string s;
  int a = 0;
  // TVectorF vthreshold;  TVectorF vcount;
   std::vector<float> vthreshold;
   std::vector<float> vcount;
  while (getline(input_file, s)) {
    a++;
    std::stringstream line(s);
    float threshold;
    float count;
    line >> threshold >> count;
  
    vthreshold.push_back(-threshold - 3);
    vcount.push_back(count);
  }


  int size = vthreshold.size();

  float pthreshold[size];
  float pcount[size];
  float epcount[size];

  for(int i=0; i<size; i++){pthreshold[i]=vthreshold.at(i);pcount[i]=vcount.at(i);epcount[i] = sqrt(pcount[i]);}
  TGraphErrors *gr = new TGraphErrors(size,pthreshold,pcount,0,epcount);
  gr->GetXaxis()->SetTitle("Threshold, [mV])");
  gr->GetYaxis()->SetTitle("counts #");
  gr->SetTitle("Threshold scan (30s count time)");
  gr->GetXaxis()->SetRangeUser(-0.2,1.4);
  gr->GetYaxis()->SetRangeUser(0,1000);

  gr->Draw("AP*");
  gr->SetFillColor(1);
  gr->SetMarkerColor(2);
  gr->SetMarkerStyle(3);

}
