#include "Hydraulic.h"

#include <fstream>

HObject Build_HObject(std::ifstream& configFile)
{
    std::string type;
    configFile >> type;
    if (type == "<PIPE>") {
        return HPipe(configFile);
    }
    return HObject(configFile);
}

HObject::HObject(std::ifstream& configFile)
{
    configFile >> name;
}

HPipe::HPipe(std::ifstream& configFile) : HObject(configFile)
{

}

HTank::HTank(std::ifstream& configFile) : HObject(configFile)
{

}

HVent::HVent(std::ifstream& configFile) : HObject(configFile)
{

}
