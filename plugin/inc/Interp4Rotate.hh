#ifndef  COMMAND4ROTATE_HH
#define  COMMAND4ROTATE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Rotate
 *
 * Plik zawiera definicję klasy Interp4Rotate, która modeluje
 * polecenie obrotu dla robota mobilnego.
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego obrót
 *
 * Klasa modeluje polecenie obrotu robota mobilnego wokół wybranej osi.
 */
class Interp4Rotate: public AbstractInterp4Command {
  /*
   * Pola przechowujące wartości parametrów polecenia obrotu.
   */
  char   _Axis;         // Oś obrotu: x, y lub z
  double _Angle_deg;    // Kąt obrotu w stopniach
  double _AngSpeed_degS; // Prędkość kątowa w stopniach na sekundę

 public:
  /*!
   * \brief Konstruktor domyślny
   */
  Interp4Rotate();  
  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  virtual void PrintCmd() const override;
  /*!
   * \brief Wyświetla składnię polecenia
   */
  virtual void PrintSyntax() const override;
  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  virtual void PrintParams() const override;

  /*!
   * \brief Udostępnia nazwę polecenia
   */
  virtual const char* GetCmdName() const override;

  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   *
   * Wykonuje polecenie oraz wizualizuje jego realizację.
   * \param[in,out]  rScn - scena zawierającą obiekty mobilne,
   * \param[in]      sMobObjName - wskaźnik na nazwę lokalizującą i identyfikującą obiekt,
   * \param[in,out]  rComChann - kanał komunikacyjny z serwerem graficznym.
   * \retval true - operacja powiodła się,
   * \retval false - w przypadku przeciwnym.
   */
  virtual bool ExecCmd( AbstractScene      &rScn, 
                        const char         *sMobObjName,
                        AbstractComChannel &rComChann ) override;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList) override;

  
  /*!
   * \brief Tworzy instancję polecenia Rotate
   *
   * Ta metoda nie musi być zdefiniowana w klasie bazowej.
   */
  static AbstractInterp4Command* CreateCmd();
 };

#endif
