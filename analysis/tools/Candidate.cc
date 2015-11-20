#include "analysis/tools/Candidate.hh"

#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

// instanciate static counter
#include "analysis/utils/Counter.cc"

#include "analysis/utils/Constants.hh"
#include "analysis/utils/KineUtils.hh"

size_t Candidate::_curUid=0;
map<size_t,const Candidate*> Candidate::_baseCand;

void
Candidate::reset()
{
 
  _curUid=0;
  for(map<size_t,const Candidate*>::iterator it=_baseCand.begin();
      it!=_baseCand.end(); ++it) {
    delete it->second;
  }
  _baseCand.clear();
 
}

Candidate::Candidate()
{
  init();
  lock();
}

Candidate::~Candidate() {
}

Candidate::Candidate( const TVector3& mom,
		      float charge,
		      float mass,  
		      Vertex* vtx ) {
  init();
  setP3( mom );
  _q = charge;
  _m = mass;  
  _vtx = vtx;
  
  lock();
}


Candidate::Candidate(float pt, float eta, float phi,
		     int pdgId,
		     float charge,
		     float mass,  
		     Vertex* vtx ) {
  init();
  setPtEtaPhi(pt, eta, phi);
  _pdgId = pdgId;
  _q = charge;
  _m = mass;  
  _vtx = vtx;
  
  lock();
}


// Candidate::Candidate( const TVector3& mom,
// 		      const TParticlePDG& pdtEntry,
// 		      Vertex* vtx )
// {
//   init();
//   setP3( mom ); 
//   setPdtEntry( pdtEntry );
//   _vtx = vtx;
// }

Candidate::Candidate( const TVector2& tmom,
		      Vertex* vtx ) {
  init();
  _type = kTransverse;
  _pt   = tmom.Mod();
  _phi  = tmom.Phi();
  _eta  = 0.;
  _vtx  = vtx;
  
  lock();
}

Candidate::Candidate( float pt, float phi,
		      Vertex* vtx ) {
  init();
  _type = kTransverse;
  _pt   = pt;
  _phi  = phi;
  _eta  = 0.;
  _vtx  = vtx;
  
  lock();
}

Candidate::Candidate( Vertex* vtx )  
{
  init();
  _vtx = vtx;
  assert( _vtx!=0 );
  
  for( size_t ii=0; ii<_vtx->nOutgoingCand(); ii++ )
    {
      addDaughter( _vtx->outgoingCand( ii ) );
    }
  
  lock();
  
}

//Candidate::Candidate( const vector< const Candidate* >& listOfDau )
Candidate::Candidate( const CandList& listOfDau )
{
  //cout<<" lflflf "<<endl;
  init();
  //cout<<" uid begin "<<_uid<<endl;
  _uid--;
  _curUid--;
  //cout<<" lflflfddd "<<listOfDau.size()<<endl;
  for( size_t idau=0; idau<listOfDau.size(); idau++ )
    {
      const Candidate* dau = listOfDau[idau];
      //cout<<idau<<" --- "<<endl;
      if( dau->isTransverse() ) _type = kTransverse;
      //cout<<idau<<" ---c "<<_curUid<<"   "<<_baseCand.size()<<"   "<<dau->uid()<<"   "<<dau<<endl;
      addDaughter( dau->clone() );
      //cout<<idau<<" ---cc "<<_curUid<<"   "<<_baseCand.size()<<endl;
    }
  //cout<<" lflflfddddddd "<<endl;
  _uid+=listOfDau.size()+1;
  _curUid+=1;
  //cout<<"uid :"<<_uid<<endl;

  // int p;
  // cin >> p;
  //cout<<" buvid "<<endl;
  // now loop on the daughters
  //cout<< " cui "<<endl;
  TVector2 p2_(0,0);
  //cout<<" blou "<<endl;
  float pz_(0);
  //cout<<" blou1 "<<endl;
  float E_(0);
  //cout<<" blou2 "<<endl;
  _q=0;
  //cout<<" blou3 "<<endl;
  Vertex* vtx_(0);
  //cout<<" blou4 "<<endl;
  bool sameVtx(false);
  //cout<<" lflflf2 "<<endl;
  for( size_t idau=0; idau<nDaughters(); idau++ )
    {
      const Candidate* dau = daughter(idau);
      if( vtx_==0 ) 
	{
	  sameVtx=true;
	  vtx_=dau->vertex();
	}
      else if( dau->vertex()!=vtx_ )
	{
	  sameVtx=false;
	}
      _q  += dau->charge(); 
      p2_ += dau->p2();
      if( isTransverse() )
	{
	  E_  += dau->Et();
	}
      else
	{
	  E_  += dau->E();
	  pz_ += dau->pz();
	}
    }
  _pt  = p2_.Mod(); 
  _phi = p2_.Phi();
  TVector3 p3_( p2_.X(), p2_.Y(), pz_ );
  _eta = 0;
  if( !isTransverse() && _pt>0 ) 
    { 
      _eta = p3_.Eta();
    }
  float m2_= pow(E_,2)-p3_.Mag2();
  if( m2_<0 ) m2_=0;
  _m = sqrt(m2_);
  if( sameVtx ) setVertex( vtx_ );

  //cout<<" shgwhgwg "<<endl;
  lock();
}

Candidate::Candidate( const Candidate& o )
  : 
  _uid(    ++_curUid  ),
  _type(   o._type ),
  _name(   o._name ),
  _q(      o._q    ),
  _m(      o._m    ),
  _pt(     o._pt   ),
  _eta(    o._eta  ),
  _phi(    o._phi  ),
  //_pdtEntry(    o._pdtEntry  ),
  _vtx(    o._vtx  )
  //_info(   o._info )
{
  _status = kUnlocked;
 
  //cout<<" uid "<<_curUid<<" // "<<o.uid()<<" locking "<<_baseCand.size()<<"   "<<_baseCand.count(o.uid())<<endl; 
  // make sure the original is in the bank of base candidates
  if( _baseCand.count(o.uid())==0 ) _baseCand[_uid]=&o;

  // _curUid++;
  lock();

  for( size_t idau=0; idau<o.nDaughters(); idau++ )
    {
      //cout<<" doing daughter "<<endl;
      addDaughter( o.daughter(idau)->clone() );
    } 
  
}


Candidate* 
Candidate::create()
{ 
  return new Candidate; 
}

Candidate* 
Candidate::create( const TVector3& mom,
		   float charge,
		   float mass,  
		   Vertex* vtx ) { 
  return new Candidate( mom, charge, mass, vtx ); 
} 

Candidate* 
Candidate::create( float pt, float eta, float phi,
		   int pdgId,
		   float charge,
		   float mass,  
		   Vertex* vtx ) { 

  return new Candidate( pt, eta, phi, pdgId, charge, mass, vtx ); 
} 


// Candidate* 
// Candidate::create( const TVector3& mom,
// 		   const TParticlePDG& pdtEntry,
// 		   Vertex* vtx )
// { 
//   return new Candidate( mom, pdtEntry, vtx ); 
// }

// Candidate* 
// Candidate::create( const TVector3& mom,
// 		   int pdgId,
// 		   Vertex* vtx )
// { 
//   //FIXME MM
//   if(pdgId==4414 || pdgId==4434)
//     {pdgId=445;}
//   // cout<<pdgId<<endl;
//   const TParticlePDG* pdt_ 
//     = ParticleData::Table()->GetParticle( pdgId );
//   assert( pdt_!=0 );
//   return create( mom, *pdt_, vtx ); 
// }

Candidate* 
Candidate::create( const TVector2& tmom,
		   Vertex* vtx ) { 
  return new Candidate( tmom, vtx ); 
}

Candidate* 
Candidate::create( float pt, float phi,
		   Vertex* vtx ) { 
  return new Candidate( pt, phi, vtx ); 
}
	     
Candidate* 
Candidate::create( Vertex* vtx )
{ 
  return new Candidate( vtx ); 
}
	     
Candidate*
//Candidate::create( const vector< const Candidate* >& listOfDau )
Candidate::create( const CandList& listOfDau )
{
  return new Candidate( listOfDau );
}

Candidate*
Candidate::create( const Candidate* dau1, const Candidate* dau2 )
{
  //  vector< const Candidate* > listOfDau;
  CandList listOfDau;
  listOfDau.push_back( (Candidate*)dau1 ); 
  listOfDau.push_back( (Candidate*)dau2 );
  return new Candidate( listOfDau );
}

Candidate* 
Candidate::clone() const
{ 
  return new Candidate(*this); 
}

Candidate* 
Candidate::transverseClone() const
{ 
  Candidate* out = new Candidate(*this);
  if( out->isTransverse() )  return out;
  out->_type = kTransverse;
  out->_eta  = 0;
  return out;
}

void
Candidate::setP3( const TVector3& mom )
{
  assert( !isLocked() );
  _pt  = mom.Pt();
  _eta = 1.e09;
  if( _pt!=0 ) _eta = mom.Eta();
  if( _eta>1.e09 )
    {
      mom.Print();
      //assert(0);
    }
  _phi = mom.Phi();
}


void
Candidate::setP2( const TVector2& mom )
{
  assert( !isLocked() );
  _pt  = mom.Mod();
  _phi = mom.Phi();
}


void
Candidate::setPdgId( int pdgId )
{
  assert( !isLocked() );
  _pdgId = pdgId;
}

// void
// Candidate::setPdgCode( int pdgId )
// {
//   // const TParticlePDG* pdt_ 
//   //   = ParticleData::Table()->GetParticle( pdgId );
//   // assert( pdt_!=0 );
//   // setPdtEntry( *pdt_ );
// }    

void
Candidate::setPxPyPz( float px, float py, float pz )
{
  assert( !isLocked() );
  TVector3 mom( px, py, pz );
  setP3( mom );
}

void
Candidate::setPtEtaPhi( float pt, float eta, float phi )
{
  assert( !isLocked() );
  _pt  = pt;
  _eta = eta;
  _phi = phi;
}

void
Candidate::setMass( float m )
{
  assert( !isLocked() );
  _m = m;
}

void
Candidate::setVertex( Vertex* v )
{
  assert( !isLocked() );
  _vtx = v;
}

void
Candidate::init()
{
  _name = "";
  _status = kUnlocked;
  _uid  = ++_curUid;
  _type = kFull;
  _q    = 0.;
  _m    = 0.;
  _pt   = 0.;
  _eta  = 0.;
  _phi  = 0.;
  // _pdtEntry  = 0;
  _vtx  = 0;

  _mother = 0;
  //_info   = 0;
}

void
Candidate::lock()
{
  // map<size_t,const Candidate*>::iterator it;
  // for(it=_baseCand.begin();it!=_baseCand.end();++it)
    //cout<<it->first<<"  ---> "<<it->second<<endl;
  //cout<<_uid<<"   "<<_curUid<<" ==> "<<_baseCand.count(_uid)<<endl;
  _status=kLocked;   
  assert( _baseCand.count(_uid)==0 );
  _baseCand[_uid]=this;
}

float          
Candidate::charge()               const
{
  return _q;
}

float          
Candidate::mass()                 const
{
  return _m;
}

TVector3       
Candidate::pos()                  const
{
  if( _vtx!=0 ) return _vtx->pos();
  return TVector3(0,0,0);
}

TVector3       
Candidate::p3()                   const
{
  TVector3 p3_;
  p3_.SetPtEtaPhi( _pt, _eta, _phi );
  return p3_;
}

TVector2       
Candidate::p2()                   const
{
  return TVector2( _pt*cos(_phi), _pt*sin(_phi) );
}

TLorentzVector 
Candidate::p4()                   const
{
  TLorentzVector p4_;
  p4_.SetPtEtaPhiM( _pt, _eta, _phi, _m );
  return p4_;
}

float          
Candidate::px()                    const
{
  return p3().X();
}

float          
Candidate::py()                    const
{
  return p3().Y();
}

float
Candidate::pz()                    const
{
  return p3().Z();
}

float          
Candidate::E()                    const
{
  return sqrt( pow(_m,2) + pow(p(),2) );
}

float          
Candidate::Et()                    const
{
  return sqrt( pow(_m,2) + pow(_pt,2) );
}

float          
Candidate::p()                   const
{
  return p3().Mag();
}

float          
Candidate::pt()                   const
{
  return _pt;
}

float          
Candidate::eta()                  const
{
  return _eta;
}

float          
Candidate::phi( int unit )   const
{
  float phi_ = _phi;
  if( phi_<0     ) phi_ += 2*Constants::pi;
  if( unit==kDeg ) phi_ *= Constants::radToDeg;
  return phi_;
}

float          
Candidate::sinPhi()               const
{
  return sin(_phi);
}

float          
Candidate::cosPhi()               const
{
  return cos(_phi);
}

float          
Candidate::tanPhi()               const
{
  return tan(_phi);
}

float          
Candidate::theta( int unit ) const
{
  float th_ = p3().Theta();
  if( unit==kDeg ) th_ *= Constants::radToDeg;
  return th_;
}

float          
Candidate::sinTheta()               const
{
  return sin(theta());
}

float          
Candidate::cosTheta()               const
{
  return cos(theta());
}

float          
Candidate::tanTheta()               const
{
  return tan(theta());
}

float          
Candidate::tanDip()               const
{
  return tan(Constants::pi/2.-theta());
}

Vertex*          
Candidate::vertex()               const
{
  return _vtx;
}

// const TParticlePDG* 
// Candidate::pdtEntry() const
// {
//   return _pdtEntry;
// }

// int
// Candidate::pdgCode() const
// {
//   if( _pdtEntry==0 ) return 0;
//   return _pdtEntry->PdgCode();
// }

int 
Candidate::pdgId() const 
{
  return _pdgId;
}

const string &
Candidate::name() const
{
  return _name;
}

void
Candidate::print( ostream& o ) const
{
  o << "\n";
  o << "Candidate -- ";
  o << name();
  o << "\tuid=" << uid() << "\tptr=" << this << endl;
  o << "-- (Px=" << px() << ", Py=" << py() << ", Pz=" << pz() << "; E=" << E() <<  ") q=" << charge() << " M=" << mass() << " Gev/c2 ";    
  o << endl;
  // print daughter links
  if( _vtx ) { o << " vtx= "; _vtx->print(o); }
  o << "pt="  << pt() << " GeV, ";
  o << "\teta=" << eta() << ", ";
  o << "\tphi=" << phi( kDeg ) << " deg";
  o << endl;
  if( isComposite() )   
    {
      o << "M="   << mass() << " GeV, ";
      o << "E="   << E()    << " GeV ";
      o << "d: "<< nDaughters();
      for( size_t ii=0; ii<nDaughters(); ii++ ) 
	{
	  o << " - " << daughter(ii)->uid();
	  o << endl;
	}
      o << endl;
    }						
  //  o << "mother=" << theMother() << endl;
  //if( _info!=0 ) _info->print( o );
}
 
bool  
Candidate::operator==( const Candidate& o ) const
{
  return _uid == o._uid;
}

bool  
Candidate::operator<( const Candidate& o ) const
{
  return pt() < o.pt();
}


size_t
Candidate::nDaughters() const
{
  return _daughter.size();
}

bool 
Candidate::isComposite() const
{
  return nDaughters()>0;
}

const Candidate* 
Candidate::theBase() const
{
  //  if( isComposite() ) return this;
  //  if( isLocked()    ) return this;
  const Candidate* cand = _baseCand[_uid];
   if( cand==0 ) cand = this;
   return cand;
} 
Candidate* 
Candidate::theBase()
{
  //  if( isComposite() ) return this;
  //  if( isLocked()    ) return this;
  Candidate* cand = const_cast<Candidate*>(_baseCand[_uid]);
  if( cand==0 ) cand = this;
  return cand;
} 

const Candidate* 
Candidate::daughter( size_t idau ) const
{
  assert( idau<nDaughters() );
  return _daughter[idau];
}

Candidate* 
Candidate::daughter( size_t idau )
{
  assert( idau<nDaughters() );
  return _daughter[idau];
}

void 
Candidate::setMother( Candidate* mo )
{
  //  assert( !isLocked() );
  assert( mo!=0 );
  _mother = mo;
  //  mo->addDaughter(this);
}

void 
Candidate::addDaughter( Candidate* dau )
{
  //  assert( !isLocked() );  
  assert( dau!=0 );
  _daughter.push_back( dau );
  dau->setMother(this);
}

void
Candidate::basePrint( ostream& o )
{
  for( map<size_t,const Candidate*>::const_iterator it=_baseCand.begin();
       it!=_baseCand.end(); ++it )
   {
     it->second->print(o);
   }
}

const Candidate* 
Candidate::base( size_t uid )
{
  return 0;
  map<size_t,const Candidate*>::const_iterator it = _baseCand.find(uid);
  if( it==_baseCand.end() ) return 0;
  return it->second; 
}



float
Candidate::dz( const Vertex* pv ) const
{

  float dz_=0;
  
  float vx_= _vtx->pos().X();
  float vy_= _vtx->pos().Y();
  float vz_= _vtx->pos().Z();

  float pvx_= pv->pos().X();
  float pvy_= pv->pos().Y();
  float pvz_= pv->pos().Z();

  
  dz_ = (vz_-pvz_) - ((vx_-pvx_)*px()+(vy_-pvy_)*py())/pt() * pz()/pt(); 


  return dz_;

}


float
Candidate::d0( const Vertex* pv ) const
{

  float d0_=0;

  float vx_= _vtx->pos().X();
  float vy_= _vtx->pos().Y();

  float pvx_= pv->pos().X();
  float pvy_= pv->pos().Y();

  d0_ = ( -(vx_-pvx_)*py() + (vy_-pvy_)*px() ) / pt();

  return d0_;

}


float
Candidate::dR( const Candidate* cand) const
{

  return KineUtils::dR( eta(),  cand->eta(), phi() , cand->phi() );

}

float
Candidate::d3r( const Vertex* pv ) const
{
  
  float vx_= _vtx->pos().X();
  float vy_= _vtx->pos().Y();
  float vz_= _vtx->pos().Z();

  float pvx_= pv->pos().X();
  float pvy_= pv->pos().Y();
  float pvz_= pv->pos().Z();

  return (vz_-pvz_)*pt()/p() - ((vx_-pvx_)*px()+(vy_-pvy_)*py())/pt() *pz()/p(); 

}

bool
Candidate::isAtPrimaryVertex() const
{
  Vertex* vtx_ = vertex();
  if( vtx_==0 ) return false;
  return vtx_->isPrimary();
}

int
Candidate::vertexIndex() const
{
  int vtxid =-1;
  // Vertex* vtx_=vertex();
  // if( vtx_!=0 )
  //   {
  //     vtxid = vtx_->index();
  //   }
  return vtxid;
}
