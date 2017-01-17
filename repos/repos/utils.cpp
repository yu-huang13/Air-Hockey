#include "utils.h"

const double EPS = 1e-6;
const double PI = 3.1415926;

double sign(const double &x){
	return isZero(x)? 0.0 : (x < 0? -1.0 : 1.0);
}

bool isZero(const double &x){
	return x < EPS && x > -EPS;
}

bool equal(const double &x, const double &y){
	return isZero(x - y);
}