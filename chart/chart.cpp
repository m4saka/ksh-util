#include "chart.h"
#include <fstream>

static std::string BOM = "\xEF\xBB\xBF";

Chart::Chart(std::string filename)
    : m_filename(filename)
    , meta(filename)
    , body(filename)
{
}

std::ostream & operator<<(std::ostream & os, const Chart & obj)
{
    os << BOM << obj.meta << "--\r\n" << obj.body;
    return os;
}

void Chart::save() const
{
    save(m_filename);
}

void Chart::save(const std::string & filename) const
{
    std::ofstream ofs(filename);
    ofs << *this;
}
