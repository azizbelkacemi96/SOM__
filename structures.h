

 struct N_config
 {
   int tailleVecteur; 
   int nbNeuronneLigne; 
   int nbNeuronneColone; 
   int nbNeuronne; 
   int nbIteration; 
   double minAlpha;
   int train; 
   int ftrain; 
 }N_conf;




 struct neurone
 {
    double *w;
    char *etiquette;
    double distance_eql;
 };
typedef struct neurone Neurone;


struct best {
	double distance_eql; 
	int r; // ligne 
	int c; //colone
};

typedef struct best bmu;



 struct reseau
 {
   int voisinage;  
  Neurone **map;
  double *vecteur_courant; 
  double alpha; 
  char *etiquette;   
 }reseau;


 struct vecteur
	{
        char *nom;
        double *argument;
        double norme;
	};
struct vecteur * vecteur_tab;
