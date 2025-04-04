#pragma once
#include "../Geometry.h"
#include <cmath>


class SpheroidGeometry : public Geometry {
public:
    SpheroidGeometry(double radiusX, double radiusY, double radiusZ, unsigned int segments = 72, unsigned int rings = 72) {
        generateSpheroid(radiusX, radiusY, radiusZ, segments, rings);
        generateBuffer();
    }

private:
    void generateSpheroid(float radiusX, float radiusY, float radiusZ, int segments, int rings) {
        
        // Generate vertices, normals, and UVs
        for (int i = 0; i <= rings; ++i) {
            float v = static_cast<float>(i) / rings; // V texture coordinate
            float phi = v * glm::pi<float>();      // Polar angle

            for (int j = 0; j <= segments; ++j) {
                float u = static_cast<float>(j) / segments; // U texture coordinate
                float theta = u * 2.0f * glm::pi<float>(); // Azimuthal angle

                // Vertex position
                float x = radiusX * std::sin(phi) * std::cos(theta);
                float y = radiusY * std::cos(phi);
                float z = radiusZ * std::sin(phi) * std::sin(theta);
                vertices.push_back(glm::vec3(x, y, z));

                // Normal (normalized vertex position)
                glm::vec3 normal = glm::normalize(glm::vec3(x / radiusX, y / radiusY, z / radiusZ));
                normals.push_back(normal);

                // UV coordinates
                uv.push_back(glm::vec2(u, v));

                // Tangent and bitangent (approximated for a spheroid)
                glm::vec3 tangent = glm::normalize(glm::vec3(
                    -radiusX * std::sin(phi) * std::sin(theta),
                    0.0f,
                    radiusZ * std::sin(phi) * std::cos(theta)
                ));
                tangents.push_back(tangent);

                glm::vec3 bitangent = glm::normalize(glm::cross(normal, tangent));
                bitangents.push_back(bitangent);
            }
        }

        // Generate indices
        for (int i = 0; i < rings; ++i) {
            for (int j = 0; j < segments; ++j) {
                int first = (i * (segments + 1)) + j;
                int second = first + segments + 1;

                indices.push_back(first);
                indices.push_back(second);
                indices.push_back(first + 1);

                indices.push_back(second);
                indices.push_back(second + 1);
                indices.push_back(first + 1);
            }
        }

        generateBuffer();
    }
};