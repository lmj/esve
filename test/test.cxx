
#include "common.hxx"
#include <limits>

void test_complex() ;
void test_quat() ;
void test_moebius() ;

int g_assertion_count = 0 ;

int main()
{
    std::srand(std::time(0)) ;
    std::cout.precision(std::numeric_limits<real>::digits10 + 1) ;

    test_complex() ;
    test_quat() ;
    test_moebius() ;

    std::cout << g_assertion_count
              << " assertions succeeded."
              << std::endl ;
}

