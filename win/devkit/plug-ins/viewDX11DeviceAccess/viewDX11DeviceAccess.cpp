//-
// Copyright 2015 Autodesk, Inc.  All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license agreement
// provided at the time of installation or download, or which otherwise
// accompanies this software in either electronic or hard copy form.
//+
#if _MSC_VER >= 1700
#pragma warning( disable: 4005 )
#endif

#include <stdio.h>

#include <maya/MIOStream.h>
#include <maya/MGlobal.h>
#include <maya/MString.h>
#include <maya/MFnPlugin.h>

// For sample draw traversal
#include <maya/MDrawTraversal.h>
#include <maya/MHardwareRenderer.h>
#include <maya/MFnDagNode.h>
#include <maya/MBoundingBox.h>

#include <maya/M3dView.h>
#include <maya/MPoint.h>
#include <maya/MImage.h>
#include <maya/MViewport2Renderer.h>
#include <maya/MRenderTargetManager.h>
#include <maya/MShaderManager.h>
#include <maya/MTextureManager.h>
#include <maya/MDrawContext.h>
#include <maya/MStateManager.h>
#include <maya/MGLFunctionTable.h>

// Includes for DX
#define WIN32_LEAN_AND_MEAN
#include <d3d11.h>
#include <d3dx11.h>


#include <d3dcompiler.h>
#include <xnamath.h>
#include <string>
#include <map>

//////////////////////////////////////////////////////////////////////////
//
// Trivial scene draw classes
//
//------------------------------------------------------------------------
// Draw traversal utility
//
class MSurfaceDrawTraversal : public MDrawTraversal
{
	virtual bool		filterNode( const MDagPath &traversalItem )
	{
		bool prune = false;

		// Check to only prune shapes, not transforms.
		//
		if ( traversalItem.childCount() == 0)
		{
			if ( !traversalItem.hasFn( MFn::kMesh) &&
				!traversalItem.hasFn( MFn::kNurbsSurface) &&
				!traversalItem.hasFn( MFn::kSubdiv)
				)
			{
				prune = true;
			}
		}
		return prune;
	}
};

//------------------------------------------------------------------------
/*
	A very simplistic custom scene draw example which just draws
	coloured bounding boxes for surface types.

	This code is similiar to the example code found in the
	plugin example OpenGLViewportRenderer and DX11ViewportRenderer which just
	traverses the scene to perform a draw.
*/
class MCustomSceneDraw
{
	bool mDeviceIsGL;

	///////////////////////////////////////////////////////////////
	// OpenGL device members
	MGLFunctionTable *mGLFT;

	///////////////////////////////////////////////////////////////
	// DirectX device members
	ID3D11Device*			m_pD3DDevice;			// Device
	ID3D11DeviceContext*	m_pD3DDeviceContext;	// Device context
	ID3D11RenderTargetView* m_pRenderTargetView;	// Active color target
	ID3D11DepthStencilView* m_pDepthStencilView;	// Active depth target

	// DirectX Rasterizer states.
	ID3D11RasterizerState*	m_pWireframeRS;
	ID3D11RasterizerState*	m_pNormalRS;
	const MHWRender::MRasterizerState *m_apiWireframeRS;
	const MHWRender::MRasterizerState *m_apiNormalRS;

	// DirectX Sampler states
	ID3D11SamplerState* m_pSamplerState;
	const MHWRender::MSamplerState* m_apiSamplerState;

	// DirectX bounding box information
	struct BoundsVertex
	{
		XMFLOAT3	fPosition;
	};
	struct BoundsConstants
	{
		XMMATRIX	fWVP;
		XMFLOAT3	fDiffuseMaterial;
	};
	ID3D11Buffer*			m_pBoundsVertexBuffer;
	ID3D11Buffer*			m_pBoundsIndexBuffer;
	ID3D11Buffer*			m_pPlaneVertexBuffer;
	ID3D11Buffer*			m_pPlaneIndexBuffer;
	ID3D11Buffer*			m_pBoundsConstantBuffer;

	// DirectX plane information
	struct PlaneVertex
	{
		XMFLOAT3	fPosition;
		XMFLOAT2	fUV;
	};

	struct FixedFunctionConstants
	{
		XMMATRIX	wvIT;
		XMMATRIX	wvp;
		XMMATRIX	wv;

		XMFLOAT4	lightDir;
		XMFLOAT4	lightColor;
		XMFLOAT4	ambientLight;
		XMFLOAT4	diffuseMaterial;
		XMFLOAT4	specularColor;
		float		diffuseCoeff;
		float		shininess;
		float		transparency;
	};
	ID3D11Buffer*			m_pFixedFunctionConstantBuffer;

	// Temporary matrices
	XMMATRIX				m_currentViewMatrix;
	XMMATRIX				m_currentProjectionMatrix;

	// Surface effect item
	struct SurfaceEffectItem
	{
		ID3D11VertexShader*	fVertexShader;
		ID3D11PixelShader*	fPixelShader;
		ID3D11InputLayout*	fInputLayout;
	};
	typedef std::map<std::string, SurfaceEffectItem*> SurfaceEffectItemList;

	// List of surface effect items (by name)
	SurfaceEffectItemList	m_SurfaceEffectItemList;

	// Sample image
	MHWRender::MTexture*	m_apiTexture;
	ID3D11ShaderResourceView *m_pTextureView;

public:
	MCustomSceneDraw(bool deviceIsGL)
	{
		mDeviceIsGL = deviceIsGL;

		m_pD3DDevice = NULL;
		m_pRenderTargetView = NULL;
		m_pDepthStencilView = NULL;
		m_pD3DDeviceContext = NULL;
		m_pBoundsVertexBuffer = NULL;
		m_pBoundsIndexBuffer = NULL;
		m_pPlaneVertexBuffer = NULL;
		m_pPlaneIndexBuffer = NULL;
		m_pBoundsConstantBuffer = NULL;
		m_pFixedFunctionConstantBuffer = NULL;
		m_pNormalRS = NULL;
		m_pWireframeRS = NULL;
		m_apiNormalRS = NULL;
		m_apiWireframeRS = NULL;
		m_pSamplerState = NULL;
		m_apiSamplerState = NULL;
		m_apiTexture = NULL;
		m_pTextureView = NULL;

		if ( mDeviceIsGL )
		{
			// Get the function table to perform commands from
			mGLFT = MHardwareRenderer::theRenderer()->glFunctionTable();
		}
		else
		{
			// Get the device and device context
			MHWRender::MRenderer *theRenderer = MHWRender::MRenderer::theRenderer();
			if (theRenderer)
			{
				m_pD3DDevice = (ID3D11Device *)theRenderer->GPUDeviceHandle();
				if (m_pD3DDevice)
				{
					m_pD3DDevice->GetImmediateContext( &m_pD3DDeviceContext );
					if (m_pD3DDeviceContext)
					{
						createGeometryBuffers();
						createTextures();

						//
						// Load effects
						//
						MString shaderLocation(MString(getenv("MAYA_LOCATION")) + MString("\\devkit\\plug-ins"));

						D3D11_INPUT_ELEMENT_DESC layout[] =
						{
							{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
						};
						int numLayoutElements = sizeof layout/sizeof layout[0];
						initializeEffect( shaderLocation, "Maya_unlit1",  "mainVS", "mainPS", layout, numLayoutElements );


						D3D11_INPUT_ELEMENT_DESC layoutUV[] =
						{
							{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
							{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
						};
						numLayoutElements = sizeof layoutUV/sizeof layoutUV[0];
						initializeEffect( shaderLocation, "Maya_unlitUV",  "mainVS", "mainPS", layoutUV, numLayoutElements );
					}
				}
			}
		}
	}
	~MCustomSceneDraw()
	{
		mGLFT = NULL;

		if ( m_pNormalRS )
		{
			// If no api object, then was created locally and must release
			if (!m_apiNormalRS)
				m_pNormalRS->Release();
			else
				MHWRender::MStateManager::releaseRasterizerState(m_apiNormalRS);
			m_apiNormalRS = 0;
			m_pNormalRS = 0;
		}
		if ( m_pWireframeRS )
		{
			// If no api object, then was created locally and must release
			if (!m_apiWireframeRS)
				m_pWireframeRS->Release();
			else
				MHWRender::MStateManager::releaseRasterizerState(m_apiWireframeRS);
			m_apiWireframeRS = 0;
			m_pWireframeRS = 0;
		}
		if (m_pSamplerState)
		{
			if (!m_apiSamplerState)
				m_pSamplerState->Release();
			m_pSamplerState = NULL;
		}
		if (m_apiSamplerState)
		{
			MHWRender::MStateManager::releaseSamplerState(m_apiSamplerState);
			m_apiSamplerState = NULL;
		}
		if ( m_pBoundsVertexBuffer )
		{
			m_pBoundsVertexBuffer->Release();
			m_pBoundsVertexBuffer = NULL;
		}
		if ( m_pBoundsIndexBuffer )
		{
			m_pBoundsIndexBuffer->Release();
			m_pBoundsIndexBuffer = NULL;
		}
		if ( m_pPlaneVertexBuffer )
		{
			m_pPlaneVertexBuffer->Release();
			m_pPlaneVertexBuffer = NULL;
		}
		if ( m_pPlaneIndexBuffer )
		{
			m_pPlaneIndexBuffer->Release();
			m_pPlaneIndexBuffer = NULL;
		}
		if ( m_pBoundsConstantBuffer )
		{
			m_pBoundsConstantBuffer->Release();
			m_pBoundsConstantBuffer = NULL;
		}
		if ( m_pFixedFunctionConstantBuffer )
		{
			m_pFixedFunctionConstantBuffer->Release();
			m_pFixedFunctionConstantBuffer = NULL;
		}
		if (m_pTextureView)
		{
			if (!m_apiTexture)
				m_pTextureView->Release();
			m_pTextureView = NULL;
		}
		if (m_apiTexture)
		{
			MHWRender::MRenderer* renderer = MHWRender::MRenderer::theRenderer();
			if (renderer)
			{
				MHWRender::MTextureManager* textureManager = renderer->getTextureManager();
				if (textureManager)
				{
					textureManager->releaseTexture(m_apiTexture);
				}
			}
			m_apiTexture = NULL;
		}

		m_pD3DDevice = NULL;
		m_pD3DDeviceContext = NULL;
		m_pRenderTargetView = NULL;
		m_pDepthStencilView = NULL;
	}

	// Create states objects. Should be obtained from MStateManager...
	//
	bool createStateObjects( const MHWRender::MDrawContext & drawContext )
	{
		// Return if already created the states
		if (m_pNormalRS)
			return true;

		HRESULT hr;

		MHWRender::MStateManager* stateManager = drawContext.getStateManager();
		bool createStatesViaAPI = (stateManager != NULL);

		if (createStatesViaAPI)
		{
			MHWRender::MRasterizerStateDesc rasterizerStateDesc;
			rasterizerStateDesc.fillMode = MHWRender::MRasterizerState::kFillSolid;
			rasterizerStateDesc.cullMode = MHWRender::MRasterizerState::kCullNone;
			rasterizerStateDesc.frontCounterClockwise = true;
			rasterizerStateDesc.depthBiasIsFloat = true;
			rasterizerStateDesc.depthBias = 0.0f;
			rasterizerStateDesc.depthBiasClamp = 0.0f;
			rasterizerStateDesc.slopeScaledDepthBias = 0.0f;
			rasterizerStateDesc.depthClipEnable = true;
			rasterizerStateDesc.scissorEnable = false;
			rasterizerStateDesc.multiSampleEnable = false;
			rasterizerStateDesc.antialiasedLineEnable = false;

			m_apiNormalRS = stateManager->acquireRasterizerState( rasterizerStateDesc );
			if (m_apiNormalRS)
			{
				m_pNormalRS = (ID3D11RasterizerState *)m_apiNormalRS->resourceHandle();
			}
			else
			{
				MHWRender::MStateManager::releaseRasterizerState(m_apiNormalRS);
				m_apiNormalRS = NULL;
				createStatesViaAPI = false;
			}

			if (createStatesViaAPI)
			{
				rasterizerStateDesc.fillMode = MHWRender::MRasterizerState::kFillWireFrame;
				m_apiWireframeRS = stateManager->acquireRasterizerState( rasterizerStateDesc );
				if (m_apiWireframeRS)
				{
					m_pWireframeRS = (ID3D11RasterizerState *)m_apiWireframeRS->resourceHandle();
				}
				else
				{
					delete m_pWireframeRS;
					m_pWireframeRS = NULL;
					createStatesViaAPI = false;
				}
			}

			MHWRender::MSamplerStateDesc sd;
			m_apiSamplerState = stateManager->acquireSamplerState( sd );
			if (m_apiSamplerState)
			{
				m_pSamplerState = (ID3D11SamplerState* )m_apiSamplerState->resourceHandle();
			}
		}

		if (!createStatesViaAPI)
		{
			D3D11_RASTERIZER_DESC rd;
			rd.FillMode = D3D11_FILL_SOLID;
			rd.CullMode = D3D11_CULL_BACK;
			rd.FrontCounterClockwise = TRUE;
			rd.DepthBias = 0;
			rd.SlopeScaledDepthBias = 0.0f;
			rd.DepthBiasClamp = 0.0f;
			rd.DepthClipEnable = TRUE;
			rd.ScissorEnable = FALSE;
			rd.MultisampleEnable = FALSE;
			rd.AntialiasedLineEnable = FALSE;

			hr = m_pD3DDevice->CreateRasterizerState( &rd, &m_pNormalRS );
			if ( FAILED( hr ) )
				return false;

			rd.FillMode = D3D11_FILL_WIREFRAME;

			hr = m_pD3DDevice->CreateRasterizerState( &rd, &m_pWireframeRS );
			if ( FAILED( hr ) )
				return false;
		}

		return true;
	}

	// Utility to compile a shader
	//
	HRESULT compileShaderFromFile( const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
	{
		HRESULT hr = S_OK;

#ifndef D3DCOMPILE_ENABLE_STRICTNESS
		// allow the plug-in to compile against the Maya 2011 default DXSDK version (August 2009)
#define D3DCOMPILE_ENABLE_STRICTNESS D3D10_SHADER_ENABLE_STRICTNESS
#define D3DCOMPILE_DEBUG D3D10_SHADER_DEBUG
#endif

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows
		// the shaders to be optimized and to run exactly the way they will run in
		// the release configuration of this program.
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		ID3DBlob* pErrorBlob;
		hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel,
			dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
		if( FAILED(hr) )
		{
			if( pErrorBlob != NULL )
				MGlobal::displayInfo( (char*)pErrorBlob->GetBufferPointer() );
			if( pErrorBlob ) pErrorBlob->Release();
			return hr;
		}
		if( pErrorBlob ) pErrorBlob->Release();

		return S_OK;
	}

	//
	// Initialize an effect
	//
	bool initializeEffect( const MString& effectsLocation,
						const MString& effectName,
						const MString& vsName, const MString& psName,
						const D3D11_INPUT_ELEMENT_DESC* layout, int numLayoutElements )
	{
		HRESULT hres;
		MString effectLocation = effectsLocation + "\\" + effectName + ".hlsl";

		// Set up vertex shader
		//
		ID3DBlob* pVSBlob = NULL;
		hres = compileShaderFromFile( effectLocation.asChar(), vsName.asChar(), "vs_5_0", &pVSBlob );
		if (FAILED(hres))
		{
			printf("Failed to compile vertex shader %s in file: %s\n", vsName.asChar(), effectLocation.asChar());
			return false;
		}
		ID3D11VertexShader* pVertexShader = NULL;
		hres = m_pD3DDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &pVertexShader );
		if (FAILED(hres))
		{
			printf("Failed to create vertex shader %s + in file: %s\n", + vsName.asChar()  + effectLocation);
			pVSBlob->Release();
			return false;
		}
		ID3D11InputLayout* pVertexLayout = NULL;
		hres = m_pD3DDevice->CreateInputLayout( layout, numLayoutElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &pVertexLayout );
		pVSBlob->Release();
		if (FAILED(hres))
		{
			printf("Failed to create input layout for file: %s\n", effectLocation.asChar());
			return false;
		}

		// Set up pixel shader
		//
		ID3DBlob* pPSBlob = NULL;
		hres = compileShaderFromFile( effectLocation.asChar(), psName.asChar(), "ps_5_0", &pPSBlob );
		if (FAILED(hres))
		{
			printf("Failed to compile pixel shader %s in file: %s\n", psName.asChar(), effectLocation.asChar());
			pVertexShader->Release();
			pVertexLayout->Release();
			return false;
		}
		ID3D11PixelShader* pPixelShader = NULL;
		hres = m_pD3DDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &pPixelShader );
		pPSBlob->Release();
		if (FAILED(hres))
		{
			printf("Failed to create pixel shader %s in file: %s\n", psName.asChar(), effectLocation.asChar());
			pVertexShader->Release();
			pVertexLayout->Release();
			return false;
		}

		// Create a new effect item
		//
		SurfaceEffectItem *pei = new SurfaceEffectItem;
		if (pei)
		{
			pei->fVertexShader = pVertexShader;
			pei->fPixelShader = pPixelShader;
			pei->fInputLayout = pVertexLayout;

			printf("Created shader: %s\n", effectLocation.asChar());
			m_SurfaceEffectItemList[ effectName.asChar() ] = pei;
		}
		return true;
	}

	//
	//	Update color and depth target pointers for DX
	//
	void setDXColorDepthTargets( void *colorTarget, void *depthTarget )
	{
		m_pRenderTargetView = (ID3D11RenderTargetView* )colorTarget;
		m_pDepthStencilView = (ID3D11DepthStencilView* )depthTarget;
	}

	//
	// Update current view and projection matrices for DX
	void setViewProjectionMatrices( const MMatrix & view, const MMatrix & projection )
	{
		m_currentViewMatrix = XMMATRIX( (float)view.matrix[0][0], (float)view.matrix[0][1], (float)view.matrix[0][2], (float)view.matrix[0][3],
			(float)view.matrix[1][0], (float)view.matrix[1][1], (float)view.matrix[1][2], (float)view.matrix[1][3],
			(float)view.matrix[2][0], (float)view.matrix[2][1], (float)view.matrix[2][2], (float)view.matrix[2][3],
			(float)view.matrix[3][0], (float)view.matrix[3][1], (float)view.matrix[3][2], (float)view.matrix[3][3]);

		m_currentProjectionMatrix = XMMATRIX( (float)projection.matrix[0][0], (float)projection.matrix[0][1], (float)projection.matrix[0][2], (float)projection.matrix[0][3],
			(float)projection.matrix[1][0], (float)projection.matrix[1][1], (float)projection.matrix[1][2], (float)projection.matrix[1][3],
			(float)projection.matrix[2][0], (float)projection.matrix[2][1], (float)projection.matrix[2][2], (float)projection.matrix[2][3],
			(float)projection.matrix[3][0], (float)projection.matrix[3][1], (float)projection.matrix[3][2], (float)projection.matrix[3][3]);
	}

	//
	// Create textures required for drawing
	//
	bool createTextures()
	{
		if (m_pTextureView)
			return true;

		MString imageLocation( MString(getenv("MAYA_LOCATION")) + MString("\\devkit\\plug-ins") );
		MString sampleImageName( "directx11.jpg");

		bool useAPItoLoad = true;
		bool loaded = false;
		if (useAPItoLoad)
		{
			MHWRender::MRenderer *theRenderer = MHWRender::MRenderer::theRenderer();
			if (!theRenderer)
				return false;

			MHWRender::MTextureManager* textureMgr = theRenderer->getTextureManager();
			if (!textureMgr)
				return false;

			// Set up a search location
			textureMgr->addImagePath( imageLocation );

			// Load in a sample image
			m_apiTexture = textureMgr->acquireTexture( sampleImageName );

			if (m_apiTexture)
			{
				m_pTextureView = (ID3D11ShaderResourceView *)m_apiTexture->resourceHandle();
				if (m_pTextureView)
					loaded = true;
			}
		}
		else
		{
			MString absoluteFileName( imageLocation + MString("\\") + sampleImageName );
			HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
				m_pD3DDevice,
				absoluteFileName.asChar(),
				/* D3DX11_IMAGE_LOAD_INFO * */ NULL,
				/* ID3DX11ThreadPump * */ NULL,
				&m_pTextureView,
				NULL);
			if (hr == S_OK)
				loaded = true;
		}

		if (loaded)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC desc;
            m_pTextureView->GetDesc( &desc );

			unsigned int dimension = 0;
            switch( desc.ViewDimension )
            {
            case D3D11_SRV_DIMENSION_TEXTURE1D :
				dimension = 1;
				break;
            case D3D11_SRV_DIMENSION_TEXTURE2D :
				dimension = 2;
				break;
			case D3D11_SRV_DIMENSION_TEXTURE2DMS :
				dimension = 2;
				break;
            case D3D11_SRV_DIMENSION_TEXTURE3D :
				dimension = 3;
				break;
			default:
				break;
			};

			MString absoluteFileName( imageLocation + MString("\\") + sampleImageName );
			printf("Loaded in DX a %dD texture %s.\n", dimension, absoluteFileName.asChar());
		}

		return loaded;
	}

	//
	// Create buffers required for drawing
	//
	bool createGeometryBuffers()
	{
		HRESULT hr;

		// Create vertex buffer
		BoundsVertex vertices[] =
		{
			{ XMFLOAT3( -1.0f, -1.0f, -1.0f ) },
			{ XMFLOAT3( -1.0f, -1.0f,  1.0f ) },
			{ XMFLOAT3( -1.0f,  1.0f, -1.0f ) },
			{ XMFLOAT3( -1.0f,  1.0f,  1.0f ) },
			{ XMFLOAT3(  1.0f, -1.0f, -1.0f ) },
			{ XMFLOAT3(  1.0f, -1.0f,  1.0f ) },
			{ XMFLOAT3(  1.0f,  1.0f, -1.0f ) },
			{ XMFLOAT3(  1.0f,  1.0f,  1.0f ) },
		};

		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT; // D3D11_USAGE_IMMUTABLE
		bd.ByteWidth = sizeof( BoundsVertex ) * 8;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory( &InitData, sizeof(InitData) );
		InitData.pSysMem = vertices;
		hr = m_pD3DDevice->CreateBuffer( &bd, &InitData, &m_pBoundsVertexBuffer );
		if ( FAILED( hr ) )
			return false;

		// Create index buffer
		WORD indices[] =
		{
			0, 1,
			1, 3,
			3, 2,
			2, 0,
			4, 5,
			5, 7,
			7, 6,
			6, 4,
			0, 4,
			1, 5,
			2, 6,
			3, 7,
		};

		bd.Usage = D3D11_USAGE_DEFAULT; // D3D11_USAGE_IMMUTABLE
		bd.ByteWidth = sizeof( WORD ) * 24;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = indices;
		hr = m_pD3DDevice->CreateBuffer( &bd, &InitData, &m_pBoundsIndexBuffer );
		if ( FAILED( hr ) )
			return false;

		PlaneVertex planeVertices[] =
		{
			{ XMFLOAT3( -1.0f, 0.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
			{ XMFLOAT3( -1.0f, 0.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f )},
			{ XMFLOAT3(  1.0f,  0.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
			{ XMFLOAT3( 1.0f,  0.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
		};

		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT; // D3D11_USAGE_IMMUTABLE
		bd.ByteWidth = sizeof( PlaneVertex ) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		ZeroMemory( &InitData, sizeof(InitData) );
		InitData.pSysMem = planeVertices;
		hr = m_pD3DDevice->CreateBuffer( &bd, &InitData, &m_pPlaneVertexBuffer );
		if ( FAILED( hr ) )
			return false;

		WORD planeIndices[] =
		{
			0, 1, 2,
			0, 2, 3
		};
		bd.Usage = D3D11_USAGE_DEFAULT; // D3D11_USAGE_IMMUTABLE
		bd.ByteWidth = sizeof( WORD ) * 6;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = planeIndices;
		hr = m_pD3DDevice->CreateBuffer( &bd, &InitData, &m_pPlaneIndexBuffer );
		if ( FAILED( hr ) )
			return false;

		// Create constant buffer
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( BoundsConstants );
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		hr = m_pD3DDevice->CreateBuffer( &bd, NULL, &m_pBoundsConstantBuffer );
		if ( FAILED( hr ) )
			return false;

		// Create constants for fixed function shading
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( FixedFunctionConstants );
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		hr = m_pD3DDevice->CreateBuffer( &bd, NULL, &m_pFixedFunctionConstantBuffer );
		if ( FAILED( hr ) )
			return false;

		return true;
	}

	// Draw a bounding box (OpenGL version)
	//
	void drawBoundsGL( const MDagPath &dagPath,
					 const MBoundingBox &box,
					 float boundsColor[3])
	{
		if (!mDeviceIsGL)
			return;

		MMatrix  matrix = dagPath.inclusiveMatrix();
		MPoint	minPt = box.min();
		MPoint	maxPt = box.max();

		double bottomLeftFront[3] =		{ minPt.x, minPt.y, minPt.z };
		double topLeftFront[3] = 		{ minPt.x, maxPt.y, minPt.z };
		double bottomRightFront[3] =	{ maxPt.x, minPt.y, minPt.z };
		double topRightFront[3] =		{ maxPt.x, maxPt.y, minPt.z };
		double bottomLeftBack[3] =		{ minPt.x, minPt.y, maxPt.z };
		double topLeftBack[3] =			{ minPt.x, maxPt.y, maxPt.z };
		double bottomRightBack[3] =		{ maxPt.x, minPt.y, maxPt.z };
		double topRightBack[3] =		{ maxPt.x, maxPt.y, maxPt.z };

		mGLFT->glColor3f( boundsColor[0], boundsColor[1], boundsColor[2] );

		mGLFT->glMatrixMode( MGL_MODELVIEW );
		mGLFT->glPushMatrix();
		mGLFT->glMultMatrixd( &(matrix.matrix[0][0]) );

		mGLFT->glBegin(MGL_LINE_STRIP);
		mGLFT->glVertex3dv( bottomLeftFront );
		mGLFT->glVertex3dv( bottomLeftBack );
		mGLFT->glVertex3dv( topLeftBack );
		mGLFT->glVertex3dv( topLeftFront );
		mGLFT->glVertex3dv( bottomLeftFront );
		mGLFT->glVertex3dv( bottomRightFront );
		mGLFT->glVertex3dv( bottomRightBack);
		mGLFT->glVertex3dv( topRightBack );
		mGLFT->glVertex3dv( topRightFront );
		mGLFT->glVertex3dv( bottomRightFront );
		mGLFT->glEnd();

		mGLFT->glBegin(MGL_LINES);
		mGLFT->glVertex3dv(bottomLeftBack);
		mGLFT->glVertex3dv(bottomRightBack);

		mGLFT->glVertex3dv(topLeftBack);
		mGLFT->glVertex3dv(topRightBack);

		mGLFT->glVertex3dv(topLeftFront);
		mGLFT->glVertex3dv(topRightFront);
		mGLFT->glEnd();

		mGLFT->glPopMatrix();
	}

	void drawPlaneDX(const MHWRender::MDrawContext & drawContext)
	{
		if (mDeviceIsGL)
			return;

		if (!m_pPlaneVertexBuffer || !m_pPlaneIndexBuffer ||
			!m_pBoundsConstantBuffer )
		{
			return;
		}

		MHWRender::MStateManager* stateManager = drawContext.getStateManager();
		if (stateManager)
		{
			stateManager->setRasterizerState( m_apiNormalRS );
		}

		// Scale plane to size 10
		//
		XMMATRIX mat( 4.0f, 0.0f,	0.0f, 0.0f,
						0.0f, 4.0f, 0.0f, 0.0f,
						0.0f, 0.0f,	4.f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f );

		// Set vertex buffer
		UINT stride = sizeof( PlaneVertex );
		UINT offset = 0;
		m_pD3DDeviceContext->IASetVertexBuffers( 0, 1, &m_pPlaneVertexBuffer, &stride, &offset );

		// Set index buffer
		m_pD3DDeviceContext->IASetIndexBuffer( m_pPlaneIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );

		// Set primitive topology
		m_pD3DDeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

		// Set constant buffer
		BoundsConstants cb;
		cb.fWVP = XMMatrixTranspose( mat * m_currentViewMatrix * m_currentProjectionMatrix );
		cb.fDiffuseMaterial = XMFLOAT3( 1.0f, 1.0f, 1.0f);
		m_pD3DDeviceContext->UpdateSubresource( m_pBoundsConstantBuffer, 0, NULL, &cb, 0, 0 );

		// Get the shader
		SurfaceEffectItemList::const_iterator it = m_SurfaceEffectItemList.find( "Maya_unlitUV" );
		if ( it == m_SurfaceEffectItemList.end() )
			return;
		const SurfaceEffectItem* sei = it->second;

		// Bind a shader
		m_pD3DDeviceContext->VSSetShader( sei->fVertexShader, NULL, 0 );
		m_pD3DDeviceContext->VSSetConstantBuffers( 0, 1, &m_pBoundsConstantBuffer );
		m_pD3DDeviceContext->IASetInputLayout( sei->fInputLayout );
		m_pD3DDeviceContext->PSSetShader( sei->fPixelShader, NULL, 0 );
		m_pD3DDeviceContext->PSSetConstantBuffers( 0, 1, &m_pBoundsConstantBuffer );

		// Bind a texture
		if (m_pSamplerState && m_pTextureView)
		{
			m_pD3DDeviceContext->PSSetSamplers( 0, 1, &m_pSamplerState );
			m_pD3DDeviceContext->PSSetShaderResources( 0, 1, &m_pTextureView );
		}

		// draw
		m_pD3DDeviceContext->DrawIndexed( 6, 0, 0 );
	}

	// Draw a bounding box (DX version). This code is in progress
	//
	void drawBoundsDX(const MHWRender::MDrawContext & drawContext,
					 const MDagPath &dagPath,
					 const MBoundingBox &box,
					 float boundsColor[3])
	{
		if (mDeviceIsGL)
			return;

		if (!m_pBoundsVertexBuffer || !m_pBoundsIndexBuffer ||
			!m_pBoundsConstantBuffer )
		{
			return;
		}

		// Set rasterizer state.
		//
		// This code demonstrates how the API wrapper for a rasterizer state
		// can be used to perform the same functionality as
		// directly calling int the device context.
		//
		// Using the state manager means that state will be tracked interally
		// and will reduce the frequency of redundant state changes
		//
		bool useDrawContextToSetState = true;
		MStatus status = MStatus::kFailure;
		if (useDrawContextToSetState)
		{
			MHWRender::MStateManager* stateManager = drawContext.getStateManager();
			if (stateManager)
			{
				status = stateManager->setRasterizerState( m_apiWireframeRS );
			}
		}
		if (status != MStatus::kSuccess)
		{
			m_pD3DDeviceContext->RSSetState( m_pWireframeRS );
		}

		MMatrix  matrix = dagPath.inclusiveMatrix();

		// Transform from object to world space
		//
		XMMATRIX mat = XMMATRIX
			(
			(float)matrix.matrix[0][0], (float)matrix.matrix[0][1], (float)matrix.matrix[0][2], (float)matrix.matrix[0][3],
			(float)matrix.matrix[1][0], (float)matrix.matrix[1][1], (float)matrix.matrix[1][2], (float)matrix.matrix[1][3],
			(float)matrix.matrix[2][0], (float)matrix.matrix[2][1], (float)matrix.matrix[2][2], (float)matrix.matrix[2][3],
			(float)matrix.matrix[3][0], (float)matrix.matrix[3][1], (float)matrix.matrix[3][2], (float)matrix.matrix[3][3]
		);

		// Adjust the unit cube to the bounds
		//
		MPoint	minPt = box.min();
		MPoint	maxPt = box.max();
		float minVal[3] = { (float)minPt.x, (float)minPt.y, (float)minPt.z };
		float maxVal[3] = { (float)maxPt.x, (float)maxPt.y, (float)maxPt.z };
		XMMATRIX bounds( 0.5f*(maxVal[0]-minVal[0]), 0.0f,						 0.0f,							0.0f,
						0.0f,						 0.5f*(maxVal[1]-minVal[1]), 0.0f,							0.0f,
						0.0f,						 0.0f,						 0.5f*(maxVal[2]-minVal[2]),	0.0f,
						0.5f*(maxVal[0]+minVal[0]), 0.5f*(maxVal[1]+minVal[1]), 0.5f*(maxVal[2]+minVal[2]),	1.0f );

		// Set vertex buffer
		UINT stride = sizeof( BoundsVertex );
		UINT offset = 0;
		m_pD3DDeviceContext->IASetVertexBuffers( 0, 1, &m_pBoundsVertexBuffer, &stride, &offset );

		// Set index buffer
		m_pD3DDeviceContext->IASetIndexBuffer( m_pBoundsIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );

		// Set constant buffer
		BoundsConstants cb;
		cb.fWVP = XMMatrixTranspose( bounds * mat * m_currentViewMatrix * m_currentProjectionMatrix );
		cb.fDiffuseMaterial = XMFLOAT3( boundsColor[0], boundsColor[1], boundsColor[2] );
		m_pD3DDeviceContext->UpdateSubresource( m_pBoundsConstantBuffer, 0, NULL, &cb, 0, 0 );

		// Set primitive topology
		m_pD3DDeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_LINELIST );

		// get shader
		SurfaceEffectItemList::const_iterator it = m_SurfaceEffectItemList.find( "Maya_unlit1" );
		if ( it == m_SurfaceEffectItemList.end() )
			return;
		const SurfaceEffectItem* sei = it->second;

		// bind shaders
		m_pD3DDeviceContext->VSSetShader( sei->fVertexShader, NULL, 0 );
		m_pD3DDeviceContext->VSSetConstantBuffers( 0, 1, &m_pBoundsConstantBuffer );
		m_pD3DDeviceContext->IASetInputLayout( sei->fInputLayout );
		m_pD3DDeviceContext->PSSetShader( sei->fPixelShader, NULL, 0 );
		m_pD3DDeviceContext->PSSetConstantBuffers( 0, 1, &m_pBoundsConstantBuffer );

		// draw
		m_pD3DDeviceContext->DrawIndexed( 24, 0, 0 );
	}

	// Draw a scene full of bounding boxes
	//
	bool draw(const MHWRender::MDrawContext & drawContext,
			  MDagPath &cameraPath, unsigned int width, unsigned int height)
	{
		// Setup (GL). Push state and clear the background
		if (mDeviceIsGL)
		{
			GLenum error;

			while( (error = mGLFT->glGetError()) != MGL_NO_ERROR ) {
				;
			}
			mGLFT->glPushAttrib(MGL_ALL_ATTRIB_BITS);
			mGLFT->glPushClientAttrib(MGL_CLIENT_VERTEX_ARRAY_BIT);

			// Red for OpenGL
			mGLFT->glClearColor(0.8f, 0.2f, 0.2f, 0.0f);
			mGLFT->glClear(MGL_COLOR_BUFFER_BIT | MGL_DEPTH_BUFFER_BIT);
		}

		// Setup (DX). Clear the background
		else
		{
			if (m_pD3DDeviceContext)
			{
				if (m_pRenderTargetView)
				{
					// Blue for DX
					float clearColor[4] = { 0.0f, 0.125f, 0.6f, 0.0f };
					m_pD3DDeviceContext->ClearRenderTargetView( m_pRenderTargetView, clearColor );
				}
				if (m_pDepthStencilView)
				{
					m_pD3DDeviceContext->ClearDepthStencilView( m_pDepthStencilView,
						D3D11_CLEAR_DEPTH, 1.0f, 0 );
				}


				drawPlaneDX( drawContext );
			}
		}

		if (!cameraPath.isValid())
			return false;

		MDrawTraversal *trav = NULL;
		trav = new MSurfaceDrawTraversal;

		if (!trav)
			return false;

		trav->enableFiltering( true );
		trav->setFrustum( cameraPath, width, height );
		if (!trav->frustumValid())
		{
			delete trav; trav = NULL;
			return false;
		}
		trav->traverse();

		unsigned int numItems = trav->numberOfItems();
		unsigned int i;
		for (i=0; i<numItems; i++)
		{
			MDagPath path;
			trav->itemPath(i, path);

			if (path.isValid())
			{
				bool performBoundsDraw = false;
				//
				// Draw surfaces (polys, nurbs, subdivs)
				//
				bool active = false;
				bool templated = false;
				float boundsColor[3] = { 1.0f, 1.0f, 1.0f };
				if ( path.hasFn( MFn::kMesh) ||
					path.hasFn( MFn::kNurbsSurface) ||
					path.hasFn( MFn::kSubdiv) )
				{
					performBoundsDraw = true;
					if (trav->itemHasStatus( i, MDrawTraversal::kActiveItem ))
					{
						active = true;
					}
					else if (trav->itemHasStatus( i, MDrawTraversal::kTemplateItem ))
					{
						boundsColor[0] = 0.2f;
						boundsColor[1] = 0.2f;
						boundsColor[2] = 0.2f;
						templated = true;
					}
					else
					{
						if (path.hasFn( MFn::kMesh ))
						{
							boundsColor[0] = 0.286f;
							boundsColor[1] = 0.706f;
							boundsColor[2] = 1.0f;
						}
						else if (path.hasFn( MFn::kNurbsSurface))
						{
							boundsColor[0] = 0.486f;
							boundsColor[1] = 0.306f;
							boundsColor[2] = 1.0f;
						}
						else
						{
							boundsColor[0] = 0.886f;
							boundsColor[1] = 0.206f;
							boundsColor[2] = 1.0f;
						}
					}
				}

				// Draw bounds
				if (performBoundsDraw)
				{
					MFnDagNode dagNode(path);
					MBoundingBox box = dagNode.boundingBox();
					if (mDeviceIsGL)
						drawBoundsGL( path, box, boundsColor );
					else
						drawBoundsDX( drawContext, path, box, boundsColor );
				}
			}
		}

		if (trav)
		{
			delete trav;
			trav = NULL;
		}

		// Cleanup (GL). Pop state
		if (mDeviceIsGL)
		{
			GLenum error;

			while( (error = mGLFT->glGetError()) != GL_NO_ERROR ) {
				;
			}
			mGLFT->glPopAttrib();
			mGLFT->glPopClientAttrib();
		}
		// Clean (DX). Nothing currently
		else
		{
			;
		}
		return true;
	}
};

//////////////////////////////////////////////////////////////////////////
//
// Render override classes
//

//------------------------------------------------------------------------
/*
	Custom user operation. One approach to adding a pre and
	post scene callback. In this approach only 1 operation
	is reused twice with internal state as to when it is being
	used. Another approach which may be more suitable for when
	global state is changed is to create 2 instances of this
	operation and keep global state on the override instead of
	locally here.

	The cost of an override is very small so creating more instances
	can provide a clearer and cleaner render loop logic.
*/
class viewRenderUserOperation : public MHWRender::MUserRenderOperation
{
public:
	viewRenderUserOperation(const MString &name)
		: MUserRenderOperation( name )
		, mCustomSceneDraw(NULL)
	{
		mTargets[0] = mTargets[1] = NULL;
	}
	virtual ~viewRenderUserOperation()
	{
		delete mCustomSceneDraw;
		mCustomSceneDraw = NULL;
		mTargets[0] = mTargets[1] = NULL;
	}

	virtual MStatus execute( const MHWRender::MDrawContext & drawContext )
	{
		// Example code to find the active override.
		// This is not necessary if the operations just keep a reference
		// to the override, but this demonstrates how this
		// contextual information can be extracted.
		//
		MHWRender::MRenderer *theRenderer = MHWRender::MRenderer::theRenderer();
		const MHWRender::MRenderOverride *overridePtr = NULL;
		bool deviceIsGL = true;
		if (theRenderer)
		{
			const MString & overrideName = theRenderer->activeRenderOverride();
			overridePtr = theRenderer->findRenderOverride( overrideName );

			deviceIsGL  = theRenderer->drawAPIIsOpenGL();
		}

		//  Draw some addition things after the scene draw
		//
		bool drawingInteractive = false;
		M3dView mView;
		if (mPanelName.length() &&
			(M3dView::getM3dViewFromModelPanel(mPanelName, mView) == MStatus::kSuccess))
		{
			drawingInteractive = true;
		}

		// Get the current viewport and scale it relative to that
		//
		int targetW, targetH;
		drawContext.getRenderTargetSize( targetW, targetH );

		// Some user drawing
		//
		MDagPath cameraPath;
		if (drawingInteractive)
			mView.getCamera( cameraPath);

		if (!mCustomSceneDraw)
			mCustomSceneDraw = new MCustomSceneDraw( deviceIsGL );
		if (mCustomSceneDraw)
		{
			if (deviceIsGL)
			{
				mCustomSceneDraw->setDXColorDepthTargets(NULL, NULL);
			}
			else
			{
				// Set targets
				void *handle1 = mTargets[0] ? mTargets[0]->resourceHandle() : NULL;
				void *handle2 = mTargets[1] ? mTargets[1]->resourceHandle() : NULL;
				mCustomSceneDraw->setDXColorDepthTargets( handle1, handle2 );

				// Set view and projection
				MMatrix view =
					drawContext.getMatrix(MHWRender::MFrameContext::kWorldViewMtx );
				MMatrix projection =
					drawContext.getMatrix(MHWRender::MFrameContext::kProjectionMtx );
				mCustomSceneDraw->setViewProjectionMatrices( view, projection );

				// Update state objects
				mCustomSceneDraw->createStateObjects( drawContext );
			}
			mCustomSceneDraw->draw( drawContext, cameraPath, targetW, targetH );
		}
		return MStatus::kSuccess;
	}

	// Camera override
	virtual const MHWRender::MCameraOverride * cameraOverride()
	{
		M3dView mView;
		if (mPanelName.length() &&
			(M3dView::getM3dViewFromModelPanel(mPanelName, mView) == MStatus::kSuccess))
		{
			mView.getCamera( mCameraOverride.mCameraPath );
			return &mCameraOverride;
		}
		return NULL;
	}

	// Target override
	virtual MHWRender::MRenderTarget* const* targetOverrideList(unsigned int &listSize)
	{
		if (mTargets[0] && mTargets[1])
		{
			listSize = 2;
			return &mTargets[0];
		}
		return NULL;
	}

	void setRenderTarget(unsigned int i, MHWRender::MRenderTarget* val)
	{
		if (i<2)
			mTargets[i] = val;
	}

	const MString & panelName() const
	{
		return mPanelName;
	}
	void setPanelName( const MString & name )
	{
		mPanelName.set( name.asChar() );
	}

protected:
	MString mPanelName;
	MHWRender::MCameraOverride mCameraOverride;
	MHWRender::MRenderTarget* mTargets[2];
	MCustomSceneDraw *mCustomSceneDraw;
};

//------------------------------------------------------------------------
// Custom present target operation
//
class viewRenderPresentTarget : public MHWRender::MPresentTarget
{
public:
	viewRenderPresentTarget(const MString &name)
	: MPresentTarget( name )
	{
		mTargets[0] = mTargets[1] = NULL;
	}

	~viewRenderPresentTarget()
	{
		mTargets[0] = mTargets[1] = NULL;
	}

	virtual MHWRender::MRenderTarget* const* targetOverrideList(unsigned int &listSize)
	{
		if (mTargets[0] && mTargets[1])
		{
			listSize = 2;
			return &mTargets[0];
		}
		return NULL;
	}

	void setRenderTarget(unsigned int i, MHWRender::MRenderTarget* val)
	{
		if (i<2)
			mTargets[i] = val;
	}
protected:
	// Targets used as input parameters to mShaderInstance;
	MHWRender::MRenderTarget* mTargets[2];
};


//------------------------------------------------------------------------
// Custom hud operation
//
//------------------------------------------------------------------------
// Custom hud operation
//
class viewRenderHUDOperation : public MHWRender::MHUDRender
{
public:
	viewRenderHUDOperation()
	{
		mTargets[0] = mTargets[1] = NULL;
	}

	~viewRenderHUDOperation()
	{
		mTargets[0] = mTargets[1] = NULL;
	}

	// Target override
	virtual MHWRender::MRenderTarget* const* targetOverrideList(unsigned int &listSize)
	{
		if (mTargets[0] && mTargets[1])
		{
			listSize = 2;
			return &mTargets[0];
		}
		return NULL;
	}

	void setRenderTarget(unsigned int i, MHWRender::MRenderTarget* val)
	{
		if (i<2)
			mTargets[i] = val;
	}
protected:
	MHWRender::MRenderTarget* mTargets[2];
};

//------------------------------------------------------------------------
/*
	Custom render override class
*/
class viewDX11DeviceAccess : public MHWRender::MRenderOverride
{
public:
	enum {
		// User op draw to target 1
		kUserOpNumber,
		// Draw HUD on top
		kHUDBlit,
		// Present
		kPresentOp,
		kNumberOfOps
	};

	viewDX11DeviceAccess( const MString & name )
		: MRenderOverride( name )
		, mUIName("DX11 Render Override Sample")
	{
		for (unsigned int i=0; i<kNumberOfOps; i++)
			mRenderOperations[i] = NULL;
		mCurrentOperation = -1;

		// Init target information for the override
		mTargetOverrideNames[0] = MString("__viewDX11DeviceAccessCustomColorTarget__");
		mTargetOverrideNames[1] = MString("__viewDX11DeviceAccessCustomDepthTarget__");
		MHWRender::MRasterFormat colorFormat = MHWRender::kR8G8B8A8_UNORM;
			//MHWRender::kR32G32B32_FLOAT; -- this currently causes issues with DX11
		MHWRender::MRasterFormat depthFormat = MHWRender::kD24S8;
		unsigned int sampleCount = 1; // no multi-sampling
		mTargetDescriptions[0] =
			new MHWRender::MRenderTargetDescription(mTargetOverrideNames[0], 256, 256, sampleCount, colorFormat, 0, false);
		mTargetDescriptions[1] =
			new MHWRender::MRenderTargetDescription(mTargetOverrideNames[1], 256, 256, sampleCount, depthFormat, 0, false);

		mTargets[0] = NULL;
		mTargets[1] = NULL;

		// For debugging
		mDebugOverride = false;

		mPanelName.clear();
	}
	virtual ~viewDX11DeviceAccess()
	{
		// Cleanup targets
		if (mTargetDescriptions[0])
		{
			delete mTargetDescriptions[0];
			mTargetDescriptions[0] = NULL;
		}
		if (mTargetDescriptions[1])
		{
			delete mTargetDescriptions[1];
			mTargetDescriptions[1] = NULL;
		}

	    MHWRender::MRenderer* theRenderer = MHWRender::MRenderer::theRenderer();
	    if (theRenderer)
	    {
			const MHWRender::MRenderTargetManager* targetManager = theRenderer->getRenderTargetManager();
			if (targetManager)
			{
				if (mTargets[0])
				{
					targetManager->releaseRenderTarget(mTargets[0]);
				}
				if (mTargets[1])
				{
					targetManager->releaseRenderTarget(mTargets[1]);
				}
			}
		}
		mTargets[0] = NULL;
		mTargets[1] = NULL;

		cleanup();

		// Delete all the operations
		for (unsigned int i=0; i<kNumberOfOps; i++)
		{
			if (mRenderOperations[i])
			{
				delete mRenderOperations[i];
				mRenderOperations[i] = NULL;
			}
		}
	}

	virtual MHWRender::DrawAPI supportedDrawAPIs() const
	{
		return MHWRender::kDirectX11;
	}

	virtual MString uiName() const
	{
		return mUIName;
	}

	// Operation iterator methods
	virtual bool startOperationIterator()
	{
		mCurrentOperation = 0;
		return true;
	}
	virtual MHWRender::MRenderOperation * renderOperation()
	{
		if (mCurrentOperation >= 0 && mCurrentOperation < kNumberOfOps)
		{
			while(!mRenderOperations[mCurrentOperation])
			{
				mCurrentOperation++;
				if (mCurrentOperation >= kNumberOfOps)
				{
					return NULL;
				}
			}

			if (mRenderOperations[mCurrentOperation])
			{
				if (mDebugOverride)
				{
					printf("\t%s : Queue render operation[%d] = (%s)\n",
						mName.asChar(),
						mCurrentOperation,
						mRenderOperations[mCurrentOperation]->name().asChar());
				}
				return mRenderOperations[mCurrentOperation];
			}
		}
		return NULL;
	}
	virtual bool nextRenderOperation()
	{
		mCurrentOperation++;
		if (mCurrentOperation < kNumberOfOps)
		{
			return true;
		}
		return false;
	}

	// Create the required render targets
	bool updateRenderTargets()
	{
		if (mDebugOverride)
		{
			printf("\t%s : Set output render target overrides: color=%s, depth=%s\n",
				mName.asChar(),
				mTargetDescriptions[0]->name().asChar(), mTargetDescriptions[1]->name().asChar());
		}

		MHWRender::MRenderer *theRenderer = MHWRender::MRenderer::theRenderer();

        unsigned int targetWidth = 0;
        unsigned int targetHeight = 0;
        if( theRenderer )
		{
            theRenderer->outputTargetSize( targetWidth, targetHeight );
        }

		if (mTargetDescriptions[0]->width() != targetWidth ||
			mTargetDescriptions[1]->height() != targetHeight)
		{
			// A resize occured
		}

		mTargetDescriptions[0]->setWidth( targetWidth );
		mTargetDescriptions[0]->setHeight( targetHeight );
		mTargetDescriptions[1]->setWidth( targetWidth );
		mTargetDescriptions[1]->setHeight( targetHeight );

		const MHWRender::MRenderTargetManager *targetManager = theRenderer ? theRenderer->getRenderTargetManager() : NULL;
		if (targetManager)
		{
			if (!mTargets[0])
			{
				mTargets[0] =  targetManager->acquireRenderTarget( *( mTargetDescriptions[0]) );
			}
			else
			{
				mTargets[0]->updateDescription( *( mTargetDescriptions[0]) );
			}
			if (!mTargets[1])
			{
				mTargets[1] =  targetManager->acquireRenderTarget( *( mTargetDescriptions[1]) );
			}
			else
			{
				mTargets[1]->updateDescription( *( mTargetDescriptions[1]) );
			}
		}

		// Update the render targets on the individual operations
		//
		viewRenderUserOperation *userOp = (viewRenderUserOperation *) mRenderOperations[kUserOpNumber];
		viewRenderPresentTarget *presentOp = (viewRenderPresentTarget *) mRenderOperations[kPresentOp];
		viewRenderHUDOperation *hudOp = (viewRenderHUDOperation *) mRenderOperations[kHUDBlit];

		if (mTargets[0])
		{
			if (userOp)
				userOp->setRenderTarget(0, mTargets[0]);
			if (presentOp)
				presentOp->setRenderTarget(0, mTargets[0]);
			if (hudOp)
				hudOp->setRenderTarget(0, mTargets[0]);
		}
		if (mTargets[1])
		{
			if (userOp)
				userOp->setRenderTarget(1, mTargets[1]);
			if (presentOp)
				presentOp->setRenderTarget(1, mTargets[1]);
			if (hudOp)
				hudOp->setRenderTarget(1, mTargets[1]);
		}

		return (mTargets[0] && mTargets[1]);
	}

	// Setup is just a regular render with no overrides
	virtual MStatus setup( const MString & destination )
	{
		if (mDebugOverride)
		{
			printf("%s : Perform setup with panel [%s]\n",
				mName.asChar(), destination.asChar() );
		}

		// Set the active panel if any
		mPanelName.set( destination.asChar() );

		if (mRenderOperations[kUserOpNumber] == NULL)
		{
			mRenderOperationNames[kUserOpNumber] = "__MyCustomSceneRender";
			viewRenderUserOperation *userOp = new viewRenderUserOperation( mRenderOperationNames[kUserOpNumber] );
			mRenderOperations[kUserOpNumber] = userOp;

			mRenderOperations[kHUDBlit] = new viewRenderHUDOperation();
			mRenderOperationNames[kHUDBlit] = (mRenderOperations[kHUDBlit])->name();

			mRenderOperationNames[kPresentOp] = "__MyPresentTarget";
			mRenderOperations[kPresentOp] = new viewRenderPresentTarget( mRenderOperationNames[kPresentOp] );
			mRenderOperationNames[kPresentOp] = (mRenderOperations[kPresentOp])->name();
		}

		bool gotTargets = updateRenderTargets();

		if (mRenderOperations[kUserOpNumber])
			((viewRenderUserOperation *)mRenderOperations[kUserOpNumber])->setPanelName( mPanelName );

		mCurrentOperation = -1;

		return (gotTargets ? MStatus::kSuccess : MStatus::kFailure );
	}
	virtual MStatus cleanup()
	{
		if (mDebugOverride)
		{
			printf("%s : Perform cleanup. panelname=%s\n", mName.asChar(), mPanelName.asChar());
		}

		// Reset the active view
		mPanelName.clear();
		// Reset current operation
		mCurrentOperation = -1;

		return MStatus::kSuccess;
	}

	// Unique name to identify this type of override. Identifier
	// is used when setting an override for a viewport panel
	// or for batch rendering
	//
	static MString gsVROName;

	const MString & panelName() const { return mPanelName; }

protected:

	// Operation lists
	MHWRender::MRenderOperation * mRenderOperations[kNumberOfOps];
	MString mRenderOperationNames[kNumberOfOps];
	int mCurrentOperation;

	// Shared render target list
	MString mTargetOverrideNames[2];
	MHWRender::MRenderTargetDescription* mTargetDescriptions[2];
	MHWRender::MRenderTarget* mTargets[2];

	// Override is for this panel
	MString mPanelName;

	// UI name
	MString mUIName;

	bool mDebugOverride;
};


static viewDX11DeviceAccess *viewDX11DeviceAccessInstance = NULL;

///////////////////////////////////////////////////
//
// Plug-in functions
//
///////////////////////////////////////////////////

MStatus initializePlugin( MObject obj )
{
	MStatus   status;
	MFnPlugin plugin( obj, PLUGIN_COMPANY, "1.0", "Any");

	// Create and register an override.
	if (!viewDX11DeviceAccessInstance)
	{
		MHWRender::MRenderer* renderer = MHWRender::MRenderer::theRenderer();
		if (renderer)
		{
			viewDX11DeviceAccessInstance = new viewDX11DeviceAccess( "my_viewDX11DeviceAccess" );
			status = renderer->registerOverride(viewDX11DeviceAccessInstance);
		}
	}

	if (!status)
	{
		status.perror("registerOverride");
	}

	return status;
}

MStatus uninitializePlugin( MObject obj)
{
	MStatus   status;
	MFnPlugin plugin( obj );

	// Degister and delete override
	if (viewDX11DeviceAccessInstance)
	{
		MHWRender::MRenderer* renderer = MHWRender::MRenderer::theRenderer();
		if (renderer)
		{
			status = renderer->deregisterOverride(viewDX11DeviceAccessInstance);
		}

		delete viewDX11DeviceAccessInstance;
		viewDX11DeviceAccessInstance = NULL;
	}

	if (!status)
	{
		status.perror("deregisterOverride");
	}

	return status;
}

