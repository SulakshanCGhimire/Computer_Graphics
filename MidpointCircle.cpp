// Midpoint Circle Algorithm
#include <graphics.h> // Include graphics library for drawing
#include <conio.h>    // Include console I/O library for getch()
#include <stdio.h>    // Include standard I/O library
// Function to draw a circle using the Midpoint Circle Algorithm
void drawCircleMidpoint(int xc, int yc, int radius, int color) {
    int x = 0;                     // Initialize x to 0
    int y = radius;                // Initialize y to the radius
    int p = 1 - radius;            // Initial decision parameter
    // Plot the initial points in all octants
    while (x <= y) {
        // Plot points in all octants
        putpixel(xc + x, yc + y, color); // Octant 1
        putpixel(xc - x, yc + y, color); // Octant 2
        putpixel(xc + x, yc - y, color); // Octant 3
        putpixel(xc - x, yc - y, color); // Octant 4
        putpixel(xc + y, yc + x, color); // Octant 5
        putpixel(xc - y, yc + x, color); // Octant 6
        putpixel(xc + y, yc - x, color); // Octant 7
        putpixel(xc - y, yc - x, color); // Octant 8
        // Update the decision parameter
        if (p < 0) {
            p += 2 * x + 3; // Move to the next pixel in the x-direction
        } else {
            p += 2 * (x - y) + 5; // Move to the next pixel in the y-direction
            y--; // Decrement y
        }
        x++; // Increment x
    }
}
int main() {
    int gd = DETECT, gm; // Graphics driver and mode
    int xc = 300, yc = 250; // Center of the circle
    int radius = 150;       // Radius of the circle
    // Initialize graphics mode
    initgraph(&gd, &gm, "");
    // Draw the circle using the Midpoint Circle Algorithm
    drawCircleMidpoint(xc, yc, radius, RED);
    // Wait for a key press to close the graphics window
    getch();
    // Close the graphics mode
    closegraph();
    return 0;
}
