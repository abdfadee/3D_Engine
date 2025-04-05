#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../shader.h"


using namespace glm;


/* Shaders */
class Shaders {
public:
    inline static Shader
        *Basic,
        *GeometryShader,
        *LightShader,
        *NormalVisualizer;



    static void compile() {
        //Basic = new Shader("lib/renderer/core/shading/shaders/Vertex/Basic.vert", "lib/renderer/core/shading/shaders/Fragment/Basic.frag");
        GeometryShader = new Shader("lib/renderer/core/shading/shaders/Vertex/GeometryPass.vert", "lib/renderer/core/shading/shaders/Fragment/GeometryPass.frag");
        LightShader = new Shader("lib/renderer/core/shading/shaders/Vertex/LightPass.vert", "lib/renderer/core/shading/shaders/Fragment/LightPass.frag");
        //NormalVisualizer = new Shader("lib/renderer/core/shading/shaders/Vertex/NormalVisualizer.vert", "lib/renderer/core/shading/shaders/Fragment/Basic.frag", "lib/renderer/core/shading/shaders/Geometry/NormalsGenerator.geom");
        
    }


    static void bindBuffers() {
        //Basic->bindBlock("CameraBuffer", 0);
        GeometryShader->bindBlock("CameraBuffer", 0);
        LightShader->bindBlock("CameraBuffer", 0);
    }


    static void prepare() {
        Shaders::compile();
        Shaders::bindBuffers();
    }


};