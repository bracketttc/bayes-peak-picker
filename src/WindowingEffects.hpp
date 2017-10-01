#ifndef WINDOWING_EFFECTS_H
#define WINDOWING_EFFECTS_H

#include <algorithm>
#include <cmath>
#include <complex>
#include <functional>
#include <type_traits>
#include <vector>

#include "EigenFFT.hpp"

namespace bpp
{

/// @brief The WindowingEffects class.
///
/// Expands the input window by UP (padding with 0's) and takes the FFT of this
/// scaled-up window.
/// @tparam T  arithmetic type used for all calculations
/// @tparam UP window scale-up factor, must be a power of 2
template< typename T = float,
          unsigned int UP = 2>
class WindowingEffects
{
    static_assert( std::is_arithmetic< T >::value,
                   "Template parameter T must be an arithmetic type." );
#ifndef WIN32
    static_assert( UP && std::log2( UP ) == std::floor( std::log2( UP ) ),
                   "Template parameter UP must be a power of 2." );
#else
    // At time of writing, the MS implementation of the standard C libraries
    // does not include constexpr versions of the functions used in the
    // expression above, so we have to go the low-tech route. If you want to
    // enable UP factor values > 64, they can be added to this boolean
    // expression.
    static_assert( UP == 2 || UP == 4 || UP == 8 || UP == 16 || UP == 32 || UP == 64,
                   "Template parameter UP must be a power of 2." );
#endif // WIN32
public:
    WindowingEffects() = delete;

    /// @brief Constructor.
    /// @param[in] window windowing function applied before FFT.
    WindowingEffects( const std::vector< T >& window )
    {
        _window = window;
        _window.resize( _window.size() * UP, 0 );

        EigenFFT< T > fft;
        fft.fwd( _envelope, _window );

        _magnitude.resize( _envelope.size() );
        std::transform( _envelope.begin(), _envelope.end(), _magnitude.begin(), std::function< T ( std::complex< T > ) >( std::abs<T> ) );
    }

    WindowingEffects( const WindowingEffects& ) = delete;

    WindowingEffects& operator=( const WindowingEffects& ) = delete;

    /// @brief Destructor.
    virtual ~WindowingEffects()
    {
    }

    const std::vector< T > window() const { return _window; }
    const std::vector< std::complex< T > > envelope() const { return _envelope; }
    const std::vector< T > magnitude() const { return _magnitude; }

protected:
private:
    std::vector< T >                 _window;
    std::vector< std::complex< T > > _envelope;
    std::vector< T >                 _magnitude;
};

}

#endif // WINDOWING_EFFECTS_H
