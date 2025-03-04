// Depth-Sorting method (Painter's algorithm)
#include <graphics.h> // Include graphics library for drawing
#include <conio.h>    // Include console I/O library for getch()
#include <stdio.h>    // Include standard I/O library
#include <stdlib.h>   // Include standard library for dynamic memory allocation
// Structure to represent a 3D polygon
typedef struct {
    int x1, y1, z1; // Vertex 1
    int x2, y2, z2; // Vertex 2
    int x3, y3, z3; // Vertex 3
    int color;      // Color of the polygon
} Polygon3D;
// Function to calculate the average depth of a polygon
float calculateAverageDepth(Polygon3D poly) {
    return (poly.z1 + poly.z2 + poly.z3) / 3.0f;
}
// Function to sort polygons based on their average depth (back to front)
void sortPolygons(Polygon3D polygons[], int numPolygons) {
    for (int i = 0; i < numPolygons - 1; i++) {
        for (int j = i + 1; j < numPolygons; j++) {
            float depth1 = calculateAverageDepth(polygons[i]);
            float depth2 = calculateAverageDepth(polygons[j]);
            if (depth1 < depth2) { // Swap if polygon i is behind polygon j
                Polygon3D temp = polygons[i];
                polygons[i] = polygons[j];
                polygons[j] = temp;
            }
        }
    }
}
// Function to draw a 3D polygon
void drawPolygon(Polygon3D poly) {
    // Draw the edges of the polygon
    line(poly.x1, poly.y1, poly.x2, poly.y2);
    line(poly.x2, poly.y2, poly.x3, poly.y3);
    line(poly.x3, poly.y3, poly.x1, poly.y1);
    // Fill the polygon with its color
    setfillstyle(SOLID_FILL, poly.color);
    floodfill((poly.x1 + poly.x2 + poly.x3) / 3, (poly.y1 + poly.y2 + poly.y3) / 3, WHITE);
}
int main() {
    int gd = DETECT, gm; // Graphics driver and mode
    // Initialize graphics mode
    initgraph(&gd, &gm, (char*)""); // Cast the string literal to char*
    if (graphresult() != grOk) {
        printf("Graphics initialization failed!\n");
        return 1; // Exit the program if initialization fails
    }
    // Define the polygons in the scene
    Polygon3D polygons[] = {
        {100, 100, 200, 200, 100, 200, 150, 200, 300, RED},    // Polygon 1
        {150, 150, 100, 250, 150, 100, 200, 250, 150, GREEN},  // Polygon 2
        {200, 100, 150, 300, 100, 150, 250, 200, 200, BLUE}    // Polygon 3
    };
    int numPolygons = sizeof(polygons) / sizeof(polygons[0]);
    // Sort the polygons based on their average depth (back to front)
    sortPolygons(polygons, numPolygons);
    // Draw the polygons in sorted order
    for (int i = 0; i < numPolygons; i++) {
        drawPolygon(polygons[i]);
    }
    // Wait for a key press to close the graphics window
    getch();
    // Close the graphics mode
    closegraph();
    return 0;
}
