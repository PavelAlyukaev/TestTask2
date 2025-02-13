#include <gtest/gtest.h>
#include <fstream>
#include "Vector.h"
#include "Tools.h"


TEST(VectorTest, ConstructorXYZ) {
    Vector v(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.getX(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY(), 2.0);
    EXPECT_DOUBLE_EQ(v.getZ(), 3.0);
}

TEST(VectorTest, ConstructorFromPoints) {
    Point a(1.0, 2.0, 3.0);
    Point b(4.0, 5.0, 6.0);
    Vector v(a, b);
    EXPECT_DOUBLE_EQ(v.getX(), 3.0);
    EXPECT_DOUBLE_EQ(v.getY(), 3.0);
    EXPECT_DOUBLE_EQ(v.getZ(), 3.0);
}

TEST(VectorTest, AdditionOperator) {
    Vector v1(1.0, 2.0, 3.0);
    Vector v2(4.0, 5.0, 6.0);
    Vector result = v1 + v2;
    EXPECT_DOUBLE_EQ(result.getX(), 5.0);
    EXPECT_DOUBLE_EQ(result.getY(), 7.0);
    EXPECT_DOUBLE_EQ(result.getZ(), 9.0);
}

TEST(VectorTest, ScalarMultiplication) {
    Vector v(1.0, 2.0, 3.0);
    Vector result = v * 2.0;
    EXPECT_DOUBLE_EQ(result.getX(), 2.0);
    EXPECT_DOUBLE_EQ(result.getY(), 4.0);
    EXPECT_DOUBLE_EQ(result.getZ(), 6.0);
}

TEST(VectorTest, DotProduct) {
    Vector v1(1.0, 2.0, 3.0);
    Vector v2(4.0, 5.0, 6.0);
    double result = v1.dot(v2);
    EXPECT_DOUBLE_EQ(result, 32.0);
}

TEST(VectorTest, CrossProduct) {
    Vector v1(1.0, 0.0, 0.0);
    Vector v2(0.0, 1.0, 0.0);
    Vector result = v1.cross(v2);
    EXPECT_DOUBLE_EQ(result.getX(), 0.0);
    EXPECT_DOUBLE_EQ(result.getY(), 0.0);
    EXPECT_DOUBLE_EQ(result.getZ(), 1.0);
}

TEST(VectorTest, Length) {
    Vector v(3.0, 4.0, 0.0);
    double length = v.length();
    EXPECT_DOUBLE_EQ(length, 5.0);
}

TEST(VectorTest, Normalized) {
    Vector v(3.0, 4.0, 0.0);
    Vector normalized = v.normalized();
    EXPECT_DOUBLE_EQ(normalized.length(), 1.0);
    EXPECT_DOUBLE_EQ(normalized.getX(), 0.6);
    EXPECT_DOUBLE_EQ(normalized.getY(), 0.8);
    EXPECT_DOUBLE_EQ(normalized.getZ(), 0.0);
}

TEST(VectorTest, ToPoint) {
    Vector v(1.0, 2.0, 3.0);
    Point p = v.toPoint();
    EXPECT_DOUBLE_EQ(p.x, 1.0);
    EXPECT_DOUBLE_EQ(p.y, 2.0);
    EXPECT_DOUBLE_EQ(p.z, 3.0);
}


TEST(ReadPointsFromFileTest, ReadValidFile) {
    std::string filename = "test_points.txt";
    std::ofstream outfile(filename);
    outfile << "1.0 2.0\n4.0 5.0\n7.0 8.0 \n";
    outfile.close();

    std::vector<Point2D> points = readPointsFromFile(filename);

    ASSERT_EQ(points.size(), 3);
    EXPECT_EQ(points[0], Point2D(1.0, 2.0));
    EXPECT_EQ(points[1], Point2D(4.0, 5.0));
    EXPECT_EQ(points[2], Point2D(7.0, 8.0));


    std::remove(filename.c_str());
}

TEST(ReadPointsFromFileTest, ReadInvalidFile) {
    std::string filename = "non_existent_file.txt";
    std::vector<Point2D> points = readPointsFromFile(filename);

    EXPECT_TRUE(points.empty());
}

TEST(DeleteCollinearPointsTest, RemovesCollinearPoints) {
    std::vector<Point2D> points = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {1, 0}};
    auto result = DeleteCollinearPoints(points);
    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0].x, 0);
    EXPECT_DOUBLE_EQ(result[0].y, 0);
    EXPECT_DOUBLE_EQ(result[1].x, 3);
    EXPECT_DOUBLE_EQ(result[1].y, 3);
    EXPECT_DOUBLE_EQ(result[2].x, 1);
    EXPECT_DOUBLE_EQ(result[2].y, 0);
}

TEST(SetIntermediatePointsTest, AddsIntermediatePoints) {
    std::vector<Point2D> points = {{0, 0}, {2, 0}};
    auto result = SetIntermediatePoints(points);
    ASSERT_EQ(result.size(), 4);
    EXPECT_DOUBLE_EQ(result[0].x, 0);
    EXPECT_DOUBLE_EQ(result[0].y, 0);
    EXPECT_DOUBLE_EQ(result[1].x, 1);
    EXPECT_DOUBLE_EQ(result[1].y, 0);
    EXPECT_DOUBLE_EQ(result[2].x, 2);
    EXPECT_DOUBLE_EQ(result[2].y, 0);
    EXPECT_DOUBLE_EQ(result[3].x, 1);
    EXPECT_DOUBLE_EQ(result[3].y, 0);
}


TEST(GetSymmetryAxisTest, FindsSymmetryAxis) {
    std::vector<Point2D> points = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    auto result = GetSymmetryAxis(points);
    ASSERT_EQ(result.size(), 2);
    EXPECT_DOUBLE_EQ(result[0].first.x, 0);
    EXPECT_DOUBLE_EQ(result[0].first.y, 0);
    EXPECT_DOUBLE_EQ(result[0].second.x, 1);
    EXPECT_DOUBLE_EQ(result[0].second.y, 1);
    EXPECT_DOUBLE_EQ(result[1].first.x, 1);
    EXPECT_DOUBLE_EQ(result[1].first.y, 0);

}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}