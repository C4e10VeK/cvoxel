#include "renderer.h"

void drawMesh(Mesh* mesh)
{
    bindVertexArray(mesh->_vao);
    bindBuffer(mesh->_ebo);
    glDrawElements(GL_TRIANGLES, mesh->_indCount, GL_UNSIGNED_INT, NULL);
}

