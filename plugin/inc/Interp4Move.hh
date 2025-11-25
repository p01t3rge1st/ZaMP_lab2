#ifndef  COMMAND4MOVE_HH
#define  COMMAND4MOVE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"




class Interp4Move: public AbstractInterp4Command {
 
  double  _Speed_mmS;
  double  _Distance_m;
 public:
 
  Interp4Move();  
 
  virtual void PrintCmd() const override;
 
  virtual void PrintSyntax() const override;
 
  virtual void PrintParams() const override;

  virtual const char* GetCmdName() const override;

 
  virtual bool ExecCmd( AbstractScene      &rScn, 
                        const char         *sMobObjName,
                        AbstractComChannel &rComChann ) override;
 
  virtual bool ReadParams(std::istream& Strm_CmdsList) override;

  
 
  static AbstractInterp4Command* CreateCmd();
 };

#endif
