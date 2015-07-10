#ifndef D3DResourceManager_h_
#define D3DResourceManager_h_

#include <maya/MViewportRenderer.h>
#include <maya/MDagPath.h>
#include <maya/MObjectHandle.h>
#include <maya/MMessage.h> // For monitoring geometry list nodes
#include <maya/MStringArray.h>
#include <list>

// Resources
#include "D3DGeometryItem.h"
#include "D3DTextureItem.h"

//#define D3D9_SUPPORTED
#if defined(D3D9_SUPPORTED)
#include <d3d9.h>
#include <d3dx9.h>

// Light Item
struct LightItem {
	D3DLIGHT9				m_lightDesc;
	MCallbackId				m_objectDeleteMonitor;
	MCallbackId				m_objectDirtyMonitor;
	bool					m_enabled;
};
typedef std::list<LightItem*> LightItemList;

struct CameraItem {
	// View matrix parameters
	D3DXVECTOR3				m_vEyePt;		// Eye position
    D3DXVECTOR3				m_vLookatPt;	// Look at position
    D3DXVECTOR3				m_vUpVec;		// Up vector

	// Projection matrix parameters
	float					m_FieldOfView;	// Field of view (in degrees)
	float					m_nearClip;		// Near clip plane
	float					m_farClip;		// Far clip plane
	bool					m_isOrtho;		// Is orthographic
};

// Post-processing effect item
struct PostEffectItem
{
	LPD3DXEFFECT		fEffect;
	MString				fName;
};
typedef std::list<PostEffectItem*> PostEffectItemList;

// Surface effect item
struct SurfaceEffectItem
{
	LPD3DXEFFECT		fEffect;
	MString				fName;
};
typedef std::list<SurfaceEffectItem*> SurfaceEffectItemList;

class MDagPath;
class MObject;
class MRenderingInfo;

//
// Manager for D3D resources
//
class D3DResourceManager 
{
public:
	D3DResourceManager();
	virtual ~D3DResourceManager();

	D3DGeometry*			getGeometry( const MDagPath& dagPath, LPDIRECT3DDEVICE9 D3D);
	D3DTexture*				getTexture( MObject& mayaTexture);

	void					clearResources(bool onlyInvalidItems, bool clearShaders);

	bool					cleanupLighting(LPDIRECT3DDEVICE9 D3D);
	bool					setupLighting(LPDIRECT3DDEVICE9 D3D);
	void					enableLights( bool val, LPDIRECT3DDEVICE9 D3D );

	bool					translateCamera( const MDagPath &cameraPath);
	CameraItem*				getCamera() { return &m_camera; }

	bool					initializePostEffects( const MString &effectsLocation,
													LPDIRECT3DDEVICE9 D3D);
	const MStringArray &	getListOfEnabledPostEffects();
	const PostEffectItemList & getPostEffectItemList() const
	{
		return m_PostEffectItemList;
	}

	bool					initializeDefaultSurfaceEffect( const MString &effectsLocation, LPDIRECT3DDEVICE9 D3D,
															const MString & effectName );
	const SurfaceEffectItemList & getSurfaceEffectItemList() const
	{
		return m_SurfaceEffectItemList;
	}

protected:
	void					initializeDefaultCamera();
	//LPDIRECT3DDEVICE9		D3D

	// List of D3D lights corresponding to Maya lights.
	//
	LightItemList			m_lightItemList;
	unsigned int			m_numberLightsEnabled;

	// List of D3D geometry corresponding to Maya dag paths
	//
    GeometryItemList		m_geometryItemList;

	// List of D3D textures corresponding to Maya texture nodes
	//
    TextureItemList			m_textureItemList;

	// List od D3d 2D post processing effects
	PostEffectItemList		m_PostEffectItemList;
	// - List items (by name) in previous list which are enabled.	
	MStringArray			m_EnabledPostEffectItemList; 
	CameraItem				m_camera;

	// List of surface effect items (by name)
	SurfaceEffectItemList	m_SurfaceEffectItemList;
};

#endif

#endif /* D3DResourceManager_h_ */

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

