#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void endPage();
void createPage(char *s);
char **str(int nbr,int nb);
void transPlus(char *str1);
void writef();
void modif(char *var);

//----------------------------------------------------------------------
int main (int argc, char* argv[])
{
    char var[256];
    strcpy(var,getenv("QUERY_STRING"));
    if(var==NULL)
    	printf("Aucune QUERY_STRING");

    else
    {
       // sscanf(var,"mod=%s",ligne);
        transPlus(var);
        modif(var);
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

void modif(char *var)
{
    char ligne[256];
    char name[100],name1[100];
    int verifie=0;
    char fname[100],fname1[100];
    char pwd[100],pwd1[100];
    char genre[5],genre1[5];
    sscanf(var,"name=%[^&]&pre=%[^&]&pwd=%s",name1,fname1,pwd1);
   // sscanf(var,"%s %s %s",name1,fname1,genre1);
       int k=0,ok=0,oui=0;
    FILE *fpr=fopen("/var/www/html/inscription/inscri/inscri.txt","r");
    FILE *fpw=fopen("/var/www/html/inscription/inscri/inscri10.txt","w");

    if(fpw==NULL || fpr==NULL)
        printf("BASE DE DONNE FERME");

    else
    {
        while(fgets(ligne,256,fpr))
        {
            sscanf(ligne,"name=%[^&]&pre=%[^&]&genre=%[^&]&pwd=%s",name,fname,genre,pwd);
            fprintf(fpw,"name=%s&pre=%s&pwd=%s\n",name,fname,pwd);
        }
        fclose(fpw);
        fclose(fpr);
    }


FILE *fpr2=fopen("/var/www/html/inscription/inscri/inscri10.txt","r");
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
            if(oui!=ok)
            {
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

    createPage("Modification");
        printf("<style>\n ");
        printf("body{background-color: black;}");

        printf(".form{width: 500px;height: 500px;margin-top:5%%;position: relative;");
        printf(" left: 50%%;border-radius: 15px;transform: translateX(-50%%);background-color: rgba(27, 25, 57, 0.626);}");

        printf(" input{width: 50%%;height: 45px;position: relative;top:100px;");
        printf(" left: 50%%;transform: translateX(-50%%);font-size: medium;font-style: italic;font-weight: 800;");
        printf(" border-radius: 20px;border: 3px solid rgb(247, 244, 248);background-color: #3808e42d;");
        printf(" margin: 10px 15px;text-align: center;color: rgb(255, 255, 255);}");

        printf(" select{width: 50%%;height: 45px;position: relative;top:100px; ");
        printf("  left: 50%%;transform: translateX(-50%%);font-size: medium;font-style: italic;");
        printf(" font-weight: 800;border-radius: 20px;border: 3px solid rgb(247, 244, 248);");
        printf("  background-color: #41128d6f;");
        printf("  margin: 10px 15px;text-align: center;color: rgb(254, 254, 255);}");

        printf(" .retour{width: 25%%;height: 45px;position: relative;font-size: medium;");
        printf("  font-style: italic;font-weight: 800;border-radius: 20px;");
        printf("border: 3px solid rgb(247, 244, 248);background-color: #380888;");
        printf(" margin: 10px 15px;text-align: center;color: rgb(255, 255, 255);}");

        printf(" .sub{top:150px; left: 25%%;transform: translateX(-25%%);}");
        printf(" .res{top:70px; left: 75%%;transform: translateX(-75%%);}");
        printf(" .a1{color: aliceblue;}");

        printf(" .p2{ width: 75%%; height: auto; padding: 7px 5px;");
        printf("background-color: rgb(219, 139, 97);");
        printf(" padding-left: 10px;  position: relative;  top:20px;");
        printf("left: 50%%;border-radius: 4px;text-align: center;");
        printf("color: black;text-decoration-line:underline ;text-transform: uppercase;");
        printf(" transform: translateX(-50%%); margin-bottom: 20px; }  ");
        
        printf("</style></head><!-- 15-08-24 --><body>");

        printf(" <p class='p2'> <b> Votre Modification  </b></p>  ");
        printf(" <div class='form'>  ");
        printf("  <form action='html123.cgi' method='get'>");
        printf("  <p><input type='text' name='name' id='LOG' required placeholder=' nouveau NOM' value='%s'></p> ",name1);
        printf("  <p><input type='prenom' name='pre' id='PRE' required placeholder=' nouveau Prenom' value='%s'></p>  ",fname1);

        printf("  <select name='genre' id='G' required placeholder='Genre' >");
        printf(" <option value='M'>Masculin</option>  ");
        printf(" <option value='F'>Feminin</option>  ");
        printf("</select>");
        
        printf("  <p><input type='submit' value='modifier' class='retour sub'></p>");
        printf(" <p><input type='reset' value='Effacer' class='retour res'></p>");

        printf("</form>");
        printf(" </div>");
    endPage();
}

if(verifie==0)
 { 
   /*createPage("ok");
       printf("%s %s %s",name1,fname1,pwd1);
endPage();*/
    char modd[300];
 FILE *MODIF;
 MODIF=fopen("/var/www/html/inscription/inscri/modifCountEr.html","r");
 printf ("Content-Type:text/html\n\n");
        while(fgets(modd,256,MODIF))
        {
            printf("%s\n",modd);
        } 
    fclose(MODIF);
    }
}
void createPage(char *s){
    printf ("Content-Type:text/html\n\n");
    printf ("<HTML>\n");
    printf ("<HEAD>\n");
    printf ("<TITLE>%s</TITLE>\n",s);
  /*printf ("</HEAD>\n");
    printf ("<BODY>\n"); */

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
    char ligne[256];
    char name[100],fname[100],genre[5];
    FILE *fpw=fopen("/var/www/html/inscription/inscri/inscri.html","w");

    if(fpw==NULL || fpr==NULL)
        printf("BASE DE DONNE FERME");

    else
    {
        fprintf(fpw,"<!DOCTYPE html><html lang='en'><head>");
        fprintf(fpw,"<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>liste Modifie</title><style>");
        fprintf(fpw,"  table{display: flex; align-items: start; justify-content: center; height: 100vh;}");
        fprintf(fpw," td{border: 1px solid black;text-align:center;padding: 3px 3px;}");
        fprintf(fpw," tr{background-color: rgb(238, 229, 219);}");
        fprintf(fpw," tr:hover{background-color: rgb(17, 14, 14);color: aliceblue;} ");
        fprintf(fpw," .SUP:hover{border:3px solid rgb(250, 0, 0);} ");
        fprintf(fpw," .MOD:hover{border:3px solid rgb(0,0, 250);} ");
        fprintf(fpw," .NOM{text-transform: uppercase;}");
        fprintf(fpw," .PRENOM{text-transform: capitalize;}");
        fprintf(fpw," .p1{width: 50%% ; height: auto;padding: 5px 5px;background-color: rgb(115, 74, 52); padding-left: 10px;");
        fprintf(fpw,"  position: relative;left: 50%%; border-radius: 4px;text-align: center;");
        fprintf(fpw," transform: translateX(-50%%); margin-bottom: 20px;}");
        
        fprintf(fpw,".p1:hover{background-color: rgb(115, 74, 52);}");
        fprintf(fpw," .p2{width: 75%%; height: auto;padding: 7px 5px;");
        fprintf(fpw,"background-color: rgb(219, 139, 97);");
        fprintf(fpw," padding-left: 10px;position: relative;left: 50%%;border-radius: 4px;");
        fprintf(fpw,"text-align: center;color: black;text-decoration-line:underline;");
        fprintf(fpw,"text-transform: uppercase;transform: translateX(-50%%); margin-bottom: 20px;}");
        fprintf(fpw," .a1{color: aliceblue; font-size:25px;}");
        fprintf(fpw," </style></head><body>");
        fprintf(fpw," <p class='p1'><a class='a1' href='html123.html'><b>Inscription</b><a></p>");
        fprintf(fpw,"<p class='p1'><a class='a1' href='modification.html'><b>Modification</b><a></p>");
        fprintf(fpw,"<p class='p1'><a class='a1' href='suppression.html'><b>Suppression</b><a></p>");
        fprintf(fpw,"<p class='p2'> <b>liste des personnes inscris(apres modification)</b></p><table>");
        fprintf(fpw,"<tr style='color: blue;' ><td >NOM</td><td>PRENOM</td><td>GENRE</td><td>MODification</td> <td>SUPpression</td> </tr>");


            while(fgets(ligne,256,fpr))
            {
                sscanf(ligne,"name=%[^&]&pre=%[^&]&genre=%s",name,fname,genre);
            fprintf(fpw,"<tr><td class='NOM'>%s</td><td class='PRENOM'>%s</td> <td>%s</td> \n",name,fname,genre);
  
                fprintf(fpw," <td class='MOD'> <form action='htmlM.cgi' method='get'>  ");
                fprintf(fpw,"  <input type='hidden' name='mod' value='%s %s %s'>\n",name,fname,genre);
                fprintf(fpw," <input type='submit' value='MOD'  ></form></td>\n");

                fprintf(fpw,"  <td class='SUP' ><form action='html12.cgi' method='get'>\n");
                fprintf(fpw," <input type='hidden' name='del' value='%s %s %s'>\n",name,fname,genre);
                fprintf(fpw," <input type='submit' value='SUP'  ></form></td></tr>\n");
            }
        fclose(fpr);
        fclose(fpw);
    } 
}
