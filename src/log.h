//  Copyright 2013 Kitti Vongsay
// 
//  This file is part of stratum.
//
//  stratum is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as 
//  published by the Free Software Foundation, either version 3 of
//  the License, or(at your option) any later version.
//
//  stratum is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with stratum.   If not, see <http://www.gnu.org/licenses/>.

#ifndef LOG_H
#define LOG_H

#include <boost/format.hpp> 
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>

#define LOG BOOST_LOG_SEV(stratum::Log::boost_log::get(), stratum::Log::generic)
#define LOGGFX BOOST_LOG_SEV(stratum::Log::boost_log::get(), stratum::Log::gfx)
#define LOGP BOOST_LOG_SEV(stratum::Log::boost_log::get(), stratum::Log::platform)
#define LOGW BOOST_LOG_SEV(stratum::Log::boost_log::get(), stratum::Log::warning)
#define LOGE BOOST_LOG_SEV(stratum::Log::boost_log::get(), stratum::Log::error)
#define LOGC BOOST_LOG_SEV(stratum::Log::boost_log::get(), stratum::Log::critical)

namespace stratum
{
    namespace Log 
    {
        enum severity_level
        {
            generic,
            gfx,
            platform,
            warning,
            error,
            critical
        };

        BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(boost_log, boost::log::sources::severity_logger_mt<severity_level>)
            
        extern void initialize();

    } //namespace Log

} // namespace stratum

#endif // LOG_H
