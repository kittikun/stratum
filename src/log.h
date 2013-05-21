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

#define LOG BOOST_LOG_SEV(stratum::boost_log::get(), stratum::Log_Generic)
#define LOGGFX BOOST_LOG_SEV(stratum::boost_log::get(), stratum::Log_Gfx)
#define LOGP BOOST_LOG_SEV(stratum::boost_log::get(), stratum::Log_Platform)
#define LOGW BOOST_LOG_SEV(stratum::boost_log::get(), stratum::Log_Warning)
#define LOGE BOOST_LOG_SEV(stratum::boost_log::get(), stratum::Log_Error)
#define LOGC BOOST_LOG_SEV(stratum::boost_log::get(), stratum::Log_Critical)

namespace stratum
{
    enum ELogLevel
    {
        Log_Generic,
        Log_Gfx,
        Log_Platform,
        Log_Warning,
        Log_Error,
        Log_Critical
    };

    BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(boost_log, boost::log::sources::severity_logger_mt<ELogLevel>)

    class Log
    {
    public:
        static void initialize();
    };

} // namespace stratum

#endif // LOG_H
