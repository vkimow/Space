#include "Engine/Essentials/Meshes/Cube.h"

namespace Engine::Graphics
{
    static std::vector<Vertex> vertices = {
        Vertex({-0.5f, -0.5f, 0.5f},  {0.0f, 0.0f}),
        Vertex({0.5f, -0.5f, 0.5f},   {1.0f, 0.0f}),
        Vertex({0.5f, 0.5f, 0.5f},    {1.0f, 1.0f}),
        Vertex({-0.5f, 0.5f, 0.5f},   {0.0f, 1.0f}),

        Vertex({-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}),
        Vertex({-0.5f, 0.5f, -0.5f},  {1.0f, 1.0f}),
        Vertex({0.5f, 0.5f, -0.5f},   {0.0f, 1.0f}),
        Vertex({0.5f, -0.5f, -0.5f},  {0.0f, 0.0f}),

        Vertex({0.5f, -0.5f, 0.5f},   {0.0f, 0.0f}),
        Vertex({0.5f, -0.5f, -0.5f},  {1.0f, 0.0f}),
        Vertex({0.5f, 0.5f, -0.5f},   {1.0f, 1.0f}),
        Vertex({0.5f, 0.5f, 0.5f},    {0.0f, 1.0f}),

        Vertex({-0.5f, -0.5f, 0.5f},  {1.0f, 0.0f}),
        Vertex({-0.5f, 0.5f, 0.5f},   {1.0f, 1.0f}),
        Vertex({-0.5f, 0.5f, -0.5f},  {0.0f, 1.0f}),
        Vertex({-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}),

        Vertex({-0.5f, 0.5f, 0.5f},   {0.0f, 0.0f}),
        Vertex({0.5f, 0.5f, 0.5f},    {1.0f, 0.0f}),
        Vertex({0.5f, 0.5f, -0.5f},   {1.0f, 1.0f}),
        Vertex({-0.5f, 0.5f, -0.5f},  {0.0f, 1.0f}),

        Vertex({-0.5f, -0.5f, 0.5f},  {0.0f, 0.0f}),
        Vertex({-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}),
        Vertex({0.5f, -0.5f, -0.5f},  {1.0f, 1.0f}),
        Vertex({0.5f, -0.5f, 0.5f},   {0.0f, 1.0f})
    };

    static std::vector<Triangle> triangles = {
        {0, 2, 1}, {2, 0, 3},  // Front face
        {4, 6, 5}, {6, 4, 7},  // Back face
        {8, 10, 9}, {10, 8, 11},  // Right face
        {12, 14, 13}, {14, 12, 15},  // Left face
        {16, 18, 17}, {18, 16, 19},  // Top face
        {20, 22, 21}, {22, 20, 23}  // Bottom face
    };

    static void CalculateNormals(std::vector<Vertex> &vertices, std::vector<Triangle> &triangles)
    {
        for (auto it = vertices.begin(); it != vertices.end(); ++it)
        {
            it->normal = glm::vec3();
        }

        for (auto it = triangles.begin(); it != triangles.end(); ++it)
        {
            Vertex &v1 = vertices[it->Get(0)];
            Vertex &v2 = vertices[it->Get(1)];
            Vertex &v3 = vertices[it->Get(2)];

            glm::vec3 faceNormal = glm::normalize(glm::cross(v2.position - v1.position, v3.position - v1.position));

            v1.normal += faceNormal;
            v2.normal += faceNormal;
            v3.normal += faceNormal;
        }

        for (auto it = vertices.begin(); it != vertices.end(); ++it)
        {
            it->normal = glm::normalize(it->normal);
        }
    }

    Mesh *Cube()
    {
        CalculateNormals(vertices, triangles);
        return new Mesh(vertices, triangles);
    }
}


