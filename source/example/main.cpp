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
#include <graphic.h>
#include <log.h>

namespace po = boost::program_options;

int main(int ac, char** av)
{
    Stratum::Graphic graphic;

    try {
        po::options_description desc("Allowed options");

        desc.add_options()
            ("help,h", "output help message")
            ("width,w", po::value<int>()->required(), "window width")
        ;

        po::positional_options_description p;
        p.add("width", 1);

        po::variables_map vm;
        po::store(po::command_line_parser(ac, av).
                  options(desc).positional(p).run(), vm);


        if (vm.count() == 0) {
            std::cout << "salpo" << std::endl;
        }

        if (vm.count("help")) {
            std::cout << "USAGE: " << av[0] << &p <<  std::endl;
            return 0;
        }

        po::notify(vm);

        if (vm.count("width")) {
            std::cout << "width: " << vm["width"].as<int>() << "\n";
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;

        return 1;
    } catch (...) {
        std::cout << "Exception of unknown type!" << std::endl;
    }

    Stratum::Log::init();

    if (graphic.initialize()) {
        while (!Stratum::inputRead());

        graphic.cleanUp();
    }

    return 0;
}
