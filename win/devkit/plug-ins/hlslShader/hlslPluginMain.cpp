//-
// ==========================================================================
// Copyright 1995,2006,2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================
//+

#include "hlslShader.h"

#include <maya/MFnPlugin.h>
#include <maya/MIOStream.h>
#include <maya/MGlobal.h>

#include <maya/MHWShaderSwatchGenerator.h>
#include <maya/MHardwareRenderer.h>


MStatus initializePlugin( MObject obj )
//
//	Description:
//		this method is called when the plug-in is loaded into Maya.  It 
//		registers all of the services that this plug-in provides with 
//		Maya.
//
//	Arguments:
//		obj - a handle to the plug-in object (use MFnPlugin to access it)
//
{ 
	MFnPlugin plugin( obj, "Autodesk", "1.0", MApiVersion );
	MString UserClassify = MString( "shader/surface/utility" );
	

	// Don't initialize swatches in batch mode
	if (MGlobal::mayaState() != MGlobal::kBatch)
	{
		static MString swatchName("hlslRenderSwatchGen");
		MSwatchRenderRegister::registerSwatchRender(swatchName, MHWShaderSwatchGenerator::createObj );
		UserClassify = MString( "shader/surface/utility/:swatch/"+swatchName );
	}


	CHECK_MSTATUS( plugin.registerNode("hlslShader",
		hlslShader::sId,
		hlslShader::creator,
		hlslShader::initialize,
		MPxNode::kHardwareShader,
		&UserClassify));

	CHECK_MSTATUS( plugin.registerCommand("hlslShader",
		hlslShaderCmd::creator,
		hlslShaderCmd::newSyntax));

	return MStatus::kSuccess;
}

MStatus uninitializePlugin( MObject obj)
//
//	Description:
//		this method is called when the plug-in is unloaded from Maya. It 
//		deregisters all of the services that it was providing.
//
//	Arguments:
//		obj - a handle to the plug-in object (use MFnPlugin to access it)
//
{
	MStatus   status;
	MFnPlugin plugin( obj );

	// Deregister our node types.
	//
	CHECK_MSTATUS( plugin.deregisterNode( hlslShader::sId ));

	return MStatus::kSuccess;
}


