#ifndef CUBOID_HH
#define CUBOID_HH

#include "AbstractMobileObj.hh"
#include <string>

class Cuboid : public AbstractMobileObj {
    std::string _name;
    Vector3D _position_m;
    Vector3D _scale;
    Vector3D _shift;
    double _roll_deg;
    double _pitch_deg;
    double _yaw_deg;
    Vector3D _rgb;

public:
    Cuboid();
    
    virtual double GetAng_Roll_deg() const override { return _roll_deg; }
    virtual double GetAng_Pitch_deg() const override { return _pitch_deg; }
    virtual double GetAng_Yaw_deg() const override { return _yaw_deg; }
    
    virtual void SetAng_Roll_deg(double Ang_Roll_deg) override { _roll_deg = Ang_Roll_deg; }
    virtual void SetAng_Pitch_deg(double Ang_Pitch_deg) override { _pitch_deg = Ang_Pitch_deg; }
    virtual void SetAng_Yaw_deg(double Ang_Yaw_deg) override { _yaw_deg = Ang_Yaw_deg; }
    
    virtual const Vector3D & GetPositoin_m() const override { return _position_m; }
    virtual void SetPosition_m(const Vector3D &rPos) override { _position_m = rPos; }
    
    virtual void SetName(const char* sName) override { _name = sName; }
    virtual const std::string & GetName() const override { return _name; }
    
    const Vector3D& GetScale() const { return _scale; }
    void SetScale(const Vector3D& scale) { _scale = scale; }
    
    const Vector3D& GetShift() const { return _shift; }
    void SetShift(const Vector3D& shift) { _shift = shift; }
    
    const Vector3D& GetRGB() const { return _rgb; }
    void SetRGB(const Vector3D& rgb) { _rgb = rgb; }
};

#endif
