#ifndef _SystUtils_
#define _SystUtils_

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>

#include "tools/src/DataBaseManager.hh"
#include "tools/src/Format.cc"

#include <TRandom3.h>

using namespace std;

class SystUtils {

private:
  
  vector<string> parseDb(string db, vector<bool>& specVars);

  map<string,SystST> _uncSrcs;

  DataBaseManager* _dbm;

  TRandom3 rnd;

public:

  enum {kUp=0, kDown, kNone, kNDirs};
  static std::string uDir[kNDirs];

  SystUtils();
  ~SystUtils();
  
  void addSystSource(string name, int dir, string type, vector<string> modVar,
		     float val);
  void addSystSource(string name, int dir, string type, vector<string> modVar,
		     string db, string hname="");
  
  void init(DataBaseManager* dbm) {_dbm=dbm;};

  SystST getSystInfos(string name, int dir);

  template <typename T> inline 
  void systOp(string name, int dir, string type, T &v, float x) {
    
    if(type=="+" && dir==kDown) { //down absolute variation
      v -= x;
    }
    if(type=="+" && dir==kUp) { //up absolute variation
      v += x;
    }
    if(type=="*" && dir==kDown) { //down relative variation
      v *= 2-x;
    }
    if(type=="*" && dir==kUp) { //up relative variation
      v *= x;
    }
    if(type=="%" && dir==kDown) { //down 1-relative variation
      v *= 1-x;
    }
    if(type=="%" && dir==kUp) { //up 1+relative variation
      v *= 1+x;
    }
    if(type=="r" && dir==kDown) { //down 1-relative variation
      v *= rnd.Gaus(1,x);
    }
    if(type=="r" && dir==kUp) { //up 1+relative variation
      v *= rnd.Gaus(1,x);
    }

  };
  
  template <typename T> inline
  void systOpV(string name, int dir, string type, vector<T>* &v, float x) {
    for(size_t i=0;i<v->size();i++) {
      systOp<T>(name, dir, type,(*v)[i],x);
    }
  };

  template <typename T> inline
  void systOpA(string name, int dir, string type, T* &v, float x) {
    unsigned int sa = sizeof(v)/sizeof(v[0]);
    for(size_t i=0;i<sa;i++) {
      systOp<T>(name, dir, type,v[i],x);
    }
  };

  template <typename T> inline
  void systOp(string name, int dir, string type, T &v, 
	      unsigned int idx, string db,
	      vector<float> vals) {
    
    //find db value
    float vs[10];
    for(size_t i=0;i<10;i++) {
      vs[i]=-1000000;
      if(i<vals.size())
	vs[i] = vals[i];
    }
    //cout<<_dbm->exists(db)<<"   "<<vs[0]<<"  "<<vs[1]<<endl;
    float x = _dbm->getDBValue(db, vs[0], vs[1], vs[2], vs[3], vs[4], 
			       vs[5], vs[6], vs[7], vs[8], vs[9]);
    
    //cout<<"var == "<<name<<"  "<<v<<"  "<<x<<endl;
    systOp<T>(name, dir, type, v, x);
    
  };

  template <typename T> inline 
  void systOpV(string name, int dir, string type,
	       vector<T>* &v, string db, 
	       vector<vector<float> > vals) {

    //splitting objects
    vector<float> p(vals.size());//,vector<float>(0,0));
    for(size_t i=0;i<v->size();i++) {
      for(size_t iv=0;iv<vals.size();iv++) {
	p[iv]=vals[iv][i];
      }
      systOp<T>(name, dir, type,(*v)[i], i, db, p);
    }

  };

  
  template <typename T> inline 
  void systOpA(string name, int dir, string type,
	       T* &v, string db, 
	       vector<vector<float> > vals) {

    //splitting objects
    vector<float> p(vals.size());//,vector<float>(0,0));
    unsigned int sa = sizeof(v)/sizeof(v[0]);
    for(size_t i=0;i<sa;i++) { //for each object to modify
      for(size_t iv=0;iv<vals.size();iv++) {
       	p[iv]=vals[iv][i];//picking the proper dependency values object
	//cout<<" --> "<<i<<"  "<<iv<<"  "<<vals[iv][i]<<endl;
      }
      //cout<<" ==> "<<name<<"  "<<dir<<"  "<<type<<"  "<<v[i]<<"  "<<db<<endl;
      systOp<T>(name, dir, type, v[i], i, db, p);
    }

  };
  
  void systOpW(string name, int dir, string type, float& w,
	       string db, vector<float> vals);
  void systOpW(string name, int dir, string type, float& w, float x);

  //  ClassDef(SystUtils,0)
};

#endif
