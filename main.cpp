#include <iostream>
#include <nana/gui/wvl.hpp>
#include "gui/form.h"

#ifdef _WIN32
int WinMain()
#else
int main()
#endif
{
    Form::getInstance();
    nana::exec();
    return 0;
}
