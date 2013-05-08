//  This file is part of Stratum.
//
//  Stratum is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Stratum is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with Stratum.  If not, see <http://www.gnu.org/licenses/>.

#include "log.h"

#include <iostream>
#include <boost/date_time.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>

namespace attrs = boost::log::attributes;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace logging = boost::log;
namespace src = boost::log::sources;

namespace Stratum
{
    namespace Log
    {

        BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)

        void init() 
        { 
            logging::add_console_log(std::cout, keywords::format = (expr::format("%1%: [%2%] %3%")
                                                                    % expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%H:%M:%S")
                                                                    % severity
                                                                    % expr::message
                                                                    )); 
            
            logging::add_common_attributes();
        }

        std::ostream& operator<<(std::ostream& strm, severity_level level) 
        { 
            static const char* strings[] = 
            { 
                "generic", 
                "gfx", 
                "WARNING", 
                "ERROR", 
                "CRITICAL"
            }; 
            
            if (static_cast<std::size_t>(level) < sizeof(strings) / sizeof(*strings)) 
                strm << strings[level]; 
            else 
                strm << static_cast<int>(level); 
            
            return strm;
        }

    } // namespace Log
} // namespace Stratum
