/*
    Pour chaque version de la simulation, on a 5 fichiers de performances
    pour des tailles dans 500, 1000, 5000, 10000, 20000
    on veut avoir la moyenne des temps d'itérations pour chaque taille
    ainsi que les écarts types
*/

#include <stdio.h>

FILE* openFile(char* filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
        printf("Error in load file : can't open '%s'\n", filename);
    return fp;
}

int main()
{
    // Number of time steps used
    int Nt = 10;


    // Array to store data
    double base[5][Nt];
    double soa[5][Nt];
    double quad[5][Nt];

    // Array to store processed data
    double base_mean[5]    ; double base_sigma[5];
    double soa_mean[5]     ; double soa_sigma[5];
    double quad_mean[5]    ; double quad_sigma[5];

    double sizes[5] = {500, 1000, 5000, 10000, 20000};

    // Initialiaze arrays
    for(int i=0 ; i<5 ; i++)
    {
        base_mean[i] = 0 ; base_sigma[i] = 0;
        soa_mean[i]  = 0 ; soa_sigma[i]  = 0;
        quad_mean[i] = 0 ; quad_sigma[i] = 0;
    }

    FILE *f_base500   = openFile("data/files/base500.dat");
    FILE *f_base1000  = openFile("data/files/base1000.dat");
    FILE *f_base5000  = openFile("data/files/base5000.dat");
    FILE *f_base10000 = openFile("data/files/base10000.dat");
    FILE *f_base20000 = openFile("data/files/base20000.dat");

    FILE *f_soa500   = openFile("data/files/soa500.dat");
    FILE *f_soa1000  = openFile("data/files/soa1000.dat");
    FILE *f_soa5000  = openFile("data/files/soa5000.dat");
    FILE *f_soa10000 = openFile("data/files/soa10000.dat");
    FILE *f_soa20000 = openFile("data/files/soa20000.dat");

    FILE *f_quad500   = openFile("data/files/quad500.dat");
    FILE *f_quad1000  = openFile("data/files/quad1000.dat");
    FILE *f_quad5000  = openFile("data/files/quad5000.dat");
    FILE *f_quad10000 = openFile("data/files/quad10000.dat");
    FILE *f_quad20000 = openFile("data/files/quad20000.dat");

    double b500, b1000, b5000, b10000, b20000;
    double s500, s1000, s5000, s10000, s20000;
    double q500, q1000, q5000, q10000, q20000;
    double tmp;

    // Getting data
    for(int i=0 ; i<Nt ; i++)
    {
        fscanf(f_base500,   "%lf %lf\n", &tmp, &b500);
        fscanf(f_base1000,  "%lf %lf\n", &tmp, &b1000);        
        fscanf(f_base5000,  "%lf %lf\n", &tmp, &b5000);        
        fscanf(f_base10000, "%lf %lf\n", &tmp, &b10000);        
        fscanf(f_base20000, "%lf %lf\n", &tmp, &b20000);        

        fscanf(f_soa500,   "%lf %lf\n", &tmp, &s500);
        fscanf(f_soa1000,  "%lf %lf\n", &tmp, &s1000);        
        fscanf(f_soa5000,  "%lf %lf\n", &tmp, &s5000);        
        fscanf(f_soa10000, "%lf %lf\n", &tmp, &s10000);        
        fscanf(f_soa20000, "%lf %lf\n", &tmp, &s20000);        

        fscanf(f_quad500,   "%lf %lf\n", &tmp, &q500);
        fscanf(f_quad1000,  "%lf %lf\n", &tmp, &q1000);        
        fscanf(f_quad5000,  "%lf %lf\n", &tmp, &q5000);        
        fscanf(f_quad10000, "%lf %lf\n", &tmp, &q10000);        
        fscanf(f_quad20000, "%lf %lf\n", &tmp, &q20000);        

        base[0][i] = b500;
        base[1][i] = b1000;
        base[2][i] = b5000;
        base[3][i] = b10000;
        base[4][i] = b20000;

        soa[0][i] = s500;
        soa[1][i] = s1000;
        soa[2][i] = s5000;
        soa[3][i] = s10000;
        soa[4][i] = s20000;

        quad[0][i] = q500;
        quad[1][i] = q1000;
        quad[2][i] = q5000;
        quad[3][i] = q10000;
        quad[4][i] = q20000;
    }

    // Mean
    for(int i=0 ; i<5 ; i++)
        for(int j=0 ; j<Nt ; j++)
        {
            base_mean[i] += base[i][j]/Nt;
            soa_mean[i]  += soa[i][j]/Nt;
            quad_mean[i] += quad[i][j]/Nt;
        }

    // Standard Deviation
    for(int i=0 ; i<5 ; i++)
        for(int j=0 ; j<1000 ; j++)
        {
            base_sigma[i] += (base[i][j] - base_mean[i]) * (base[i][j] - base_mean[i]);
            soa_sigma[i]  += (soa[i][j]  - soa_mean[i])  * (soa[i][j]  - soa_mean[i]);
            quad_sigma[i] += (quad[i][j] - quad_mean[i]) * (quad[i][j] - quad_mean[i]);
        }

    
    // Writing processed data
    FILE *f_base_mean  = fopen("data/files/base_mean.dat" , "wb");
    FILE *f_soa_mean   = fopen("data/files/soa_mean.dat"  , "wb");
    FILE *f_quad_mean  = fopen("data/files/quad_mean.dat" , "wb");

    FILE *f_base_sigmam = fopen("data/files/base_sigmam.dat", "wb");
    FILE *f_base_sigmap = fopen("data/files/base_sigmap.dat", "wb");

    FILE *f_soa_sigmam  = fopen("data/files/soa_sigmam.dat" , "wb");
    FILE *f_soa_sigmap  = fopen("data/files/soa_sigmap.dat" , "wb");

    FILE *f_quad_sigmam = fopen("data/files/quad_sigmam.dat", "wb");
    FILE *f_quad_sigmap = fopen("data/files/quad_sigmap.dat", "wb");

    // Speed up
    FILE *f_quad_speedup = fopen("data/files/quad_speedup.dat", "wb");
    FILE *f_soa_speedup  = fopen("data/files/soa_speedup.dat" , "wb");

    for(int i=0 ; i<5 ; i++)
    {
        fprintf(f_base_mean, "%lf ", sizes[i]);
        fprintf(f_base_mean, "%lf \n", base_mean[i]);

        fprintf(f_soa_mean, "%lf ", sizes[i]);
        fprintf(f_soa_mean, "%lf \n" , soa_mean[i]);

        fprintf(f_quad_mean, "%lf ", sizes[i]);
        fprintf(f_quad_mean, "%lf \n", quad_mean[i]);

        fprintf(f_base_sigmap, "%lf ", sizes[i]);
        fprintf(f_base_sigmap, "%lf \n", base_mean[i] + base_sigma[i]);
        fprintf(f_base_sigmam, "%lf ", sizes[i]);
        fprintf(f_base_sigmam, "%lf \n", base_mean[i] - base_sigma[i]);

        fprintf(f_soa_sigmap, "%lf ", sizes[i]);
        fprintf(f_soa_sigmap, "%lf \n" , soa_mean[i] + soa_sigma[i]);
        fprintf(f_soa_sigmam, "%lf ", sizes[i]);
        fprintf(f_soa_sigmam, "%lf \n" , soa_mean[i] - soa_sigma[i]);

        fprintf(f_quad_sigmap, "%lf ", sizes[i]);
        fprintf(f_quad_sigmap, "%lf \n", quad_mean[i] + quad_sigma[i]);
        fprintf(f_quad_sigmam, "%lf ", sizes[i]);
        fprintf(f_quad_sigmam, "%lf \n", quad_mean[i] - quad_sigma[i]);

        // Speedup
        fprintf(f_quad_speedup, "%lf ", sizes[i]);
        fprintf(f_quad_speedup, "%lf \n", base_mean[i] / quad_mean[i]);

        fprintf(f_soa_speedup, "%lf ", sizes[i]);
        fprintf(f_soa_speedup, "%lf \n", base_mean[i] / soa_mean[i]);
    }

    fclose(f_base500);
    fclose(f_base1000);
    fclose(f_base5000);
    fclose(f_base10000);
    fclose(f_base20000);

    fclose(f_soa500);
    fclose(f_soa1000);
    fclose(f_soa5000);
    fclose(f_soa10000);
    fclose(f_soa20000);

    fclose(f_quad500);
    fclose(f_quad1000);
    fclose(f_quad5000);
    fclose(f_quad10000);
    fclose(f_quad20000);

    fclose(f_base_mean);
    fclose(f_soa_mean);
    fclose(f_quad_mean);

    fclose(f_base_sigmap);
    fclose(f_base_sigmam);
    fclose(f_soa_sigmap);
    fclose(f_soa_sigmam);
    fclose(f_quad_sigmap);
    fclose(f_quad_sigmam);

    // Speedup
    fclose(f_quad_speedup);
    fclose(f_soa_speedup);


    return 0;
}