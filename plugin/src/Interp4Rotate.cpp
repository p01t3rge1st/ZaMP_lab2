#include <iostream>
#include "Interp4Rotate.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief Tworzy obiekt polecenia Rotate
 *
 * Funkcja eksportowana przez wtyczkę, która tworzy obiekt polecenia.
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 * \brief Konstruktor - inicjalizuje pola wartościami domyślnymi
 */
Interp4Rotate::Interp4Rotate(): _Axis('z'), _Angle_deg(0), _AngSpeed_degS(0)
{}


/*!
 * \brief Wyświetla nazwę i parametry polecenia
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   * Wyświetlenie nazwy polecenia oraz wartości parametrów
   */
  cout << GetCmdName() << " " << _Axis << " " << _Angle_deg 
       << " " << _AngSpeed_degS << endl;
}


/*!
 * \brief Zwraca nazwę polecenia
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 * \brief Wykonuje polecenie obrotu (na razie tylko szkielet)
 */
bool Interp4Rotate::ExecCmd( AbstractScene      &rScn, 
                             const char         *sMobObjName,
                             AbstractComChannel &rComChann
                           )
{
  /*
   * Tu będzie kod wykonujący obrót obiektu
   */
  return true;
}


/*!
 * \brief Wczytuje parametry polecenia ze strumienia (na razie tylko szkielet)
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   * Tu będzie kod wczytujący parametry: oś, kąt, prędkość
   */
  return true;
}


/*!
 * \brief Tworzy nową instancję obiektu Interp4Rotate
 */
AbstractInterp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 * \brief Wyświetla składnię polecenia Rotate
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  Os[x|y|z]  KatObrotu[deg]  SzybkoscKatowa[deg/s]" << endl;
}


/*!
 * \brief Wyświetla wczytane wartości parametrów
 */
void Interp4Rotate::PrintParams() const
{
  cout << "   Os: " << _Axis << endl;
  cout << "   Kat obrotu: " << _Angle_deg << " deg" << endl;
  cout << "   Szybkosc katowa: " << _AngSpeed_degS << " deg/s" << endl;
}
