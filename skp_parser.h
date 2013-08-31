#include <slapi/slapi.h>
#include <slapi/geometry.h>
#include <slapi/initialize.h>
#include <slapi/unicodestring.h>
#include <slapi/model/model.h>
#include <slapi/model/entities.h>
#include <slapi/model/component_instance.h>
#include <slapi/model/component_definition.h>
#include <slapi/model/face.h>
#include <slapi/model/group.h>
#include <slapi/model/vertex.h>
#include <slapi/model/mesh_helper.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

const double INCH_IN_MM = 24.5;

std::ostream& operator<<(std::ostream& os, const SUPoint3D &point) {
    os << point.x * INCH_IN_MM << " ";
    os << point.y * INCH_IN_MM << " ";
    os << point.z * INCH_IN_MM;
    return os;
}

std::ostream& operator<<(std::ostream& os, const SUFaceRef &face) {

    SUMeshHelperRef mesh_ref = SU_INVALID;
    SUMeshHelperCreate(&mesh_ref,face);

    //Get vertices.
    size_t num_vertices = 0;
    SUMeshHelperGetNumVertices(mesh_ref, &num_vertices);
    if (num_vertices == 0)
      return os;
    std::vector<SUPoint3D> vertices(num_vertices);
    SUMeshHelperGetVertices(mesh_ref, num_vertices, &vertices[0], &num_vertices);

    // Get triangle indices.
    size_t num_triangles = 0;
    SUMeshHelperGetNumTriangles(mesh_ref, &num_triangles);
    const size_t num_indices = 3 * num_triangles;
    size_t num_retrieved = 0;
    std::vector<size_t> indices(num_indices);
    SUMeshHelperGetVertexIndices(mesh_ref, num_indices, &indices[0], &num_retrieved);

    // Get UV coords.
    for (size_t i_triangle = 0; i_triangle < num_triangles; i_triangle++) {
        if(i_triangle > 0)
            os << "\n";
        // Three points in each triangle
        for (size_t i = 0; i < 3; i++) {
            if(i > 0)
                os << " ";
            // Get vertex
            size_t index = indices[i_triangle * 3 + i];
            os << vertices[index].x << " " << vertices[index].y << " " << vertices[index].z;
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const SUEntitiesRef &entities) {
    // Get all the faces from the entities object
    size_t faceCount = 0;
    SUEntitiesGetNumFaces(entities, &faceCount);
    if(faceCount > 0) {
        std::vector<SUFaceRef> faces(faceCount);
        SUEntitiesGetFaces(entities, faceCount, &faces[0], &faceCount);
        //std::cout << faceCount << " faces" << std::endl;
        for (size_t i = 0; i < faceCount; i++)
            os << faces[i] << "\n";
    }

    // Get all the groups from the entities object
    size_t num_groups = 0;
    SUEntitiesGetNumGroups(entities, &num_groups);
    if (num_groups > 0) {
        std::vector<SUGroupRef> groups(num_groups);
        SUEntitiesGetGroups(entities, num_groups, &groups[0], &num_groups);
        for (size_t g = 0; g < num_groups; g++) {
            SUGroupRef group = groups[g];
            SUComponentDefinitionRef group_component = SU_INVALID;
            SUEntitiesRef group_entities = SU_INVALID;
            SUGroupGetEntities(group, &group_entities);
            //std::cout << "group" << g << std::endl;
            // Write entities
            os << group_entities;
        }
    }

    // Get all the instance from the entities object
    size_t num_instance = 0;
    SUEntitiesGetNumInstances(entities, &num_instance);
    if (num_instance > 0) {
        std::vector<SUComponentInstanceRef> instances(num_instance);
        SUEntitiesGetInstances(entities, num_instance, &instances[0], &num_instance);
        for (size_t i = 0; i < num_instance; ++i) {
            SUComponentInstanceRef instance = instances[i];
            SUComponentDefinitionRef definition = SU_INVALID;
            SUComponentInstanceGetDefinition(instance, &definition);
            SUEntitiesRef instance_entities = SU_INVALID;
            SUComponentDefinitionGetEntities(definition, &instance_entities);
            //std::cout << "instance" << i << std::endl;
            // Write entities
            os << instance_entities;
        }
    }
    return os;
}
