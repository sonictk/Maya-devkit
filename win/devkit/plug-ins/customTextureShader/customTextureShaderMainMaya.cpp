//-
// Copyright 2012 Autodesk, Inc.  All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license agreement
// provided at the time of installation or download, or which otherwise
// accompanies this software in either electronic or hard copy form.
//+

#include <maya/MFnPlugin.h>
#include <maya/MDGMessage.h>
#include <maya/MDrawRegistry.h>

#include "customTextureShader.h"
#include "customTextureShaderOverride.h"

// Plugin configuration
//
MStatus initializePlugin( MObject obj )
{
	MStatus status;
	MFnPlugin plugin(obj, "Autodesk", "1.0", "Any");

	MString UserClassify = MString("shader/surface/utility:");
	UserClassify += customTextureShader::m_drawDbClassification;

	// Register node
	status = plugin.registerNode(
		customTextureShader::m_TypeName,
		customTextureShader::m_TypeId,
		customTextureShader::creator,
		customTextureShader::initialize,
		MPxNode::kHardwareShader,
		&UserClassify);
	if (status != MS::kSuccess)
	{
		status.perror("registerNode");
		return status;
	}

	// Register a shader override for this node
	status = MHWRender::MDrawRegistry::registerShaderOverrideCreator(
		customTextureShader::m_drawDbClassification,
		customTextureShader::m_RegistrantId,
		customTextureShaderOverride::Creator);
	if (status != MS::kSuccess)
	{
		status.perror("registerShaderOverrideCreator");
		return status;
	}

	return status;
}

MStatus uninitializePlugin( MObject obj)
{
	MFnPlugin plugin(obj);
	MStatus status;

	status = MHWRender::MDrawRegistry::deregisterShaderOverrideCreator(
		customTextureShader::m_drawDbClassification,
		customTextureShader::m_RegistrantId);
	if (status != MS::kSuccess)
	{
		status.perror("deregisterShaderOverrideCreator");
		return status;
	}

	status = plugin.deregisterNode(customTextureShader::m_TypeId);
	if (status != MS::kSuccess)
	{
		status.perror("deregisterNode");
		return status;
	}

	return status;
}

