#include <iostream>
#include <vector>

#include "WindowingEffects.hpp"

int main( int, char** )
{
    std::vector< float > ones( 256, 1 );

    bpp::WindowingEffects< float > win( ones );
    const std::vector< float >& window = win.window();

    std::cout << "Window has " << window.size() << " elements." << std::endl;
    for ( const float& mag : win.magnitude() )
    {
        std::cout << mag << " ";
    }
    std::cout << std::endl;

    return 0;
}
