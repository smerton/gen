// This function writes members of the input class to the supplied filename

// Author S. R. Merton

#include <iostream>
#include "input.h"
#include <fstream>
#include <iomanip>

using namespace std;

void Output(char* outputfile,Input*I){

  cout<<"Output(): Writing input pipeline to meshfile "<<outputfile<<endl;

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

  long nx(max(1,I->Nodes(0)-1)),ny(max(1,I->Nodes(1)-1)),nz(max(1,I->Nodes(2)-1));
  for(long k=0;k<nz;k++){
    for(long j=0;j<ny;j++){
      for(long i=0;i<nx;i++){
        file<<(j*I->Nodes(0))+i<<endl;
        file<<(j*I->Nodes(0))+i+1<<endl;
        file<<(j*I->Nodes(0))+i+1+nx+1<<endl;
        file<<(j*I->Nodes(0))+i+1+nx<<endl;
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

// materials

  file<<"# material number in each element"<<endl;

// set up element-wise material array

  long ncellsx(max(1,I->Nodes(0)-1)),ncellsy(max(1,I->Nodes(1)-1)),ncellsz(max(1,I->Nodes(2)-1));
  long totele(ncellsx*ncellsy*ncellsz);
  int elmat[ncellsx*ncellsy*ncellsz];

  long iel(0);
  for(long k=0;k<ncellsz;k++){
    for(long j=0;j<ncellsy;j++){
      for(long i=0;i<ncellsx;i++){

// place ambient material in this cell first

        elmat[iel]=I->Ambient();

// compute element centre coordinates

        double xc=vx[i]+0.5*(vx[i+1]-vx[i]);
        double yc=vy[j]+0.5*(vy[j+1]-vy[j]);
        double zc=vz[k]+0.5*(vz[k+1]-vz[k]);

// find which material the point (xc,yc,zc) intersects and place this in the cell

        for(int imat=0;imat<I->NMaterials();imat++){
          if((xc>I->Range(0,imat)&&xc<I->Range(1,imat))&&(yc>I->Range(2,imat)&&yc<I->Range(3,imat))&&(zc>I->Range(4,imat)&&zc<I->Range(5,imat))){
            elmat[iel]=I->Material(imat);
            break;
          }
        }

        iel++;
      }
    }
  }

// write out material in each element

  for(long iel=0;iel<totele;iel++){
    file<<elmat[iel]<<endl;
  }

// output polyhedral types

  file<<"# polyhedral type to insert in each element (address on type list below)"<<endl;

  for(long iel=0;iel<totele;iel++){
    file<<"1"<<endl;
  }

// output polyhedral order for the kinematics

  file<<"# polyhedral order to insert in each element for kinematics (1 = linear, 2 = quadratic, 3= cubic, etc...)"<<endl;

  for(long iel=0;iel<totele;iel++){
    file<<I->Pk()<<endl;
  }

// output polyhedral order for the thermodynamics

  file<<"# polyhedral order to insert in each element for thermodynamics (1 = linear, 2 = quadratic, 3= cubic, etc...)"<<endl;

  for(long iel=0;iel<totele;iel++){
    file<<I->Pt()<<endl;
  }

  file<<"# polyhderal orders present for kinematics"<<endl;
  file<<I->Pk()<<endl;

  file<<"# polyhderal orders present for thermodynamics"<<endl;
  file<<I->Pt()<<endl;

  file<<"# number of polyhedral orders present"<<endl;
  file<<"1"<<endl;
  file<<"# name of each polyhedral type"<<endl;
  file<<"QUAD"<<endl;
  file<<"# polyhedral element types present (2001 = QUAD, 2002 = TRI, 3001 = HEX, 3002 = TET)"<<endl;
  file<<"2001"<<endl;
  file<<"# number of polyhedral element types present"<<endl;
  file<<"1"<<endl;

// output material data

  file<<"# initial energy in each material"<<endl;
  for(int imat=0;imat<I->NMaterials();imat++){
    file<<"0.0001"<<endl; // code starts with pressure and inverts EoS to get energy, so values here should be irrelevant
  }

  file<<"# initial density in each material"<<endl;
  for(int imat=0;imat<I->NMaterials();imat++){
    file<<I->Density(imat)<<endl;
  }

  file<<"# initial pressure in each material"<<endl;
  for(int imat=0;imat<I->NMaterials();imat++){
    file<<I->Pressure(imat)<<endl;
  }

  file<<"# initial velocity in x-direction in each material"<<endl;
  for(int imat=0;imat<I->NMaterials();imat++){
    file<<I->Velocity(0,imat)<<endl;
  }

  file<<"# initial velocity in y-direction in each material"<<endl;
  for(int imat=0;imat<I->NMaterials();imat++){
    file<<I->Velocity(1,imat)<<endl;
  }

  file<<"# initial velocity in z-direction in each material"<<endl;
  for(int imat=0;imat<I->NMaterials();imat++){
    file<<I->Velocity(2,imat)<<endl;
  }

  file<<"# material numbers present in this mesh"<<endl;
  for(int imat=0;imat<I->NMaterials();imat++){
    file<<I->Material(imat)<<endl;
  }

  file<<"# number of materials"<<endl;
  file<<I->NMaterials()<<endl;

  file<<"# number of cells"<<endl;
  file<<totele<<endl;

  long nvertices=I->Nodes(0)*I->Nodes(1)*I->Nodes(2);
  file<<"# number of vertices"<<endl;
  file<<nvertices<<endl;

  file<<"# boundary condition on each face of the mesh (anticlockwise from bottom face)"<<endl;

  for(int iface=0;iface<6;iface++){
    if(I->Boundary(iface).compare("R")==0){
      file<<"REFLECTIVE"<<endl;
    }else{
      file<<"TRANSMISSIVE"<<endl;
    }
  }

  file<<"# length of each mesh dimension"<<endl;

  for(int idim=0;idim<I->NDims();idim++){
    file<<I->Nodes(idim)<<endl;
  }

  file<<"# number of mesh dimensions"<<endl;
  file<<I->NDims()<<endl;

  cout<<"Output(): Done."<<endl;

  return;

}

