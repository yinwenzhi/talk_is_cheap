#include <iostream>
#include "config.h"

template <typename T>
void operator>>(const YAML::Node& node, T& i) {
    i = node.as<T>();
};

using namespace SLAM::Utils;

Config::Config():m_sLoadPath("config.yaml")
{
    std::cout << "config initting ... " << std::endl;
    
    std::cout << "config inited." <<std::endl;
}
Config::~Config(){

}
    
// load config from yame file
bool Config::Load(const std::string& configfile ){
    std::cout << "yaml file: " << configfile << std::endl;
    YAML::Node node = YAML::LoadFile(configfile);
    std::cout << "yaml file loaded" << std::endl;
    node["modulesparameters"]["camera"] >> Config::m_mModuleParams.camera;
    node["modulesparameters"]["imu"] >> Config::m_mModuleParams.imu;
    std::cout <<"camera:"<< Config::m_mModuleParams.camera << std::endl;
    std::cout <<"imu:"  <<  Config::m_mModuleParams.imu << std::endl; 
    
}

// std::string Config::RelativePath2AbslutePath(
//     const std::string& root, const std::string& p)
// {

// }


int main(){
    SLAM::Utils::Config  config;
    config.Load("stereo_INDE.yaml");

}

