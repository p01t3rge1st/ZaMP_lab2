#include "Scene.hh"

Scene::Scene() {}



AbstractMobileObj* Scene::FindMobileObj(const char *sName) {
    auto it = _objects.find(sName);
    if (it != _objects.end()) {
        return it->second.get();  
    }
    return nullptr;
}

std::shared_ptr<AbstractMobileObj> Scene::FindMobileObjShared(const char *sName) {
    auto it = _objects.find(sName);
    if (it != _objects.end()) {
        return it->second;
    }
    return nullptr;
}

void Scene::AddMobileObj(AbstractMobileObj *pMobObj) {
    
    if (pMobObj) {
        _objects[pMobObj->GetName()] = std::shared_ptr<AbstractMobileObj>(pMobObj);
    }
}

void Scene::AddMobileObjShared(std::shared_ptr<AbstractMobileObj> pMobObj) {
    if (pMobObj) {
        _objects[pMobObj->GetName()] = pMobObj;
    }
}
