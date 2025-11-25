#ifndef SCENE_HH
#define SCENE_HH

#include "AbstractScene.hh"
#include <map>
#include <string>
#include <memory>

class Scene : public AbstractScene {
private:
    std::map<std::string, std::shared_ptr<AbstractMobileObj>> _objects;

 public:
    Scene();
    virtual ~Scene() = default;
    
    virtual AbstractMobileObj* FindMobileObj(const char *sName) override;
    std::shared_ptr<AbstractMobileObj> FindMobileObjShared(const char *sName);
    virtual void AddMobileObj(AbstractMobileObj *pMobObj) override;
    void AddMobileObjShared(std::shared_ptr<AbstractMobileObj> pMobObj);
};

#endif
