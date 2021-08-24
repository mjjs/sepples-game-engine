// CORE
#include "engine/core/game.h"
#include "engine/core/input.h"
#include "engine/core/log.h"
#include "engine/core/transform.h"

// MATH

// RENDERING
#include "engine/rendering/buffers/bufferlayout.h"
#include "engine/rendering/buffers/indexbuffer.h"
#include "engine/rendering/buffers/uniformbuffer.h"
#include "engine/rendering/buffers/vertexarray.h"
#include "engine/rendering/buffers/vertexbuffer.h"
#include "engine/rendering/camera.h"
#include "engine/rendering/framebuffer.h"
#include "engine/rendering/mesh.h"
#include "engine/rendering/model.h"
#include "engine/rendering/renderer.h"
#include "engine/rendering/shader.h"
#include "engine/rendering/texture.h"
#include "engine/rendering/texture2d.h"
#include "engine/rendering/vertex.h"

// SCENE
#include "engine/ecs/components/cameracomponent.h"
#include "engine/ecs/components/cppscriptcomponent.h"
#include "engine/ecs/components/meshrenderercomponent.h"
#include "engine/ecs/components/modelrenderercomponent.h"
#include "engine/ecs/components/transformcomponent.h"
#include "engine/ecs/gameobject.h"
#include "engine/ecs/scene.h"
#include "engine/ecs/scriptable.h"

// DEBUGGING
#include "engine/debug/profiler.h"
