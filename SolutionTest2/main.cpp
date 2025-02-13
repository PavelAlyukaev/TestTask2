#include <iostream>
#include <vector>
#include "Tools.h"


int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Using: " << argv[0] << " <path_to_file>" << std::endl;
        return 1;
    }

    std::vector<Point2D> data = readPointsFromFile(argv[1]);

    auto tmp = DeleteCollinearPoints(data);
    tmp = SetIntermediatePoints(tmp);

    auto res = GetSymmetryAxis(tmp);

    for (const auto &[p1, p2]: res) {
        std::cout << p1.toString() << " - " << p2.toString() << std::endl;
    }

    if(res.empty())
        std::cout<<"non-symmetric"<<std::endl;

    return 0;
}