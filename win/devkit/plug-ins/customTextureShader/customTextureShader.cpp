//-
// Copyright 2012 Autodesk, Inc.  All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license agreement
// provided at the time of installation or download, or which otherwise
// accompanies this software in either electronic or hard copy form.
//+

#include "customTextureShader.h"

#include <maya/MFnTypedAttribute.h>
#include <maya/MFnStringData.h>
#include <maya/MFnDependencyNode.h>
#include <maya/M3dView.h>

const MTypeId customTextureShader::m_TypeId(0x00081056);
const MString customTextureShader::m_TypeName("customTextureShader");
const MString customTextureShader::m_RegistrantId("customTextureShaderRegistrantId");
const MString customTextureShader::m_drawDbClassification("drawdb/shader/surface/customTextureShader");

customTextureShader::customTextureShader()
{
}

customTextureShader::~customTextureShader()
{
}

MStatus customTextureShader::initialize()
{
	return MS::kSuccess;
}

void* customTextureShader::creator()
{
	return new customTextureShader();
}

MStatus	customTextureShader::render( MGeometryList& iterator)
{
	MStatus result = MStatus::kFailure;

	// for now we render nothing in OpenGL in default viewport
	return result;
}