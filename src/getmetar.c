/*
    Programa que gera comandos wget para baixar
    METAR do site www.wunderground.com
    Autor: Rodrigo Matola de Miranda Cardoso
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>


int main (void){

int di, mi, yi;
int df, mf, yf;
int l,n,i,d,m,y,j;
int k;
int dji, djf; 
char codigo[10]; 
int temp;

FILE *output;

do{
    printf("Entre com a sigla da estacao (ex.: SBGL)\n");
    fgets(codigo, 10, stdin);

    if(strlen(codigo) > 5)
        printf("Erro! Sigla com mais de 4 (quatro) letras.\nTente novamente.\n");

} while(strlen(codigo) > 5);

for(k = 0; k < strlen(codigo); k++)
    codigo[k] = toupper(codigo[k]);
    
codigo[strlen(codigo)-1] = '\0';

do{
    printf("Entre com o dia mes e ano inicial (formato: 01 01 1970)\n");
    scanf("%d %d %d", &di, &mi, &yi);
    if(di > 31 || mi > 12)
        printf("Erro na entrada. Tente novamente\n");

} while(di > 31 || mi > 12);

do{
    printf("Entre com o dia mes e ano final (formato: 01 01 1970)\n");
    scanf("%d %d %d", &df, &mf, &yf);
    if(df > 31 || mf > 12)
        printf("Erro na entrada. Tente novamente\n");

} while(df > 31 || mf > 12);


/* calculando os dias julianos inicial e final */
dji = ( 1461 * ( yi + 4800 + ( mi - 14 ) / 12 ) ) / 4 + 
          ( 367 * ( mi - 2 - 12 * ( ( mi - 14 ) / 12 ) ) ) / 12 - 
          ( 3 * ( ( yi + 4900 + ( mi - 14 ) / 12 ) / 100 ) ) / 4 + 
          di - 32075;

djf = ( 1461 * ( yf + 4800 + ( mf - 14 ) / 12 ) ) / 4 + 
          ( 367 * ( mf - 2 - 12 * ( ( mf - 14 ) / 12 ) ) ) / 12 - 
          ( 3 * ( ( yf + 4900 + ( mf - 14 ) / 12 ) / 100 ) ) / 4 + 
          df - 32075;

if(djf < dji){
    temp = dji;
    dji = djf;
    djf = temp;
}

/* abrindo o arquivo de saida */
output=fopen("wgetmetar","w");

fprintf(output, "#!/bin/sh\n");
fprintf(output,"# script gerado a partir do programa getmetar.c\n");
fprintf(output, "#Autor: Rodrigo Matola de Miranda Cardoso\n");
fprintf(output, "cd ..\nmkdir %s\ncd %s\n", codigo, codigo);

/* convertendo de dia juliano pra o calendario civil */
for (k = dji; k <= djf; k++){

 l = k + 68569;
        n = ( 4 * l ) / 146097;
        l = l - ( 146097 * n + 3 ) / 4;
        i = ( 4000 * ( l + 1 ) ) / 1461001;
        l = l - ( 1461 * i ) / 4 + 31;
        j = ( 80 * l ) / 2447;
        d = l - ( 2447 * j ) / 80;
        l = j / 11;
        m = j + 2 - ( 12 * l );
        y = 100 * ( n - 49 ) + i + l;

fprintf(output, "wget -O %d-%d-%d-%s.txt \"http://www.wunderground.com/history/airport/%s/%d/%d/%d/DailyHistory.html?req_city=NA&req_state=NA&req_statename=NA&format=1\"\n", y, m, d, codigo, codigo, y, m, d);
}

fprintf(output, "cd ..");

return 0;
}
