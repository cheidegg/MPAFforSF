#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <iterator>
#include <math.h>
#include <stdlib.h>
#include <complex>

using namespace std;

int main() {
  
 ifstream fDb( "logJES", ios::in );

  string line;
  string dsName;

  map<string, vector<pair<string, float> > > vMap;
  
  while(getline(fDb, line)) {

    istringstream iss(line);
    vector<string> tks;
    copy(istream_iterator<string>(iss),
	 istream_iterator<string>(),
	 back_inserter<vector<string> >(tks));
    // cout<<line<<"  "<<tks.size()<<endl;
    if(tks.size()==0) continue;
    if(tks.size()==4) dsName=tks[1];
    else {
      
      string SR=tks[0];
      float y=atof(tks[1].c_str());
      float ey=atof(tks[3].c_str());
      
      float eyl, eyh;
      if(tks.size()==10) {
	eyl = atof(tks[5].c_str());
      	eyh = atof(tks[5].c_str());
      }
      else {
	eyh = atof(tks[5].c_str());
      	eyl = atof(tks[7].c_str());
      }
    
      //float unc=(std::abs(eyl)+std::abs(eyh))/2.;
      //float unc=max(std::abs(eyl),std::abs(eyh));
      float unc=eyh;
      if(unc==0) unc=10.;
      vector<pair<string, float> > map;
      if(vMap.find(dsName)==vMap.end())
	vMap[ dsName ]=map;

      vMap[dsName].push_back(make_pair(SR, unc));
    }
  }
  cout<<" file read"<<endl;
  map<string, vector<pair<string, float> > >::const_iterator it;
  for(it=vMap.begin();it!=vMap.end();++it) {
    cout<<"BTag"<<it->first<<"=( "<<endl;
    
    for(unsigned int ii=0;ii<it->second.size(); ii++) {
      //cout<<it->second[ii].first<<"  "<<it->second[ii].second<<endl;
      cout<<fixed<<setprecision(2)<<"\""<<(1+it->second[ii].second/100.)<<"\"  ";
    }
    
    cout<<endl<<")"<<endl<<endl; 
  }

  ofstream ofile("JESUp.txt", ios::out | ios::trunc );
  if(ofile) {

    for(it=vMap.begin();it!=vMap.end();++it) {
      for(unsigned int ii=0;ii<it->second.size(); ii++) {
	ofile<<it->first<<" "<<it->second[ii].first<<"  "<<it->second[ii].second<<endl;
      }
    }
  }
  
}
