#ifndef EIGEN_FFT_HPP
#define EIGEN_FFT_HPP

#include <complex>
#include <type_traits>
#include <vector>

#include <unsupported/Eigen/FFT>

#include "FFTWrapper.hpp"

namespace bpp
{

/// @brief Implementation of FFTWrapper for Eigen.
template< typename T >
class EigenFFT : public FFTWrapper< T >
{
public:
    EigenFFT() :
        _fft()
    {
    }

    virtual ~EigenFFT()
    {
    }

    virtual void fwd( std::vector< std::complex< T > >& dst, const std::vector< T >& src )
    {
        _fft.fwd( dst, src );
    }

    virtual void inv( std::vector< T >& dst, const std::vector< std::complex< T > >& src )
    {
        _fft.inv( dst, src );
    }
protected:
private:
    Eigen::FFT< T > _fft;
};

}

#endif // EIGEN_FFT_HPP
