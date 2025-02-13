#include "Point.h"

std::vector<Point2D> readPointsFromFile(const std::string& filename);

std::vector<Point2D> DeleteCollinearPoints(const std::vector<Point2D>& data);

std::vector<Point2D> SetIntermediatePoints(const std::vector<Point2D>& data);

std::vector<std::pair<Point2D,Point2D>> GetSymmetryAxis(const std::vector<Point2D>& data);

Point2D midpoint(Point2D p1, Point2D p2);