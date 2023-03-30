#include "s21_math.h"

#include <limits.h>  // LLONG_MAX, LLONG_MI

// вычисляет абсолютное значение целого числа
long int s21_abs(int x) {
    if (x < 0)
        x = -x;
    return x;
}

// вычисляет синус
long double s21_sin(double x) {
    long double res = 0.0, pow = x, fact = 1.0;
    if (x != x) {
        res = -s21_NAN;
    } else if (x == s21_INFINITY || x == -s21_INFINITY) {
        res = -s21_NAN;
    } else {
        int flag_minus = 0;
        double a = x * 180 / s21_PI;  // перевод из радианов в градусы
        if (a < 0) {                  // отражаем отрицательное значение относительно оси x
            a = 0 - a;                // 0 - x (например, -30° = 0° - (-30°) = 30°)
            flag_minus++;             // запоминаем минус (sin(-x) = -sin(x))
        }
        if (a > 360) {                 // возвращаем большое значение в рабочую область единичной окружности
            while (a > 360) a -= 360;  // x - 2PI (например, 390° = 390° - 360° = 30°)
        }
        if (a > 180 && a <= 270) {  // находим синонимичное значение (из третьей четверти в первой)
            a -= 180;               // x - PI (например, 210° = 210° - 180° = 30°)
            flag_minus++;           // запоминаем минус (например, sin(210°) = -1/2)
        }
        if (a > 90 && a <= 180) {  // находим синонимичное значение (из второй четверти в первой)
            a = 180 - a;           // PI - x (например, 150° = 180° - 150° = 30°)
        }
        if (a > 270 && a <= 360) {  // находим синонимичное значение (из второй четверти в первой)
            a = 360 - a;            // 2PI - x (например, 330° = 360° - 330° = 30°)
            flag_minus++;           // запоминаем минус (sin(330°) = -1/2)
        }
        x = a * s21_PI / 180;  // перевод из градусов в радианы
        pow = x;
        for (double i = 0.0; i < 1000; ++i) {
            res += pow / fact;                          // sin (x) = x - x^3 / 3! + x^5 / 5! - x^7 / 7! + ...
            pow *= -1 * x * x;                          // x*(−x^2)
            fact *= (2 * (i + 1)) * (2 * (i + 1) + 1);  // факториал (1! + 3! + 5! + 7! = 1 + 6 + 120 + 5040)
        }
        if (x == s21_PI_2) res = 1;
        if (flag_minus >= 1) res *= -1;
        if (flag_minus == 2) res *= -1;
    }
    return res;
}

// вычисляет косинус
long double s21_cos(double x) {
    long double res = 0.0;
    if (x != x) {
        res = -s21_NAN;
    } else if (x == s21_INFINITY || x == -s21_INFINITY) {
        res = -s21_NAN;
    } else {
        if (x < 0) x *= -1;        // правило отрицательного аргумента для cos: cos(-x) = cos(x)
        while (x >= 2 * s21_PI) {  // возвращаем большое значение в рабочую область единичной окружности
            x -= 2 * s21_PI;       // x - 2PI (например, 390° = 390° - 360° = 30°)
        }
        x = s21_PI_2 - x;  // соотношение sin/cos для двух острых углов прямоугольного треугольника
        res = s21_sin(x);  // sin(90° - x) = cos(x)
    }
    return res;
}

// вычисляет тангенс
long double s21_tan(double x) {
    long double res = 0.0;
    if (x != x) {
        res = -s21_NAN;
    } else if (x == s21_INFINITY || x == -s21_INFINITY) {
        res = -s21_NAN;
    } else if (x != 0.0) {
        long double sinx = s21_sin(x), cosx = s21_cos(x);
        if (cosx == 0) {
            if (sinx > 0)
                res = s21_INFINITY;
            else if (sinx < 0)
                res = -s21_INFINITY;
        } else {
            res = sinx / cosx;
        }
    } else {
        res = x;
    }
    return res;
}

// возводит число в заданную степень
long double s21_pow(double base, double exp) {
    long double res = 0.0;
    if (base < 0) {
        if (exp < 0) {
            if (base == -s21_INFINITY) {
                if (exp < 0 && (int)exp % 2 != 0) res = -0.0;  // (-1/0)^(-1) = -0
            }
        } else if ((long int)exp == exp) {  // сравнение double и int
            if (exp > 0) {                  // если степень интегральная, то считаем по простому методу
                res = s21_simple_pow(base, exp);
            } else if (exp == 0) {
                res = 1;
            } else {
                res = 1 / base;
                for (long int i = 0; i < (long int)exp * (-1) - 1; i++) {
                    res /= base;
                }
            }
        } else {
            if (exp == -s21_INFINITY || exp == s21_INFINITY) {
                if (base * (-1) < 1) {
                    res = 0;
                } else if (base * (-1) == 1) {
                    res = 1;
                } else {
                    if (exp == -s21_INFINITY)
                        res = 0;
                    else
                        res = s21_INFINITY;
                }
            } else {
                res = -s21_NAN;
            }
        }
    } else if (base == 0) {
        if (exp == 0)
            res = 1;
        else if (exp < 0)
            res = s21_INFINITY;
        else
            res = 0;
    } else if (base == 1) {
        res = 1;
    } else {
        if ((long int)exp == exp) {
            if (exp > 0) {
                res = s21_simple_pow(base, exp);
            } else if (exp == 0) {
                res = 1;
            } else {
                res = 1 / base;
                for (long int i = 0; i < (long int)exp * (-1) - 1; i++) {
                    res /= base;
                }
            }
        } else {
            res = s21_exp(exp * s21_log(base));  // x = a^b = exp(b*ln(a))
        }
    }
    return res;
}

// вычисляет квадратный корень
long double s21_sqrt(double x) {
    long double res = s21_pow(x, 0.5);  // x = √a = a^(1/2)
    return res;
}

// возвращает значение e, возведенное в заданную степень
long double s21_exp(double x) {
    long double res = 0.0, e_r = 0.0, fact = 1.0;
    if (x == s21_INFINITY) {
        res = x;
    } else if (x == -s21_INFINITY) {
        res = 0;
    } else if (x != x) {
        res = -s21_NAN;
    } else if (x > 709) {
        res = s21_INFINITY;
    } else if (x < -709) {
        res = 0;
    } else if (x != 0) {
        int minus = 0;
        if (x < 0) {
            x *= -1;
            minus = 1;
        }
        int k = 0;
        long double r = (long double)x;          // x = k*ln2 + r
        k = x / E_2;                             // k - int, сколько раз x нацело делится на ln2
        r = x - E_2 * k;                         // r - double, остаток от предыдущего деления (|r| <= ln2)
        for (int i = 0; i < 1000; i++) {         //
            e_r += s21_simple_pow(r, i) / fact;  // e^x = e^(k*ln2 + r) = 2^k * e^r
            fact *= i + 1;
        }
        res = s21_simple_pow(2.0, k) * e_r;
        if (minus) res = 1 / res;
    } else {
        res = 1;
    }
    return res;
}

// вычисляет натуральный логарифм
long double s21_log(double x) {
    long double res = 0;
    if (x != x) {
        res = -s21_NAN;
    } else if (x == s21_INFINITY) {
        res = x;
    } else if (x == -s21_INFINITY || x < 0) {
        res = -s21_NAN;
    } else if (x == 0) {
        res = -s21_INFINITY;
    } else {
        if (x >= 0.1 && x <= 10) {
            if (x > 0.6) {
                x = (x / (x - 1));
                for (int i = 1.0; i < 1000; i++) {
                    res += 1.0 / (i * s21_simple_pow(x, i));
                }
            } else {
                res = s21_log(x * 2) - s21_log(2);
            }
        } else {
            int exp = 0;
            if (x > 10) {
                while (x > 10) {
                    x /= 10;
                    exp++;
                }
            } else {
                if (x != S21_DBL_MIN) {
                    while (x < 0.1) {
                        x *= 10;
                        exp--;
                    }
                }
            }
            if (x != S21_DBL_MIN)
                res = s21_log(x) + exp * E_10;
            else if (x == S21_DBL_MIN)
                res = -708.396419;
        }
    }
    return res;
}

// вычисляет арккосинус
long double s21_acos(double x) {
    long double res = 0.0;
    if (x != x || x > 1.0 || x < -1.0) {
        res = s21_NAN;
    } else if (x == 1) {
        res = 0;
    } else if (x == -1) {
        res = s21_PI;
    } else {
        res = s21_PI_2 - s21_asin(x);
    }
    return res;
}

// вычисляет арксинус
long double s21_asin(double x) {
    long double res = 0.0;
    if (x != x || x > 1.0 || x < -1.0) {
        res = s21_NAN;
    } else if (x == 1) {
        res = s21_PI_2;
    } else if (x == -1) {
        res = -s21_PI_2;
    } else {
        res = s21_atan(x / s21_sqrt(1 - x * x));
    }
    return res;
}

// вычисляет арктангенс
long double s21_atan(double x) {
    long double res = 0.0;
    if (x != x) {
        res = -s21_NAN;
    } else if (x == s21_INFINITY) {
        res = s21_PI_2;
    } else if (x == -s21_INFINITY) {
        res = -s21_PI_2;
    } else {
        int minus = 0;
        if (x < 0) {
            x *= -1;
            minus = 1;
        }
        if (x >= 0 && x <= 0.4375) {  // ряд Маклорена в нуле
            for (int n = 0; n < 100; ++n) {
                res += (s21_pow(-1, n) * s21_pow(x, (2 * n + 1))) / (2 * n + 1);
            }
        }
        if (x > 0.4375 && x <= 0.6875) {
            res = s21_atan_05 + s21_atan((x - 0.5) / (1 + x / 2));
        }
        if (x > 0.6875 && x <= 1.1875) {
            res = s21_atan_1 + s21_atan((x - 1) / (1 + x));
        }
        if (x > 1.1875 && x <= 2.4375) {
            res = s21_atan_15 + s21_atan((x - 1.5) / (1 + 1.5 * x));
        }
        if (x > 2.4375) {
            res = s21_PI_2 + s21_atan(-1 / x);
        }
        if (minus) res *= -1;
    }
    return res;
}

// возвращает ближайшее целое число, не меньшее заданного значения
long double s21_ceil(double x) {
    int flag = 0;
    long double result;
    if (x >= LLONG_MAX || x <= LLONG_MIN) {
        flag = 1;
        result = x;
    }
    if (x == 0.0) {
        flag = 1;
        result = x;
    }
    if (flag != 1) {
        long long num = (long long)x;
        result = (double)num;
        if (result == x || x < 0) {
        } else {
            result = result + 1;
        }
    }
    return x != x ? s21_NAN : result;
}

// вычисляет абсолютное значение числа с плавающей точкой
long double s21_fabs(double x) {
    long double result = x;
    if (result < 0)
        result = -result;
    return result;
}

// возвращает ближайшее целое число, не превышающее заданное значение
long double s21_floor(double x) {
    int flag = 0;
    long double result;
    if (x >= LLONG_MAX || x <= LLONG_MIN) {  // if use inf some assumptiond would not work right
        flag = 1;
        result = x;
    }
    if (x == 0.0) {
        flag = 1;
        result = x;
    }
    if (flag != 1) {
        long long num = (long long)x;
        result = (double)num;
        if (result == x || x > 0) {
        } else {
            result = result - 1;
        }
    }
    return x != x ? s21_NAN : result;
}

// остаток операции деления с плавающей точкой
long double s21_fmod(double x, double y) {
    long double result;
    if ((x && y) || (y != 0)) {
        result = x - ((long int)(x / y) * y);
        if (x == s21_NAN || y == s21_NAN)
            result = s21_NAN;
        if (y == +0.0 || y == -0.0)
            result = s21_NAN;
        if (x == s21_INFINITY || x == -s21_INFINITY)
            result = s21_NAN;
        if (x == 0.0)
            result = 0.0;
    } else {
        result = s21_NAN;
    }
    return result;
}

// вавилонский метод возведения в степень | x1 = 1/2(x0 + 2/x0)
long double s21_simple_pow(double base, int exp) {
    long double result = 1.0;
    for (double i = 0.0; i < exp; ++i) result *= (long double)base;
    return result;
}
