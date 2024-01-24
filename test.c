#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Etudiant{
    char matricule[20];
    char nom[100];
    char prenom[100];
    float moyenne;
}Etudiant;
 typedef struct entete_fichier{
   size_t file_size;
   char file_name[100];
   char file_extension[30];
   int nb_element;
 }entete_fichier;
typedef struct block_entete{
    size_t block_size;
    int nb_block_element;
    int facteur_blockage;
    char data_type[50];
}block_entete;

void creefichier(char *nomfichier,char *extension){
    char *nomfichiercomplet=malloc(strlen(name) + strlen(extension)+2);
    strcpy(nomfichiercomplet,nomfichier);
    strcpy(nomfichiercomplet,extension);
    FILE *fichier=fopen(nomfichiercomplet,"wb");
    entete_fichier entete;
    strcpy(entete.file_name,nomfichier);
    strcpy(entete.file_extension,extension);
    entete.file_size=sizeof(entete_fichier);
    entete.nb_element=0;
    fwrite(&entete,sizeof(entete_fichier),1,fichier);
    fclose(fichier);
    free(nomfichiercomplet);

}



void insertion_block (char *file_path, Etudiant *T ,int facteur_blockage, int n){
    FILE *file= fopen(file_path,"r+b");
    fseek(file,0,SEEK_END);
    block_entete block;
    entete_fichier entete;
    strcpy(block.data_type,"Etudiant");
    block.facteur_blockage=facteur_blockage;
    void *buffer;
    for (int i =0 ;i < n ; i=i+facteur_blockage){
        int facteur;
        if (i + facteur_blockage > n ){

            facteur= facteur_blockage  // Ajustement du facteur
             while (i + facteur > n ) 
        {                            
           --facteur;    
        } 

        block.nb_block_element= facteur;
        }
        else{
            facteur=facteur_blockage;
            block.nb_block_element=facteur_blockage;
        }
        block.block_size = sizeof(Etudiant) * facteur_blockage; // calcul de la taille du bloc
        size_t block_memory_size = sizeof(block_entete) + block.block_size; // calcul de la taille totale du bloc en memoire
        buffer = malloc(block_memory_size); // allocation de mémoire pour le buffer
        memcpy( buffer , &block , sizeof(block_entete) ); // copie de la structure block_entete dans le buffer
        memcpy (buffer + sizeof (block_entete),(Etudiant *)T+i,sizeof (Etudiant)*facteur); // Copie des données d'etudiants dans le tampon
        fwrite (buffer,block_memory_size,1,file); // ecriture du buffer  dans le fichier
        free(buffer);
        
    }
    fseek (file , 0, SEEK_SET); // Positionnement au debut du fichier
    fread (&entete,sizeof(entete_fichier),1,file); // Lecture de l entête actuel du fichier
    entete.nb_element= entete.nb_element + n; // Mise à jour du nombre total d'éléments
    fseek (file,0,SEEK_END); // Positionnement à la fin du fichier pour obtenir la taille actuelle
    entete.file_size = ftell(file); // Mise a jour de la taille totale du fichier dans l'entête
    fseek (file,0,SEEK_SET); // Repositionnement au début du fichier
    fwrite (&entete, sizeof(entete_fichier),1,file); // ecriture de l'entête mis à jour dans le fichier
    fclose(file);

}

      void read_file (char * file_path){
        FILE *file = fopen(file_path,"rb");
        entete_fichier myentete;
        fread (&myentete,sizeof(entete_fichier),1,file);
        Etudiant T[entete.nb_element];
        block_entete myblock;
        int i =0;
        while (fread(&myblock,sizeof(block_entete),1,file)>0)
        {
            if(myblock.nb_block_element != 0 ){                               //
                fread( T+i ,sizeof(Etudiant),myblock.nb_block_element,file); // Lecture des elements du bloc
                i = i + myblock.nb_block_element;                           //
            }
        }
         
       for (int j = 0; j < header_file.nb_element; j++)
       {
            read_element(T[j]);
       }
        

      fclose(file);





      }


void read_element(Etudiant x){

    printf("matricule) : %s \n",x.matricule);
    printf("nom / prenom : %s / %s \n",x.nom,x.prenom);
    printf("moyenne : %s \n",x.moyenne);
}





void search (char *file_path, char *mat){
    FILE *fic=fopen(*file_path,"rb");

    entete_fichier Ftete;
    fread(&Ftete,sizeof(entete_fichier),1,fic);
    Etudiant T[Ftete.nb_element];//On crée un tableau dont la taille correspond aux éléments du fichier, pour stocker les éléments avant de les vérifier

    block_entete Tbloc;
    int trouver =0,  i=0 ,c ,j;

    while(fread(&Tbloc,sizeof(block_entete),1,fic)> 0 && trouver == 0)//On vérifie s'il existe encore des blocs au cas où on n'aurait pas trouvé l'étudiant cible
    {
        if(Tbloc.nb_block_element!=0){
            fread(T+i,sizeof(Etudiant),Tbloc.nb_block_element,fic)//On place les éléments du block dans le tableau pour les vérifier
            {
                c=Tbloc.nb_block_element;
                j=i;
                while(c>0 && trouver==0){
                    if(strcmp(T[j].matricule,mat)==0){
                        trouver=1;
                        read_element(t[j]);
                    }j++;  c--;
                    }
               i=i+Tbloc.nb_block_element;     

                if(Tbloc.nb_block_element != Tbloc.facteur_blockage)//verifi si il y des element vide dans le bloc
                    {
                        int vide=Tbloc.facteur_blockage - Tbloc.nb_block_element;
                        fseek(fic,sizeof(Etudiant)*vide, SEEK_CUR);
            
                    }
            }
        }
        else//au cas où le bloc est vide
        {
            fseek(fic,sizeof(Etudiant) * Tbloc.facteur_blockage, SEEK_CUR);
        }
    }
   
    if(trouver==0)//Au cas où l'élément n'existe pas
    {
        printf("\n -L'élément n'existe pas. \n")
    }
    fclose(fic);

}




  /*void supprimer(char *file_path,char *mat){
   FILE *fichier = fopen(file_path,"r+b"); //ouvrir le fichier en mode lecture ecriture binaire.
   struct entete_fichier entete;
   struct block_entete block;
   fread(&entete,sizeof(entete_fichier),1,fichier); //recuperer l'entete de notre fichier (les informations).
   struct Etudiant T[entete.nb_element];  //un tableau pour stocker les enregistrement .


   }*/

int main ()
{

    return 0 ;
}