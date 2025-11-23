#include <iostream>
#include "Interp4Rotate.hh"


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
 
  return true;
}
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Axis;
  Strm_CmdsList >> _Angle_deg;
  Strm_CmdsList >> _AngSpeed_degS;
  return !Strm_CmdsList.fail();
}
AbstractInterp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  Os[x|y|z]  KatObrotu[deg]  SzybkoscKatowa[deg/s]" << endl;
}
void Interp4Rotate::PrintParams() const
{
  cout << "   Os: " << _Axis << endl;
  cout << "   Kat obrotu: " << _Angle_deg << " deg" << endl;
  cout << "   Szybkosc katowa: " << _AngSpeed_degS << " deg/s" << endl;
}
