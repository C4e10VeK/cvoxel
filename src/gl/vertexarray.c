#include "vertexarray.h"

VertexArray vertexArrayCreate()
{
	VertexArray res;
	glCreateVertexArrays(1, &res);
	return res;
}

void vertexArrayBind(VertexArray vertexArray)
{
	glBindVertexArray(vertexArray);
}

void vertexArrayUnbind()
{
	glBindVertexArray(0);
}

void vertexArrayDelete(VertexArray vertexArray)
{
	glDeleteVertexArrays(1, &vertexArray);
}

