#ifndef CONFIG_H_
#define CONFIG_H_
#include <string>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <yaml-cpp/yaml.h>

#include "../include/parameter.h"
template <typename T>
void operator>>(const YAML::Node& node, T& i);


namespace SLAM{
    namespace Utils{
        class Config{
        public:
            Config();
            ~Config();
            
            // load config from yame file
            bool Load(const std::string& path = "");
        private:
            std::string RelativePath2AbslutePath(const std::string& root, const std::string& p);
        private:
            std::string m_sLoadPath;
            ModuleParameters m_mModuleParams;
        };
    }

}// namespace SLAM::Utils

#endif