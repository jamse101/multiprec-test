#define NDEBUG

#include <iostream>
#include <chrono>
#include <cmath>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/float128.hpp>
#include <boost/multiprecision/mpfr.hpp>

#include <immintrin.h>

namespace mp = boost::multiprecision;

void taxi_cab(mp::uint128_t tc)
{
    mp::uint128_t raja = (mp::cbrt(tc.convert_to<mp::float128>()) + 0.5).convert_to<mp::uint128_t>();

    std::cout << raja << "\n";

    mp::uint128_t temp1 = 0, temp2 = 0, temp3 =0, temp4 = 0;

    mp::uint128_t i = 0;
    mp::uint128_t j = 0;

    for ( i = 1 ; i < raja ; i+= 4 )
    {
        mp::uint128_t t1 = tc - i*i*i;
        mp::uint128_t i2 = i+1;
        mp::uint128_t t2 = tc - i2*i2*i2;
        mp::uint128_t i3 = i+2;
        mp::uint128_t t3 = tc - i3*i3*i3;
        mp::uint128_t i4 = i + 3;
        mp::uint128_t t4 = tc - i4*i4*i4;

        __m256d v1 = {t1.convert_to<double>(),
                      t2.convert_to<double>(),
                      t3.convert_to<double>(),
                      t4.convert_to<double>()};

        //__m256d v2 =_mm256_cbrt_pd(v1);

        __m256d v2 = {std::cbrt(v1[0]), std::cbrt(v1[1]), std::cbrt(v1[2]), std::cbrt(v1[3])};

        j = mp::uint128_t(std::round(v2[0]));

        if (j*j*j == t1)
        {
            if (i == temp1)
                break;

            std::cout << i << " " << j << "\n";

            temp1 = j;
        }

        j = mp::uint128_t(std::round(v2[1]));

        if (j*j*j == t2)
        {
            if (i2 == temp2)
                break;

            std::cout << i2 << " " << j << "\n";

            temp2 = j;
        }

        j = mp::uint128_t(std::round(v2[2]));

        if (j*j*j == t3)
        {
            if (i3 == temp3)
                break;

            std::cout << i3 << " " << j << "\n";

            temp3 = j;
        }

        j = mp::uint128_t(std::round(v2[3]));

        if (j*j*j == t4)
        {
            if (i4 == temp4)
                break;

            std::cout << i4 << " " << j << "\n";

            temp4 = j;
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
