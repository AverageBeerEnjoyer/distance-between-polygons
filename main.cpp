#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

double distance_between_polygons(vector<pair<double, double>> polygon1, vector<pair<double, double>> polygon2);
double distance_between_polygon_and_dot(pair<double, double> dot, vector<pair<double, double>> polygon);
double distance_between_straight_and_dot(pair<double,double> A, pair<double,double> B, pair<double, double> C);
double distance_between_dots(pair<double, double> dot1, pair<double, double> dot2);
pair<double, double> revert(pair<double, double> p);
double scalar_product(pair<double, double> a, pair<double, double> b);
double norm(double a, double b);
static double eps = 0.00001;

int main() {
	FILE* read = fopen("read.txt", "r");
	vector<pair<double,double>> polygon1, polygon2;
	int n1, n2;
	fscanf(read,"%d %d", &n1, &n2);
	for (int i = 0; i < n1; ++i) {
		pair<double,double> p;
		fscanf(read, "%lf %lf", &p.first, &p.second);
		polygon1.push_back(p);
	}
	for (int i = 0; i < n2; ++i) {
		pair<double, double> p;
		fscanf(read, "%lf %lf", &p.first, &p.second);
		polygon2.push_back(p);
	}
	double distance = distance_between_polygons(polygon1, polygon2);
	cout << distance;
}
double distance_between_polygons(vector<pair<double,double>> polygon1, vector<pair<double, double>> polygon2) {
	double min = -1;
	for (int i = 0; i < polygon1.size(); ++i) {
		double distance = distance_between_polygon_and_dot(polygon1[i], polygon2);
		if (distance < min || min > -1 - eps && min < -1 +eps) min = distance;
	}
	for (int i = 0; i < polygon2.size(); ++i) {
		double distance = distance_between_polygon_and_dot(polygon2[i], polygon1);
		if (distance < min) min = distance;
	}
	return min;
}
double distance_between_polygon_and_dot(pair<double,double> dot, vector<pair<double,double>> polygon) {
	double min = -1;
	for (int i = 0; i < polygon.size(); ++i) {
		double distance = distance_between_straight_and_dot(polygon[i], polygon[(i + 1)%polygon.size()], dot);
		if (distance < min || min > -1 - eps && min < -1 + eps) {
			min = distance;
		}
	}
	return min;
}
double distance_between_straight_and_dot(pair<double, double> A, pair<double, double> B, pair<double, double> C) {
	//отрезок АВ, лежащий на прямой, точка С
	pair<double, double> AB, BA, AC, BC;
	
	AB = make_pair(B.first - A.first, B.second - A.second);

	BA = revert(AB);

	AC = make_pair(C.first - A.first, C.second - A.second);

	BC = make_pair(C.first - B.first, C.second - B.second);

	//углы
	double ABC, BAC;

	ABC = scalar_product(BA, BC);

	BAC = scalar_product(AB, AC);

	if (BAC * ABC < 0) {
		double distance = min(distance_between_dots(A, C), distance_between_dots(B, C));
		return distance;
	}
	else {
		double a, b, c;
		a = AB.second;
		b = BA.first;
		c = BA.second * A.first + AB.first * A.second;

		double nrm = norm(a, b);

		a /= nrm;
		b /= nrm;
		c /= nrm;

		double distance =  abs(a * C.first + b * C.second + c);
		return distance;
	}
}
double distance_between_dots(pair<double, double> dot1, pair<double, double> dot2) {
	return norm(dot1.first - dot2.first, dot1.second - dot2.second);
}
pair<double,double> revert(pair<double, double> p) {
	return make_pair(p.first *= -1, p.second *= -1);

}
double scalar_product(pair<double, double> a, pair<double, double> b) {
	return a.first * b.first + a.second * b.second;
}
double norm(double a, double b) {
	return sqrt(a * a + b * b);
}