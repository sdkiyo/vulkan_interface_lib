#pragma once
#ifndef _LAVA_BASE_COLORS_H_
#define _LAVA_BASE_COLORS_H_

/* COLOR TABLE */
/*
Name            FG  BG
Black           30  40
Red             31  41
Green           32  42
Yellow          33  43
Blue            34  44
Magenta         35  45
Cyan            36  46
White           37  47
Bright Black    90  100
Bright Red      91  101
Bright Green    92  102
Bright Yellow   93  103
Bright Blue     94  104
Bright Magenta  95  105
Bright Cyan     96  106
Bright White    97  107
*/
#define UNDERLINE "\033[4m"
#define DOUBLE_UNDERLINE "\033[21m"
#define LINE_THROUGH "\033[9m"
#define ITALIC "\033[3m"

#define RESET_COLOR "\033[0m"

#define GRAY "\033[2m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#endif
