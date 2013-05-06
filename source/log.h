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

#ifndef LOG_H
#define LOG_H

#include <boost/log/expressions/keyword.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>

#define LOG BOOST_LOG_SEV(Stratum::Log::boost_log::get(), Stratum::Log::normal)
#define LOGN BOOST_LOG_SEV(Stratum::Log::boost_log::get(), Stratum::Log::notification)
#define LOGC BOOST_LOG_SEV(Stratum::Log::boost_log::get(), Stratum::Log::critical)

namespace Stratum
{
    namespace Log 
    {
        enum severity_level
        {
            normal,
            notification,
            warning,
            error,
            critical
        };

        BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(boost_log, boost::log::sources::severity_logger_mt<severity_level>)
            
        extern void init();

    } //namespace Log

} // namespace Stratum

#endif // LOG_H
