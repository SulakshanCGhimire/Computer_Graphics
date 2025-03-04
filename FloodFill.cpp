// Flood fill algorithm
#include <graphics.h> // Include graphics library for drawing
#include <conio.h>    // Include console I/O library for getch()
#include <stdio.h>    // Include standard I/O library
// Function to perform flood fill
void floodFill(int x, int y, int fillColor, int oldColor) {
    // Get the color of the current pixel
    int currentColor = getpixel(x, y);
    // If the current pixel has the old color, fill it
    if (currentColor == oldColor) {
        putpixel(x, y, fillColor); // Fill the pixel with the fill color
        // Recursively fill the 4-connected neighbors
        floodFill(x + 1, y, fillColor, oldColor); // Right
        floodFill(x - 1, y, fillColor, oldColor); // Left
        floodFill(x, y + 1, fillColor, oldColor); // Bottom
        floodFill(x, y - 1, fillColor, oldColor); // Top
    }
}
int main() {
    int gd = DETECT, gm; // Graphics driver and mode
    // Initialize graphics mode
    initgraph(&gd, &gm, "");
    // Draw a rectangle filled with a specific color (e.g., WHITE)
    setfillstyle(SOLID_FILL, WHITE);
    bar(100, 100, 300, 300);
    // Perform flood fill starting from a seed point inside the rectangle
    floodFill(150, 150, RED, WHITE);
    // Wait for a key press to close the graphics window
    getch();
    // Close the graphics mode
    closegraph();
    return 0;
}
