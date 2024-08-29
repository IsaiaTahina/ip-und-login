
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void endPage();
void createPage(char *s);

char *stringg(int nbr);
char **str(int nbr,int nb);
void freee(char **tab);
void transPlus(char *str);

void reegister(char *var);
void writef();
void suppr();
void modif();
void readf();

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
       // transPlus(var);
        transPlus(ligne);
        reegister(ligne);
        readf();

}
return (EXIT_SUCCESS);
}

//-------------------------------------------------------------
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
		printf("Erreur d'allocation");
		exit(1);
	}
	return (tab);
}

void freee(char **tab)
{
    for(int i=0;i<10;i++)
        free(tab[i]);
	free(tab);
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

void reegister(char *var)
{
//verification
    int verifie=0;
    char ligne[256];
    char name1[100],fname1[100],pwd1[100],genre1[5];
    char name[100],fname[100],pwd[100],genre[5];
    sscanf(var,"name=%[^&]&pre=%[^&]&genre=%[^&]&pwd=%s",name,fname,genre,pwd);
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
             else  if(strcmp(name1,name)==0 && strcmp(fname1,fname)==0  && strcmp(genre1,genre)==0)
                verifie=1; 
        }
        fclose(fp2);
    }

if (verifie==0)
{
//inscription normal
    FILE *fp1;
    fp1=fopen("/var/www/html/inscription/inscri/inscri.txt","a");
    if(fp1==NULL)
    {
        printf("DONNE NON ENREGISTRE");
        exit(0);
    }
    else
    {
        fprintf(fp1,"%s\n",var);
        fclose(fp1);
    }

 printf ("Content-Type:text/html\n\n");
 printf("<!DOCTYPE html>\n\
<html lang='en'>\n\
<head>\n\
    <meta charset='UTF-8'>\n\
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n\
     <title>connecter ou quiter</title>\n\
    <style> " );
   printf(" a{\n\
            text-decoration: none;\n\
            color: #000;\n\
            font-weight: 900;\n\
            font-size: 1.5rem;\n\
        }\n\
.fond{\n\
    width:90%%;\n\
    text-align: center;\n\
    position: absolute;\n\
    top: 50%%;\n\
    left: 50%%;\n\
    color: hsl(0, 0%%, 83%%);\n\
    transform: translate(-50%%,-50%%);\n\
    border-radius: 20px;\n\
    height: 100vh;\n\
    background-color: #0d0c0b;\n\
}.connect{\n\
    width:25%%;\n\
    height:60px;\n\
    text-align: center;\n\
     align-content: center;\n\
    position: relative;\n\
    top: 50%%;\n\
    border-radius: 10px;\n\
    background-color: #d3d3d3;\n\
    left: 25%%;\n\
    transform: translate(-25%%,-50%%);\n\
}\n\
.quit{\n\
    width:25%%;\n\
    height:60px;\n\
    text-align: center;\n\
    position: relative;\n\
    top: 42%%;\n\
    align-content: center;\n\
    border-radius: 10px;\n\
    background-color: #d3d3d3;\n\
    left: 75%%;\n\
    transform: translate(-75%%,-50%%);\n\
}\n\
.label{\n\
    font-size: 1.5rem;\n\
    text-align: center;\n\
    position: relative;\n\
    top: 42%%;\n\
    align-content: center;\n\
    border-radius: 10px;\n\
}\n\
    </style>\n\
</head>\n\
<body>\n\
    <div class='fond'>\n\
      <p class='label'>Inscription avec <b> SUCCES</b> de <i>%s %s </i>\n\n</p>\n\
         <p class='connect'> <a href='ip.html' >check IP  </a></p>\n\
          <p class='quit'> <a href='quit.html' >quit </a> </p>\n\
    </div>\n\
</body>\n\
</html>",name,fname);

}
if (verifie==1)
{
    // donne deja enregistre
     createPage("Verrification");
        printf("<br><br><br>");
        printf("<hr><hr>");
        printf("<CENTER> <i>%s %s</i> <b> est deja INSCRIT </b>  sur la liste des eleves,et elle ne peut pas s'inscrire deux fois <br>",name,fname);
        printf("Veuillez regarder ,<a href='inscri.html'><b>tous les inscris</b> <a> <br>");
        printf("ou  revenir au,<a href='html123.html'><b> page d'inscription</b> <a> <br> </CENTER>");
        printf("<hr><hr>");
        printf("<br><br>");
    endPage();
}
}



void writef()
{
    FILE *fpr=fopen("/var/www/html/inscription/inscri/inscri.txt","r");
    FILE *fpw=fopen("/var/www/html/inscription/inscri/inscri.html","w");
    char ligne[256];
    char name[100],fname[100],genre[5],pwd[100];

    if(fpw==NULL || fpr==NULL)
        printf("BASE DE DONNE FERME");

    else{
    fprintf(fpw,"<!DOCTYPE html><html lang='en'><head>\n");
    fprintf(fpw,"<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Document</title><style>\n");
    fprintf(fpw," table{display: flex; align-items: start; justify-content: center; height: 100vh;}\n");
    fprintf(fpw," td{border: 1px solid black;text-align:center;padding: 3px 3px;}\n");
    fprintf(fpw,"tr{background-color: rgb(238, 229, 219);}\n");
    fprintf(fpw,"tr:hover{background-color: rgb(17, 14, 14);color: aliceblue;}\n ");
    fprintf(fpw,".SUP:hover{border:3px solid rgb(250, 0, 0);}\n ");
    fprintf(fpw,".MOD:hover{border:3px solid rgb(0,0, 250);} \n");
    fprintf(fpw,".NOM{text-transform: uppercase;}\n");
    fprintf(fpw,".PRENOM{text-transform: capitalize;}");
    fprintf(fpw,".p1{width: 50%% ; height: auto;padding: 5px 5px;background-color: rgb(115, 74, 52); padding-left: 10px; \n");
    fprintf(fpw," position: relative;left: 50%%; border-radius: 4px;text-align: center;\n");
    fprintf(fpw,"transform: translateX(-50%%); margin-bottom: 20px;}\n");
    
    fprintf(fpw," .p1:hover{background-color: rgb(115, 74, 52);}\n");
    fprintf(fpw,"  .p2{width: 75%%; height: auto;padding: 7px 5px;\n");
    fprintf(fpw," background-color: rgb(219, 139, 97);\n");
    fprintf(fpw,"  padding-left: 10px;position: relative;left: 50%%;border-radius: 4px;\n");
    fprintf(fpw," text-align: center;color: black;text-decoration-line:underline;\n");
    fprintf(fpw," text-transform: uppercase;transform: translateX(-50%%); margin-bottom: 20px;}\n");
    fprintf(fpw," .a1{color: aliceblue; font-size:25px;}\n");
    fprintf(fpw," </style></head><body>\n");
    fprintf(fpw," <p class='p1'><a class='a1' href='html123.html'><b>Inscription</b><a></p>\n");
    fprintf(fpw,"<p class='p1'><a class='a1' href='modification.html'><b>Modification</b><a></p>\n");
    fprintf(fpw,"<p class='p1'><a class='a1' href='suppression.html'><b>Suppression</b><a></p>\n");
    fprintf(fpw," <p class='p2'> <b>liste des personnes inscris</b></p><table>\n");
    fprintf(fpw," <tr style='color: blue;' ><td >NOM</td><td>PRENOM</td><td>GENRE</td><td>MODification</td> <td>SUPpression</td> </tr>\n");


    while(fgets(ligne,256,fpr))
    {
        sscanf(ligne,"name=%[^&]&pre=%[^&]&genre=%[^&]&pwd=%s",name,fname,genre,pwd);
        fprintf(fpw,"<tr><td class='NOM'>%s</td><td class='PRENOM'>%s</td> <td>%s</td> \n",name,fname,genre);

        fprintf(fpw," <td class='MOD'> <form action='htmlM.cgi' method='get'> ");
        fprintf(fpw," <input type='hidden' name='mod' value='%s %s %s'>\n",name,fname,genre);
        fprintf(fpw," <input type='submit' value='MOD'  ></form></td>\n");

        fprintf(fpw,"  <td class='SUP' ><form action='html12.cgi' method='get'>\n");
        fprintf(fpw," <input type='hidden' name='del' value='%s %s %s'>\n",name,fname,genre);
        fprintf(fpw," <input type='submit' value='SUP'  ></form></td></tr>\n");
    }
    }
    fclose(fpr);
    fclose(fpw);
}


void modif()
{
    char ligne[256];
    char name[100],fname[100], pwd[100],genre[5];
    FILE *fpr=fopen("/var/www/html/inscription/inscri/inscri.txt","r");
    FILE *fpw=fopen("/var/www/html/inscription/inscri/modification.html","w");

    if(fpw==NULL || fpr==NULL)
        printf("BASE DE DONNE FERME");

    else{
        fprintf(fpw,"<!DOCTYPE html>  <html lang='en'><head>\n");
        fprintf(fpw," <meta charset='UTF-8'>\n");
        fprintf(fpw,"<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n");
        fprintf(fpw," <title>MODIFICATION</title>\n");
        fprintf(fpw," <style>\n");
        fprintf(fpw," body{ margin: 0; padding: 0;\n");
        fprintf(fpw," background-color: rgb(205, 233, 163);}\n");

        fprintf(fpw," .retour{background-color: rgb(151, 193, 87);\n");
        fprintf(fpw,"width: 100px;height: 30px;position:fixed;\n");
        fprintf(fpw," top:0%%; left: 90%%;transform: translate(-80%%, -0%%);\n");
        fprintf(fpw," margin: 10px -10px;border-radius: 5px;text-align: center;}\n");

        fprintf(fpw," h3{width: 75%%; text-transform: uppercase;\n");
        fprintf(fpw,"background-color: rgb(151, 193, 87);\n");
        fprintf(fpw," font-size: 24px;color: blue;text-align: center;\n");
        fprintf(fpw,"position: relative;text-decoration:underline;\n");
        fprintf(fpw,"top: 50%%; left: 50%%; transform: translate(-50%%, -50%%);\n");
        fprintf(fpw," border-radius: 5px; margin: 100px 10px;padding: 10px; }\n");


        fprintf(fpw," .menudepart{width:50%%; height: 5%%;margin: 10px  5px 30px ;\n");
        fprintf(fpw," background:linear-gradient(to left,#445c0f,#1d2d0c);\n");
        fprintf(fpw," position: absolute;top: 20%%;left: 40%%;transform: translate(-40%%, -25%%);\n");
        fprintf(fpw," font-size: 30px;border-radius: 20px;\n");
        fprintf(fpw," color: #fff;text-decoration: none;text-align: center;\n");
        fprintf(fpw," @media (max-width:800px) {");
        fprintf(fpw,"font-size:20px;  width:45%%;margin: 10px  5px ;height: 4%%; }}\n");

        fprintf(fpw," .button{background-color: rgb(14, 73, 2);transform: translate(-80%%,-50%%);\n");
        fprintf(fpw,"  width: 100px;height: 30px; position:fixed; top:21%%; left: 90%%;\n");
        fprintf(fpw," margin: 10px -10px;font-size: larger;color: #fff;border-radius: 10px;\n");
        fprintf(fpw," text-align: center;transition: 0.3s;}\n");
        fprintf(fpw," .button:hover{cursor: pointer;background-color: rgb(10, 12, 4);font-weight: 700;}\n");

        fprintf(fpw,"</style></head><body> <h3>  Modification  </h3>\n");
        fprintf(fpw,"  <div class='retour'><a href='inscri.html' >Liste</a>\n ");
        fprintf(fpw," <form action='htmlM.cgi' method='get'>\n ");

        fprintf(fpw,"  </div><input list='from'  class='menudepart'required placeholder=' ....Modifier....' name='mod' >\n");
        fprintf(fpw," <input type='submit'class='button'  value='Modifier'  ><datalist id='from' >\n");


            while(fgets(ligne,256,fpr))
            {
                sscanf(ligne,"name=%[^&]&pre=%[^&]&genre=%[^&]&pwd=%s",name,fname,genre,pwd);
                fprintf(fpw,"<option>%s %s %s</option>\n",name,fname,genre);
            }
    fclose(fpr);
    fclose(fpw);
    }
}


void suppr()
{
    FILE *fpw=fopen("/var/www/html/inscription/inscri/suppression.html","w");
    FILE *fpr=fopen("/var/www/html/inscription/inscri/inscri.txt","r");
    char ligne[256];
    char name[100],fname[100],pwd[100],genre[5];

    if(fpw==NULL || fpr==NULL)
        printf("BASE DE DONNE FERME");

    else{
        fprintf(fpw," <!DOCTYPE html>  <html lang='en'><head>");
        fprintf(fpw,"  <meta charset='UTF-8'>");
        fprintf(fpw," <meta name='viewport' content='width=device-width, initial-scale=1.0'>");
        fprintf(fpw,"  <title>SUPpression</title>");
        fprintf(fpw,"  <style>");
        fprintf(fpw,"body{ margin: 0; padding: 0;");
        fprintf(fpw,"  background-color: rgb(205, 233, 163);}");

        fprintf(fpw," .retour{background-color: rgb(151, 193, 87);");
        fprintf(fpw," width: 100px;height: 30px;position:fixed;");
        fprintf(fpw,"  top:0%%; left: 90%%;transform: translate(-80%%, -0%%);");
        fprintf(fpw,"  margin: 10px -10px;border-radius: 5px;text-align: center;}");

        fprintf(fpw," h3{width: 75%%; text-transform: uppercase;");
        fprintf(fpw," background-color: rgb(151, 193, 87);");
        fprintf(fpw,"  font-size: 24px;color: blue;text-align: center;");
        fprintf(fpw," position: relative;text-decoration:underline;");
        fprintf(fpw," top: 50%%; left: 50%%; transform: translate(-50%%, -50%%);");
        fprintf(fpw,"  border-radius: 5px; margin: 100px 10px;padding: 10px; }");


        fprintf(fpw," .menudepart{width:50%%; height: 5%%;margin: 10px  5px 30px ;");
        fprintf(fpw,"  background:linear-gradient(to left,#445c0f,#1d2d0c);");
        fprintf(fpw,"  position: absolute;top: 20%%;left: 40%%;transform: translate(-40%%, -25%%);");
        fprintf(fpw," font-size: 30px;border-radius: 20px;");
        fprintf(fpw," color: #fff;text-decoration: none;text-align: center;");
        fprintf(fpw," @media (max-width:800px) {");
        fprintf(fpw,"  font-size:20px;  width:45%%;margin: 10px  5px ;height: 4%%; }}");

        fprintf(fpw," .button{background-color: rgb(14, 73, 2);transform: translate(-80%%, -50%%);");
        fprintf(fpw," width: 100px;height: 30px; position:fixed; top:21%%; left: 90%%;");
        fprintf(fpw,"margin: 10px -10px;font-size: larger;color: #fff;border-radius: 10px;");
        fprintf(fpw,"  text-align: center;transition: 0.3s;}");
        fprintf(fpw," .button:hover{cursor: pointer;background-color: rgb(10, 12, 4);font-weight: 700;}");

        fprintf(fpw," </style></head><body> <h3>  SUPpression  </h3>");
        fprintf(fpw,"  <div class='retour'><a href='inscri.html' >Liste</a> ");
        fprintf(fpw,"  <form action='html12.cgi' method='get'> ");
        fprintf(fpw,"  </div><input list='from'  class='menudepart' placeholder=' ....SUPprimer....' required  name='del'>");
        fprintf(fpw," <input type='submit'class='button' value='Supprimer' ><datalist id='from' >");


            while(fgets(ligne,256,fpr))
            {
                sscanf(ligne,"name=%[^&]&pre=%[^&]&genre=%[^&]&pwd=%s",name,fname,genre,pwd);
                fprintf(fpw,"<option>%s %s %s</option>\n",name,fname,genre);
            }

    fclose(fpr);
    fclose(fpw);
    }
}
 void readf( )
 {
    writef();
    suppr();
    modif();
}
