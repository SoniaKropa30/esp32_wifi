#include "mx_function.h"
char *mx_itoa(int number) {
    int n = number;
    int try = number;
    int count = 0;
    
    if (n == -2147483648) {
	    return "-2147483648\0";
	}
	if (n == 0) {
		return "0\0";
    }
        while(n != 0) {
            if(n < 0) {
                n *= -1;
                count++;
                }
            n /= 10;
            count++;
            }
        char *str = mx_strnew(count + 1);
        for (int j = (count -1); j >= 0; j--) {
            if (number < 0) {
                number *= (-1);
                str[0] = (char)(45);
            }
            if (j == 0 && str[0] == 45)
                break;
        try = number;
        try %= 10;
        str[j] = (char)(try + 48);
        number /=10;
    }
        return str;
        
}


