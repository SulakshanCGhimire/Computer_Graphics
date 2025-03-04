// Projections Implementation
#include <graphics.h> // Include graphics library for drawing
#include <conio.h>    // Include console I/O library for getch()
#include <stdio.h>    // Include standard I/O library
#include <math.h>     // Include math library for trigonometric functions
// Structure to represent a 3D point
typedef struct {
    float x, y, z;
} Point3D;
// Structure to represent a 2D point
typedef struct {
    int x, y;
} Point2D;
// Function to perform orthographic projection
Point2D orthographicProjection(Point3D p, float param1, float param2) {
    Point2D result;
    result.x = (int)p.x; // Ignore z-coordinate
    result.y = (int)p.y; // Ignore z-coordinate
    printf("Orthographic: (%f, %f, %f) -> (%d, %d)\n", p.x, p.y, p.z, result.x, result.y);
    return result;
}
// Function to perform oblique projection
Point2D obliqueProjection(Point3D p, float alpha, float theta) {
    Point2D result;
    float l = cos(theta); // Length of the projection line
    float m = sin(theta); // Angle of the projection line
    result.x = (int)(p.x + l * p.z * cos(alpha));
    result.y = (int)(p.y + m * p.z * sin(alpha));
    printf("Oblique: (%f, %f, %f) -> (%d, %d)\n", p.x, p.y, p.z, result.x, result.y);
    return result;
}
// Function to perform perspective projection
Point2D perspectiveProjection(Point3D p, float d, float unused) {
    Point2D result;
    result.x = (int)((p.x * d) / (p.z + d)); // Perspective formula
    result.y = (int)((p.y * d) / (p.z + d)); // Perspective formula
    printf("Perspective: (%f, %f, %f) -> (%d, %d)\n", p.x, p.y, p.z, result.x, result.y);
    return result;
}
// Function to draw a 3D object using a given projection
void draw3DObject(Point3D vertices[], int numVertices, int edges[][2], int numEdges, Point2D (*projection)(Point3D, float, float), float param1, float param2) {
    Point2D projectedVertices[numVertices];
    // Project all vertices
    for (int i = 0; i < numVertices; i++) {
        projectedVertices[i] = projection(vertices[i], param1, param2);
    }
    // Draw all edges
    for (int i = 0; i < numEdges; i++) {
        int start = edges[i][0];
        int end = edges[i][1];
        line(projectedVertices[start].x, projectedVertices[start].y,
             projectedVertices[end].x, projectedVertices[end].y);
    }
}
int main() {
    int gd = DETECT, gm; // Graphics driver and mode
    // Initialize graphics mode
    initgraph(&gd, &gm, (char*)""); // Cast the string literal to char*
    if (graphresult() != grOk) {
        printf("Graphics initialization failed!\n");
        return 1; // Exit the program if initialization fails
    }
    // Define the vertices of a 3D cube
    Point3D vertices[] = {
        {100, 100, 100}, {200, 100, 100}, {200, 200, 100}, {100, 200, 100},
        {100, 100, 200}, {200, 100, 200}, {200, 200, 200}, {100, 200, 200}
    };
    int numVertices = sizeof(vertices) / sizeof(vertices[0]);
    // Define the edges of the cube
    int edges[][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Bottom face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Top face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Connecting edges
    };
    int numEdges = sizeof(edges) / sizeof(edges[0]);
    // Draw the cube using orthographic projection
    setcolor(WHITE);
    draw3DObject(vertices, numVertices, edges, numEdges, orthographicProjection, 0, 0);
    getch();
    cleardevice();
    // Draw the cube using oblique projection
    setcolor(GREEN);
    draw3DObject(vertices, numVertices, edges, numEdges, obliqueProjection, 45, 45); // Example angles
    getch();
    cleardevice();
    // Draw the cube using perspective projection
    setcolor(RED);
    draw3DObject(vertices, numVertices, edges, numEdges, perspectiveProjection, 500, 0); // Example distance
    getch();
    // Close the graphics mode
    closegraph();
    return 0;
}
