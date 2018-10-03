#include "chart_body.h"
#include <cassert>
#include <fstream>
#include <sstream>

ChartBody::ChartBody(const std::string & filename)
{
    std::ifstream ifs(filename);

    // Eliminate UTF-8 BOM
    // TODO: Convert Shift-JIS (or other encodes) to UTF-8 if BOM doesn't exist
    ifs.seekg(3, std::ios_base::beg);

    std::string line;
    bool barLineExists = false;
    while (std::getline(ifs, line, '\n'))
    {
        // Eliminate CR
        if(!line.empty() && *line.rbegin() == '\r') {
            line.pop_back();
        }

        if (line == "--")
        {
            // Chart meta data is before first bar line ("--")
            barLineExists = true;
            break;
        }
    }

    // .ksh files should have at least one bar line ("--")
    assert(barLineExists);

    std::istreambuf_iterator<char> it(ifs), end;
    m_str = std::string(it, end);
}

std::ostream & operator<<(std::ostream & os, const ChartBody & obj)
{
    os << obj.m_str << std::flush;
    return os;
}

std::string ChartBody::toString() const
{
    std::ostringstream oss;
    oss << *this;
    return oss.str();
}
