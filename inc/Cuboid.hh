#ifndef CUBOID_HH
#define CUBOID_HH

#include "AbstractMobileObj.hh"
#include <string>

class Cuboid : public AbstractMobileObj {
private:
    std::string priv_name;
    Vector3D priv_position_m;
    Vector3D priv_scale;
    Vector3D priv_shift;
    double priv_roll_deg;
    double priv_pitch_deg;
    double priv_yaw_deg;
    Vector3D priv_rgb;

public:
    Cuboid();
    
    virtual double GetAng_Roll_deg() const override { return priv_roll_deg; }
    virtual double GetAng_Pitch_deg() const override { return priv_pitch_deg; }
    virtual double GetAng_Yaw_deg() const override { return priv_yaw_deg; }
    
    virtual void SetAng_Roll_deg(double Ang_Roll_deg) override { priv_roll_deg = Ang_Roll_deg; }
    virtual void SetAng_Pitch_deg(double Ang_Pitch_deg) override { priv_pitch_deg = Ang_Pitch_deg; }
    virtual void SetAng_Yaw_deg(double Ang_Yaw_deg) override { priv_yaw_deg = Ang_Yaw_deg; }
    
    virtual const Vector3D & GetPositoin_m() const override { return priv_position_m; }
    virtual void SetPosition_m(const Vector3D &rPos) override { priv_position_m = rPos; }
    
    virtual void SetName(const char* sName) override { priv_name = sName; }
    virtual const std::string & GetName() const override { return priv_name; }
    
    const Vector3D& GetScale() const { return priv_scale; }
    void SetScale(const Vector3D& scale) { priv_scale = scale; }
    
    const Vector3D& GetShift() const { return priv_shift; }
    void SetShift(const Vector3D& shift) { priv_shift = shift; }
    
    const Vector3D& GetRGB() const { return priv_rgb; }
    void SetRGB(const Vector3D& rgb) { priv_rgb = rgb; }
};

#endif
