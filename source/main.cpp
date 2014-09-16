#include "AIE.h"
#include <iostream>
#include "MyMaths.h"

int main( int argc, char* argv[] )
{	
    Initialise(800, 600, false, "poNg");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));


    //Game Loop
    do
    {

        ClearScreen();

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
