//---------------------------------------------------------------------------

#ifndef UnitSTLH
#define UnitSTLH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <vector>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
using namespace std;
////////////////////////////////////PointSTL///////////////////////////////////////
class Point_stl
{
   double x,y,z ;

   public:

   void set_x ( double x ){this->x = x ;}
   void set_y ( double y ){this->y = y ;}
   void set_z ( double z ){this->z = z ;}

   double get_x() { return x ;}
   double get_y() { return y ;}
   double get_z() { return z ;}
};
//---------classe brut ---------------------------
class Brute
 {

   Point_stl Point_max,Point_max_init;
   Point_stl Point_min,Point_min_init;

   double longueur,largeur,epaisseur;

   public:

   double  get_longueur() { return longueur ;}
   void set_longueur (double l ) {longueur =l;}

   double  get_largeur() { return largeur ;}
   void set_largeur (double la ) {largeur =la;}

   double  get_epaisseur() { return epaisseur ;}
   void set_epaisseur (double ep ) {epaisseur =ep;}

   Point_stl getPoint_max(){ return Point_max ;};
   Point_stl getPoint_min(){ return Point_min ;};

   void setPoint_min(Point_stl aa){Point_min=aa;};
   void setPoint_max(Point_stl aa){Point_max=aa;};

   Point_stl getPoint_max_init(){ return Point_max_init ;};
   Point_stl getPoint_min_init(){ return Point_min_init ;};

   void setPoint_min_init(Point_stl a){Point_min_init=a;};
   void setPoint_max_init(Point_stl a){Point_max_init=a;};

  };

///////////////////////////////class normale////////////////////////////////////
class Normal_Triangle
{
  double nx,ny,nz ;

  public:
  Normal_Triangle() {nx=0; ny=0; nz=0; }

  void set_nx ( double nx ){this->nx = nx ;}
  void set_ny ( double ny ){this->ny = ny ;}
  void set_nz ( double nz ){this->nz = nz ;}

  double get_nx() { return nx ;}
  double get_ny() { return ny ;}
  double get_nz() { return nz ;}

};
//////////////////////////////class triangle////////////////////////////////////
class Triangle_stl
{

   Point_stl P1;
   Point_stl P2;
   Point_stl P3;

   Point_stl P1_init;
   Point_stl P2_init;
   Point_stl P3_init;

   Normal_Triangle normal ;
   double centre_x;
   double centre_y;
   double centre_z;

   public:
	//getters
   Point_stl getP1(){ return P1 ;};
   Point_stl getP2(){ return P2 ;};
   Point_stl getP3(){ return P3 ;};

   Point_stl getP1_init(){ return P1_init ;};
   Point_stl getP2_init(){ return P2_init ;};
   Point_stl getP3_init(){ return P3_init ;};

   Normal_Triangle get_normal(){ return normal ;};
   double get_centre_x () { return centre_x  ;}
   double get_centre_y() { return centre_y ;}
   double get_centre_z() { return centre_z ;}
	 //setters
   void set_P1 (Point_stl p ) { P1=p ;}
   void set_P2 (Point_stl p ) { P2=p ;}
   void set_P3 (Point_stl p ) { P3=p ;}

   void set_P1_init (Point_stl p ) { P1_init=p ;}
   void set_P2_init (Point_stl p ) { P2_init=p ;}
   void set_P3_init (Point_stl p ) { P3_init=p ;}

   void set_normal ( Normal_Triangle n ){ normal=n; }
   void set_centre_x (double centre_xx ) { centre_x= centre_xx;}
   void set_centre_y (double centre_yy ) { centre_y = centre_yy ;}
   void set_centre_z (double centre_zz ) { centre_z = centre_zz ;}
};
////////////////////////////////STL/////////////////////////////////////////////
class STL
{
	int nbre_sommets, nbre_triangles;
	vector <Triangle_stl> tableau_triangle;
	vector <Point_stl> tableau_points;
	Brute brute;

	public :

	Brute getBrute(){return brute;};
	void setBrute(Brute a){brute = a;};

	Triangle_stl getellementTriangle(int i){return tableau_triangle[i];};
	Point_stl getellementPoint(int i){return tableau_points[i];};

	void setellementTriangle(int i ,Triangle_stl t){tableau_triangle[i] =  t;};
	void setellementpoints(int i ,Point_stl p){tableau_points[i] =  p;};

	int get_nbre_sommets () { return nbre_sommets ;};
	void set_nbre_sommets (int nbre_sommets ) { nbre_sommets=nbre_sommets ;}

	int get_nbre_triangles () { return nbre_triangles ;}
	void set_nbre_triangles (int nbre_triangles ) { nbre_triangles=nbre_triangles ;}

	vector<Triangle_stl> gettableau_triangle(){return  tableau_triangle;}
	vector<Point_stl> gettableau_points(){return  tableau_points;}
	void settableau_triangle(vector<Triangle_stl> a){tableau_triangle = a;}
	Point_stl get_elt_tableau_points(int i){return  tableau_points[i];}
	void settableau_points(vector<Point_stl> p){tableau_points = p;}
	//methodes
	bool ajouter_point(Point_stl p);
	void lire_stl (AnsiString fichier,bool &valide);
	bool verifier_extension_fichier_stl(AnsiString fichier);

};







class TForm2 : public TForm
{
__published:	// Composants gérés par l'EDI
	TButton *Button1;
	TGroupBox *GroupBox0;
	TLabel *Label1;
	TLabel *Label6;
	TLabel *Label2;
	TLabel *Label5;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	TEdit *Edit6;
	TEdit *Edit7;
	TEdit *Edit8;
	TEdit *Edit9;
	TEdit *Edit11;
	TEdit *Edit12;
	TOpenDialog *OpenDialog1;
	void __fastcall Button1Click(TObject *Sender);
private:	// Déclarations utilisateur
public:		// Déclarations utilisateur
			STL   stl ;
			Brute b;
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
