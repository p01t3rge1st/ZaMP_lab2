#ifndef XMLREADER_HH
#define XMLREADER_HH

#include <string>
#include <vector>
#include <map>

struct XMLCube {
    std::string name;
    double shift[3];
    double scale[3];
    double rot[3];
    double trans[3];
    int rgb[3];
};

class XMLReader {
public:
    std::vector<std::string> plugins;
    std::vector<XMLCube> cubes;
    
    bool ReadFile(const std::string& filename);
    
private:
    std::string GetAttributeValue(const std::string& line, const std::string& attr);
    void ParseVector3(const std::string& str, double* out);
    void ParseVector3Int(const std::string& str, int* out);
};

#endif
