#include <iostream>
#include <sstream>
#include "Interp4Set.hh"
#include "ComChannel.hh"

using std::cout;
using std::endl;

extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}

AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}

Interp4Set::Interp4Set(): _Trans_x(0), _Trans_y(0), _Trans_z(0), _Roll_deg(0), _Pitch_deg(0), _Yaw_deg(0)
{}

void Interp4Set::PrintCmd() const
{
  cout << GetCmdName() << " " << _Trans_x << " " << _Trans_y << " " << _Trans_z << " " << _Roll_deg << " " << _Pitch_deg << " " << _Yaw_deg << endl;
}

const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}

bool Interp4Set::ExecCmd(AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChann)
{
  AbstractMobileObj* pObj = rScn.FindMobileObj(sMobObjName);
  if (!pObj) {
    cout << "Blad: nie znaleziono obiektu " << sMobObjName << endl;
    return false;
  }

  Vector3D pos = pObj->GetPositoin_m();
  pos[0] = _Trans_x;
  pos[1] = _Trans_y;
  pos[2] = _Trans_z;
  pObj->SetPosition_m(pos);
  
  pObj->SetAng_Roll_deg(_Roll_deg);
  pObj->SetAng_Pitch_deg(_Pitch_deg);
  pObj->SetAng_Yaw_deg(_Yaw_deg);

  std::ostringstream oss;
  oss << "UpdateObj Name=" << sMobObjName 
      << " RotXYZ_deg=(" << pObj->GetAng_Roll_deg() << ","
      << pObj->GetAng_Pitch_deg() << "," << pObj->GetAng_Yaw_deg() << ")"
      << " Trans_m=(" << pos[0] << "," << pos[1] << "," << pos[2] << ")";
  
  ComChannel* pComCh = dynamic_cast<ComChannel*>(&rComChann);
  if (!pComCh) return false;
  return pComCh->Send(oss.str());
}

bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Trans_x >> _Trans_y >> _Trans_z;
  Strm_CmdsList >> _Roll_deg >> _Pitch_deg >> _Yaw_deg;
  return !Strm_CmdsList.fail();
}

AbstractInterp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}

void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  Tx Ty Tz  Roll Pitch Yaw" << endl;
}

void Interp4Set::PrintParams() const
{
  cout << "   Trans: (" << _Trans_x << ", " << _Trans_y << ", " << _Trans_z << ")" << endl;
  cout << "   RotXYZ: (" << _Roll_deg << ", " << _Pitch_deg << ", " << _Yaw_deg << ")" << endl;
}
