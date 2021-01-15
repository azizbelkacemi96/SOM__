#include "init.h"

/*on initialise les valeurs
 comme suite (elles peuvent étre initialisé autrement
 j'ai mis α a 0.7
 et le nombre d'iterations a 30000
*/
void init_n_conf()
{
    N_conf.nbNeuronneLigne=6;
    N_conf.nbNeuronneColone=10;
    N_conf.nbNeuronne=N_conf.nbNeuronneLigne*N_conf.nbNeuronneColone;
    N_conf.tailleVecteur=4;
    N_conf.nbIteration=30000;
    N_conf.minAlpha=0.7;
    N_conf.ftrain=N_conf.nbIteration/5;
    N_conf.train=2;
}



/*
Fonction pour lire le fichier iris.data
 avec utilisation de strtok
*/
void read_data()
{
    FILE * in;

    char *str=malloc(sizeof(char)*500);
    in=fopen("iris.data","r");

    int i,j;
 for(i=0;i<150;i++)
 {
        fscanf(in,"%s",str);
        char *tok=strtok(str,",");

        for(j=0;j<N_conf.tailleVecteur;j++)
            {
                vecteur_tab[i].argument[j]=atof(tok);
                tok=strtok(NULL,",");
            }

        if (strcmp(tok, "Iris-setosa") == 0)
     strcpy(vecteur_tab[i].nom,"S");
        else if(strcmp(tok,"Iris-versicolor")==0)
            strcpy(vecteur_tab[i].nom,"V");
        else
            strcpy(vecteur_tab[i].nom,"G");

        norm_vecteur_tab(i,N_conf.tailleVecteur);
        printf("%d",vecteur_tab[i].argument);
 }

 fclose(in);
    free(str);
}
