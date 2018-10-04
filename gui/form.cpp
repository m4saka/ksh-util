#include "form.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <cstddef>
#include <URLParser.hpp>
#include <boost/filesystem.hpp>
#include "chart/chart_manager.h"

namespace fs = boost::filesystem;

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
            fs::path filePath = http::URLDecode(file);
            if (!fs::exists(filePath))
            {
                continue;
            }

            if (fs::is_directory(filePath))
            {
                fs::recursive_directory_iterator it(filePath), last;
                while (it != last)
                {
                    auto path = it->path();
                    if (fs::extension(path) == ".ksh")
                    {
                        m_fileListbox.at(0).append({path.filename().string(), path.string()});
                    }
                    ++it;
                }
            }
            else if (fs::extension(filePath) == ".ksh")
            {
                m_fileListbox.at(0).append({filePath.filename().string(), filePath.string()});
            }
        }
        fileListChanged();
    });

    m_paramListbox.append_header("key", 120);
    m_paramListbox.append_header("value", 290);
    m_paramListbox.events().dbl_click([&](){
        auto selections = m_paramListbox.selected();
        if (selections.size() == 1)
        {
            auto && paramItem = m_paramListbox.at(selections[0]);
            std::string key = paramItem.text(0);
            nana::inputbox::text textBox("", paramItem.text(1));
            nana::inputbox inbox(m_form, key + "=?", "Change value");
            if (inbox.show(textBox))
            {
                paramItem.text(1, textBox.value());
                if (textBox.value() != "####")
                {
                    ChartManager::getInstance().changeMetaDataValueForAll(key, textBox.value());
                }
            }
        }
    });

    m_form.div("<filelist width=180> <paramlist>");
    m_form["filelist"] << m_fileListbox;
    m_form["paramlist"] << m_paramListbox;
    m_form.collocate();
    m_form.show();
}

void Form::fileListChanged()
{
    std::vector<std::string> filenames;
    for (std::size_t i = 0; i < m_fileListbox.at(0).size(); ++i)
    {
        filenames.push_back(m_fileListbox.at(0).at(i).text(1));
    }

    ChartManager::getInstance().updateChartList(filenames);
}

void Form::updateParams(std::unordered_map<std::string, std::string> params)
{
    m_paramListbox.clear();
    for (auto && param : params)
    {
        m_paramListbox.at(0).append({param.first, param.second});
    }
}
