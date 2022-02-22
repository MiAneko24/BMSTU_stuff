#ifndef DIRECTOR_H
#define DIRECTOR_H
#include "baseBuilder.hpp"
#include "baseLoader.hpp"

class Director
{
    public:
        Director() = default;
        std::shared_ptr<Object> create(ObjectType, std::shared_ptr<BaseBuilder>, std::string filename);
        void setLoader(std::shared_ptr<BaseLoader> load);

    private:
        void createCamera(std::shared_ptr<BaseBuilder> builder);
        void createModel(std::shared_ptr<BaseBuilder> builder);
        void createComposite(std::shared_ptr<BaseBuilder> builder);
        std::shared_ptr<BaseLoader> loader;
        
};


#endif