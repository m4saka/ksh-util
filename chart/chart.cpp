#include "chart.h"
#include <fstream>

Chart::Chart(std::string filename)
    : meta(filename)
    , body(filename)
{
}

std::ostream & operator<<(std::ostream & os, const Chart & obj)
{
    os << obj.meta << "--\r\n" << obj.body;
}

void Chart::save(const std::string & filename) const
{
    std::ofstream ofs(filename);
    ofs << *this;
}