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

#include "core_impl.h"

#include "graphic_impl.h"
#include "log.h"

namespace stratum
{
    Core* CreateCore()
    {
        static bool instance = false;

        if (instance == false) {
            instance = true;

            return new CoreImpl();
        }

        return nullptr;
    }

    const bool CoreImpl::initialize(const uint32_t width, const uint32_t height)
    {
        bool res;

        Log::initialize();
        m_platform = Platform::CreatePlatform();

        GraphicOptions options;
        options.width = width;
        options.height = height;
        options.depthSize = 16;

        m_graphic.reset(new GraphicImpl());
        res = m_graphic->initialize(options, m_platform);
        if (!res) {
            return false;
        }

        res = m_platform->initializeInput();
        if (!res) {
            return false;
        }


        return true;
    }

    void CoreImpl::start()
    {
        LOGGFX << "Creating Graphic thread..";
        m_threads.create_thread(boost::bind(&GraphicImpl::renderLoop, m_graphic));

        while (1) {
            m_platform->inputRead();
        }
    }

    void CoreImpl::stop()
    {
        m_threads.join_all();
    }

} // namespace stratum


