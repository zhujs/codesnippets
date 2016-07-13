#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


// 由于坐标范围为 0 ~ 10^8，必须使用long double做乘法运算以防止溢出
struct Point {
    int xi;
    int yi;
    long double x;
    long double y;
};

int main()
{
    std::ios::sync_with_stdio(false);    

    int N = 0;
    std::cin >> N;
    std::vector<Point> points(N);
    for (int i = 0; i<N; i++) {
        std::cin >> points[i].xi >> points[i].yi;
        points[i].x = points[i].xi;
        points[i].y = points[i].yi;
    }

    // 寻找位于坐标平面上最左下方的点，swap至points[0]
    auto min = std::min_element(points.begin(), points.end(), [] (const Point& point, const Point& smallest) -> bool {
                return point.x == smallest.x ? point.y < smallest.y : point.x < smallest.x;
            });
    std::swap(*(points.begin()), *min);

    // 利用向量的cross product，寻找一条所有点都位于其同一侧的直线，端点为points[0]，points[1]
    // https://en.wikipedia.org/wiki/Cross_product#Computing_the_cross_product
    for (int i = 2; i < N; ++i) {
            Point vectorU, vectorV;
            vectorU.x = points[1].x - points[0].x;
            vectorU.y = points[1].y - points[0].y;
            vectorV.x = points[i].x - points[0].x;
            vectorV.y = points[i].y - points[0].y;
            if (vectorU.x * vectorV.y - vectorU.y * vectorV.x < 0)
                std::swap(points[1], points[i]);
    }

    // 计算points[0]，points[1]，points[i]（i>=2，points[i]为角的顶点）三点形成的角度
    // 排序后中值对应的三个点即为所求
    // 利用dot product计算角度 
    auto &point0 = points[0];
    auto &point1 = points[1];
    std::nth_element(points.begin() + 2, points.begin() + 2 + (N-2) / 2, points.end(), 
            [point0, point1] (const Point& pointA, const Point& pointB) -> bool {
                Point vectorA0, vectorA1;
                vectorA0.x = point0.x - pointA.x; vectorA0.y = point0.y - pointA.y;
                vectorA1.x = point1.x - pointA.x; vectorA1.y = point1.y - pointA.y;

                Point vectorB0, vectorB1;
                vectorB0.x = point0.x - pointB.x; vectorB0.y = point0.y - pointB.y;
                vectorB1.x = point1.x - pointB.x; vectorB1.y = point1.y - pointB.y;

                return std::acos( (vectorA0.x * vectorA1.x + vectorA0.y * vectorA1.y) / 
                        std::sqrt( (vectorA0.x * vectorA0.x + vectorA0.y * vectorA0.y) * (vectorA1.x * vectorA1.x + vectorA1.y * vectorA1.y)) )
                     > std::acos( (vectorB0.x * vectorB1.x + vectorB0.y * vectorB1.y) / 
                        std::sqrt( (vectorB0.x * vectorB0.x + vectorB0.y * vectorB0.y) * (vectorB1.x * vectorB1.x + vectorB1.y * vectorB1.y)) );
            });

    auto iter = points.begin() + 2 + (N-2) / 2;
    std::cout << point0.xi << " " << point0.yi << std::endl;
    std::cout << point1.xi << " " << point1.yi << std::endl;
    std::cout << iter->xi << " " << iter->yi;

    return 0;
}
