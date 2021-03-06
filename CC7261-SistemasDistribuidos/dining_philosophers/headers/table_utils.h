#include <string>
#include <algorithm>

// Funcao para converter um valor inteiro em uma string de n digitos (ex: 3 -> "003")
std::string fixedLength(int value, int digits = 2) 
{
    unsigned int uvalue = value;
    if (value < 0) {
        uvalue = -uvalue;
    }
    std::string result;
    while (digits-- > 0) {
        result += ('0' + uvalue % 10);
        uvalue /= 10;
    }
    if (value < 0) {
        result += '-';
    }
    std::reverse(result.begin(), result.end());
    return result;
}