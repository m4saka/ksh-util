#include "form.h"
#include <URLParser.hpp>

Form::Form()
    : m_form(nana::rectangle(nana::API::make_center(600, 400)))
    , m_fileListbox(m_form)
    , m_paramListbox(m_form)
{
    nana::API::enable_dropfiles(m_fileListbox, true);

    m_fileListbox.show_header(false);
    m_fileListbox.enable_single(false, false);
    m_fileListbox.append_header("filename");
    m_fileListbox.append_header("fullpath", 0);
    m_fileListbox.events().mouse_dropfiles([&](const nana::arg_dropfiles& arg){
        for (auto && file : arg.files)
        {
            std::string fullPath = http::URLDecode(file);
            auto slashPos = fullPath.find_last_of('/');
            std::string filename = slashPos == std::string::npos ? fullPath : fullPath.substr(slashPos + 1);
            m_fileListbox.at(0).append({filename, fullPath});
        }
    });

    m_fileListbox.events().selected([&](){
        updateParamList(m_fileListbox.selected());
    });

    m_paramListbox.append_header("key", 120);
    m_paramListbox.append_header("value", 290);

    m_form.div("<filelist width=180> <paramlist>");
    m_form["filelist"] << m_fileListbox;
    m_form["paramlist"] << m_paramListbox;
    m_form.collocate();
    m_form.show();
}

void Form::updateParamList(nana::listbox::index_pairs indexPairs)
{
    for (auto && indexPair : indexPairs)
    {
        std::cout << m_fileListbox.at(indexPair).text(1) << std::endl;
    }
}