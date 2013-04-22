#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H 

#include "InputState.h"
#include "../core/GraphNode.h"
#include "../core/RenderingContext.h"
#include "../animations/Animation.h"
#include "Settings.h"

/// SceneManager holds current game state and takes care of populating and
/// updating the scene.
class SceneManager
{
public:
	SceneManager(Settings *settings);
	virtual ~SceneManager();
	virtual void update(float timestep);
	virtual void render();
	virtual void onViewportReshape(int width, int height);
	virtual void handleInput(InputState *st) {};
	void setShadowmapReference(GraphNode *r) { shadowmap_ref = r; };

protected:
	Settings *settings;
	GraphNode *scene;
	RenderingContext *rendering_context;
	std::list<Animation*> animations;

private:
	Texture *null_shadow_buffer;
	GraphNode *shadowmap_ref;
};

#endif