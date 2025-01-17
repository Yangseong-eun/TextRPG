#pragma once

#include "ConsoleObject.h"

class Scene
{
public:
    Scene();
    Scene(const Scene& Scene) = delete;
    virtual ~Scene();
public:
    virtual void Start() = NULL;
    virtual void Update(float DeltaTime);
    virtual void Render(float DeltaTime);
protected:
    std::vector<std::unique_ptr<ConsoleObject>> m_vecObject;
    bool m_delete = false;
public:
    void SetDelete() { m_delete = true; }
};

