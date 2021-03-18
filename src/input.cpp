// Function definitions for members of the input class

// Author S. R. Merton

#include <iostream>
#include "input.h"
#include <fstream>

using namespace std;

// Constructor to instantiate a new input from data in the input file

Input::Input(char* inputfile){

  cout<<"Input::Input(): Loading an input from file "<<inputfile<<endl;

// read the file

  mKeyword.empty();

  ifstream file(inputfile);

  while(mKeyword.compare("End")!=0){
    file>>mKeyword;

    if(mKeyword.compare("Title")==0){getline(file,mTitle);}
    if(mKeyword.compare("Description")==0){getline(file,mbuffer);mDescription.push_back(mbuffer);}
    if(mKeyword.compare("Nodes")==0){file>>mNodes[0]>>mNodes[1]>>mNodes[2];}
    if(mKeyword.compare("Domain")==0){file>>mKeyword>>mXMin>>mXMax>>mKeyword>>mYMin>>mYMax>>mKeyword>>mZMin>>mZMax;}
    if(mKeyword.compare("Boundaries")==0){for(int i=0;i<6;i++){file>>mBoundaries[i];}}
    if(mKeyword.compare("Pk")==0){file>>mPk;}
    if(mKeyword.compare("Pt")==0){file>>mPt;}
    if(mKeyword.compare("Material")==0){
      int matno;bool zambient(false);double d,p,u[3],x[2],y[2],z[2];
      file>>matno;mMaterial.push_back(matno);
      file>>mKeyword;if(mKeyword.compare("ambient")==0){zambient=true;}
      file>>mKeyword;if(mKeyword.compare("density")==0){file>>d;}
      file>>mKeyword;if(mKeyword.compare("pressure")==0){file>>p;}
      file>>mKeyword;if(mKeyword.compare("velocity")==0){for(int i=0;i<3;i++){file>>u[i];}}
      file>>mKeyword;if(mKeyword.compare("x")==0){for(int i=0;i<2;i++){file>>x[i];}}
      file>>mKeyword;if(mKeyword.compare("y")==0){for(int i=0;i<2;i++){file>>y[i];}}
      file>>mKeyword;if(mKeyword.compare("z")==0){for(int i=0;i<2;i++){file>>z[i];}}
      mAmbient.push_back(zambient);
      mDensity.push_back(d);
      mPressure.push_back(p);
      for(int i=0;i<3;i++){mVelocity[i].push_back(u[i]);}
      mRange[0].push_back(x[0]);mRange[1].push_back(x[1]);
      mRange[2].push_back(y[0]);mRange[3].push_back(y[1]);
      mRange[4].push_back(z[0]);mRange[5].push_back(z[1]);
    }

  }

  return;

}

// Accessor functions to member data

    string Input::Title(){return mTitle;} // returns problem title
    int Input::NDescriptions(){return mDescription.size();} // returns number of lines in the problem description
    string Input::Description(int i){return mDescription[i];} // returns line i of the problem description
    int Input::Nodes(int idim){return mNodes[idim];} // returns the number of nodes along direction idim
    double Input::XMin(){return mXMin;} // returns the mesh extent
    double Input::XMax(){return mXMax;} // returns the mesh extent
    double Input::YMin(){return mYMin;} // returns the mesh extent
    double Input::YMax(){return mYMax;} // returns the mesh extent
    double Input::ZMin(){return mZMin;} // returns the mesh extent
    double Input::ZMax(){return mZMax;} // returns the mesh extent
    string Input::Boundary(int iface){mBoundaries[iface];} // returns the boundary condition of face iface
    int Input::Pk(){return mPk;} // returns the polyhedral order of the kinematic element
    int Input::Pt(){return mPt;} // returns the polyhedral order of the thermodynamic element
    int Input::NMaterials(){return mMaterial.size();} // returns the number of materials
    int Input::Material(int imat){return mMaterial[imat];} // returns material number of material imat
    bool Input::Ambient(int imat){return mAmbient[imat];} // returns ambience of material imat
    double Input::Density(int imat){return mDensity[imat];} // returns density of material imat
    double Input::Pressure(int imat){return mPressure[imat];} // returns pressure in material imat
    double Input::Velocity(int idim,int imat){return mVelocity[idim][imat];} // returns velocity in direction idim of m

// Destructor function to release storage associated with an input class object

Input::~Input(){}
