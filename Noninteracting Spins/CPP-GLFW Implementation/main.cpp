#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//this code is incomplete

void square(float i, float j,float side, float offsetX, float offsetY);
void grid(float spacing,int number);

int main(void)
{
    int side=30;
    int windowSize = (0.5+(float)sqrt(side)/150)*side*side;

    float spacing = (float)side/windowSize;

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowSize, windowSize, "Lattice", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        int Fill[side][side];


        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        grid(spacing,side);
        for (int i=0;i<side;i++){
            for (int j=0;j<side;j++){
                Fill[i][j]=2*(rand()%2)-1; //Setting up random spins as -1 or +1
                if (Fill[i][j]==1) square(i,j,spacing,(float)side/2,(float)side/2);
            };
            //printf("\n");
        };

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

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
