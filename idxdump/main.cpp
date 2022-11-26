//  Created by Charles Kerr on 11/26/22.
//

#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <string>
#include <fstream>
#include "strutil.hpp"
using namespace std::string_literals;


int main(int argc, const char * argv[]) {
    try{
        if (argc != 3){
            throw std::runtime_error("Missing idx or output file.");
        }
        auto input = std::ifstream(argv[1],std::ios::binary);
        if (!input.is_open()){
            throw std::runtime_error(strutil::format("Unable to open: %s",argv[1]) );
        }
        auto output = std::ofstream(argv[2]);
        if (!output.is_open()){
            throw std::runtime_error(strutil::format("Unable to create: %s",argv[2]) );
        }
        auto offset = std::uint32_t(0);
        auto length = std::uint32_t(0) ;
        auto extra = std::uint32_t(0) ;
        auto count = 0 ;
        while (input.good() && !input.eof()){
            input.read(reinterpret_cast<char*>(&offset),4);
            input.read(reinterpret_cast<char*>(&length),4);
            input.read(reinterpret_cast<char*>(&extra),4);
            if (input.gcount()==4){
                output << count<<","<<strutil::ntos(offset,strutil::radix_t::hex,true,8)<<","<<length<<","<<strutil::ntos(extra,strutil::radix_t::hex,true,8)<<"\n";
            }
            count++;

        }
    }
    catch (const std::exception &e){
        std::cerr <<e.what()<<std::endl;
    }
    return 0;
}
