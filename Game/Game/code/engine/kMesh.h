#pragma once
#ifndef _MESH_H_
#define _MESH_H_

// TODO:: FINISH THIS SHEITE

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Desc: Mesh is a model that is generated at runtime.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class kVertexBuffer;
class kIndexBuffer;
class kMesh
{
	kVertexBuffer* m_VertexBuffer;
	kIndexBuffer* m_IndexBuffer;
public:
	kMesh( void );
	~kMesh( void );

};

#endif