#include "SceneManager.h"

#include "scene/Camera.h"
#include "scene/Skybox.h"
#include "scene/Terrain.h"
#include "scene/Mech.h"
#include "animations/CameraTracking.h"
#include "animations/MechWalk.h"

class DemoSceneManager : public SceneManager
{
public:
	DemoSceneManager();

private:
	Camera *mechcam;
	Terrain *terrain;
	Mech *mech;
	CameraTracking *scene_rot;
	MechWalk *walk_animation;
};
