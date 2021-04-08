////////////////////////// TP10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"

int lireProchaineCommande() //pour lire l'int contenu dans nextFact
{
FILE *f;
int N;
f=fopen("nextFact","r");
fread(&N,sizeof(int),1,f);
fclose(f);
//printf("\n--->lu N=%d",N);
return N;
}

void convertirNenChaine4(int N,char *N4) //convertit l'int N en une chaine de 4 caracteres
{ // si N=1234 alors N4 sera égal à "1234"
int m,c,d,u;
char cm,cc,cd,cu;
m=N/1000;cm=48+m;
N%=1000;
c=N/100;cc=48+c;
N%=100;
d=N/10;cd=48+d;
u=N%10;
cu=48+u;
N4[0]=cm;N4[1]=cc;N4[2]=cd;N4[3]=cu;N4[4]='\0';
}
int lireProduits(T_TableauDeProduits Lproduits){ // on charge nos produits
	int i = 0; 
	FILE *fichier = NULL;
	fichier = fopen("produits.txt","rt");
	if(fichier != NULL){
		do{
			fscanf(fichier,"%d %s %f",&(Lproduits[i].reference),Lproduits[i].libelle,&(Lproduits[i].prixU));

			//printf("\n ref:%d %s %f\n",Lproduits[i].reference,Lproduits[i].libelle,Lproduits->prixU);
			i++;

		}
		while(!(feof(fichier)));

	}
	fclose(fichier);
	return i;
}

void lireCommande(FILE* fc,char *nomCommande, char *NNNN){
	char Prenom[20];
	int numeroC[NB_MAX_PRODUITS], quantiteC[NB_MAX_PRODUITS];
	T_TableauDeProduits Lproduits;
	int k = 0;
	int i = 0;
	char facture[29] = "./factures/facture";
	char produits[] = "produits.txt";
	int taille;
	FILE *fic = NULL;
	float total;
		
	strcat(facture,NNNN); //on crée le répertoire et le nom de la facture
	
	strcat(facture,".txt");
	taille = lireProduits(Lproduits);

	fscanf(fc,"%s",Prenom);
	do{
		fscanf(fc,"%d %d",&numeroC[k],&quantiteC[k]);
		k++;
	}

	while(!feof(fc));

							//creation de factures
	fic = fopen(facture,"wt");
	if(fic != NULL)
	fprintf(fic,"CLIENT %s\n",Prenom);

	{
		for(i = 0; i < k;i++ ){ //on balaye toutes les commandes
			for(int j = 0; j < taille;j++)
			{
				
				if(numeroC[i] == Lproduits[j].reference || stock(numeroC[i],quantiteC[i]))
				{
					total = total + (Lproduits[j].prixU)*(quantiteC[i]);
					fprintf(fic,"%d %s (PU = %f€) :: %f €\n",quantiteC[i],Lproduits[j].libelle,Lproduits[j].prixU,(Lproduits[j].prixU)*(quantiteC[i]));
					
				}
			}

		
		}
		fprintf(fic,"\n\n			total : %f €",total);
	}
	fclose(fic);


}
int stock(int numeroC, int quantiteC){
	T_TableauDeProduits Lproduits;
	int taille = lireProduits(Lproduits);

}

void lireLesCommandes() //cette fonction ouvre tous les fichiers commandeXXX.txt avec XXXX démarrant à N
{
	FILE *ficCommande=NULL;
	int FINI=0;
	int N = lireProchaineCommande(); //numero de la premiere commande qui sera lue et traitee
	char NNNN[5];
	char nomCommande[29];

	do //ce do while prend fin dès que fichier commandeXXXX.txt est absent 
		{
		strcpy(nomCommande,"./commandes/commande");
		convertirNenChaine4(N,NNNN); 
		//printf("\n==>%s<==",NNNN);
		ficCommande=NULL;
		strcat(nomCommande,NNNN);
		strcat(nomCommande,".txt"); //on concatène tout pour avoir une facture
		
		//printf("\n traitement de  %s",nomCommande);
		
		ficCommande=fopen(nomCommande,"rt"); //on lit la facture
		if (ficCommande!=NULL) // si le fichier commandeNNNN.txt existe
			{ 
				printf("\n fichier %s present",nomCommande);
				lireCommande(ficCommande,nomCommande,NNNN); // à vous de coder cette fonction lors de ce TP9
				fclose(ficCommande);
			}
		else
			{
				printf("\n toutes les commandes presentes ont ete traitees.");
				FILE *f=fopen("nextFact","w"); // on va ecrire la valeur de N dans enxtFact 
				// pour 
				fwrite(&N,1,sizeof(int),f);
				fclose(f);
				FINI=1;			
			}

		N++;
		}while(FINI==0);		

}


int main()
{
	//creation d un fichier d'un seul int nommé nextFact et contenant l'int 1
	// code à utiliser pour réinitialiser nextFact à 1 si besoin au cours du TP 
	
	FILE *f;int N=1;
	f=fopen("nextFact","w");
	fwrite(&N,1,sizeof(int),f);
	fclose(f);
	

	//PARTIE 1 du TP : sans Gestion de stock
	//T_TableauDeProduits Lproduits;
	//lireProduits(Lproduits);
	lireLesCommandes(); //lecture de tous les fichiers commandeXXX.txt (fichiers non traités jusqu'ici)	
	

	//PARTIE 2 du TP : avec Gestion de stock
	//copiez coller votre travail précédent puis modifiez le  
	//lireLesCommandes2(); 	

	return 0;
}
