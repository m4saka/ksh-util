#pragma once

#include <string>

#include "chart_meta_data.h"
#include "chart_body.h"

struct Chart
{
public:
    std::string m_filename;
    ChartMetaData meta;
    ChartBody body;

    Chart(std::string filename);

    friend std::ostream & operator<<(std::ostream & os, const Chart & obj);
    void save() const;
    void save(const std::string & filename) const;
};
