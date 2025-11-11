#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include "AbstractInterp4Command.hh"

using namespace std;


int main()
{
  // Ładowanie wtyczki Move
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmd_Move)(void);
  void *pFun;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: libInterp4Move.so" << endl;
    return 1;
  }

  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd w libInterp4Move.so" << endl;
    return 1;
  }
  pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);

  // Ładowanie wtyczki Rotate
  void *pLibHnd_Rotate = dlopen("libInterp4Rotate.so",RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmd_Rotate)(void);

  if (!pLibHnd_Rotate) {
    cerr << "!!! Brak biblioteki: libInterp4Rotate.so" << endl;
    return 1;
  }

  pFun = dlsym(pLibHnd_Rotate,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd w libInterp4Rotate.so" << endl;
    return 1;
  }
  pCreateCmd_Rotate = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);

  // Testowanie wtyczki Move
  AbstractInterp4Command *pCmd = pCreateCmd_Move();

  cout << endl;
  cout << "========== Test polecenia Move ==========" << endl;
  cout << "Nazwa polecenia: " << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  // Testowanie wtyczki Rotate
  pCmd = pCreateCmd_Rotate();

  cout << endl;
  cout << "========== Test polecenia Rotate ==========" << endl;
  cout << "Nazwa polecenia: " << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  cout << endl;
  cout << "========== Test preprocesora ==========" << endl;
  cout << endl;
  
  const char* input_file = "cmd/przykladowe_polecenia.cmd";
  const char* output_file = "/tmp/polecenia_po_preprocesorze.cmd";
  
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

  // Zamykanie bibliotek
  dlclose(pLibHnd_Move);
  dlclose(pLibHnd_Rotate);
}
