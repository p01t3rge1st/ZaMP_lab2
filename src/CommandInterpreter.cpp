#include "CommandInterpreter.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

CommandInterpreter::CommandInterpreter() {}

void CommandInterpreter::RegisterCommand(const string& name, AbstractInterp4Command* (*createFunc)(void)) {
    _cmdMap[name] = createFunc;
}

bool CommandInterpreter::ProcessFile(AbstractScene& scn, AbstractComChannel& channel, const string& filePath) {
    const char* output_file = "/tmp/polecenia_po_preprocesorze_etap2.cmd";
    
    ostringstream pre;
    pre << "cpp -P " << filePath << " > " << output_file;
    int ret = system(pre.str().c_str());
    if (ret != 0) {
        cerr << "Blad preprocesora dla pliku CMD: " << filePath << endl;
        return false;
    }

    ifstream in(output_file);
    if (!in.good()) { 
        cerr << "Nie moge otworzyc " << output_file << endl; 
        return false; 
    }

    string cmdName, objName;
    while (in >> cmdName) {
        if (cmdName.empty() || cmdName[0] == '#') { 
            string dummy; 
            getline(in, dummy); 
            continue; 
        }
        if (cmdName == "Begin_Parallel_Actions" || cmdName == "End_Parallel_Actions") {
            continue;
        }
        
        auto it = _cmdMap.find(cmdName);
        if (it == _cmdMap.end()) {
            cerr << "Nieznana komenda: " << cmdName << endl;
            string dummy; 
            getline(in, dummy);
            continue;
        }
        
        AbstractInterp4Command* pCmd = it->second();
        if (!pCmd) {
            cerr << "Blad tworzenia komendy: " << cmdName << endl;
            continue;
        }
        
        if (cmdName == "Pause") {
            objName = "";
        } else {
            in >> objName;
        }
        
        if (!pCmd->ReadParams(in)) {
            cerr << "Blad czytania parametrow dla: " << cmdName << endl;
            delete pCmd;
            continue;
        }
        
        if (!pCmd->ExecCmd(scn, objName.c_str(), channel)) {
            cerr << "Blad wykonania: " << cmdName << " " << objName << endl;
        }
        
        delete pCmd;
    }
    
    return true;
}
