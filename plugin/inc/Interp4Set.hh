#ifndef COMMAND4SET_HH
#define COMMAND4SET_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"

class Interp4Set: public AbstractInterp4Command {

  double _Trans_x, _Trans_y, _Trans_z;
  double _Roll_deg, _Pitch_deg, _Yaw_deg;

  public:
    Interp4Set();
    virtual void PrintCmd() const override;
    virtual void PrintSyntax() const override;
    virtual void PrintParams() const override;
    virtual const char* GetCmdName() const override;
    virtual bool ExecCmd(AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChann) override;
    virtual bool ReadParams(std::istream& Strm_CmdsList) override;
    static AbstractInterp4Command* CreateCmd();
};

#endif
