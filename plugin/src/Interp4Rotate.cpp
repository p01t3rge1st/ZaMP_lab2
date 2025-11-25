#include <iostream>
#include <sstream>
#include "Interp4Rotate.hh"
#include "ComChannel.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}

Interp4Rotate::Interp4Rotate(): _Axis('z'), _Angle_deg(0), _AngSpeed_degS(0){}

void Interp4Rotate::PrintCmd() const
{
 
  cout << GetCmdName() << " " << _Axis << " " << _Angle_deg << " " << _AngSpeed_degS << endl;
}

const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}
bool Interp4Rotate::ExecCmd
( 
  AbstractScene      &rScn, 
  const char         *sMobObjName, 
  AbstractComChannel &rComChann 
)
{
  
  AbstractMobileObj* pObj = rScn.FindMobileObj(sMobObjName);
  if (!pObj) {
    cout << "Blad: nie znaleziono obiektu " << sMobObjName << endl;
    return false;
  }

  
  if (_Axis == 'x') {
    double newAngle = pObj->GetAng_Roll_deg() + _Angle_deg;
    pObj->SetAng_Roll_deg(newAngle);
  }
  else if (_Axis == 'y') {
    double newAngle = pObj->GetAng_Pitch_deg() + _Angle_deg;
    pObj->SetAng_Pitch_deg(newAngle);
  }
  else if (_Axis == 'z') {
    double newAngle = pObj->GetAng_Yaw_deg() + _Angle_deg;
    pObj->SetAng_Yaw_deg(newAngle);
  }
  else {
    cout << "Blad: zla os (tylko x, y, z)" << endl;
    return false;
  }

  std::ostringstream oss;
  oss << "UpdateObj Name=" << sMobObjName 
      << " RotXYZ_deg=(" << pObj->GetAng_Roll_deg() << ","
      << pObj->GetAng_Pitch_deg() << "," << pObj->GetAng_Yaw_deg() << ")";
  
  ComChannel* pComCh = dynamic_cast<ComChannel*>(&rComChann);
  if (!pComCh) return false;
  return pComCh->Send(oss.str());
}
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  std::string axisStr;
  Strm_CmdsList >> axisStr;
  Strm_CmdsList >> _AngSpeed_degS;
  Strm_CmdsList >> _Angle_deg;
  
  if (Strm_CmdsList.fail()) return false;
  
  // Convert OX/OY/OZ to x/y/z
  if (axisStr == "OX") _Axis = 'x';
  else if (axisStr == "OY") _Axis = 'y';
  else if (axisStr == "OZ") _Axis = 'z';
  else return false;
  
  return true;
}
AbstractInterp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  Os[OX|OY|OZ]  SzybkoscKatowa[deg/s]  KatObrotu[deg]" << endl;
}
void Interp4Rotate::PrintParams() const
{
  cout << "   Os: " << _Axis << endl;
  cout << "   Kat obrotu: " << _Angle_deg << " deg" << endl;
  cout << "   Szybkosc katowa: " << _AngSpeed_degS << " deg/s" << endl;
}
