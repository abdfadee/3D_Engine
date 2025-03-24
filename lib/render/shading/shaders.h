#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../core/shader.h"


using namespace glm;


/* Shaders */
class Shaders {
public:
    inline static Shader
        Basic,
        Phong,
        NormalVisualizer;



    static void compile() {
        Basic = Shader("lib/render/shading/shaders/Vertex/Basic.vert", "lib/render/shading/shaders/Fragment/Basic.frag");
        NormalVisualizer = Shader("lib/render/shading/shaders/Vertex/NormalVisualizer.vert", "lib/render/shading/shaders/Fragment/Basic.frag", "lib/render/shading/shaders/Geometry/NormalsGenerator.geom");
        
    }

};