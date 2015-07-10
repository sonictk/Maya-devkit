#ifndef D3DTextureItem_h_
#define D3DTextureItem_h_

#if defined(D3D9_SUPPORTED)

#include <maya/MObjectHandle.h>
#include <maya/MMessage.h> // For monitoring geometry list nodes
#include <list>

#include <d3d9.h>
#include <d3dx9.h>

//
// A class for a D3D texture
//
class D3DTexture
{
public:
	inline D3DTexture( MObject Node = MObject::kNullObj) : MayaTexture( Node), HwTexture( NULL) 
	{
		mipFilter = magFilter = minFilter = D3DTEXF_LINEAR;
		wrapU = D3DRS_WRAP0;
		wrapV = D3DRS_WRAP1;
		wrapW = D3DRS_WRAP2;
	}
	inline ~D3DTexture() { Release(); }
	void				Populate( MObject MayaTextureNode) { Release(); MayaTexture = MayaTextureNode; }
	void				Release() { if( HwTexture) { /* MGlobal::displayInfo( "Releasing D3D texture\n"); */ HwTexture->Release(); HwTexture = NULL; } }
	inline MObject		Node() const { return MayaTexture; }
	inline LPDIRECT3DTEXTURE9 Texture( LPDIRECT3DDEVICE9 D3D) { if( !HwTexture) Bind( D3D); return HwTexture; }
	void	setTextureState( LPDIRECT3DDEVICE9 D3D );

	D3DTEXTUREFILTERTYPE		minFilter;
	D3DTEXTUREFILTERTYPE		magFilter;
	D3DTEXTUREFILTERTYPE		mipFilter;
	D3DRENDERSTATETYPE wrapU;
	D3DRENDERSTATETYPE wrapV;
	D3DRENDERSTATETYPE wrapW;
private:
	void				Bind( LPDIRECT3DDEVICE9 D3D);
	LPDIRECT3DTEXTURE9	HwTexture;
	MObject				MayaTexture;
};

// Class to associate D3DTexture with Maya texture nodes
struct TextureItem {
	MObjectHandle			m_mayaNode;
	D3DTexture*				m_texture;
	MCallbackId				m_objectDeleteMonitor;
	MCallbackId				m_objectChangeMonitor;
};
typedef std::list<TextureItem*> TextureItemList;

#endif

#endif /* D3DTextureItem_h_ */

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

