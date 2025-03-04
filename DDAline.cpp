// DDA line drawing algorithm
#include <graphics.h> // Include graphics library for drawing
#include <conio.h>    // Include console I/O library for getch()
#include <stdio.h>    // Include standard I/O library
// Function to draw a line using DDA algorithm
void drawLineDDA(int x0, int y0, int x1, int y1, int color) {
    float x, y;       // Current pixel coordinates
    float dx, dy;     // Differences in x and y
    float steps;      // Number of steps to draw the line
    int i;            // Loop counter
    // Calculate the difference between the start and end points
    dx = (float)(x1 - x0);
    dy = (float)(y1 - y0);
    // Determine the number of steps needed
    if (abs(dx) >= abs(dy)) {
        steps = abs(dx); // More steps in x-direction
    } else {
        steps = abs(dy); // More steps in y-direction
    }
    // Calculate the increment in x and y for each step
    dx = dx / steps;
    dy = dy / steps;
    // Initialize the starting point
    x = x0;
    y = y0;
    // Loop to plot the line
    for (i = 1; i <= steps; i++) {
        putpixel((int)x, (int)y, color); // Plot the pixel at (x, y)
        x += dx; // Increment x
        y += dy; // Increment y
    }
}
int main() {
    int gd = DETECT, gm; // Graphics driver and mode
    int x0 = 100, y0 = 200; // Start point of the line
    int x1 = 500, y1 = 300; // End point of the line
    // Initialize graphics mode
    initgraph(&gd, &gm, "");
    // Draw the line using DDA algorithm
    drawLineDDA(x0, y0, x1, y1, RED);
    // Wait for a key press to close the graphics window
    getch();
    // Close the graphics mode
    closegraph();
    return 0;
}
