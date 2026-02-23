#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <limits>
#include <cmath>
#include <functional>
#include <fstream>

struct Point {
    double x, y;        // 2D coordinates
    int cluster;        // Assigned cluster ID (-1 if unassigned)

    Point(double val_x, double val_y) : x(val_x), y(val_y), cluster(-1){}
};

class KMeans {

    public:
    KMeans(int val_k, double val_threashold, int val_iterations) : \
    k(val_k), tolerance(val_threashold), maxIterations(val_iterations), iterations(0) {}

    void generateSyntheticData(int numPoints);
    void fit();
    void saveAsImage(const std::string& filename);
    bool updateCenters();
    void assignPoints();
    void initializeCenters();

    private:

    std::vector<Point> points;        // All data points
    std::vector<Point> centers;       // K cluster centers
    int k;                            // Number of clusters
    double tolerance;                 // Convergence threshold
    int maxIterations;                // Maximum iterations
    int iterations;                   // Actual iterations completed

    double distance(const Point& p1, const Point& p2);

    double calculateInertia();
    void addPoint(double x, double y);

};

int main() {
    KMeans kmeans(3, 1e-4, 100);                            // k=3 clusters, tolerance=1e-4, max 100 iterations
    std::cout << "Generating data points" << std::endl;
    kmeans.generateSyntheticData(300);                      // Generate 300 random points
    kmeans.fit();
    kmeans.saveAsImage("kmeans.ppm");                       // Save visualization    
    return 0;
}

void KMeans::addPoint(double x, double y) {
    points.push_back(Point(x, y));
}

void KMeans::generateSyntheticData(int numPoints) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dis(0, 1);

    std::vector<std::pair<double, double>> clusterCenters = {
        {2, 2}, {8, 8}, {8, 2}
    };

    int pointsPerCluster = numPoints / k;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < pointsPerCluster; j++) {
            double x = clusterCenters[i % clusterCenters.size()].first + \
                        dis(gen) * 0.5;

            double y = clusterCenters[i % clusterCenters.size()].second + \
                        dis(gen) * 0.5;

            addPoint(x, y);
        }
    }
}

double KMeans::distance(const Point& p1, const Point& p2){
    return sqrt(pow(p2.x - p1.x,2) + pow(p2.y - p1.y,2));
}

void KMeans::initializeCenters(){
    srand((time(NULL)));
    std::vector<int> randPoint;
    for(int i = 0; i < k; i++){
        Point temp = points[rand() % points.size()];
        centers.push_back(temp);
    }
    
}

void KMeans::assignPoints(){
    int nearest_index = -1;
    double min_dist = std::numeric_limits<double>::max();

    // Find distance between current point and all centers
    for(int i = 0; i < points.size(); i++){
        min_dist = std::numeric_limits<double>::max();
        nearest_index = -1;
        // Assign point to center that is closest
        for(int z = 0; z < centers.size(); z++){
            if(distance(points[i], centers[z]) < min_dist){
                nearest_index = z;
                min_dist = distance(points[i], centers[z]);
            }
        }
        points[i].cluster = nearest_index;
    }
    
}

bool KMeans::updateCenters(){
    std::vector<Point>  newCenters(k,Point(0.0,0.0));
    std::vector<int>  counts(k, 0);

    // Sum points per cluster
    for(int i = 0; i < points.size();i++) {
        int c = points[i].cluster;
        newCenters[c].x += points[i].x;
        newCenters[c].y += points[i].y;
        counts[c]++;
    }

    // Compute means
    for(int c = 0; c < k; c++) {
        if(counts[c] > 0) {
            newCenters[c].x /= counts[c];
            newCenters[c].y /= counts[c];
        }
    }

    // Check Convergence
    bool converged = false;
    for(int c = 0; c < k; c++) {
        double diff = distance(centers[c], newCenters[c]);
        std::cout << "The difference between centers " << c << " The difference is " << diff << std::endl;
        if(diff < tolerance){
            converged = true;
        }else{                  // If one center still needs converging 
            converged = false;
            break;
        }
        centers[c] = newCenters[c];
    }

    // Set Model Computed centers
    for(int c = 0; c < k; c++) {
        centers[c].x = newCenters[c].x;
        centers[c].y = newCenters[c].y;
    }

    return converged;
}

void KMeans::fit(){
    // Select K points from data set as initial cluster centers.
    initializeCenters();

    bool converged = false;
    for(int i = 0; i < maxIterations; i++){
        assignPoints();
        converged = updateCenters();
        std::cout << "Current epoch is " << i+1 << " and current Inertia: " << calculateInertia() << std::endl;

        if(converged){
            std::cout << "models done converging. ending fitting..." << std::endl;
            iterations = i;
            break;
        }
    }
    std::string converged_Status = (converged) ? "converged" : "Not Converged";
    std::cout << "Converge status: " << converged_Status << \
    " :: Max iterations reached: " << iterations << " Done." << std::endl;
}

double KMeans::calculateInertia(){
    double inertia = 0;
    for(int i = 0 ; i < points.size(); i++){
        int currclusterid = points[i].cluster;
        inertia += pow(distance(centers[currclusterid], points[i]), 2);
    }
    return inertia;
}

void KMeans::saveAsImage(const std::string& filename){
    // Sets colors of .PPM pixel
    typedef struct Pixel{
        int r, g, b;
    };

    // Find max X,Y coords
    Point MaxXY(0,0);
    for(int i = 0; i < points.size(); i++) {
        if(points[i].x > MaxXY.x)
            MaxXY.x = points[i].x;
        else if(points[i].y > MaxXY.y)
            MaxXY.y = points[i].y;
    }

    // Cartesian bounds
    const double x_min = -10 * MaxXY.x, x_max = 10 * MaxXY.x;
    const double y_min = -10 * MaxXY.y, y_max = 10 * MaxXY.y;
    const int width = 1000;
    const int height = 1000;

    // Set background to white
    std::vector<Pixel> image(width * height,{255, 255, 255});

    // Color pixel at (x,y) in image
    std::function<Pixel(int, int, Pixel)> set_pixel = [&](int x, int y, Pixel color) {
        if (x > 0 && x < width && y >= 0 && y < height)
            image[y * width + x] = color;                // Similar to finding matrix index.
        return color;
    };

    // Transforms (x,y) coordinates to pixel coordinates
    std::function<std::pair<int,int>(double, double)> cartesian_to_pixel = [&](double x, double y){
        int px = static_cast<int>((x-x_min) / (x_max - x_min) * width);     // Ratio of point/viewport and scaled to width.
        int py = static_cast<int>((y-y_min) / (y_max - y_min) * height);
        return std::pair<int, int>(px, py);
    };

    // Draw X and Y axes 
    for (double x = x_min; x <= x_max; x += 0.01){
        std::pair<int, int> p = cartesian_to_pixel(x, 0.0);
        set_pixel(p.first, p.second, {0, 0, 0});
    }

    for (double y = y_min; y <= y_max; y += 0.01) {
        auto [px, py] = cartesian_to_pixel(0.0, y);
        set_pixel(px, py, {0, 0, 0});
    }

    // Draw screen
    for (double x = x_min; x <= x_max; x += 0.01) {
  
        // Draw generated points
        for(int i = 0; i < points.size(); i++){
            auto [px, py] = cartesian_to_pixel(points[i].x, points[i].y);
            set_pixel(px, py, {0, 255, 0});     // Green 
        }

        // Draw centers
        for(int i = 0; i < k; i++){
            auto [px, py] = cartesian_to_pixel(centers[i].x, centers[i].y);
            set_pixel(px, py, {255, 0, 0});     // Red
        }
    }

    // Write PPM
    std::ofstream out(filename, std::ios::out);
    // Setting header
    out << "P3\n" << width << " " << height << "\n255\n";

    // Print pixel to image
    for (const auto& p : image) {
        out << p.r << " " << p.g << " " << p.b << "\n";
    }

    out.close();
    std::cout << "Generated " << filename << std::endl;
}
