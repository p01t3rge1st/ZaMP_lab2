#include "Cuboid.hh"

Cuboid::Cuboid() 
    : _name(""), 
      _roll_deg(0),
      _pitch_deg(0),
      _yaw_deg(0)
{
    _position_m[0] = 0; _position_m[1] = 0; _position_m[2] = 0;
    _scale[0] = 1; _scale[1] = 1; _scale[2] = 1;
    _shift[0] = 0; _shift[1] = 0; _shift[2] = 0;
    _rgb[0] = 128; _rgb[1] = 128; _rgb[2] = 128;
}
