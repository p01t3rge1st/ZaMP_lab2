#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include "AbstractInterp4Command.hh"

using namespace std;

int main() {

  map<string, AbstractInterp4Command* (*)(void)> cmdMap;

  void * pLibHnd_Move = dlopen("libInterp4Move.so", RTLD_LAZY);
  AbstractInterp4Command * ( * pCreateCmd_Move)(void);
  void * pFun;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: libInterp4Move.so" << endl;
    return 1;
  }

  pFun = dlsym(pLibHnd_Move, "CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd w libInterp4Move.so" << endl;
    return 1;
  }
  pCreateCmd_Move = reinterpret_cast < AbstractInterp4Command * ( * )(void) > (pFun);

  void * pLibHnd_Rotate = dlopen("libInterp4Rotate.so", RTLD_LAZY);
  AbstractInterp4Command * ( * pCreateCmd_Rotate)(void);

  if (!pLibHnd_Rotate) {
    cerr << "!!! Brak biblioteki: libInterp4Rotate.so" << endl;
    return 1;
  }

  pFun = dlsym(pLibHnd_Rotate, "CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd w libInterp4Rotate.so" << endl;
    return 1;
  }
  pCreateCmd_Rotate = reinterpret_cast < AbstractInterp4Command * ( * )(void) > (pFun);

  void * pLibHnd_Set = dlopen("libInterp4Set.so", RTLD_LAZY);
  AbstractInterp4Command * ( * pCreateCmd_Set)(void);

  if (!pLibHnd_Set) {
    cerr << "!!! Brak biblioteki: libInterp4Set.so" << endl;
    return 1;
  }

  pFun = dlsym(pLibHnd_Set, "CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd w libInterp4Set.so" << endl;
    return 1;
  }
  pCreateCmd_Set = reinterpret_cast < AbstractInterp4Command * ( * )(void) > (pFun);

  void * pLibHnd_Pause = dlopen("libInterp4Pause.so", RTLD_LAZY);
  AbstractInterp4Command * ( * pCreateCmd_Pause)(void);

  if (!pLibHnd_Pause) {
    cerr << "!!! Brak biblioteki: libInterp4Pause.so" << endl;
    return 1;
  }

  pFun = dlsym(pLibHnd_Pause, "CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd w libInterp4Pause.so" << endl;
    return 1;
  }
  pCreateCmd_Pause = reinterpret_cast < AbstractInterp4Command * ( * )(void) > (pFun);

  cmdMap["Move"] = pCreateCmd_Move;
  cmdMap["Rotate"] = pCreateCmd_Rotate;
  cmdMap["Set"] = pCreateCmd_Set;
  cmdMap["Pause"] = pCreateCmd_Pause;

  AbstractInterp4Command * pCmd = pCreateCmd_Move();

  cout << endl;
  cout << "========== Test polecenia Move ==========" << endl;
  cout << "Nazwa polecenia: " << pCmd -> GetCmdName() << endl;
  cout << endl;
  pCmd -> PrintSyntax();
  cout << endl;
  pCmd -> PrintCmd();
  cout << endl;

  delete pCmd;

  pCmd = pCreateCmd_Rotate();

  cout << endl;
  cout << "========== Test polecenia Rotate ==========" << endl;
  cout << "Nazwa polecenia: " << pCmd -> GetCmdName() << endl;
  cout << endl;
  pCmd -> PrintSyntax();
  cout << endl;
  pCmd -> PrintCmd();
  cout << endl;

  delete pCmd;

  cout << endl;
  cout << "========== Test preprocesora ==========" << endl;
  cout << endl;

  const char * input_file = "cmd/przykladowe_polecenia.cmd";
  const char * output_file = "/tmp/polecenia_po_preprocesorze.cmd";

  string preproc_cmd = string("cpp -P ") + input_file + " > " + output_file;

  int ret = system(preproc_cmd.c_str());

  if (ret != 0) {
    cerr << "!!! Blad preprocesora" << endl;
  } else {
    cout << "Zawartosc pliku po przetworzeniu preprocesora:" << endl;
    cout << "===============================================" << endl;

    ifstream file(output_file);
    string line;
    while (getline(file, line)) {
      if (!line.empty()) {
        cout << line << endl;
      }
    }
    file.close();
  }

  cout << endl;
  cout << "========== Wykonywanie polecen z pliku ==========" << endl;
  cout << endl;

  ifstream cmdFile(output_file);
  string cmdName;
  string objectName;

  while (cmdFile >> cmdName) {
    if (cmdMap.find(cmdName) == cmdMap.end()) {
      cerr << "Nieznane polecenie: " << cmdName << endl;
      string line;
      getline(cmdFile, line);
      continue;
    }

    pCmd = cmdMap[cmdName]();

    if (cmdName == "Pause") {
      if (!pCmd->ReadParams(cmdFile)) {
        cerr << "Blad wczytywania parametrow dla: " << cmdName << endl;
        delete pCmd;
        continue;
      }
      cout << "Polecenie: " << cmdName << endl;
      pCmd->PrintParams();
      cout << endl;
    } else {
      cmdFile >> objectName;
      
      if (!pCmd->ReadParams(cmdFile)) {
        cerr << "Blad wczytywania parametrow dla: " << cmdName << endl;
        delete pCmd;
        continue;
      }

      cout << "Polecenie: " << cmdName << " dla obiektu: " << objectName << endl;
      pCmd->PrintParams();
      cout << endl;
    }

    delete pCmd;
  }

  cmdFile.close();

  dlclose(pLibHnd_Move);
  dlclose(pLibHnd_Rotate);
  dlclose(pLibHnd_Set);
  dlclose(pLibHnd_Pause);
}