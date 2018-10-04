#pragma once

#include <vector>
#include <string>
#include "chart.h"

class ChartManager
{
private:
    std::vector<Chart> m_charts;
    ChartManager() = default;
    ~ChartManager() = default;

public:
    ChartManager(const ChartManager &) = delete;
    ChartManager & operator=(const ChartManager &) = delete;
    ChartManager(ChartManager &&) = delete;
    ChartManager & operator=(ChartManager &&) = delete;

    static ChartManager & getInstance()
    {
        static ChartManager instance;
        return instance;
    }

    void refreshParamKeys();
    void updateChartList(const std::vector<std::string> & filenames);
    void changeMetaDataValueForAll(std::string key, std::string value);
};