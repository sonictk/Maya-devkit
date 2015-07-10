//-
// Copyright 2015 Autodesk, Inc.  All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license agreement
// provided at the time of installation or download, or which otherwise
// accompanies this software in either electronic or hard copy form.
//+

#include <maya/MString.h>
#include <maya/MDrawContext.h>
#include <maya/MHWGeometry.h>


#include "GLSLShaderOverride.h"
#include "GLSLShaderSemantics.h"
#include "GLSLShader.h"

#if defined(OSMac_)
# include <OpenGL/gl.h>
#else
# include <GL/gl.h>
#endif


#define ENABLE_TRACE_API_CALLS
#ifdef ENABLE_TRACE_API_CALLS
#define TRACE_API_CALLS(x) cerr << "GLSLShaderOverride: "<<(x)<<"\n"
#else
#define TRACE_API_CALLS(x)
#endif

#define ENABLE_PRINT_DEBUGGING
#ifdef ENABLE_PRINT_DEBUGGING
#define PRINT_DEBUGGING(x) cerr << "GLSLShaderOverride:: "<<(x)<<"\n"
#else
#define PRINT_DEBUGGING(x)
#endif



GLSLShaderOverride::GLSLShaderOverride(const MObject& obj)
: MHWRender::MPxShaderOverride(obj)
, fShaderBound(false)
, fShaderNode(NULL)
{
}

MHWRender::MPxShaderOverride* GLSLShaderOverride::Creator(const MObject& obj)
{
	return new GLSLShaderOverride(obj);
}

GLSLShaderOverride::~GLSLShaderOverride()
{
}

MString GLSLShaderOverride::initialize(const MInitContext& initContext, MInitFeedback& initFeedback)
{
	fShaderNode = NULL;
	if (initContext.shader != MObject::kNullObj) {
		MInitContext* nonConst = const_cast<MInitContext*>(&initContext);
		fShaderNode =(GLSLShaderNode*)MPxHardwareShader::getHardwareShaderPtr(nonConst->shader);
	}

	if(fShaderNode)
	{
		MHWRender::MShaderInstance * shaderInstance = fShaderNode->GetGLSLShaderInstance();
		
		if (shaderInstance)
		{
			setGeometryRequirements(*shaderInstance);

			if (shaderInstance)
			{
				addShaderSignature(*shaderInstance);
			}
		}

		//Setup indexing requirement
		MString customPrimitiveGeneratorName = fShaderNode->techniqueIndexBufferType();
		{
			MHWRender::MIndexBufferDescriptor indexingRequirement
				(MHWRender::MIndexBufferDescriptor::kCustom, customPrimitiveGeneratorName, MHWRender::MGeometry::kTriangles);
			addIndexingRequirement(indexingRequirement);
		}
	
	}

	// Build key string, note that if any attribute on the node changes that
	// would affect the value of this string, then we must trigger rebuild of
	// the shader
	MString result = MString("Autodesk Maya GLSLShaderOverride, nodeName=");
	result += fShaderNode ? fShaderNode->name() : MString("null");
	result += MString(", effectFileName=");
	result += fShaderNode ? fShaderNode->effectName() : MString("null");
	result += MString(", technique=");
	result += (fShaderNode) ? fShaderNode->techniqueName() : MString("null");
	return result;
}


void GLSLShaderOverride::updateDG(MObject object)
{
}

void GLSLShaderOverride::updateDevice()
{
}

void GLSLShaderOverride::endUpdate()
{
}

void GLSLShaderOverride::activateKey(MHWRender::MDrawContext& context, const MString& /*key*/)
{
	if(fShaderNode)
	{
		MHWRender::MShaderInstance * shaderInstance = fShaderNode->GetGLSLShaderInstance();

		if (shaderInstance)
		{
			// Must update before binding otherwise render will lag one draw behind
			// this is quite visible when redrawing swatches.
			fShaderNode->updateParameters(context); 
			shaderInstance->bind(context);  // make sure our shader is the active shader
			fShaderBound = true;
		}
	}
}

bool GLSLShaderOverride::handlesDraw(MHWRender::MDrawContext& context)
{
	if (!fShaderNode)
		return false;

	MHWRender::MShaderInstance * shaderInstance = fShaderNode->GetGLSLShaderInstance();
	if (!shaderInstance)
		return false;

	bool isHandled = false;

	shaderInstance->bind(context);

	const unsigned int passCount = shaderInstance->getPassCount(context);
	for (unsigned int i = 0; i < passCount && !isHandled; ++i)
	{
		isHandled = fShaderNode->passHandlesContext(context, i);
	}

	shaderInstance->unbind(context);

	return isHandled;
}

bool GLSLShaderOverride::draw(MHWRender::MDrawContext& context, const MHWRender::MRenderItemList& renderItemList) const
{
	if (!fShaderNode)
		return false;

	if (!fShaderBound)
		return false;

	MHWRender::MShaderInstance * shaderInstance = fShaderNode->GetGLSLShaderInstance();
	if (!shaderInstance)
		return false;

	bool drewSomething = false;

	const unsigned int passCount = shaderInstance->getPassCount(context);
	for (unsigned int i = 0; i < passCount; ++i)
	{
		if( fShaderNode->passHandlesContext(context, i) )
		{
			shaderInstance->activatePass(context, i);
			MHWRender::MPxShaderOverride::drawGeometry(context);
			drewSomething = true;
		}
	}

	return drewSomething;
}

void GLSLShaderOverride::terminateKey(MHWRender::MDrawContext& context, const MString& /*key*/)
{
	if (fShaderBound && fShaderNode)
	{

		MHWRender::MShaderInstance * shaderInstance = fShaderNode->GetGLSLShaderInstance();
		if (shaderInstance)
		{
			shaderInstance->unbind(context);
		}
	}

	fShaderBound = false;
}

MHWRender::DrawAPI GLSLShaderOverride::supportedDrawAPIs() const
{
	return MHWRender::kOpenGLCoreProfile | MHWRender::kDirectX11 | MHWRender::kOpenGL;
}

bool GLSLShaderOverride::isTransparent()
{
	return fShaderNode && fShaderNode->techniqueIsTransparent();
}

bool GLSLShaderOverride::supportsAdvancedTransparency() const
{
	return fShaderNode && fShaderNode->techniqueSupportsAdvancedTransparency();
}

bool GLSLShaderOverride::overridesDrawState()
{
	return fShaderNode && fShaderNode->techniqueOverridesDrawState();
}


MHWRender::MShaderInstance* GLSLShaderOverride::shaderInstance() const
{
	return fShaderNode ? fShaderNode->GetGLSLShaderInstance() : NULL;
}

bool GLSLShaderOverride::rebuildAlways()
{
	return !fShaderNode || fShaderNode->rebuildAlways();
}


