#include "XMLReader.hh"
#include <fstream>
#include <sstream>
#include <iostream>

bool XMLReader::ReadFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku: " << filename << std::endl;
        return false;
    }
    
    std::string line;
    bool inPlugins = false;
    bool inObjects = false;
    
    while (std::getline(file, line)) {
        if (line.find("<Plugins>") != std::string::npos) {
            inPlugins = true;
            continue;
        }
        if (line.find("</Plugins>") != std::string::npos) {
            inPlugins = false;
            continue;
        }
        if (line.find("<Objects>") != std::string::npos) {
            inObjects = true;
            continue;
        }
        if (line.find("</Objects>") != std::string::npos) {
            inObjects = false;
            continue;
        }
        
        if (inPlugins && line.find("<Lib") != std::string::npos) {
            std::string name = GetAttributeValue(line, "Name");
            if (!name.empty()) {
                plugins.push_back(name);
            }
        }
        
        if (inObjects && line.find("<Cube") != std::string::npos) {
            XMLCube cube;
            cube.name = GetAttributeValue(line, "Name");
            
            std::string shift = GetAttributeValue(line, "Shift");
            if (!shift.empty()) ParseVector3(shift, cube.shift);
            else { cube.shift[0] = 0; cube.shift[1] = 0; cube.shift[2] = 0; }
            
            std::string scale = GetAttributeValue(line, "Scale");
            if (!scale.empty()) ParseVector3(scale, cube.scale);
            else { cube.scale[0] = 1; cube.scale[1] = 1; cube.scale[2] = 1; }
            
            std::string rot = GetAttributeValue(line, "RotXYZ_deg");
            if (!rot.empty()) ParseVector3(rot, cube.rot);
            else { cube.rot[0] = 0; cube.rot[1] = 0; cube.rot[2] = 0; }
            
            std::string trans = GetAttributeValue(line, "Trans_m");
            if (!trans.empty()) ParseVector3(trans, cube.trans);
            else { cube.trans[0] = 0; cube.trans[1] = 0; cube.trans[2] = 0; }
            
            std::string rgb = GetAttributeValue(line, "RGB");
            if (!rgb.empty()) ParseVector3Int(rgb, cube.rgb);
            else { cube.rgb[0] = 128; cube.rgb[1] = 128; cube.rgb[2] = 128; }
            
            cubes.push_back(cube);
        }
    }
    
    return true;
}

std::string XMLReader::GetAttributeValue(const std::string& line, const std::string& attr) {
    size_t pos = line.find(attr + "=\"");
    if (pos == std::string::npos) return "";
    
    pos += attr.length() + 2;
    size_t endPos = line.find("\"", pos);
    if (endPos == std::string::npos) return "";
    
    return line.substr(pos, endPos - pos);
}

void XMLReader::ParseVector3(const std::string& str, double* out) {
    std::istringstream iss(str);
    iss >> out[0] >> out[1] >> out[2];
}

void XMLReader::ParseVector3Int(const std::string& str, int* out) {
    std::istringstream iss(str);
    iss >> out[0] >> out[1] >> out[2];
}
