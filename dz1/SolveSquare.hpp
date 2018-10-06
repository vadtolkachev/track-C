#include <math.h>

/*! \mainpage Решение квадратного уравнения
 * дз1 
 */

/**
 * \file
 *
 * \author Вадим Толкачёв 
 *
 * \date 30.09.2018 
 *
 * Contact: vadtolkachev@gmail.com
 *
 */

/*!
Решает линейное уравнение
\param b, c Коэффициенты первой и нулевой степени соответственно
\param x Решение будет записано сюда(если существует и единственное)
\return 0 - нет решений 
\return 1 - существует единственное решение 
\return 3 - бесконечно много решений 
\return -1 - в случае ошибки(NAN, inf, nullptr)
*/
int solveLinear(double b, double c, double *x);
/*!
Решает квадратное уравнение
\param a, b, c Коэффициенты второй, перовй и нулевой степени соответственно
\param x1, x2 Решения будут записаны сюда(если существуют)
\return 0 - нет решений 
\return 1 - существует единственное решение
\return 2 - существует два решения
\return 3 - бесконечно много решений 
\return -1 - в случае ошибки(NAN, inf, nullptr)
*/
int solveSquare(double a, double b, double c, double *x1, double *x2);
