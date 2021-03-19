// This function writes members of the input class to the supplied filename

// Author S. R. Merton

#include <iostream>
#include "input.h"
#include <fstream>
#include <iomanip>

using namespace std;

void Output(char* outputfile,Input*I){

  cout<<"Output(): Writing input pipeline to file "<<outputfile<<endl;

// write the input pipeline

  ofstream file(outputfile);

  file<<"#"<<I->Title()<<endl;

  for(int i=0;i<I->NDescriptions();i++){
    file<<"#"<<I->Description(i)<<endl;
  }

// set up vertices

  double vx[I->Nodes(0)],vy[I->Nodes(1)],vz[I->Nodes(2)];
  double dx((I->XMax()-I->XMin())/(I->Nodes(0)-1));
  double dy((I->YMax()-I->YMin())/(I->Nodes(1)-1));
  double dz((I->ZMax()-I->ZMin())/(I->Nodes(2)-1));

  vx[0]=I->XMin();
  for(long i=1;i<I->Nodes(0);i++){vx[i]=vx[i-1]+dx;}

  vy[0]=I->YMin();
  for(long i=1;i<I->Nodes(1);i++){vy[i]=vy[i-1]+dy;}

  vz[0]=I->ZMin();
  for(long i=1;i<I->Nodes(2);i++){vz[i]=vz[i-1]+dz;}

// write vertices

  file<<"# z-coordinate of each mesh vertex"<<endl;

  file<<fixed<<setprecision(17);

  for(long k=0;k<I->Nodes(2);k++){
    for(long j=0;j<I->Nodes(1);j++){
      for(long i=0;i<I->Nodes(0);i++){
        file<<vz[k]<<endl;
      }
    }
  }

  file<<"# y-coordinate of each mesh vertex"<<endl;

  file<<fixed<<setprecision(17);

  for(long k=0;k<I->Nodes(2);k++){
    for(long j=0;j<I->Nodes(1);j++){
      for(long i=0;i<I->Nodes(0);i++){
        file<<vy[j]<<endl;
      }
    }
  }

  file<<"# x-coordinate of each mesh vertex"<<endl;

  file<<fixed<<setprecision(17);

  for(long k=0;k<I->Nodes(2);k++){
    for(long j=0;j<I->Nodes(1);j++){
      for(long i=0;i<I->Nodes(0);i++){
        file<<vx[i]<<endl;
      }
    }
  }

// write vertex numbers

  file<<"# mesh vertex number in each element corner"<<endl;

  long nx(I->Nodes(0)-1),ny(I->Nodes(1)-1),nz(max(1,I->Nodes(2)-1));
  for(long i=0;i<nx;i++){
    for(long j=0;j<ny;j++){
      for(long k=0;k<nz;k++){
        file<<i<<endl;
        file<<i+1<<endl;
        file<<i+1+nx+1<<endl;
        file<<i+1+nx<<endl;
      }
    }
  }

// number of vertices

  file<<"# number of vertices in each element (the sum of this is the length of the above list)"<<endl;

  for(long i=0;i<nx;i++){
    for(long j=0;j<ny;j++){
      for(long k=0;k<nz;k++){
        file<<"4"<<endl;
      }
    }
  }

  cout<<"Output(): Done."<<endl;

  return;

}

