#include "fonctions_vec.h"
#define SQR(x) ((x)*(x)) 

/*
Fonction pour allouer
*/

void alloc_array_struct(int n)
{
    vecteur_tab=malloc(n*sizeof(struct vecteur));
    int i;
    for(i=0;i<n;i++)
    {
        vecteur_tab[i].argument=malloc(N_conf.tailleVecteur*sizeof(double));
        vecteur_tab[i].nom=malloc(20*sizeof(char));
    }
}




//vecteur moyen
void average_vec(int n)
{
    aver=malloc(N_conf.tailleVecteur*sizeof(double));
    memset(aver,0,N_conf.tailleVecteur*sizeof(double));

    int i,j;

    for(i=0;i<N_conf.tailleVecteur;i++)
    {
        for(j=0;j<n;j++)
            aver[i]+=vecteur_tab[j].argument[i];
        aver[i]/=n;
    }
}
//vecteur min
void min_vec(double k)
{
    min=malloc(N_conf.tailleVecteur*sizeof(double));
    int i;
    for(i=0;i<N_conf.tailleVecteur;i++)
        min[i]=aver[i]-k;
}

//vecteur max
void max_vec(double k)
{
    max=malloc(N_conf.tailleVecteur*sizeof(double));
    int i;
    for(i=0;i<N_conf.tailleVecteur;i++)
        max[i]=aver[i]+k;
}


/*
Fonction pour normaliser un vecteur
*/
void norm_vecteur_tab(int i,int size)
{
    double sum=0.;
    int j;
    for(j=0;j<size;j++)
        sum+=SQR(vecteur_tab[i].argument[j]);
    vecteur_tab[i].norme=sqrt(sum);
}


double* init_rand_w()
{
    int i;
    double k=(double)rand()/RAND_MAX;
    double *tmp_w=malloc(N_conf.tailleVecteur*sizeof(double));

    for(i=0;i<N_conf.tailleVecteur;i++)
        {
            tmp_w[i]=k*(max[i]-min[i])+min[i];
        }

    double norm=0.;

    for(i=0;i<N_conf.tailleVecteur;i++)
    {
        norm+=SQR(tmp_w[i]);
    }

    for(i=0;i<N_conf.tailleVecteur;i++)
    {
            tmp_w[i]/=norm;
    }
    return tmp_w;
}



/**
On init un tableau avant de le mettre en shuffle
**/
void init_shuffle(int n)
{
    index_array=malloc(sizeof(int)*n);
    int i;
    for(i=0;i<n;i++)
        index_array[i]=i;
}
/**
On le met de façon alétoire
**/
void array_shuffle(int n)
{
    int i,r_and,k;
    srand(time(NULL));
    for(i=0;i<n;i++)
        {
            r_and=rand()%n;
            k=index_array[i];
            index_array[i]=index_array[r_and];
            index_array[r_and]=k;
        }
}
/**
Fonction pour calculer la distance euclidienne
*/
double euc_distance(double *a1, double *a2, int n)
{
	double sum=0.0;
	int i;
	for(i=0;i<n;i++)
	{
		sum+=(SQR(a1[i] - a2[i]));
	}
	return sqrt(sum);
}

/**
Fonction pour calculer le α a chaque fois
(pas sur que ca soit exactement ca a revoir )
**/

void calc_alpha(int it_n, int tot_it)
{
	reseau.alpha = N_conf.minAlpha * (1 - ((double)it_n/(double)tot_it));
}
