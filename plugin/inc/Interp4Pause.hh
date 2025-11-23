#ifndef COMMAND4PAUSE_HH
#define COMMAND4PAUSE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"

class Interp4Pause: public AbstractInterp4Command {

  double _Duration_ms;

  public:
    Interp4Pause();
    virtual void PrintCmd() const override;
    virtual void PrintSyntax() const override;
    virtual void PrintParams() const override;
    virtual const char* GetCmdName() const override;
    virtual bool ExecCmd(AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChann) override;
    virtual bool ReadParams(std::istream& Strm_CmdsList) override;
    static AbstractInterp4Command* CreateCmd();
};

#endif
