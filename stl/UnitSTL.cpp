//---------------------ABDALLAH Meriem ------------------------------------
#include "UnitSTL.h"
#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include <fstream.h>
#include <stdlib.h>
#include <System.Threading.hpp>
#include <System.Diagnostics.hpp>
#include <System.SyncObjs.hpp>
#include <System.SysUtils.hpp>
#include <System.Threading.hpp>
#include <Windows.h>
#include <iostream>
#include <cmath>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool STL::ajouter_point(Point_stl p){

  bool E=false;
  int j  ;
  int i= tableau_points.size();
  for (j = 0; j < i ; j++)
  {
	   if( (fabs(p.get_x()- tableau_points[j].get_x()) <=1e-6)  && (fabs(p.get_y()- tableau_points[j].get_y()) <=1e-6) && (fabs(p.get_z()- tableau_points[j].get_z()) <=1e-6) )
	 { E=true;  j=i;}
  }
  return E;
}
bool STL::verifier_extension_fichier_stl(AnsiString fichier)
{
bool valide=true;
  AnsiString dernier_caractere =fichier.SubString(fichier.Length(),1);
  AnsiString avant_dernier_caractere =fichier.SubString(fichier.Length()-1,1);
  AnsiString avant_av_dernier_caractere =fichier.SubString(fichier.Length()-2,1);
  AnsiString point_cible =fichier.SubString(fichier.Length()-3,1);

	  if(point_cible==".")
	  {
			AnsiString 	t1=avant_av_dernier_caractere.LowerCase();
			AnsiString 	t2=avant_dernier_caractere.LowerCase();
			AnsiString 	t3=dernier_caractere.LowerCase();
				 if (t1=="s" && t2=="t" && t3=="l")
				 {
				 valide=true;
				 return valide;
				 }
				 else
				 {
				 valide=false;
				 return valide;
				 }
	  }
	  else
	  {
	  valide=false;
	  return valide;
	  }
 }
//-------------lire_STL----------------------------------------------//
void STL::lire_stl(AnsiString fichier, bool &valide)
{
	bool TE;
	valide=true;
	char a[200];
	double nx,ny,nz;
	AnsiString b;
	double x1,y1,z1;
	double x2,y2,z2;
	double x3,y3,z3;
	double xmin,ymin,zmin;
	double xmax,ymax,zmax;
	double xminT,yminT,zminT;
	double xmaxT,ymaxT,zmaxT;
	Point_stl P1,P2,P3;
	Normal_Triangle N;
	Triangle_stl T;
   //	bool fixe;
	String nom;
	int i=0,j=0,k=0;
	xmin=ymin=zmin=1e10;
	xmax=ymax=zmax=-1e10;
	xminT=yminT=zminT=1e10;
	xmaxT=ymaxT=zmaxT=-1e10;
	tableau_triangle.clear();
	tableau_points.clear();

	ifstream fin(fichier.c_str());
 try
 {
   fin>>a; b=AnsiString(a);
   if(b!="solid"){valide=false;return;}

   while(!fin.eof())
  {
   fin>>a;
   b=AnsiString(a);
   if(b=="facet")break;
  }
 //***************
   while(!fin.eof())
  {
   fin>>a; b=AnsiString(a); if(b!="normal"){valide=false; return;}

   fin>>nx;
   fin>>ny;
   fin>>nz;
   //--------------la normal de triangle------------
   N.set_nx(nx);
   N.set_ny(ny);
   N.set_nz(nz) ;
   //------- outer loop vertex----------//
   fin>>a;  b=AnsiString(a);  if(b!="outer"){valide=false;return;}
   fin>>a;  b=AnsiString(a);  if(b!="loop"){valide=false;return;}
   fin>>a;  b=AnsiString(a);  if(b!="vertex"){valide=false;return;}

   fin>>x1;
   fin>>y1;
   fin>>z1;

  xmin=(min(xmin,x1)); xmax=(max(xmax,x1));
  ymin=(min(ymin,y1)); ymax=(max(ymax,y1));
  zmin=(min(zmin,z1)); zmax=(max(zmax,z1));
   //-----------sommets de tringle--------------
   P1.set_x(x1);
   P1.set_y(y1);
   P1.set_z(z1);
   //------------verification si l sommet existe deja-------

   TE=ajouter_point(P1);
   if(TE== false)
   {
	tableau_points.push_back(P1);
	i++;
   }
   fin>>a;
   b=AnsiString(a);
   if(b!="vertex"){valide=false; return;}

   fin>>x2;
   fin>>y2;
   fin>>z2;

   xmin=(min(xmin,x2)); xmax=(max(xmax,x2));
   ymin=(min(ymin,y2)); ymax=(max(ymax,y2));
   zmin=(min(zmin,z2)); zmax=(max(zmax,z2));

   P2.set_x(x2);
   P2.set_y(y2);
   P2.set_z(z2) ;
   TE=ajouter_point(P2);
   if(TE== false)
   {
	tableau_points.push_back(P2);
	i++ ;
   }
   fin>>a;  b=AnsiString(a);  if(b!="vertex"){valide=false; return;}

   fin>>x3;
   fin>>y3;
   fin>>z3;

   xmin=(min(xmin,x3)); xmax=(max(xmax,x3));
   ymin=(min(ymin,y3)); ymax=(max(ymax,y3));
   zmin=(min(zmin,z3)); zmax=(max(zmax,z3));

   P3.set_x(x3);
   P3.set_y(y3);
   P3.set_z(z3);
   TE=ajouter_point(P3);
   if(TE== false)
   {
	tableau_points.push_back(P3);
	i++;
   }
  //-----------------ajouter triangle-------------------------------------------------
	T.set_P1(P1);
	T.set_P2(P2);
	T.set_P3(P3);

	T.set_P1_init(P1);
	T.set_P2_init(P2);
	T.set_P3_init(P3);

	T.set_normal(N);

	double xx=(P1.get_x()+P2.get_x()+P3.get_x())/3;
	double yy=(P1.get_y()+P2.get_y()+P3.get_y())/3;
	double zz=(P1.get_z()+P2.get_z()+P3.get_z())/3;
	T.set_centre_x(xx);
	T.set_centre_y(yy);
	T.set_centre_z(zz);

	   xminT=(min(xmin,P1.get_x())); xmaxT=(max(xmax,P1.get_x()));
	   yminT=(min(ymin,P1.get_y())); ymaxT=(max(ymax,P1.get_y()));
	   zminT=(min(zmin,P1.get_z())); zmaxT=(max(zmax,P1.get_z()));

	   xminT=(min(xmin,P2.get_x())); xmaxT=(max(xmax,P2.get_x()));
	   yminT=(min(ymin,P2.get_y())); ymaxT=(max(ymax,P2.get_y()));
	   zminT=(min(zmin,P2.get_z())); zmaxT=(max(zmax,P2.get_z()));

	   xminT=(min(xmin,P3.get_x())); xmaxT=(max(xmax,P3.get_x()));
	   yminT=(min(ymin,P3.get_y())); ymaxT=(max(ymax,P3.get_y()));
	   zminT=(min(zmin,P3.get_z())); zmaxT=(max(zmax,P3.get_z()));


	   Point_stl P_max;
	   Point_stl P_min;

	   P_max.set_x(xmaxT);  P_min.set_x(xminT);
	   P_max.set_y(ymaxT);  P_min.set_y(yminT);
	   P_max.set_z(zmaxT);  P_min.set_z(zminT);


	tableau_triangle.push_back(T);
	j++;
  //-------------------------------------------------------------------------------
   fin>>a;    if(a!="endloop"){valide=false;}
   fin>>a;    if(a!="endfacet"){valide=false;}

   fin>>a; b=AnsiString(a);
   if(b=="endsolid")
   {
	valide=true;fin.close();
 //*******************************
	   Point_stl P_max;
	   Point_stl P_min;

	   P_min.set_x(xmin);
	   P_min.set_y(ymin);
	   P_min.set_z(zmin);

	   P_max.set_x(xmax);
	   P_max.set_y(ymax);
	   P_max.set_z(zmax);

	   brute.setPoint_min(P_min);
	   brute.setPoint_max(P_max);

	   brute.setPoint_min_init(P_min);
	   brute.setPoint_max_init(P_max);

	   nbre_sommets=tableau_points.size();
	   nbre_triangles=tableau_triangle.size();

	   return;
	}
   }
	}
 catch(...)
 {
   valide=false;
   ShowMessage("Fichier non valide!");
 }

}
//-------------------------------------------------------------------------------

void __fastcall TForm2::Button1Click(TObject *Sender)
{
bool valide;

OpenDialog1->FilterIndex=1;
if(OpenDialog1->Execute())
{

			  Screen->Cursor=crHourGlass;


			  if(stl.verifier_extension_fichier_stl(OpenDialog1->FileName)==false)
			  {
				ShowMessage("Extention non valide ! Veuillez sélectionner un fichier de format STL");
				Screen->Cursor= crDefault;
				return;
			  }
			  stl.lire_stl(OpenDialog1->FileName,valide);
			  Screen->Cursor=crDefault;


//*********RECUPERER DES LIMITES GLOBALES DES MODELES**********************
Form2->Edit1->Text= FormatFloat("0.000",stl.getBrute().getPoint_min().get_x());
Form2->Edit4->Text= FormatFloat("0.000",stl.getBrute().getPoint_max().get_x());
Form2->Edit2->Text= FormatFloat("0.000",stl.getBrute().getPoint_min().get_y());
Form2->Edit5->Text= FormatFloat("0.000",stl.getBrute().getPoint_max().get_y());
Form2->Edit3->Text= FormatFloat("0.000",stl.getBrute().getPoint_min().get_z());
Form2->Edit6->Text= FormatFloat("0.000",stl.getBrute().getPoint_max().get_z());
double hauteur=(stl.getBrute().getPoint_max().get_z())-(stl.getBrute().getPoint_min().get_z()) ;
double Longeur=(stl.getBrute().getPoint_max().get_x())-( stl.getBrute().getPoint_min().get_x());
double Largeur=(stl.getBrute().getPoint_max().get_y())-( stl.getBrute().getPoint_min().get_y());
Form2->Edit7->Text= FormatFloat("0.000",Longeur);
Form2->Edit8->Text= FormatFloat("0.000",Largeur);
Form2->Edit9->Text= FormatFloat("0.000", hauteur);
Form2->Edit12->Text=stl. gettableau_triangle().size() ;
Form2->Edit11->Text=stl.gettableau_points().size();
}
}


