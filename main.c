#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "structures.h"
#include "init.c"
#include "main.h"


bmu *Bmu = NULL;
int Bmu_size=1;




void update(bmu* b_mu)
{
    int nr=reseau.voisinage;
    int i,j,x1,x2,y1,y2;

 
        if(b_mu->r-nr<0)
            x1=0; 
        else
            x1=b_mu->r-nr;
        if(b_mu->c-nr<0)
            y1=0; 
        else
            y1=b_mu->c-nr;

        if(b_mu->r+nr>N_conf.nbNeuronneLigne-1)
            x2=N_conf.nbNeuronneLigne-1;
        else
            x2=b_mu->r+nr;
        if(b_mu->c+nr>N_conf.nbNeuronneColone-1)
            y2=N_conf.nbNeuronneColone-1;
        else
            y2=b_mu->c+nr;

        for(i=x1;i<=x2;i++)
            for(j=y1;j<=y2;j++)
            {

                int k; // nombre de var du vec d'entré

                for(k=0;k<N_conf.tailleVecteur;k++) // mettre a jour le vec du bmu
                    {

                        reseau.map[i][j].w[k]+=reseau.alpha*(reseau.vecteur_courant[k]-reseau.map[i][j].w[k]);
                    }
            }
   
}



void create_neuron_map()
{
    int i,j;
    reseau.map=malloc(N_conf.nbNeuronneLigne*sizeof(Neurone *));
	for(i=0;i<N_conf.nbNeuronneLigne;i++)
	{
		reseau.map[i]=malloc(N_conf.nbNeuronneColone*sizeof(Neurone));
	}
	for(i=0;i<N_conf.nbNeuronneLigne;i++)
	{
		for (j=0;j<N_conf.nbNeuronneColone;j++)
		{

            reseau.map[i][j].w=(double*)malloc(sizeof(double)*N_conf.tailleVecteur);
			reseau.map[i][j].w=init_rand_w();
			reseau.map[i][j].etiquette=malloc(20*sizeof(char));
			strcpy(reseau.map[i][j].etiquette, ".");
		}
	}
}


void print_la_map()
{
    int i,j;
    for(i=0;i<N_conf.nbNeuronneLigne;i++)
    {
        for(j=0;j<N_conf.nbNeuronneColone;j++)
            {
                printf("%s ",reseau.map[i][j].etiquette);
            }
        printf("\n");
    }
}





void training()
{
    int i,j,p,u,it;
    double min_d,dist; // distance min dis : distance entre un neuronne et le vecteur

    Bmu=malloc(sizeof(bmu)); // psk plusieur 

    for(p=0;p<N_conf.train;p++) // nombre de phase  
    {
        int cur_n_it;
        if(!p)
        {
            cur_n_it=N_conf.ftrain;  // first
        }
        else
        {
            cur_n_it=N_conf.nbIteration-N_conf.ftrain;
            N_conf.minAlpha=0.07;
            reseau.voisinage=1;
        }

        for(it=0;it<cur_n_it;it++)
        {
            calc_alpha(it,cur_n_it);

            if(it%(N_conf.ftrain/6)==0&&it!=0&&p==0)
            {
                reseau.voisinage-=1; // ?????
            }


            array_shuffle(150);

            for(u=0;u<150;u++)
            {

                reseau.vecteur_courant=vecteur_tab[index_array[u]].argument; // on selection un vecteur
                min_d=200;
                for(i=0;i<N_conf.nbNeuronneLigne;i++)
                {
                    for(j=0;j<N_conf.nbNeuronneColone;j++)
                    {
                        dist=euc_distance(reseau.vecteur_courant,reseau.map[i][j].w,N_conf.tailleVecteur);
                        reseau.map[i][j].distance_eql=dist;
                        if(dist<min_d)
                        {
                            min_d=dist;    // c'est la ou on calc la dis euc et le best 
                            if(Bmu_size>1)
                            {
                                Bmu_size=1;
                                Bmu=realloc(Bmu,Bmu_size*sizeof(bmu)); // maj de la BMU si on trouve mieux
                            }
                            Bmu[0].distance_eql=dist;
                            Bmu[0].r=i; // ligne 
                            Bmu[0].c=j; // colone
                        }
                        else if(dist==min_d) // on cas ou on trouve plusieur bmu equivalent 
                        {

                            Bmu_size++;
                            Bmu=realloc(Bmu,Bmu_size*sizeof(bmu));
                            Bmu[Bmu_size-1].distance_eql=dist;
                            Bmu[Bmu_size-1].r=i;
                            Bmu[Bmu_size-1].c=j;

                        }
                    }
                }

                if(Bmu_size>1)
                {
                    int t=rand()%(Bmu_size);
                strcpy(reseau.map[Bmu[t].r][Bmu[t].c].etiquette, vecteur_tab[index_array[u]].nom);
                update(Bmu);
                }
                
                strcpy(reseau.map[Bmu[0].r][Bmu[0].c].etiquette, vecteur_tab[index_array[u]].nom);
                update(Bmu);
                
            }
        }
    }
}


int main()
{
    init_n_conf();
    alloc_array_struct(150);
	read_data();
    average_vec(150);
    min_vec(0.005);
    max_vec(0.005);
    init_shuffle(150);
	create_neuron_map();
    print_la_map();
    printf("\n");
    reseau.voisinage=6;
    reseau.alpha=0;
    training();
    print_la_map();
    free(aver);
    free(min);
    free(max);
	return 0;
}
