#pragma once

#include <vector>
#include <string>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/listbox.hpp>

class Form
{
private:
    nana::form m_form;
    nana::listbox m_fileListbox;
    nana::listbox m_paramListbox;
    Form();
    ~Form() = default;
    void fileListChanged(nana::listbox::index_pairs indexPairs);

public:
    Form(const Form &) = delete;
    Form & operator=(const Form &) = delete;
    Form(Form &&) = delete;
    Form & operator=(Form &&) = delete;

    static Form & getInstance()
    {
        static Form instance;
        return instance;
    }

    void updateParamKeys(std::vector<std::string> paramKeys);
};