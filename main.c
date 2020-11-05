#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "header.h"

/**
* @file main.c
* @author Jan Bobrowski
* @date 01.11.2020
* @brief Glowny plik projektu
*
*\mainpage Opis projektu
* Kalkulator macierzy wczytywanych z plikow tekstowych.
* Po uruchomieniu programu pojawia sie mozliwosc wyboru,
* czy chcemy dopisac wyniki do istniejacych, badz czy chcemy wyczyscic plik i zaczac wpisywac od nowa.
* Nastepnie uzytkownik jest proszony o podanie wymiarow obydwu macierzy. Jesli nie beda sie zgadzac z tymi podanymi w plikach,
  to beda one odpowiednio skracane lub beda dopisywane zera.
* Np. Jesli macierz w pliku bedzie wymiarow 3x3, a podamy 2x2, to zostanie pobrana macierz 2x2.
  W przypadku, gdy podamy wymiar 3x3, a w pliku bedzie macierz 3x3,
* to zostanie dodana trzecia kolumna i trzeci wiersz z samymi zerami.
* Nastepnie wyswietlaja sie obie macierze oraz pojawia sie menu wyboru, ktore pyta jakie chcemy wykonac dzialanie.
  Do wyboru jest: dodawanie, odejmowanie (2 od 1 lub 1 od 2), mnozenie (1 z 2 i odwrotnie), transpozycja (1 lub 2).
  Po wykonaniu dzialania wyswietla sie wynik.
  Mozna wykonac wiele dzialan.

*/

/** Glowna funkcja main
Zmienne:
\param matt11 - wczytywana macierz 1
\param matt22 - wczytywana macierz 2
\param addedMatrix - suma macierzy
\param subMatrix - roznica macierzy
\param matt22 - wczytywana macierz 2
\param mulMatrix, mulMatrix2 - wymnozone macierze (potrzebne sa dwie, ze wzgledu na to, iz rozmiar jest zalezny od kolejnosci mnozenia
\param transposedMatrix1, transposedMatrix2 - przetransponowane macierze
 \param w1 - ilosc wierszy w 1 macierzy
\param k1 - ilosc kolumn w 1 macierzy
\param w2 - ilosc wierszy w 2 macierzy
\param wk2 - ilosc kolumn w 2 macierzy
\param i, j - iteratory petl for
\param wybor - zmienna przechowujaca wybor dzialania, jakie uzytkownik chce dokonac
\param save - zmienna przechowujaca wybor, czy uzytkownik chce nadpisac plik czy zostawic poprzednie wyniki

*/
int main()
{
        /** Deklaracja wskaznikow */
        double **mat11;
        double **mat22;
        double **addedMatrix;
        double **subMatrix;
        double **mulMatrix;
        double **mulMatrix2;
        double **transposedMatrix1;
        double **transposedMatrix2;
        int w1,k1,w2,k2;
        int i, j,wybor;
        char save;

        /**Menu glowne*/
        printf("Witaj w kalkulatorze macierzy!\nNacisnij 1 jesli chcesz nadpisac poprzednie wyniki, jesli nie- nacisnij dowolny inny klawisz.\n");
        save=getch();
        /** jesli uzytkownik wybral 1, to nadpisujemy plik z wynikami */
        if(save=='1')
        {
            FILE *res = fopen("results.txt", "w");
            fprintf(res,"Twoje wyniki:\n");
            fclose(res);

        }
        /** Podawanie wymiarow macierzy*/

        printf("Podaj wymiary macierzy 1:\nLiczba wierszy:\n");
        scanf("%d",&w1);
        printf("\nLiczba kolumn:\n");
        scanf("%d",&k1);
        printf("Wymiary macierzy 1 to:\n%d x %d\n\n",w1,k1);
        printf("\nPodaj wymiary macierzy 2:\nLiczba wierszy:\n");
        scanf("%d",&w2);
        printf("\nLiczba kolumn:\n");
        scanf("%d",&k2);


        /** Alokacja pamieci dla wczytywanych macierzy oraz macierzy z wynikami */
        mat11 = (double**)malloc(w1*sizeof(double*));
        addedMatrix = (double**)malloc(w1*sizeof(double*));
        subMatrix = (double**)malloc(w1*sizeof(double*));
        mulMatrix = (double**)malloc(w1*sizeof(double*));
        mulMatrix2 = (double**)malloc(w2*sizeof(double*));
        for (i=0; i<w1; i++){
            mat11[i] = (double*)malloc(k1*sizeof(double));
            addedMatrix[i] = (double*)malloc(k1*sizeof(double));
            subMatrix[i] = (double*)malloc(k1*sizeof(double));
            mulMatrix[i] = (double*)malloc(k2*sizeof(double));
        }
        for(i=0;i<w2;i++)
        {
            mulMatrix2[i]=(double*)malloc(k1*sizeof(double));
        }
        mat22 = (double**)malloc(w2*sizeof(double*));
        for (i=0; i<w2; i++){
            mat22[i] = (double*)malloc(k2*sizeof(double)); //creating dynamic 2D array
        }
        transposedMatrix1 = (double**)malloc(k1*sizeof(double*));
        for (i=0; i<k1; i++){
            transposedMatrix1[i] = (double*)malloc(w1*sizeof(double)); //creating dynamic 2D transposed

        }
        transposedMatrix2 = (double**)malloc(k1*sizeof(double*));
        for (i=0; i<k1; i++){
            transposedMatrix2[i] = (double*)malloc(w1*sizeof(double)); //creating dynamic 2D transposed

        }


        /**wczytywanie macierzy z plikow*/
        FILE *file1 = fopen("matrix1.txt", "r");
        /**program wczytuje macierz dopoki nie napotka konca pliku */

        while(!feof(file1))
        {
        for(i=0;i<w1;i++){
            for(j=0;j<k1;j++){
                fscanf(file1,"%lf,", &mat11[i][j]);
            }

        }
        }
        fclose(file1);


        /** wypisywanie macierzy 1 */
        printf("\nMacierz 1:\n");
        for(i=0;i<w1;i++)
        {

            for(j=0;j<k1;j++)
            {

                printf("%.2f ", mat11[i][j]);
            }
            printf("\n");
        }

        /** wczytwanie i wypisanie macierzy 2 */
        FILE *file2 = fopen("matrix2.txt", "r"); //reading 2nd matrix from .txt
        while(!feof(file2)) //to the end of the file...
        {
        for(i=0;i<w2;i++){
            for(j=0;j<k2;j++){
                fscanf(file2,"%lf,", &mat22[i][j]);
            }
        }
        }
        fclose(file2);
        printf("\nMacierz 2:\n");
        for(i=0;i<w2;i++)
        {

            for(j=0;j<k2;j++)
            {

                printf("%.2f ", mat22[i][j]);
            }
            printf("\n");
        }

        /** petla do{} while, w ktorej uzytkownik wybiera dzialanie do wykonania.
        Kazda funkcja w ostatnim argumencie pobiera tablice, w ktorej zapisywany bedzie wynik.
        */
        do{
        printf("Jakie dzialania chcesz wykonac?\nWybierz numer akcji i zatwierdz enterem:\n1 - jesli chcesz wykonac dodawanie\n2 - jesli chcesz odjac macierz 2 od 1\n3 - jesli chcesz odjac macierz 1 od 2\n4 - jesli chcesz pomnozyc macierz 1 z 2\n5 - jesli chcesz pomnozyc macierz 2 z 1\n6 - jesli chcesz transponowac macierz 1\n7 - jesli chcesz transponowac macierz 2\n0 - jesli chcesz wylaczyc kalkulator\n");
        scanf("%d",&wybor);
        switch(wybor){
        case 1:{
            addition(w1,k1,w2,k2,mat11,mat22,addedMatrix);
            break;}
        case 2:{
            substraction(w1,k1,w2,k2,mat11,mat22,subMatrix);
            break;}
        case 3:{
            substraction(w2,k2,w1,k1,mat22,mat11,subMatrix);
            break;}
        case 4:{
            multiplication(w1,k1,w2,k2,mat11,mat22,mulMatrix);
            break;}
        case 5:{
            multiplication(w2,k2,w1,k1,mat22,mat11,mulMatrix2);
            break;}
        case 6:{
            transpose(w1,k1,mat11,transposedMatrix1);
            break;}
        case 7:{
            transpose(w2,k2,mat22,transposedMatrix2);
            break;}
        case 0:{
            printf("\nDziekuje za skorzystanie z mojego kalkulatora!!!\n");
            break;
        }
        default:{
            printf("\nNiepoprawny wybor, sprobuj jeszcze raz!!\n\n");
            getch();
            break;
        }

        }
        }while(wybor!=0);

        return 0;


}
/**Procedura wykonujaca dodawanie dwoch macierzy.
\param row1 - liczba wierszy 1 macierzy
 \param col1 - liczba kolumn 1 macierzy
\param row2 - liczba wierszy 2 macierzy
\param col2 - liczba kolumn 2 macierzy
\param **m1 - wskaznik do macierzy 1
\param **m2 - wskaznik do macierzy 2
\param **resultMatrix - wskaznik do macierzy wynikowej
 Procedura ta zapisuje sume tych macierzy do pliku results.txt wynik
 oraz wypisuje ja w konsoli.
 */
void addition(int row1, int col1, int row2, int col2, double** m1, double** m2,double** resultMatrix)
{

        int i,j;
        FILE *res = fopen("results.txt", "a");
        if(row1==row2 && col1==col2){
        printf("Suma tych macierzy to:\n");
        fprintf(res,"Suma tych macierzy to:\n");

        for(i=0;i<row1;i++)
        {
            for(j=0;j<col1;j++)
            {
                resultMatrix[i][j]=m1[i][j]+m2[i][j];
                printf("%.2f ", resultMatrix[i][j]);
                fprintf(res,"%.2f, ",resultMatrix[i][j]);

            }
            printf("\n");
            fprintf(res,"\n");
        }
        fclose(res);



        printf("\n\n\nNacisnij dowolny klawisz aby powrocic do menu glownego\n\n\n");
        getch();
        }
        else{
            fclose(res);
            printf("Nie mozna dodac tych macierzy, ze wzgledu na rozne wymiary!!!\nSprobuj jeszcze raz!\n\n\nNacisnij dowolny klawisz aby powrocic do menu glownego\n\n\n");
            getch();
        }



}
/**Procedura wykonujaca odejmowanie dwoch macierzy.
\param row1 - liczba wierszy 1 macierzy
 \param col1 - liczba kolumn 1 macierzy
\param row2 - liczba wierszy 2 macierzy
\param col2 - liczba kolumn 2 macierzy
\param **m1 - wskaznik do macierzy 1
\param **m2 - wskaznik do macierzy 2
\param **resultMatrix - wskaznik do macierzy wynikowej
 Procedura ta zapisuje roznice tych macierzy do pliku results.txt wynik
 oraz wypisuje ja w konsoli.
 */
void substraction(int row1, int col1, int row2, int col2, double** m1, double** m2,double** resultMatrix)
{

        int i,j;
        FILE *res = fopen("results.txt", "a");
        if(row1==row2 && col1==col2){
        printf("Roznica tych macierzy to: to:\n");
        fprintf(res,"Roznica tych macierzy to:\n");

        for(i=0;i<row1;i++)
        {
            for(j=0;j<col1;j++)
            {
                resultMatrix[i][j]=m1[i][j]-m2[i][j];
                printf("%.2f ", resultMatrix[i][j]);
                fprintf(res,"%.2f, ",resultMatrix[i][j]);

            }
            printf("\n");
            fprintf(res,"\n");
        }
        fclose(res);
        printf("\n\n\nNacisnij dowolny klawisz aby powrocic do menu glownego\n\n\n");
        getch();
        }
        else{
            fclose(res);
            printf("Nie mozna odjac tych macierzy, ze wzgledu na rozne wymiary!!!\nSprobuj jeszcze raz!\n\n\nNacisnij dowolny klawisz aby powrocic do menu glownego\n\n\n");
            getch();
        }



}
/**Procedura wykonujaca mnozenie dwoch macierzy.
\param row1 - liczba wierszy 1 macierzy
 \param col1 - liczba kolumn 1 macierzy
\param row2 - liczba wierszy 2 macierzy
\param col2 - liczba kolumn 2 macierzy
\param **m1 - wskaznik do macierzy 1
\param **m2 - wskaznik do macierzy 2
\param **resultMatrix - wskaznik do macierzy wynikowej
 Procedura ta zapisuje iloczyn tych macierzy do pliku results.txt wynik
 oraz wypisuje ja w konsoli.
 */
void multiplication(int row1, int col1, int row2, int col2, double** m1, double** m2,double** resultMatrix)
{
        int i,j,k;
        FILE *res = fopen("results.txt", "a");
        if(col1==row2){
        printf("Iloczyn tych macierzy to:\n");
        fprintf(res,"Iloczyn tych macierzy to:\n");

        for(i=0;i<row1;i++)
        {

            for(j=0;j<col2;j++)
            {
                resultMatrix[i][j]=0;
                for(k=0;k<col2;k++)
                {
                    resultMatrix[i][j]+=m1[i][k]*m2[k][j];
                }
                printf("%.2f ", resultMatrix[i][j]);
                fprintf(res,"%.2f, ",resultMatrix[i][j]);
            }
            printf("\n");
            fprintf(res,"\n");
        }
        fclose(res);
        printf("\n\n\nNacisnij dowolny klawisz aby powrocic do menu glownego\n\n\n");
        getch();
        }
        else{
            fclose(res);
            printf("Nie mozna pomnozyc tych macierzy, ze wzgledu na rozne wymiary!!!\nSprobuj jeszcze raz!\n\n\nNacisnij dowolny klawisz aby powrocic do menu glownego\n\n\n");
            getch();
        }
}
/**Procedura wykonujaca transpozycje macierzy.
 \param row1 - liczba wierszy 1 macierzy
 \param col1 - liczba kolumn 1 macierzy
 \param **m1 - wskaznik do macierzy 1
 \param **resultMatrix - wskaznik do macierzy wynikowej
 Procedura ta zapisuje macierz transponowana w pliku results.txt
 oraz wypisuje ja w konsoli.
 */
void transpose(int row1, int col1, double** m1,double** resultMatrix)
{
        int i,j;
        FILE *res = fopen("results.txt", "a");

        printf("Transponowana macierz:\n");
        fprintf(res,"Transponowana macierz:\n");

        for(i=0;i<row1;i++)
        {

            for(j=0;j<col1;j++)
            {
                resultMatrix[j][i]=m1[i][j];

            }
            ;
        }
        for(i=0;i<col1;i++)
        {
            for(j=0;j<row1;j++)
            {
                printf("%.2f ", resultMatrix[i][j]);
                fprintf(res,"%.2f, ",resultMatrix[i][j]);
            }
            printf("\n");
            printf("\n");
            fprintf(res,"\n");
        }
        fclose(res);
        printf("\n\n\nNacisnij dowolny klawisz aby powrocic do menu glownego \n\n\n");
        getch();

}
