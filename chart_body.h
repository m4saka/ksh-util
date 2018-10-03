#pragma once

#include <iostream>
#include <string>
#include <cstddef>
#include <unordered_map>

class ChartBody
{
private:
    std::string m_str;

public:
    ChartBody(const std::string & filename);

    friend std::ostream & operator<<(std::ostream & os, const ChartBody & obj);

    std::string toString() const;
};
