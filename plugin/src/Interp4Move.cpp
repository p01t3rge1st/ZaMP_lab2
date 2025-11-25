#include <iostream>
#include <sstream>
#include <cmath>
#include "Interp4Move.hh"
#include "ComChannel.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}





AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}



Interp4Move::Interp4Move(): _Speed_mmS(0), _Distance_m(0)
{}



void Interp4Move::PrintCmd() const
{
  cout << GetCmdName() << " " << _Speed_mmS  << endl;
}



const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}



bool Interp4Move::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
  
  AbstractMobileObj* pObj = rScn.FindMobileObj(sMobObjName);
  if (!pObj) {
    cout << "Blad: nie znaleziono obiektu " << sMobObjName << endl;
    return false;
  }

  
  Vector3D pos = pObj->GetPositoin_m();
  double yaw_deg = pObj->GetAng_Yaw_deg();
  const double PI = 3.14159265358979323846;
  double yaw_rad = yaw_deg * PI / 180.0;

  
  double dx = std::cos(yaw_rad) * _Distance_m;
  double dy = std::sin(yaw_rad) * _Distance_m;
  pos[0] += dx;
  pos[1] += dy;

  
  pObj->SetPosition_m(pos);

  
  std::ostringstream oss;
  oss << "UpdateObj Name=" << sMobObjName
      << " RotXYZ_deg=(" << pObj->GetAng_Roll_deg() << "," << pObj->GetAng_Pitch_deg() << "," << pObj->GetAng_Yaw_deg() << ")"
      << " Trans_m=(" << pos[0] << "," << pos[1] << "," << pos[2] << ")";
  
  
  ComChannel* pComCh = dynamic_cast<ComChannel*>(&rComChann);
  if (!pComCh) return false;
  return pComCh->Send(oss.str());
}



bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Speed_mmS;
  Strm_CmdsList >> _Distance_m;
  return !Strm_CmdsList.fail();
}



AbstractInterp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}



void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}

void Interp4Move::PrintParams() const
{
  cout << "   Szybkosc: " << _Speed_mmS << " m/s" << endl;
  cout << "   Dlugosc:  " << _Distance_m << " m" << endl;
}
