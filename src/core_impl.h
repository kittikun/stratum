//  Copyright 2013 Kitti Vongsay
//
//  This file is part of Stratum.
//
//  Stratum is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as
//  published by the Free Software Foundation, either version 3 of
//  the License, or(at your option) any later version.
//
//  Stratum is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with Stratum.   If not, see <http://www.gnu.org/licenses/>.

#ifndef CORE_IMPL_H
#define CORE_IMPL_H

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/utility.hpp>
#include <boost/signals2.hpp>

#include <core.h>

#include "graphic_impl.h"
#include "platform/platform_impl.h"
#include "options.h"

namespace stratum
{
    class CoreImpl : public Core, private boost::noncopyable
    {
    public:
        CoreImpl();
        ~CoreImpl();

        const bool initialize(const uint32_t width, const uint32_t height);
        void start();
        void stop();

    private:
        boost::thread_group m_threads;
        boost::shared_ptr<GraphicImpl> m_graphic;
        boost::shared_ptr<Platform> m_platform;

		typedef boost::signals2::signal<void (const bool)> StateSig;
		StateSig m_stateSig;
    };

} // namespace stratum

#endif // CORE_IMPL_H

