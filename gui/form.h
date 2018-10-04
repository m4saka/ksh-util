#pragma once

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/listbox.hpp>

class Form
{
private:
    nana::form m_form;
    nana::listbox m_fileListbox;
    nana::listbox m_paramListbox;
    void updateParamList(nana::listbox::index_pairs indexPairs);

public:
    Form();
};