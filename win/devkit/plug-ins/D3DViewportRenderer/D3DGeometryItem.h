#ifndef D3DGeometryItem_h_
#define D3DGeometryItem_h_

#if defined(D3D9_SUPPORTED)

#include <maya/MDagPath.h>
#include <maya/MObjectHandle.h>
#include <maya/MMessage.h> // For monitoring geometry list nodes
#include <list>

#include <d3d9.h>
#include <d3dx9.h>

//
// A class to manage populate and render D3D buffers representing Maya geometry
//
class D3DGeometry
{
public:
	D3DGeometry()
		: VertexBuffer( NULL), IndexBuffer( NULL), FVF( 0), Stride( 0), NumVertices( 0), NumIndices( 0)
	{
	}
	~D3DGeometry() 
	{ 
		Release(); 
	}
	bool Populate( const MDagPath& dagPath, LPDIRECT3DDEVICE9 D3D);
	bool Render( LPDIRECT3DDEVICE9 D3D)
	{
	    D3D->SetStreamSource( 0, VertexBuffer, 0, Stride );
	    D3D->SetFVF( FVF);
		D3D->SetIndices( IndexBuffer); 
		D3D->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, NumVertices, 0, NumIndices / 3);
		return true;
	}
	void Release()
	{
		if( VertexBuffer) 
			VertexBuffer->Release(); 
		if( IndexBuffer) 
			IndexBuffer->Release();	
		VertexBuffer = NULL;
		IndexBuffer = NULL;
	}

private:
	LPDIRECT3DVERTEXBUFFER9 VertexBuffer;
	LPDIRECT3DINDEXBUFFER9	IndexBuffer;
	unsigned int			NumVertices;
	unsigned int			NumIndices;
	DWORD					FVF;
	int						Stride;
};

// Geometry item use to associate a D3DGeometry with Maya geometry
//
struct GeometryItem {
	MDagPath				m_objectPath;
	D3DGeometry*			m_objectGeometry;
	MCallbackId				m_objectDeleteMonitor;
	MCallbackId				m_objectDirtyMonitor;
	MCallbackId				m_objectChangeMonitor;
};
typedef std::list<GeometryItem*> GeometryItemList;

#endif

#endif /* D3DGeometryItem_h_ */

//-
// ==========================================================================
// Copyright 2015 Autodesk, Inc.  All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================
//+

