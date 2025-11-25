#include "Cuboid.hh"

Cuboid::Cuboid() 
    : priv_name(""), 
      priv_roll_deg(0),
      priv_pitch_deg(0),
      priv_yaw_deg(0)
{
    priv_position_m[0] = 0; priv_position_m[1] = 0; priv_position_m[2] = 0;
    priv_scale[0] = 1; priv_scale[1] = 1; priv_scale[2] = 1;
    priv_shift[0] = 0; priv_shift[1] = 0; priv_shift[2] = 0;
    priv_rgb[0] = 128; priv_rgb[1] = 128; priv_rgb[2] = 128;
}
