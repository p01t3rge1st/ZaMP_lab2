#include "Scene.hh"

Scene::Scene() {}

Scene::~Scene() {
    for (auto& pair : _objects) {
        delete pair.second;
    }
}

AbstractMobileObj* Scene::FindMobileObj(const char *sName) {
    auto it = _objects.find(sName);
    if (it != _objects.end()) {
        return it->second;
    }
    return nullptr;
}

void Scene::AddMobileObj(AbstractMobileObj *pMobObj) {
    if (pMobObj) {
        _objects[pMobObj->GetName()] = pMobObj;
    }
}
