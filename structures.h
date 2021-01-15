
/*
 Structure de données pour notre configuration de base
 */
 struct N_config
 {
   int tailleVecteur; //variable pour la taille du vecteur
   int nbNeuronneLigne; // nombre de neuron map sur ligne
   int nbNeuronneColone; // npmbre de neuron sur colone
   int nbNeuronne; //total neuron (n_l_out * n_c_out)
   int nbIteration; // Nombre d'iterations qu'on calcule avec la methode donnée
   double minAlpha;//starting value
   int train; //training layer operation num
   int ftrain; //first layer operation num
 }N_conf;



/*
 Structure d'un node (neuron)
 */
 struct neurone
 {
    double *w;
    char *etiquette;
    double distance_eql;
 };
typedef struct neurone Neurone;


struct best {
	double distance_eql; // euclidian distance
	int r;
	int c;
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
