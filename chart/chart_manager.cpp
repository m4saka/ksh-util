#include "chart_manager.h"
#include <unordered_map>

#include "gui/form.h"

void ChartManager::refreshParamKeys()
{
    std::unordered_map<std::string, std::string> params;
    for (auto && chart : m_charts)
    {
        for (auto && param : chart.meta)
        {
            if (params.count(param.first))
            {
                if (param.second != params[param.first])
                {
                    params[param.first] = "####";
                }
                continue;
            }
            params.insert(param);
        }
    }
    Form::getInstance().updateParams(params);
}

void ChartManager::updateChartList(const std::vector<std::string> & filenames)
{
    m_charts.clear();
    for (auto && filename : filenames)
    {
        m_charts.emplace_back(filename);
    }
    refreshParamKeys();
}

void ChartManager::changeMetaDataValueForAll(std::string key, std::string value)
{
    for (auto && chart : m_charts)
    {
        if (chart.meta[key] != value)
        {
            chart.meta[key] = value;
            chart.save();
        }
    }
}