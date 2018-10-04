#include "chart_manager.h"
#include <unordered_set>

#include "gui/form.h"

void ChartManager::refreshParamKeys()
{
    std::unordered_set<std::string> paramKeys;
    std::vector<std::string> paramKeysInOrder;
    for (auto && chart : m_charts)
    {
        for (auto && param : chart.meta)
        {
            if (paramKeys.count(param.first))
            {
                continue;
            }
            paramKeys.insert(param.first);
            paramKeysInOrder.push_back(param.first);
        }
    }
    Form::getInstance().updateParamKeys(paramKeysInOrder);
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