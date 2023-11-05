#include "Engine/Essentials/Meshes/Sphere.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <map>

namespace Engine::Graphics
{
    constexpr float PHI = 1.618033988749895f;
    constexpr float PHIFraction = PHI - 1;

    static glm::vec2 SphericalUV(const glm::vec3 &position)
    {
        float theta = std::atan2(position.y, position.x);
        float phi = std::acos(position.z / glm::length(position));
        float u = 1.0f - (theta + glm::pi<float>()) / (2.0f * glm::pi<float>());
        float v = (phi + glm::half_pi<float>()) / glm::pi<float>();
        return glm::vec2(u, v);
    }

    static void CalculateUVs(std::vector<Vertex> &vertices)
    {
        for (auto it = vertices.begin(); it != vertices.end(); ++it)
        {
            it->uv = SphericalUV(it->position);
        }
    }

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

    const float X = .525731112119133606f;
    const float Z = .850650808352039932f;
    const float N = 0.f;

    static std::vector<Vertex> vertices =
    {
      {-X,+N,+Z},
      {+X,+N,+Z},
      {-X,+N,-Z},
      {+X,+N,-Z},
      {+N,+Z,+X},
      {+N,+Z,-X},
      {+N,-Z,+X},
      {+N,-Z,-X},
      {+Z,+X,+N},
      {-Z,+X,+N},
      {+Z,-X,+N},
      {-Z,-X,+N}
    };

    static std::vector<Triangle> triangles =
    {
      {0,4,1},
      {0,9,4},
      {9,5,4},
      {4,5,8},
      {4,8,1},
      {8,10,1},
      {8,3,10},
      {5,3,8},
      {5,2,3},
      {2,7,3},
      {7,10,3},
      {7,6,10},
      {7,11,6},
      {11,0,6},
      {0,1,6},
      {6,1,10},
      {9,0,11},
      {9,11,2},
      {9,2,5},
      {7,2,11}
    };

    using Lookup = std::map<std::pair<GLuint, GLuint>, GLuint>;

    GLuint SubdivideEdge(Lookup &lookup,
        std::vector<Vertex> &vertices, GLuint first, GLuint second)
    {
        Lookup::key_type key(first, second);
        if (key.first > key.second)
            std::swap(key.first, key.second);

        GLuint newVertex = vertices.size();
        auto inserted = lookup.insert({key, newVertex});
        if (inserted.second)
        {
            auto &edge0 = vertices[first];
            auto &edge1 = vertices[second];
            auto point = glm::normalize(edge0.position + edge1.position);
            vertices.push_back(point);
        }

        return inserted.first->second;
    }

    std::vector<Triangle> SubdivideTriangle(std::vector<Vertex> &vertices,
        std::vector<Triangle> &triangles)
    {
        Lookup lookup;
        std::vector<Triangle> result;

        for (auto &&each : triangles)
        {
            Triangle mid;
            for (int edge = 0; edge < 3; ++edge)
            {
                mid[edge] = SubdivideEdge(lookup, vertices,
                    each[edge], each[(edge + 1) % 3]);
            }

            result.push_back({each[0], mid[0], mid[2]});
            result.push_back({each[1], mid[1], mid[0]});
            result.push_back({each[2], mid[2], mid[1]});
            result.push_back({mid[0], mid[1], mid[2]});
        }

        return result;
    }

    void SubdivideIcosahedron(std::vector<Vertex> &vertices, std::vector<Triangle> &triangles, int subdivisions)
    {
        for (int i = 0; i < subdivisions; ++i)
        {
            triangles = SubdivideTriangle(vertices, triangles);
        }
    }

    void CW(std::vector<Triangle> &triangles)
    {
        for (auto it = triangles.begin(); it != triangles.end(); ++it)
        {
            std::swap(it->Get(1), it->Get(2));
        }
    }

    Mesh *Sphere()
    {
        SubdivideIcosahedron(vertices, triangles, 3);
        CalculateNormals(vertices, triangles);
        CalculateUVs(vertices);
        return new Mesh(vertices, triangles);
    }
}


