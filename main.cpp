#define NDEBUG

#include <iostream>
#include <chrono>
#include <cmath>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/float128.hpp>
#include <boost/multiprecision/mpfr.hpp>

namespace mp = boost::multiprecision;

void taxi_cab(mp::uint128_t tc)
{
    mp::uint128_t raja = (mp::cbrt(tc.convert_to<mp::float128>()) + 0.5).convert_to<mp::uint128_t>();

    std::cout << raja << "\n";

    mp::uint128_t temp = 0;

    mp::uint128_t i = 0;
    mp::uint128_t j = 0;

    for ( i = 1 ; i < raja ; i++ )
    {
        mp::uint128_t iii = i*i*i;

        //mp::float128 f = (tc-iii).convert_to<mp::float128>();

        //j = (mp::round(mp::cbrt(f))).convert_to<mp::uint128_t>();

        double f = (tc-iii).convert_to<double>();

        j = mp::uint128_t(std::round(std::cbrt(f)));

        if (iii + j*j*j == tc)
        {
            if (i == temp)
                break;

            std::cout << i << " " << j << "\n";

            temp = j;
        }
    }
}

int main()
{    
    auto t0 = std::chrono::steady_clock::now();

    taxi_cab(mp::uint128_t("24153319581254312065344"));

    auto t1 = std::chrono::steady_clock::now();

    std::chrono::duration<double> dur = t1 - t0;

    std::cout << dur.count() << "\n";

    return 0;
}
