#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void endPage();
void createPage(char *s);
char **str(int nbr,int nb);
void transPlus(char *str1);
void writef();
void suppr(char *var);

//----------------------------------------------------------------------
int main (int argc, char* argv[])
{
    char var[256];
    char ligne[256];

    strcpy(var,getenv("QUERY_STRING"));
    if(var==NULL)
    	printf("Aucune QUERY_STRING");

    else
    {
        sscanf(var,"del=%s",ligne);
        transPlus(ligne);
        suppr(ligne);
        writef();
    }
return (EXIT_SUCCESS);
}

//------------------------------------------------------------------------

char **str(int nbr,int nb)
{
	char **tab=NULL;

	tab=(char**)malloc(nbr*sizeof(char*));
    for(int i=0;i<nb;i++)
        tab[i]=(char*)malloc(nbr*sizeof(char));
	if(tab == NULL)
	{
		printf("Erreur d'allocation");
		exit(1);
	}
	return (tab);
}

void suppr(char *var)
{
    char ligne[256];
    int verifie=0;
    char name[100];
    char fname[100],pwd[100];
    char genre[5];
    int k=0,ok=1,oui=0;
    FILE *fpr=fopen("/var/www/html/inscription/inscri/inscri.txt","r");
    FILE *fpw=fopen("/var/www/html/inscription/inscri/inscri1.txt","w");

    if(fpw==NULL || fpr==NULL)
        printf("BASE DE DONNE FERME");

    else
    {
        while(fgets(ligne,256,fpr))
        {
            sscanf(ligne,"name=%[^&]&pre=%[^&]&genre=%[^&]&pwd=%s",name,fname,genre,pwd);
            fprintf(fpw,"%s %s %s\n",name,fname,genre);
        }
        fclose(fpw);
        fclose(fpr);
    }

FILE *fpr2=fopen("/var/www/html/inscription/inscri/inscri1.txt","r");
    if( fpr2==NULL)
        printf("BASE DE DONNE FERME"); 
    else
    {
            while(fgets(ligne,256,fpr2))
            {
                ligne[strcspn(ligne, "\n")] = '\0';
                if(strcmp(ligne,var)!=0){
                    k++;
                } 
                else{
                    ok=k;
                    verifie=1;
                    break;
                    }
            }
            fclose(fpr2);
    }
if (verifie==1)
{
    FILE *fpr3=fopen("/var/www/html/inscription/inscri/inscri.txt","r");
    FILE *fpw3=fopen("/var/www/html/inscription/inscri/inscri1.txt","w");

    if(fpw3==NULL || fpr3==NULL)
        printf("SUPPRESSION dans la BASE DE DONNE :impossible\n");

    else{
        while(fgets(ligne,256,fpr3))
        {   
            if(oui!=ok){
                fputs(ligne,fpw3);
            }
            oui++;
        }
    fclose(fpw3);
    fclose(fpr3);
    } 

FILE *fpw4=fopen("/var/www/html/inscription/inscri/inscri.txt","w");
FILE *fpr4=fopen("/var/www/html/inscription/inscri/inscri1.txt","r");
 while(fgets(ligne,256,fpr4))
        {
            fputs(ligne,fpw4);
        }
        fclose(fpw4);
    fclose(fpr4);

createPage("Suppression");
    printf("<br><br><br>");
    printf("<hr><hr>");
    printf("<CENTER>Suppression de <i><b>%s</b></i> avec<b> succes</b> dans la base de donnees \n\n <br>",var);
    printf(" Regarder <a href='inscri.html'><b>ICI</b> la nouvelle liste<a> modifie<br>");
    printf("Pour revenir au,<a href='html123.html'><b> page d'inscription</b> <a> <br> </CENTER>");
    printf("<hr><hr>");
    printf("<br><br>");
        endPage();

}
if(verifie==0)
 {
            createPage("Verrification");
            printf("<br><br><br>");
            printf("<hr><hr>");
            printf("<CENTER> <i>%s </i> <b> N'est PAS inscrit </b>  sur la liste des eleves,verifier votre recherche <br>",var);
            printf("Veuillez regarder ,<a href='inscri.html'><b>tous les inscris</b> <a> <br>");
            printf("ou  revenir au,<a href='html123.html'><b> page d'inscription</b> <a> <br> </CENTER>");
            printf("<hr><hr>");
            printf("<br><br>");
            endPage();
        }
}



void createPage(char *s){
    printf ("Content-Type:text/html\n\n");
    printf ("<HTML>\n");
    printf ("<HEAD>\n");
    printf ("<TITLE>%s</TITLE>\n",s);
    printf ("</HEAD>\n");
    printf ("<BODY>\n");
}
void endPage(){
    printf ("</BODY>\n");
    printf ("</HTML>\n");
}

void transPlus(char *str1)
{     
    char **token;
    token=str(10,100); 
     
    char *subtoken=strtok(str1,"+");
int i=0;
 while(subtoken!=NULL)
 {
    strcpy(token[i],subtoken);
    subtoken=strtok(NULL,"+");
    i++;
 }
int n=i;
    for(i=1;i<n;i++)
    {
        strcat(str1," ");
        strcat(str1,token[i]);
    }
}


void writef()
{
    FILE *fpr=fopen("/var/www/html/inscription/inscri/inscri.txt","r");  
    FILE *fpw=fopen("/var/www/html/inscription/inscri/inscri.html","w"); 
    char ligne[256];
    char name[100],pwd[100],fname[100],genre[5];
    
    if(fpw==NULL || fpr==NULL)
        printf("BASE DE DONNE FERME");

    else{
        fprintf(fpw,"<!DOCTYPE html><html lang='en'><head>");
        fprintf(fpw,"<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Document</title><style>");
        fprintf(fpw," table{display: flex; align-items: start; justify-content: center; height: 100vh;}");
        fprintf(fpw," td{border: 1px solid black;text-align:center;padding: 3px 3px;}");
        fprintf(fpw," tr{background-color: rgb(238, 229, 219);}");
        fprintf(fpw," tr:hover{background-color: rgb(17, 14, 14);color: aliceblue;} ");
        fprintf(fpw," .SUP:hover{border:3px solid rgb(250, 0, 0);} ");
        fprintf(fpw," .MOD:hover{border:3px solid rgb(0,0, 250);} ");
        fprintf(fpw," .NOM{text-transform: uppercase;}");
        fprintf(fpw," .PRENOM{text-transform: capitalize;}");
        fprintf(fpw," .p1{width: 50%% ; height: auto;padding: 5px 5px;background-color: rgb(115, 74, 52); padding-left: 10px; ");
        fprintf(fpw," position: relative;left: 50%%; border-radius: 4px;text-align: center;");
        fprintf(fpw,"transform: translateX(-50%%); margin-bottom: 20px;}");
        
        fprintf(fpw,".p1:hover{background-color: rgb(115, 74, 52);}");
        fprintf(fpw," .p2{width: 75%%; height: auto;padding: 7px 5px;");
        fprintf(fpw," background-color: rgb(219, 139, 97);");
        fprintf(fpw,"  padding-left: 10px;position: relative;left: 50%%;border-radius: 4px;");
        fprintf(fpw," text-align: center;color: black;text-decoration-line:underline;");
        fprintf(fpw," text-transform: uppercase;transform: translateX(-50%%); margin-bottom: 20px;}");
        fprintf(fpw," .a1{color: aliceblue; font-size:25px;}");
        fprintf(fpw," </style></head><body>");
        fprintf(fpw," <p class='p1'><a class='a1' href='html123.html'><b>Inscription</b><a></p>");
        fprintf(fpw,"<p class='p1'><a class='a1' href='modification.html'><b>Modification</b><a></p>");
        fprintf(fpw,"<p class='p1'><a class='a1' href='suppression.html'><b>Suppression</b><a></p>");
        fprintf(fpw,"<p class='p2'> <b>liste des personnes inscris</b></p><table>");
        fprintf(fpw,"<tr style='color: blue;' ><td >NOM</td><td>PRENOM</td><td>GENRE</td><td>MODification</td> <td>SUPpression</td> </tr>");


            while(fgets(ligne,256,fpr))
            {
                sscanf(ligne,"name=%[^&]&pre=%[^&]&genre=%[^&]&pwd=%s",name,fname,genre,pwd);
                fprintf(fpw,"<tr><td class='NOM'>%s</td><td class='PRENOM'>%s</td> <td>%s</td> \n",name,fname,genre);

                fprintf(fpw,"       <td class='MOD'> <form action='htmlM.cgi' method='get'> \n ");
                 fprintf(fpw,"       <input type='hidden' name='mod' value='%s %s %s'>\n",name,fname,genre);
                fprintf(fpw,"        <input type='submit' value='MOD'  ></form></td>\n");

                fprintf(fpw,"        <td class='SUP' ><form action='html12.cgi' method='get'>\n");
                fprintf(fpw,"       <input type='hidden' name='del' value='%s %s %s'>\n",name,fname,genre);
                fprintf(fpw,"       <input type='submit' value='SUP'  ></form></td></tr>\n");
            }
    fclose(fpr);
    fclose(fpw);
    }
}

