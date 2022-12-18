#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double func(double x);
int W_files(double x, int N, double delta,char group[50], char name[50]);
void binary_print(char group[50], char name[50]);
int main()
{
    char group[50]={0}, name[50]={0};
    double x1, x2, delta;
    int N;
    FILE* input_W = fopen ("Input.txt", "r");
    if (input_W==NULL)
    {
        printf("The file couldn`t be open");
    }
    else
    {
        fscanf(input_W, "%lf %lf %d %lf %s %s", &x1, &x2, &N, &delta, group, name);
        fclose(input_W);
        if(N==0)
        {
            N = ((x2 - x1) / delta) + 1;
        }
        else if( delta!=((x2 - x1) / (N - 1)))
        {
            delta = (x2 - x1) / (N - 1);
        }
        int check=0;
        check=W_files(x1,N,delta,group,name);
        if(check==1)
        {
            binary_print(group,name);
        }
    }
    return(0);
}
double func(double x)
{
    return 0.25*pow((x-25),2)+pow((x+25),3)/100+1;
}
int W_files(double x, int N, double delta,char group[50], char name[50])
{
    FILE* input_table = fopen ("Table.txt", "w");
    FILE* bina = fopen ("Binary.bin", "w+b");
    if (input_table==NULL || bina==NULL)
    {
        printf("The file couldn`t be open");
        return(0);
    }
    else
    {
        fwrite(&N, sizeof(int), 1, bina);
        fprintf(input_table, "N\tx\tf(x)\n");
        for(int i=0;i<N;i++)
        {
            fprintf(input_table,"%d\t",i+1);
            fprintf(input_table,"%.1f\t",x);
            fprintf(input_table,"%.2f\n",func(x));
            //---------------------------------
            fwrite(&x, sizeof(double), 1, bina);
            double z;
            z=func(x);
            fwrite(&z,sizeof(double),1, bina);
            x+=delta;
        }
        fprintf(input_table, "%s, %s", group, name);
        fclose(input_table);
        fclose(bina);
        return(1);
    }
}
void binary_print(char group[50], char name[50])
{
    int N=0;
    double Num=0;
    FILE* bina = fopen("Binary.bin", "r+b");
    if (bina==NULL)
    {
         printf("Error, the binary file don't exist");
    }
    else
    {
        printf("\n****************************");
        printf("\n*  N   *   X    *   F(X)   *");
        printf("\n****************************\n");
        fread(&N, sizeof(int), 1, bina);
        for(int i=0; i<N; i++)
        {
            printf("|%d\t|",i+1);
            fread(&Num, sizeof(double), 1, bina);
            printf("%.1f\t|", Num);
            fread(&Num, sizeof(double), 1, bina);
            printf("%.2f", Num);
            printf("\n");
        }
        printf("--------------------------\n");
        printf("%s, %s", group, name);
        fclose(bina);
    }
}
