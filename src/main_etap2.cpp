#include <iostream>
#include <sstream>
#include <memory>
#include <dlfcn.h>
#include "Scene.hh"
#include "Cuboid.hh"
#include "ComChannel.hh"
#include "XMLReader.hh"
#include "CommandInterpreter.hh"

using namespace std;

static inline Vector3D V3(const double a[3]) {
    Vector3D v; v[0]=a[0]; v[1]=a[1]; v[2]=a[2]; return v;
}

static inline Vector3D V3i(const int a[3]) {
    Vector3D v; v[0]=static_cast<double>(a[0]); v[1]=static_cast<double>(a[1]); v[2]=static_cast<double>(a[2]); return v;
}

static string CreateAddObjCmd(Cuboid* pCube) {
    ostringstream oss;
    oss << "AddObj Name=" << pCube->GetName();
    
    const Vector3D& scale = pCube->GetScale();
    oss << " Scale=(" << scale[0] << "," << scale[1] << "," << scale[2] << ")";
    
    const Vector3D& shift = pCube->GetShift();
    oss << " Shift=(" << shift[0] << "," << shift[1] << "," << shift[2] << ")";
    
    oss << " RotXYZ_deg=(" << pCube->GetAng_Roll_deg() << "," 
        << pCube->GetAng_Pitch_deg() << "," << pCube->GetAng_Yaw_deg() << ")";
    
    const Vector3D& pos = pCube->GetPositoin_m();
    oss << " Trans_m=(" << pos[0] << "," << pos[1] << "," << pos[2] << ")";
    
    const Vector3D& rgb = pCube->GetRGB();
    oss << " RGB=(" << (int)rgb[0] << "," << (int)rgb[1] << "," << (int)rgb[2] << ")";
    
    return oss.str();
}

static bool LoadPlugin(CommandInterpreter& interp, const string& libPath) {
    void* pLibHnd = dlopen(libPath.c_str(), RTLD_LAZY);
    if (!pLibHnd) {
        cerr << "!!! Brak biblioteki: " << libPath << endl;
        cerr << "    dlerror: " << dlerror() << endl;
        return false;
    }
    
    void* pFun = dlsym(pLibHnd, "CreateCmd");
    if (!pFun) {
        cerr << "!!! Nie znaleziono CreateCmd w " << libPath << endl;
        return false;
    }
    auto pCreateCmd = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);
    
    pFun = dlsym(pLibHnd, "GetCmdName");
    if (!pFun) {
        cerr << "!!! Nie znaleziono GetCmdName w " << libPath << endl;
        return false;
    }
    auto pGetCmdName = reinterpret_cast<const char* (*)()>(pFun);
    
    interp.RegisterCommand(pGetCmdName(), pCreateCmd);
    cout << "  Zaladowano plugin: " << pGetCmdName() << endl;
    return true;
}

int main() {
    Scene scn;
    ComChannel channel;
    XMLReader xmlReader;
    CommandInterpreter interp;
    
    cout << "=== Ladowanie pluginow ===" << endl;
    if (!LoadPlugin(interp, "libs/libInterp4Move.so")) return 1;
    if (!LoadPlugin(interp, "libs/libInterp4Rotate.so")) return 1;
    if (!LoadPlugin(interp, "libs/libInterp4Set.so")) return 1;
    if (!LoadPlugin(interp, "libs/libInterp4Pause.so")) return 1;
    
    cout << "=== Wczytywanie konfiguracji XML ===" << endl;
    if (!xmlReader.ReadFile("config.xml")) {
        cerr << "Blad wczytywania config.xml" << endl;
        return 1;
    }
    
    cout << "Znaleziono " << xmlReader.cubes.size() << " obiektow" << endl;

    


    
    for (const auto& xmlCube : xmlReader.cubes) {
        auto pCube = std::make_shared<Cuboid>();
        pCube->SetName(xmlCube.name.c_str());
        pCube->SetScale(V3(xmlCube.scale));
        pCube->SetShift(V3(xmlCube.shift));
        pCube->SetPosition_m(V3(xmlCube.trans));
        pCube->SetAng_Roll_deg(xmlCube.rot[0]);
        pCube->SetAng_Pitch_deg(xmlCube.rot[1]);
        pCube->SetAng_Yaw_deg(xmlCube.rot[2]);
        pCube->SetRGB(V3i(xmlCube.rgb));

        scn.AddMobileObjShared(pCube);
        cout << "  Dodano obiekt: " << xmlCube.name << endl;
    }
    
    cout << endl << "=== Laczenie z serwerem ===" << endl;
    if (!channel.Connect("127.0.0.1", 6217)) {
        cerr << "Zapomniales uruchomic serwer graficzny!" << endl;
        return 1;
    }
    cout << "Polaczono z serwerem!" << endl;
    
    cout << endl << "=== Wysylanie obiektow do serwera ===" << endl;
    channel.Send("Clear");
    cout << "Wyslano: Clear" << endl;
    
    for (const auto& xmlCube : xmlReader.cubes) {
        auto pObj = scn.FindMobileObjShared(xmlCube.name.c_str());
        if (pObj) {
            auto pCube = std::dynamic_pointer_cast<Cuboid>(pObj);
            if (pCube) {
                string cmd = CreateAddObjCmd(pCube.get());
                channel.Send(cmd);
                cout << "Wyslano: " << cmd << endl;
            }
        }
    }

    
    cout << endl << "=== Wykonywanie polecen z CMD ===" << endl;
    interp.ProcessFile(scn, channel, "cmd/przykladowe_polecenia.cmd");
    
    cout << endl << "=== Koniec ===" << endl;
    cin.get();
    
    channel.Close();
    
    return 0;
}
