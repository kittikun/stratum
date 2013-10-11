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

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

// Stratum headers
#include <core.h>

namespace po = boost::program_options;

int main(int ac, char** av)
{
    po::options_description desc("Allowed options");
    po::positional_options_description p;
    po::variables_map vm;

    try {

        desc.add_options()
           ("help,h", "output help message")
           ("width,w", po::value<uint32_t>()->default_value(800)->required(), "window width")
           ("height,g", po::value<uint32_t>()->default_value(600)->required(), "window height")
           ("depth,d", po::value<uint32_t>()->default_value(16)->required(), "depth buffer bits")
        ;

        p.add("width", 1);
        p.add("height", 2);
        p.add("depth", 3);

        po::store(po::command_line_parser(ac, av).
                  options(desc).positional(p).run(), vm);

        if ((ac == 0) || (vm.count("help"))) {
            std::cout << "USAGE: " << desc <<  std::endl;
            return 0;
        }

        po::notify(vm);

    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Exception of unknown type!" << std::endl;
    }

    boost::shared_ptr<stratum::Core> core(stratum::CreateCore());

    if (!core) {
        std::cout << "Failed to create stratum core" << std::endl;
        return 1;
    }

    if (!core->initialize(vm["width"].as<uint32_t>(), vm["height"].as<uint32_t>())) {
        return 1;
    }

    core->start();

    return 0;
}
