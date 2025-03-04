// Polygon shading model
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
// Function to perform flat shading for a cube face
void flatShading(Point3D points[], int numPoints, LightSource light, Surface surface, Point3D viewer) {
    // Calculate the centroid of the face
    Point3D centroid = {0, 0, 0};
    for (int i = 0; i < numPoints; i++) {
        centroid.x += points[i].x;
        centroid.y += points[i].y;
        centroid.z += points[i].z;
    }
    centroid.x /= numPoints;
    centroid.y /= numPoints;
    centroid.z /= numPoints;
    // Calculate illumination at the centroid
    float illumination = calculateIllumination(centroid, surface.normal, light, surface, viewer);
    int color = (int)fmin(255, fmax(0, illumination * 255));
    // Fill the face with the calculated color
    setfillstyle(SOLID_FILL, color);
    floodfill((points[0].x + points[1].x + points[2].x + points[3].x) / 4,
              (points[0].y + points[1].y + points[2].y + points[3].y) / 4, WHITE);
}
// Function to perform Gouraud shading for a cube face
void gouraudShading(Point3D points[], int numPoints, LightSource light, Surface surface, Point3D viewer) {
    // Calculate illumination at each vertex
    float illuminations[numPoints];
    for (int i = 0; i < numPoints; i++) {
        illuminations[i] = calculateIllumination(points[i], surface.normal, light, surface, viewer);
    }
    // Interpolate colors across the face (for simplicity, use a single color)
    int color = (int)fmin(255, fmax(0, (illuminations[0] + illuminations[1] + illuminations[2] + illuminations[3]) / 4 * 255));
    // Fill the face with the interpolated color
    setfillstyle(SOLID_FILL, color);
    floodfill((points[0].x + points[1].x + points[2].x + points[3].x) / 4,
              (points[0].y + points[1].y + points[2].y + points[3].y) / 4, WHITE);
}
// Function to perform Phong shading for a cube face
void phongShading(Point3D points[], int numPoints, LightSource light, Surface surface, Point3D viewer) {
    // Iterate over each pixel in the face (for simplicity, assume it is a rectangle)
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            // Check if the pixel is inside the face (for simplicity, assume it is)
            Point3D point = {(float)x, (float)y, 0}; // Assume z = 0 for simplicity
            float illumination = calculateIllumination(point, surface.normal, light, surface, viewer);
            // Clamp the illumination to the range [0, 255]
            int color = (int)fmin(255, fmax(0, illumination * 255));
            // Draw the pixel
            putpixel(x, y, color);
        }
    }
}
// Function to display the menu and handle user input
void displayMenu() {
    printf("Select a shading model:\n");
    printf("1. Flat Shading\n");
    printf("2. Gouraud Shading\n");
    printf("3. Phong Shading\n");
    printf("4. Exit\n");
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
    // Define the cube faces (for simplicity, assume a cube centered at (200, 200, 0))
    Point3D cubeFaces[6][4] = {
        // Front face
        {{100, 100, 0}, {300, 100, 0}, {300, 300, 0}, {100, 300, 0}},
        // Back face
        {{100, 100, -200}, {300, 100, -200}, {300, 300, -200}, {100, 300, -200}},
        // Left face
        {{100, 100, 0}, {100, 100, -200}, {100, 300, -200}, {100, 300, 0}},
        // Right face
        {{300, 100, 0}, {300, 100, -200}, {300, 300, -200}, {300, 300, 0}},
        // Top face
        {{100, 100, 0}, {300, 100, 0}, {300, 100, -200}, {100, 100, -200}},
        // Bottom face
        {{100, 300, 0}, {300, 300, 0}, {300, 300, -200}, {100, 300, -200}}
    };
    // Menu-driven program
    int choice;
    do {
        cleardevice(); // Clear the screen
        displayMenu(); // Display the menu
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                for (int i = 0; i < 6; i++) {
                    flatShading(cubeFaces[i], 4, light, surface, viewer);
                }
                break;
            case 2:
                for (int i = 0; i < 6; i++) {
                    gouraudShading(cubeFaces[i], 4, light, surface, viewer);
                }
                break;
            case 3:
                for (int i = 0; i < 6; i++) {
                    phongShading(cubeFaces[i], 4, light, surface, viewer);
                }
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
        getch(); // Wait for a key press
    } while (choice != 4);
    // Close the graphics mode
    closegraph();
    return 0;
}
