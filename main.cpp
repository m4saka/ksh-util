#include <iostream>
#include <nana/gui/wvl.hpp>
#include <URLParser.hpp>

int main()
{
    nana::form form;
    nana::API::enable_dropfiles(form, true);
    form.events().mouse_dropfiles([](const nana::arg_dropfiles& arg){
        for (auto && file : arg.files)
        {
            std::string filename = http::URLDecode(file);
        }
    });
    form.show();

    nana::exec();

    return 0;
}
