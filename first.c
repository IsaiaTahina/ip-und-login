#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void endPage();
void createPage(char *s);
char *stringg(int nbr);
char **str(int nbr,int nb);
void transPlus(char *str);

void seconnecter(char *var);

//----------------------------------------------------------------------
int main (int argc, char* argv[])
{
    char *var;
    char *ligne;
    char **token;

    token=str(10,100);
    var=stringg(256);
    ligne=stringg(256);

    var=getenv("QUERY_STRING");
    if(var==NULL)
    	printf("Aucune QUERY_STRING");

    else{
        strcpy(ligne,var);
        transPlus(ligne);
        seconnecter(ligne);
        

}
return (EXIT_SUCCESS);
}


char *stringg(int nbr)
{
	char *tab=NULL;
	tab=(char*)malloc(nbr*sizeof(char));
	if(tab == NULL)
	{
		printf("Erreur d'allocation");
		exit(1);
	}
	return (tab);
}

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

void seconnecter(char *var)
{
//verification
    int verifie=0;
    char ligne[256];
    char name1[100],fname1[100],pwd1[100],genre1[5];
    char name[100],fname[100],pwd[100],genre[5];
    sscanf(var,"name=%[^&]&pre=%[^&]&pwd=%s",name,fname,pwd);
    FILE *fp2;
    fp2=fopen("/var/www/html/inscription/inscri/inscri.txt","r");
    if(fp2==NULL)
    {
        printf("opening file error");
        exit(0);
    }
    if(fp2!=NULL)
    {
        while(fgets(ligne,256,fp2))
        {
            ligne[strcspn(ligne,"\n")]='\0';
            sscanf(ligne,"name=%[^&]&pre=%[^&]&genre=%[^&]&pwd=%s",name1,fname1,genre1,pwd1);
            if(strcmp(ligne,var)==0)
                verifie=1;
             else  if(strcmp(name1,name)==0 && strcmp(fname1,fname)==0  && strcmp(pwd,pwd1)==0)
                verifie=1; 
        }
        fclose(fp2);
    }

if (verifie==1)
{
    char ligne[300];
    FILE *ip;
    ip=fopen("/var/www/html/inscription/inscri/ip.html","r");
    FILE *co;
    co=fopen("/var/www/html/inscription/inscri/co.txt","a");
    fprintf(co,"%s %s %s\n",name,fname,pwd);
    fclose(co);
    printf ("Content-Type:text/html\n\n");
    while(fgets(ligne,300,ip))
    {
        printf("%s\n",ligne);
    }
    fclose(ip);
    }

else{
    char ligne[300];
    FILE *ip_error;
    ip_error=fopen("/var/www/html/inscription/inscri/first_error.html","r");
    printf ("Content-Type:text/html\n\n");
    while(fgets(ligne,300,ip_error))
    {
        printf("%s\n",ligne);
    }
    fclose(ip_error);
}
}