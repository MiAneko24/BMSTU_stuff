#ifndef SCENEMANAGERCREATOR_H
#define SCENEMANAGERCREATOR_H

class SceneManagerCreator
{
    public:
        std::shared_ptr<SceneManager> getManager();

    private:
        std::shared_ptr<SceneManager> manager;
        std::shared_ptr<SceneManager> createManager();
    
};


#endif