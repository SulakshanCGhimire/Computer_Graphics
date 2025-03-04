//Midpint Ellipse Algorithm
#include <graphics.h> // Include graphics library for drawing
#include <conio.h>    // Include console I/O library for getch()
#include <stdio.h>    // Include standard I/O library
// Function to plot points in all four quadrants using symmetry
void plotEllipsePoints(int xc, int yc, int x, int y, int color) {
    putpixel(xc + x, yc + y, color); // Quadrant 1
    putpixel(xc - x, yc + y, color); // Quadrant 2
    putpixel(xc + x, yc - y, color); // Quadrant 3
    putpixel(xc - x, yc - y, color); // Quadrant 4
}
// Function to draw an ellipse using the Midpoint Ellipse Algorithm
void drawEllipseMidpoint(int xc, int yc, int rx, int ry, int color) {
    int x = 0;                     // Initialize x to 0
    int y = ry;                    // Initialize y to the y-radius
    float p1, p2;                  // Decision parameters
    // Region 1: Slope < 1
    p1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx); // Initial decision parameter for Region 1
    while (2 * ry * ry * x < 2 * rx * rx * y) {
        plotEllipsePoints(xc, yc, x, y, color); // Plot points in all quadrants
        // Update decision parameter for Region 1
        if (p1 < 0) {
            x++;
            p1 += 2 * ry * ry * x + ry * ry;
        } else {
            x++;
            y--;
            p1 += 2 * ry * ry * x - 2 * rx * rx * y + ry * ry;
        }
    }
    // Region 2: Slope >= 1
    p2 = (ry * ry) * (x + 0.5) * (x + 0.5) + (rx * rx) * (y - 1) * (y - 1) - (rx * rx * ry * ry); // Initial decision parameter for Region 2
    while (y >= 0) {
        plotEllipsePoints(xc, yc, x, y, color); // Plot points in all quadrants
        // Update decision parameter for Region 2
        if (p2 > 0) {
            y--;
            p2 += -2 * rx * rx * y + rx * rx;
        } else {
            x++;
            y--;
            p2 += 2 * ry * ry * x - 2 * rx * rx * y + rx * rx;
        }
    }
}
int main() {
    int gd = DETECT, gm; // Graphics driver and mode
    int xc = 300, yc = 250; // Center of the ellipse
    int rx = 200, ry = 100; // Radii of the ellipse
    // Initialize graphics mode
    initgraph(&gd, &gm, "");
    // Draw the ellipse using the Midpoint Ellipse Algorithm
    drawEllipseMidpoint(xc, yc, rx, ry, RED);
    // Wait for a key press to close the graphics window
    getch();
    // Close the graphics mode
    closegraph();
    return 0;
}
