#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void endPage();
void createPage(char *s);
char *stringg(int nbr);
char **str(int nbr,int nb);
void transPlus(char *str);
void transPoint(char *str1);
void classerIP(char *str);

//-----------------------------------------------------
int main()
{

    char *ligne;
    char *ligne1;
    int nbPoint=0;
    ligne=stringg(256);
    ligne1=stringg(256);
    ligne=getenv("QUERY_STRING");
    if(ligne==NULL)
    	printf("Aucune QUERY_STRING");

    else{ 
    //fgets(ligne1,256,stdin);
        sscanf(ligne,"ip=%s",ligne1);
        transPlus(ligne1);
        transPoint(ligne1);

}
return (EXIT_SUCCESS);
}
//-------------------------------------------

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
		printf("Erreur d'allocation\n");
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
      //  strcat(str1," ");
        strcat(str1,token[i]);
    }
}

void transPoint(char *str1)
{     
    char **token;
    int nbPoint=0;
     int tab[4];
    int count=0;
    int i;
    int j=0;
    char *endptr;
    int ipp;
    int ok=0;
    char *str2;
    FILE *fp1;
    char ligne[300];
    fp1=fopen("/var/www/html/inscription/inscri/ip_error.html","r");
    str2=stringg(256);

    while(str1[j]!='\0')
    {
        if (isalpha(str1[j]))
        {
            count ++;
        }
        j++;
    }
  
    token=str(10,100); 
    char *subtoken=strtok(str1,".");
        while(subtoken!=NULL)
        {
            strcpy(token[nbPoint],subtoken);
            subtoken=strtok(NULL,".");
            nbPoint++;
        }

    int n=nbPoint;
    if(count !=0 || n!=4)
    {
        printf ("Content-Type:text/html\n\n");
        while(fgets(ligne,300,fp1))
        {
            printf("%s\n",ligne);
        }
        printf("<p class='pp' >ERROR:ip avec caractere ou nombre de point a verifie </p></div> <a href='setting.html' >Setting</a> </body></html>");
        fclose(fp1);
    
    }

    else 
    {
        for(i=0;i<n;i++)
        {
            tab[i]=atoi(token[i]);
        }
         for(i=0;i<n;i++)
        {
            if ((tab[i] >0 && tab[i] <=255 && strcmp(token[i],"0")!=0)||(tab[i] ==0 && strcmp(token[i],"0")==0))
                strcat(str2,token[i]);
            else{
                ok=1;
            }
         }

        if(ok==1)
        {
            printf ("Content-Type:text/html\n\n");
        while(fgets(ligne,300,fp1))
        {
            printf("%s\n",ligne);
        }
             printf("<p class='pp'> ERROR: Nombre maximale de Bits depassé  </p></div></body></html>");
            fclose(fp1);

        }
       else 
        {
            classerIP(token[0]);
        }
    }
}


void classerIP(char *str){
    // convertir l entre en entier
    char *endptr;
    int veriefie=0;
    int ip;
    ip=atoi(str);
    FILE *fp1;
    char ligne[300];
    fp1=fopen("/var/www/html/inscription/inscri/ip1.html","r");
    if(fp1==NULL)
    {
        printf("DONNE NON ENREGISTRE");
        exit(0);
    }
    else
    {
        printf ("Content-Type:text/html\n\n");
         while(fgets(ligne,300,fp1))
        {
            printf("%s\n",ligne);
        }

        if (ip>=0 && ip<=127)
        {
            printf("<p class='pp'>votre IP est de classe A</p></div> <a href='setting.html' >Setting</a> </body></html>");
            fclose(fp1);
        }
       
        else if (ip>127 && ip<=191)
        {
            printf("<p class='pp'>votre IP est de classe B</p></div> <a href='setting.html' >Setting</a> </body></html>");
            fclose(fp1);
        }
        else if (ip>191 && ip<=223)
        {
            printf("<p class='pp'>votre IP est de classe C</p></div> <a href='setting.html' >Setting</a> </body></html>");
            fclose(fp1);
        }
        else if (ip>223 && ip<=239)
        {
            printf("<p class='pp'>votre IP est de classe D</p></div> <a href='setting.html' >Setting</a> </body></html>");
            fclose(fp1);
        }
        else if (ip>239 && ip<=255)
        {
            printf("<p class='pp'>votre IP est de classe E</p></div> <a href='setting.html' >Setting</a> </body></html>");
            fclose(fp1);
        }

        else
        { 
            printf("<p class='pp' >Enter a valid IP </p></div> <a href='setting.html' >Setting</a> </body></html>");
            fclose(fp1);
        }
   }  
}