#include "form.h"
#include <vector>
#include <string>
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
    });

    m_fileListbox.events().selected([&](){
        fileListChanged(m_fileListbox.selected());
    });

    m_paramListbox.append_header("key", 120);
    m_paramListbox.append_header("value", 290);

    m_form.div("<filelist width=180> <paramlist>");
    m_form["filelist"] << m_fileListbox;
    m_form["paramlist"] << m_paramListbox;
    m_form.collocate();
    m_form.show();
}

void Form::fileListChanged(nana::listbox::index_pairs indexPairs)
{
    std::vector<std::string> filenames;
    for (auto && indexPair : indexPairs)
    {
        filenames.push_back(m_fileListbox.at(indexPair).text(1));
    }

    ChartManager::getInstance().updateChartList(filenames);
}

void Form::updateParamKeys(std::vector<std::string> paramKeys)
{
    m_paramListbox.clear();
    for (auto && paramKey : paramKeys)
    {
        m_paramListbox.at(0).append({paramKey, ""});
    }
}