#ifndef SCENE_HH
#define SCENE_HH

#include "AbstractScene.hh"
#include <map>
#include <string>
#include <memory>

class Scene : public AbstractScene {
    std::map<std::string, AbstractMobileObj*> _objects;

public:
    Scene();
    virtual ~Scene();
    
    virtual AbstractMobileObj* FindMobileObj(const char *sName) override;
    virtual void AddMobileObj(AbstractMobileObj *pMobObj) override;
};

#endif
