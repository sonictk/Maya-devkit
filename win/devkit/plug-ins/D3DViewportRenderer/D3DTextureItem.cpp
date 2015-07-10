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

#include <stdio.h>

#include "D3DTextureItem.h"

#include <maya/MGlobal.h>
#include <maya/MString.h>
#include <maya/MPlug.h>
#include <maya/MPlugArray.h>
#include <maya/MFnDependencyNode.h>

#if defined(D3D9_SUPPORTED)

void D3DTexture::Bind( LPDIRECT3DDEVICE9 D3D)
{
	// Get the filename
	MString filename;
	MFnDependencyNode( MayaTexture).findPlug( "fileTextureName").getValue( filename);
	if( filename.length())
		D3DXCreateTextureFromFileEx( D3D, filename.asChar(), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &HwTexture);
}

void D3DTexture::setTextureState( LPDIRECT3DDEVICE9 D3D )
{
	D3D->SetSamplerState( 0, D3DSAMP_MINFILTER, minFilter);
	D3D->SetSamplerState( 0, D3DSAMP_MAGFILTER, magFilter);
	D3D->SetSamplerState( 0, D3DSAMP_MIPFILTER, mipFilter);
	D3D->SetRenderState(D3DRS_WRAP0, wrapU);
	D3D->SetRenderState(D3DRS_WRAP0, wrapV);
}

#endif





