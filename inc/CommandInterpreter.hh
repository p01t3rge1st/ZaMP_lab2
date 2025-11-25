#ifndef COMMANDINTERPRETER_HH
#define COMMANDINTERPRETER_HH

#include <map>
#include <string>
#include "AbstractInterp4Command.hh"
#include "AbstractScene.hh"
#include "AbstractComChannel.hh"

class CommandInterpreter {
private:
    std::map<std::string, AbstractInterp4Command* (*)(void)> _cmdMap;
    
public:
    CommandInterpreter();
    
    void RegisterCommand(const std::string& name, AbstractInterp4Command* (*createFunc)(void));
    bool ProcessFile(AbstractScene& scn, AbstractComChannel& channel, const std::string& filePath);
};

#endif
