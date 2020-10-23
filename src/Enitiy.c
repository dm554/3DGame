#include "Entity.h"
#include "simple_logger.h"

typedef struct{
	Entity *entity_list;
	Uint32 entity_count;
}EntityManager;

static EntityManager entity_manager = { 0 };

void entity_manager_init(Uint32 maxEntities){
	
	if (entity_manager.entity_list != NULL){
		slog("Warning: Entity system already initialized");
	}
	if (!maxEntities){ 
		slog("Cannot initialize entity list of size 0"); 
	}
	entity_manager.entity_list = (Entity *)malloc(sizeof(Entity)* maxEntities);

	if (entity_manager.entity_list == NULL){
		slog("Failed to allocate %i entities for the entity manager", maxEntities);
		return;
	}

	entity_manager.entity_count = maxEntities;
	memset(entity_manager.entity_list, 0, sizeof(Entity)*maxEntities);
	slog("entity manager initialized");
	atexit(entity_manager_close);
}

void entity_manager_close()
{
	int i;
	for (i = 0; i < entity_manager.entity_count; i++)
	{
		if (entity_manager.entity_list[i]._inuse)
		{
			entity_free(&entity_manager.entity_list[i]);
		}
	}
	entity_manager.entity_count = 0;
	free(entity_manager.entity_list);
	entity_manager.entity_list = NULL;
	slog("entity manager closed");
}

Entity *entity_new(){
	int i;
	for (i = 0; i < entity_manager.entity_count; i++){
		if (entity_manager.entity_list[i]._inuse)continue; 
			memset(&entity_manager.entity_list[i], 0, sizeof(Entity));
			entity_manager.entity_list[i]._inuse = 1;
			return &entity_manager.entity_list[i];
	}
	slog("Failed Entity Creation: Need more memory");
	return NULL;
}

Entity entity_update(Entity *self){
	if (!self)return;
}

Entity entity_update_all(){
	
	for (int i = 0; i < entity_manager.entity_count; i++){
		
		if (!entity_manager.entity_list[i]._inuse)continue;
		if (entity_manager.entity_list[i].think)
		{
			entity_manager.entity_list[i].think(&entity_manager.entity_list[i]);
		}
		entity_update(&entity_manager.entity_list[i]);
	
	}

}

Entity entity_free(Entity *self){
	if (!self)return;
	memset(self, 0, sizeof(Entity));
	
	//Possibly need to be freed later
	//gf3d_mesh_free(self->mesh);
	//gf3d_texture_free(self->texture);
	//gf3d_model_free(self->model)
}

void entity_draw_all(Uint32 bufferFrame, VkCommandBuffer commandBuffer){
	
	for (int i = 0; i < entity_manager.entity_count; i++){
		if (!entity_manager.entity_list[i]._inuse)continue;
		entity_draw(&entity_manager.entity_list[i], bufferFrame, commandBuffer, &entity_manager.entity_list[i].modelMatrix);
	}

}

void entity_draw(Entity *self, Uint32 bufferFrame, VkCommandBuffer commandBuffer){
	gf3d_model_draw(self->model, bufferFrame, commandBuffer, self->modelMatrix);
}

int entity_return_num(){
	return 1;
}