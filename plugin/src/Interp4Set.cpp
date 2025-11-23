#include <iostream>
#include "Interp4Set.hh"

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

Interp4Set::Interp4Set(): _Axis('z'), _Angle_deg(0)
{}

void Interp4Set::PrintCmd() const
{
  cout << GetCmdName() << " " << _Axis << " " << _Angle_deg << endl;
}

const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}

bool Interp4Set::ExecCmd(AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChann)
{
  return true;
}

bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Axis;
  Strm_CmdsList >> _Angle_deg;
  return !Strm_CmdsList.fail();
}

AbstractInterp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}

void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  Os[x|y|z]  KatWychylenia[deg]" << endl;
}

void Interp4Set::PrintParams() const
{
  cout << "   Os: " << _Axis << endl;
  cout << "   Kat: " << _Angle_deg << " deg" << endl;
}
