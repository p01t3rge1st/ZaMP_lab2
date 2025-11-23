#include <iostream>
#include <sstream>
#include "Scene.hh"
#include "Cuboid.hh"
#include "ComChannel.hh"
#include "XMLReader.hh"

using namespace std;

string CreateAddObjCmd(Cuboid* pCube) {
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

int main() {
    Scene scn;
    ComChannel channel;
    XMLReader xmlReader;
    
    cout << "=== Wczytywanie konfiguracji XML ===" << endl;
    if (!xmlReader.ReadFile("config.xml")) {
        cerr << "Blad wczytywania config.xml" << endl;
        return 1;
    }
    
    cout << "Znaleziono " << xmlReader.cubes.size() << " obiektow" << endl;
    
    for (const auto& xmlCube : xmlReader.cubes) {
        Cuboid* pCube = new Cuboid();
        pCube->SetName(xmlCube.name.c_str());
        
        Vector3D scale, shift, trans, rgb;
        scale[0] = xmlCube.scale[0]; scale[1] = xmlCube.scale[1]; scale[2] = xmlCube.scale[2];
        shift[0] = xmlCube.shift[0]; shift[1] = xmlCube.shift[1]; shift[2] = xmlCube.shift[2];
        trans[0] = xmlCube.trans[0]; trans[1] = xmlCube.trans[1]; trans[2] = xmlCube.trans[2];
        rgb[0] = xmlCube.rgb[0]; rgb[1] = xmlCube.rgb[1]; rgb[2] = xmlCube.rgb[2];
        
        pCube->SetScale(scale);
        pCube->SetShift(shift);
        pCube->SetPosition_m(trans);
        pCube->SetAng_Roll_deg(xmlCube.rot[0]);
        pCube->SetAng_Pitch_deg(xmlCube.rot[1]);
        pCube->SetAng_Yaw_deg(xmlCube.rot[2]);
        pCube->SetRGB(rgb);
        
        scn.AddMobileObj(pCube);
        cout << "  Dodano obiekt: " << xmlCube.name << endl;
    }
    
    cout << endl << "=== Laczenie z serwerem ===" << endl;
    if (!channel.Connect("127.0.0.1", 6217)) {
        cerr << "Blad polaczenia z serwerem (czy serwer jest uruchomiony?)" << endl;
        return 1;
    }
    cout << "Polaczono z serwerem!" << endl;
    
    cout << endl << "=== Wysylanie obiektow do serwera ===" << endl;
    channel.Send("Clear");
    cout << "Wyslano: Clear" << endl;
    
    for (const auto& xmlCube : xmlReader.cubes) {
        AbstractMobileObj* pObj = scn.FindMobileObj(xmlCube.name.c_str());
        if (pObj) {
            Cuboid* pCube = dynamic_cast<Cuboid*>(pObj);
            string cmd = CreateAddObjCmd(pCube);
            channel.Send(cmd);
            cout << "Wyslano: " << cmd << endl;
        }
    }
    
    cout << endl << "Program zakonczony. Nacisnij Enter aby zamknac..." << endl;
    cin.get();
    
    channel.Close();
    
    return 0;
}
