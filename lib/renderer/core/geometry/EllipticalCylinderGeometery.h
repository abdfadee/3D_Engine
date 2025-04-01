#pragma once
#include "../Geometry.h"


class EllipticalCylinderGeometery : public Geometry {
public:

	EllipticalCylinderGeometery(double radiusX, double radiusZ, double height, int radialSegments = 32, int heightSegments = 1) {
        const float PI = 3.14159265359f;

        for (int y = 0; y <= heightSegments; ++y) {
            float v = float(y) / heightSegments;
            float currentHeight = v * height - height / 2.0f;

            for (int i = 0; i <= radialSegments; ++i) {
                float angle = (float(i) / radialSegments) * 2.0f * PI;
                float cosA = cos(angle);
                float sinA = sin(angle);

                glm::vec3 position = glm::vec3(radiusX * cosA, currentHeight, radiusZ * sinA);
                glm::vec3 normal = glm::normalize(glm::vec3(cosA / radiusX, 0.0f, sinA / radiusZ));
                glm::vec3 tangent = glm::normalize(glm::vec3(-sinA, 0.0f, cosA));
                glm::vec3 bitangent = glm::cross(normal, tangent);

                vertices.push_back(position);
                normals.push_back(normal);
                tangents.push_back(tangent);
                bitangents.push_back(bitangent);
                uv.push_back(glm::vec2(float(i) / radialSegments, v));
            }
        }

        for (unsigned int y = 0; y < heightSegments; ++y) {
            for (unsigned int i = 0; i < radialSegments; ++i) {
                unsigned int a = y * (radialSegments + 1) + i;
                unsigned int b = a + 1;
                unsigned int c = a + (radialSegments + 1);
                unsigned int d = c + 1;

                indices.insert(indices.end(), { a, c, b, b, c, d });
            }
        }

        generateBuffer();
	}

};