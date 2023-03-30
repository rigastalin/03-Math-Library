#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#define s21_INFINITY 1.0 / 0.0  // inf - константа определения бесконечно большого числа
#define s21_NAN 0.0 / 0.0       // nan - константа определения не числа

#define s21_2PI 6.28318530718               // 360°, 2PI
#define s21_PI 3.1415926535897932384650288  // 180°, PI
#define s21_PI_2 1.570796326794896558       // 90°, PI/2
#define s21_PI_3 1.047197551196597853       // 60°, PI/3
#define s21_PI_6 0.523598775598298926       // 30°, PI/6
#define s21_PI_4 0.785398163397448309       // 45°, PI/4

#define E_10 2.302585092994046  // натуральный логарифм из 10
#define E_2 0.6931471805599453  // натуральный логарифм из 2

#define S21_INT_MIN -2147483648  // Максимальный отрицательный интеджер
#define S21_INT_MAX 2147483647   // Максимальный интеджер
#define S21_DBL_MIN 2.2250738585072014E-308
#define S21_DBL_MAX 1.79769313486231571E+308

#define s21_atan_05 0.463647609000806
#define s21_atan_1 0.785398163397448
#define s21_atan_15 0.982793723247329

long int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

long double s21_simple_pow(double base, int exp);

#endif  // SRC_S21_MATH_H_
