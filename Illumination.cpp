// Illumination models
#include <graphics.h> // Include graphics library for drawing
#include <conio.h>    // Include console I/O library for getch()
#include <stdio.h>    // Include standard I/O library
#include <math.h>     // Include math library for trigonometric functions
// Screen dimensions
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
// Structure to represent a 3D point
typedef struct {
    float x, y, z;
} Point3D;
// Structure to represent a light source
typedef struct {
    float x, y, z; // Position of the light source
    float intensity; // Intensity of the light
} LightSource;
// Structure to represent a surface
typedef struct {
    Point3D normal; // Surface normal
    float ambientCoeff; // Ambient reflection coefficient
    float diffuseCoeff; // Diffuse reflection coefficient
    float specularCoeff; // Specular reflection coefficient
    float shininess; // Shininess factor for specular reflection
} Surface;
// Function to calculate the dot product of two vectors
float dotProduct(Point3D v1, Point3D v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
// Function to normalize a vector
Point3D normalize(Point3D v) {
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    Point3D normalized = {v.x / length, v.y / length, v.z / length};
    return normalized;
}
// Function to calculate the illumination at a point
float calculateIllumination(Point3D point, Point3D normal, LightSource light, Surface surface, Point3D viewer) {
    // Ambient light
    float ambient = surface.ambientCoeff * light.intensity;
    // Diffuse reflection
    Point3D lightDir = {light.x - point.x, light.y - point.y, light.z - point.z};
    lightDir = normalize(lightDir);
    float diffuse = surface.diffuseCoeff * light.intensity * fmax(0, dotProduct(normal, lightDir));
    // Specular reflection
    Point3D reflectDir = {
        2 * dotProduct(normal, lightDir) * normal.x - lightDir.x,
        2 * dotProduct(normal, lightDir) * normal.y - lightDir.y,
        2 * dotProduct(normal, lightDir) * normal.z - lightDir.z
    };
    reflectDir = normalize(reflectDir);
    Point3D viewDir = {viewer.x - point.x, viewer.y - point.y, viewer.z - point.z};
    viewDir = normalize(viewDir);
    float specular = surface.specularCoeff * light.intensity * pow(fmax(0, dotProduct(reflectDir, viewDir)), surface.shininess);
    // Total illumination
    return ambient + diffuse + specular;
}
// Function to draw a shaded surface
void drawShadedSurface(Point3D points[], int numPoints, LightSource light, Surface surface, Point3D viewer) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            // Calculate the illumination at the current pixel
            Point3D point = {(float)x, (float)y, 0}; // Assume z = 0 for simplicity
            float illumination = calculateIllumination(point, surface.normal, light, surface, viewer);
            // Clamp the illumination to the range [0, 255]
            int color = (int)fmin(255, fmax(0, illumination * 255));
            // Draw the pixel
            putpixel(x, y, color);
        }
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
    // Define the light source
    LightSource light = {100, 100, 200, 1.0}; // Light at (100, 100, 200) with intensity 1.0
    // Define the surface
    Surface surface = {
        {0, 0, 1}, // Surface normal (facing upwards)
        0.1,       // Ambient coefficient
        0.7,       // Diffuse coefficient
        0.2,       // Specular coefficient
        10.0       // Shininess factor
    };
    // Define the viewer position
    Point3D viewer = {0, 0, 500}; // Viewer at (0, 0, 500)
    // Define the surface points (for simplicity, assume a flat surface)
    Point3D points[] = {
        {0, 0, 0},
        {SCREEN_WIDTH, 0, 0},
        {SCREEN_WIDTH, SCREEN_HEIGHT, 0},
        {0, SCREEN_HEIGHT, 0}
    };
    int numPoints = sizeof(points) / sizeof(points[0]);
    // Draw the shaded surface
    drawShadedSurface(points, numPoints, light, surface, viewer);
    // Wait for a key press to close the graphics window
    getch();
    // Close the graphics mode
    closegraph();
    return 0;
}
