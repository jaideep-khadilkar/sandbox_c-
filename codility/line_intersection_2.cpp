#include <iostream>
using namespace std;

struct Pnt
{
    int x,y;
};

int orientation(Pnt point_1, Pnt point_2, Pnt point_3)
{
    int val = (point_2.y - point_1.y) * (point_3.x - point_2.x) -
              (point_2.x - point_1.x) * (point_3.y - point_2.y);

    if (val == 0) return 0;

    return (val > 0)? 1: 2;
}

bool isTouching(Pnt point_1, Pnt point_2, Pnt point_3)
{
    if (point_2.x <= max(point_1.x, point_3.x) && point_2.x >= min(point_1.x, point_3.x) &&
        point_2.y <= max(point_1.y, point_3.y) && point_2.y >= min(point_1.y, point_3.y))
       return true;

    return false;
}

bool solution(int K, int L, int M, int N, int P, int Q, int R, int S)
{
	struct Pnt a = {K, L};
	struct Pnt b = {M, N};
	struct Pnt c = {P, Q};
	struct Pnt d = {R, S};

    int abc = orientation(a, b, c);
    int adb = orientation(a, b, d);
    int cda = orientation(c, d, a);
    int cdb = orientation(c, d, b);

    if (abc != adb && cda != cdb)			return true;
    if (abc == 0 && isTouching(a, c, b)) 	return true;
    if (adb == 0 && isTouching(a, d, b)) 	return true;
    if (cda == 0 && isTouching(c, a, d)) 	return true;
    if (cdb == 0 && isTouching(c, b, d)) 	return true;

    return false;
}

int main()
{
	cout << solution(1,1,10,1,1,2,10,2) << endl;
	cout << solution(10,0,0,10,0,0,10,10) << endl;
	cout << solution(-5,-5,0,0,1,1,10,10) << endl;
    cout << solution(0,1,4,3,1,3,2,1) << endl;
    cout << solution(0,1,4,3,3,2,5,1) << endl;

    return 0;
}
