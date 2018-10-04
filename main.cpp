#include <iostream>
#include <nana/gui/wvl.hpp>
#include "gui/form.h"

int main()
{
    Form::getInstance();
    nana::exec();
    return 0;
}
