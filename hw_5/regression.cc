#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <fstream>
#include <functional>

struct DataPoint {
    double x, y;           // Actual coordinates
    double predicted;      // Predicted y value from model

    DataPoint(double val_x, double val_y) : x(val_x), y(val_y) {}
};

class LinearRegression {

    private:

    std::vector<DataPoint> data;    // Training data
    double slope;                   // m in y = mx + b
    double intercept;               // b in y = mx + b
    double rSquared;                // R² score

    public:

    void fit();
    void calculateMetrics();
    double calculateMSE();
    double calculateMAE();
    double predict(double x);
    void saveAsImage(const std::string& filename);
    void addPoint(double x, double y);

    void generateSyntheticData(int numPoints, double trueSlope = 2.5, double trueIntercept = 1.0, double noise = 0.5);
};

int main() {
    LinearRegression lr;
    // Generate synthetic data 
    lr.generateSyntheticData(300, 3.0/4.0, 3.0, 10.0);
    lr.fit();                              // Fit the model
    lr.saveAsImage("regression.ppm");      // Visualize
    
    return 0;
}

// Add a data point
void LinearRegression::addPoint(double x, double y) {
    data.push_back(DataPoint(x, y));
}

// Generate synthetic data with noise
void LinearRegression::generateSyntheticData(int numPoints, double trueSlope, double trueIntercept, double noise) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> xDis(0, 10);
    std::normal_distribution<> noiseDis(0, noise);

    for (int i = 0; i < numPoints; i++) {
        double x = xDis(gen);
        double y = trueSlope * x + trueIntercept + noiseDis(gen);
        addPoint(x, y);
    }

    std::cout << "Generated " << numPoints << " synthetic data points.\n";
    std::cout << "True model: y = " << trueSlope << "x + " << trueIntercept << "\n";
    std::cout << "Noise level: " << noise << "\n\n";
}

void LinearRegression::calculateMetrics(){
    // Store predicted y coord
    double sse = 0, sst = 0, ysum = 0, ymean = 0;

    // Mean of y values
    for(int i = 0; i < data.size(); i++) ysum += data[i].y;
    ymean = ysum / data.size();

    // Calculate predictions, Sum of Squared Error (SSE) and Total Sum of Squares (SST).
    for(int i = 0; i < data.size(); i++){
        data[i].predicted = predict(data[i].x);

        sse += pow(data[i].y - data[i].predicted, 2);
        sst += pow(data[i].y - ymean ,2);
    }

    // Calculate R^2
    rSquared = sse/sst;
    std::cout << "R^2: " << rSquared << std::endl;
    std::cout << "Mean Squared Error: " << calculateMSE() << std::endl;
    std::cout << "Mean Absolute Error: " << calculateMAE() << std::endl;
}

void LinearRegression::fit(){
    // Need to predict slop and intercept of given points
    double xsum = 0, ysum = 0;
    for(int i = 0; i < data.size()-1; i++) {
        // Find b by finding average of x/y values
        xsum += data[i].x;
        ysum += data[i].y;
    }

    // Find average movement of x and y coords
    double xavg = xsum / data.size();
    double yavg = ysum / data.size();

    // Find where values would be if not shifted by noise
    std::vector<DataPoint> point_prime;
    for(int i = 0; i < data.size(); i++) {
        point_prime.push_back(DataPoint(data[i].x - xavg, data[i].y - yavg));
    }

    // With shifted values, to find slope effectively is m = sum (x' * y') / sum(x'^2).
    // Sum shifted x*y and divide by shifted x^2 to determine current computed slope impact.
    double prime_sum = 0, prime_sum_sq = 0; 
    for(int i = 0; i < data.size(); i++) {
        prime_sum += point_prime[i].x * point_prime[i].y;
        prime_sum_sq += pow(point_prime[i].x - xavg, 2);
    }

    slope = prime_sum/ prime_sum_sq;
    intercept = yavg - slope * xavg;

    calculateMetrics();

    std::cout << "Model: y = " << slope << "* x + " << intercept << std::endl;
}

double LinearRegression::predict(double x){
    return slope * x + intercept;
}

double LinearRegression::calculateMSE(){
    double error = 0;
    for(int i = 0; i < data.size(); i++)
        error += pow(data[i].y - data[i].predicted,2);

    return error / data.size();
}

double LinearRegression::calculateMAE(){
    double error = 0;
    for(int i = 0; i < data.size(); i++)
        error += fabs(data[i].y - data[i].predicted);

    return error / data.size();
}

void LinearRegression::saveAsImage(const std::string& filename){
    // Sets colors of .PPM pixel
    struct Pixel{
        int r, g, b;
    };

    // Find max X,Y coords
    DataPoint MaxXY(0,0);
    for(int i = 0; i < data.size(); i++) {
        if(data[i].x > MaxXY.x)
            MaxXY.x = data[i].x;
        else if(data[i].y > MaxXY.y)
            MaxXY.y = data[i].y;
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
        for(int i = 0; i < data.size(); i++){
            auto [px, py] = cartesian_to_pixel(data[i].x, data[i].y);
            set_pixel(px, py, {255, 0, 0});     // Red

            // Draw predicted points
            auto [px_pred, py_pred] = cartesian_to_pixel(data[i].x, data[i].predicted);
            set_pixel(px_pred, py_pred, {0, 255, 0});     // Green

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
