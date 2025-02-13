#include "Tools.h"
#include "Point.h"
#include "Vector.h"


std::vector<Point2D> readPointsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Point2D> points;

    if (!file.is_open()) {
        std::cerr << "Mistake: couldn't open the file " << filename << std::endl;
        return points;
    }

    double x, y;
    while (file >> x >> y) {
        points.emplace_back(x, y);
    }

    file.close();
    return points;
}

std::vector<Point2D> DeleteCollinearPoints(const std::vector<Point2D>& data)
{
    std::vector<Point2D> result;
    if (data.size() < 3) return data;

    auto nextIndex = [&](size_t i) { return (i + 1) % data.size(); };
    auto prevIndex = [&](size_t i) { return (i == 0) ? data.size() - 1 : i - 1; };

    for (size_t i = 0; i < data.size(); ++i) {
        size_t prev = prevIndex(i);
        size_t next = nextIndex(i);

        double crossProduct = (data[i].x - data[prev].x) * (data[next].y - data[prev].y) -
                              (data[i].y - data[prev].y) * (data[next].x - data[prev].x);

        if (crossProduct != 0) {
            result.push_back(data[i]);
        }
    }

    return result;
}

Point2D midpoint(Point2D p1, Point2D p2)
{
    return {(p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0};
}
std::vector<Point2D> SetIntermediatePoints(const std::vector<Point2D>& data)
{
    std::vector<Point2D> result;
    if (data.empty()) return result;

    auto nextIndex = [&](size_t i) { return (i + 1) % data.size(); };

    for (size_t i = 0; i < data.size(); ++i) {
        result.push_back(data[i]);
        result.push_back(midpoint(data[i], data[nextIndex(i)]));
    }

    return result;
}


std::vector<std::pair<Point2D,Point2D>> GetSymmetryAxis(const std::vector<Point2D>& data)
{
    std::vector<std::pair<Point2D,Point2D>> result;

    if (data.size() < 2) return result;

    auto nextIndex = [&](size_t i) { return (i + 1) % data.size(); };
    auto prevIndex = [&](size_t i) { return (i == 0) ? data.size() - 1 : i - 1; };

    for (size_t k = 0; k < data.size() / 2; ++k)
    {
        size_t i = nextIndex(k);
        size_t j = prevIndex(k);
        bool isSymmetry = true;

        while (i != j)
        {
            Vector a1(data[k], data[i]);
            Vector a2(data[k], data[j]);

            if (std::abs(a1.length() - a2.length()) > 1e-6)
            {
                isSymmetry = false;
                break;
            }

            i = nextIndex(i);
            j = prevIndex(j);
        }

        if (isSymmetry)
        {
            result.emplace_back(data[k], data[i]);
        }
    }
    return result;
}
