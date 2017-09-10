#ifndef FFT_WRAPPER_HPP
#define FFT_WRAPPER_HPP

#include <complex>
#include <type_traits>
#include <vector>

namespace bpp
{

/// @brief The FFTWrapper abstract base class.
///
/// Minimal wrapper class to abstract away vendor-specific FFT idiosyncracies.
/// This project requires only a small subset of any given FFT library's
/// functionality.
///
/// It should be trivially easy to write a wrapper around your favorite FFT
/// library for use with the peak picker. There is provided an EigenFFT wrapper
/// which fulfills this role for FFTW and kissfft, dependent upon build
/// options.
template< typename T >
class FFTWrapper
{
    static_assert( std::is_arithmetic< T >::value, "Template parameter T must be an arithmetic type." );
public:
    /// @brief Real-valued forward FFT.
    /// @param[out] dst
    /// @param[in]  src
    virtual void fwd( std::vector< std::complex< T > >& dst, const std::vector< T >& src ) = 0;

    /// @brief Complex-to-real-valued inverse FFT.
    /// @param[out] dst
    /// @param[in]  src
    virtual void inv( std::vector< T >& dst, const std::vector< std::complex< T > >& src ) = 0;
};

}

#endif // FFT_WRAPPER_HPP
