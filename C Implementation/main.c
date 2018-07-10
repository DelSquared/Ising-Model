#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() //The [HC] tag in the comments is to notify hard-coded parameters. [UI] is user input
{
    int i,j;
    srand(time(NULL));
    //Randomising seed a bit better using time(NULL).
    //Change to a fixed number to generate the same lattice each run

    int side=25; //square sides [HC]
    int S [side][side]; //setting up square spin lattice

    int up=0, down=0; //Total up and down spins
    int M=0,E=0; //Magnetisation, and total Energy
    float Ebar=0,T=0.1,B=2; //Average energy per site, Temperature[UI], and External field[UI]
    double Z=0; //Partition function

    printf("Input T: ");
    scanf("%f",&T);
    printf("Input B: ");
    scanf("%f",&B);

    for (i=0;i<side;i++){
        for (j=0;j<side;j++){
            S[i][j]=2*(rand()%2)-1; //Setting up random spins as -1 or +1
            printf("%d\t",S[i][j]); //Printing lattice purely for visual reasons. Can be commented out
            if (S[i][j]==1) up++;
            else down++; //Counting spins
        }
        printf("\n");
    }
    Z=(double)up*exp(B/T)+down*exp(-B/T); //Z=sum(exp(-E[i][j]/kT)) and E[i][j]=-B*S[i][j]
    M=up-down; //Determining M
    E=abs(M*B); //Determining E
    Ebar=(float)E/(side*side); //Determining <E>
    printf("\nUp:\t%d\tDown:\t%d\n\n",up,down);
    printf("net M:\t%d\n",M);
    printf("Z:\t%f\n",Z);
    printf("E:\t%d\n",E);
    printf("<E>:\t%d\n",(B*up*exp(B/T)-B*down*exp(-B/T))/Z);
    printf("Ebar:\t%f\n\n",Ebar);
    printf("\nP(U):\t%f\nP(D):\t%f\n\n",up*exp(B/T)/Z,down*exp(-B/T)/Z);

}
