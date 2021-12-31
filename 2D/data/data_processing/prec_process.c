#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* openFile(char* filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
        printf("Error in load file : can't open '%s'\n", filename);
    return fp;
}

int main(int argc, char** argv)
{
    if (argc<5) {printf("Usage : '%s' [size] [filename1] [filename2] [filename3]\n", argv[0]) ; return 1;}

    int N = atoi(argv[1]);

    // Number of time steps
    int Nt = 10;

    // Positions for particule i, at time j, on axis k
    double pos1[N][Nt][2];
    double pos2[N][Nt][2];
    double pos3[N][Nt][2];

    // Array to store processed data
    double meanPos1[Nt][2] ;
    double meanPos2[Nt][2] ;
    double meanPos3[Nt][2] ;


    // Initialiaze arrays
    for(int n=0 ; n<Nt ; n++)
    {
        meanPos1[n][1] = 0 ; meanPos1[n][2] = 0 ;
        meanPos2[n][1] = 0 ; meanPos2[n][2] = 0 ;
        meanPos3[n][1] = 0 ; meanPos3[n][2] = 0 ;
    }
    
    FILE *f1   = openFile(argv[2]);
    FILE *f2   = openFile(argv[3]);
    FILE *f3   = openFile(argv[4]);

    double p1x, p1y;
    double p2x, p2y;
    double p3x, p3y;

    // Getting data
    for(int n=0 ; n<Nt ; n++) {
        for(int i=0 ; i<N ; i++)
        {
        fscanf(f1,   "%lf %lf\n", &p1x, &p1y);
        fscanf(f2,   "%lf %lf\n", &p2x, &p2y);
        fscanf(f3,   "%lf %lf\n", &p3x, &p3y);

        pos1[i][n][1] = p1x ; pos1[i][n][2] = p1y;
        pos2[i][n][1] = p2x ; pos2[i][n][2] = p2y;
        pos3[i][n][1] = p3x ; pos3[i][n][2] = p3y;
        }
    }

    // Mean
    for(int n=0 ; n<Nt ; n++){
        for(int i=0 ; i<N ; i++)
        {
            meanPos1[n][1] += pos1[i][n][1]/N;
            meanPos1[n][2] += pos1[i][n][2]/N;

            meanPos2[n][1] += pos2[i][n][1]/N;
            meanPos2[n][2] += pos2[i][n][2]/N;

            meanPos3[n][1] += pos3[i][n][1]/N;
            meanPos3[n][2] += pos3[i][n][2]/N;

        }
    }
    
    // Writing processed data
    FILE *fdeltas1 = fopen("data/files/prec1.dat" , "wb");
    FILE *fdeltas2 = fopen("data/files/prec2.dat" , "wb");
    
    for(int n=0 ; n<Nt ; n++)
        {
            fprintf(fdeltas1, "%d %.12lf %.12lf\n", n, meanPos2[n][1] - meanPos1[n][1], meanPos2[n][2] - meanPos1[n][2]);
            fprintf(fdeltas2, "%d %.12lf %.12lf\n", n, meanPos3[n][1] - meanPos1[n][1], meanPos3[n][2] - meanPos1[n][2]);
        }

    fclose(f1);
    fclose(f2);
    fclose(f3);

    fclose(fdeltas1);
    fclose(fdeltas2);

    return 0;
}