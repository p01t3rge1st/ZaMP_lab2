#include <iostream>
#include <chrono>
#include <thread>
#include "Interp4Pause.hh"

using std::cout;
using std::endl;

extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Pause"; }
}

AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}

Interp4Pause::Interp4Pause(): _Duration_ms(0)
{}

void Interp4Pause::PrintCmd() const
{
  cout << GetCmdName() << " " << _Duration_ms << endl;
}

const char* Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}

bool Interp4Pause::ExecCmd(AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChann)
{
  
  
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(_Duration_ms)));
  
  
  return true;
}

bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Duration_ms;
  return !Strm_CmdsList.fail();
}

AbstractInterp4Command* Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}

void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause  Czas[ms]" << endl;
}

void Interp4Pause::PrintParams() const
{
  cout << "   Czas: " << _Duration_ms << " ms" << endl;
}
