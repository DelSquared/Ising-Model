#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//be sure to include GLFW. I used this video https://www.youtube.com/watch?v=0WrSGMuU964

void square(float i, float j,float side, float offsetX, float offsetY); //functions for drawing
void grid(float spacing,int number);

int main(void)
{
    int side=30; 
    int windowSize = (0.5+(float)sqrt(side)/120)*side*side;
    float spacing = (float)side/windowSize; //setting up canvas
    
    srand(time(NULL));
    //Randomising seed a bit better using time(NULL).
    //Change to a fixed number to generate the same lattice each run

    //grid sides [HC]
    int S [side][side]; //setting up square spin lattice

    int up=0, down=0; //Total up and down spins
    int M=0; //Magnetisation
    float Ebar=0,T=5,B=1,E=0; //Average energy per site, Temperature[UI], External field[UI], and total Energy
    double Z=0; //Partition function

    printf("Input T: ");
    scanf("%f",&T);
    printf("Input B: ");
    scanf("%f",&B);

    for (int i=0;i<side;i++){
        for (int j=0;j<side;j++){
            S[i][j]=2*(rand()%2)-1; //Setting up random spins as -1 or +1
            if (S[i][j]==1) up++;
            else down++; //Counting spins
        };
    };
    Z=(double)up*exp(B/T)+down*exp(-B/T); //Z=sum(exp(-E[i][j]/kT)) and E[i][j]=-B*S[i][j]
    M=up-down; //Determining M
    E=abs((float)M*B); //Determining E
    Ebar=(float)E/((float)side*(float)side); //Determining <E>
    printf("\nUp:\t%d\tDown:\t%d\n\n",up,down);
    printf("net M:\t%d\n",M);
    printf("Z:\t%f\n",Z);
    printf("E:\t%f\n",E);
    printf("<E>:\t%f\n",(-B*up*exp(B/T)+B*down*exp(-B/T))/Z);
    printf("Ebar:\t%f\n\n",Ebar);
    printf("\nP(U):\t%f\nP(D):\t%f\n\n",up*exp(B/T)/Z,down*exp(-B/T)/Z);

    GLFWwindow* window;

    //Initialize the library
    if (!glfwInit())
        return -1;

    //Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(windowSize, windowSize, "Lattice", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //Make the window's context current
    glfwMakeContextCurrent(window);

    //Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        grid(spacing,side);
        for (int i=0;i<side;i++){
            for (int j=0;j<side;j++){
                if (S[i][j]==1) square(i,j,spacing,(float)side/2,(float)side/2);
            };
        };
        //Swap front and back buffers
        glfwSwapBuffers(window);

        //Poll for and process events
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
//functions for canvas rendering
void grid(float spacing,int number) {
    float side = (float)number*spacing;

    for(int x = 0; x <= number; x++){
        glBegin(GL_LINE_LOOP);
        glVertex2f((float)x*spacing-side/2.0f,-side/2.0f);
        glVertex2f((float)x*spacing-side/2.0f,side/2.0f);
        glEnd();
        };

    for(int y = 0; y <= number; y++){
        glBegin(GL_LINE_LOOP);
        glVertex2f(-side/2.0f,(float)y*spacing-side/2.0f);
        glVertex2f(side/2.0f,(float)y*spacing-side/2.0f);
        glEnd();
    };
}

void square(float i, float j,float side, float offsetX, float offsetY) {
    float x = (i-offsetX+0.5f)*side, y = (j-offsetY+0.5f)*side;
    glBegin(GL_POLYGON);
    glVertex2f(-side/2.0f+x,side/2.0f+y);
    glVertex2f(side/2.0f+x,side/2.0f+y);
    glVertex2f(side/2.0f+x,-side/2.0f+y);
    glVertex2f(-side/2.0f+x,-side/2.0f+y);
    glEnd();
}
