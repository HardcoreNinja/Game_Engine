#include "Header.h"
#include "Entity.h"

/*Constructor & Destructor*/
Entity::Entity(std::map<std::string, std::unique_ptr<Audio>>& audio_map)
	:audioMap(audio_map)
{
}
Entity::~Entity()
{
}
