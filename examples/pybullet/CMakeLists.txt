
INCLUDE_DIRECTORIES( 
		${BULLET_PHYSICS_SOURCE_DIR}/src
		${BULLET_PHYSICS_SOURCE_DIR}/examples
		${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs
		${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad
		${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/enet/include
		${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/clsocket/src
		${BULLET_PHYSICS_SOURCE_DIR}/Extras/VHACD/inc #[IGE]: add include
		${BULLET_PHYSICS_SOURCE_DIR}/Extras/VHACD/public #[IGE]: add include
		${PYTHON_INCLUDE_DIRS}
  )
IF(BUILD_PYBULLET_NUMPY)
	INCLUDE_DIRECTORIES(
		${PYTHON_NUMPY_INCLUDE_DIR}
	)
ENDIF()

ADD_DEFINITIONS(-DSTATIC_LINK_SPD_PLUGIN)

SET(pybullet3_SRCS
	pybullet.c
	)
	
SET(pybullet_SRCS
	pybullet.c
	#[IGE]: add source
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/tinyxml2/tinyxml2.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/plugins/stablePDPlugin/BulletConversion.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/plugins/stablePDPlugin/KinTree.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/plugins/stablePDPlugin/MathUtil.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/plugins/stablePDPlugin/RBDModel.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/plugins/stablePDPlugin/RBDUtil.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/plugins/stablePDPlugin/Shape.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/plugins/stablePDPlugin/SpAlg.cpp"
	# "${BULLET_PHYSICS_SOURCE_DIR}/src/btLinearMathAll.cpp"
	# "${BULLET_PHYSICS_SOURCE_DIR}/src/btBulletCollisionAll.cpp"
	# "${BULLET_PHYSICS_SOURCE_DIR}/src/btBulletDynamicsAll.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ExampleBrowser/InProcessExampleBrowser.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/TinyRenderer/geometry.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/TinyRenderer/model.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/TinyRenderer/tgaimage.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/TinyRenderer/our_gl.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/TinyRenderer/TinyRenderer.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/plugins/pdControlPlugin/pdControlPlugin.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/plugins/collisionFilterPlugin/collisionFilterPlugin.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/plugins/fileIOPlugin/fileIOPlugin.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/b3RobotSimulatorClientAPI_NoDirect.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/IKTrajectoryHelper.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/InProcessMemory.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsClient.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsServer.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/GraphicsClientExample.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/GraphicsServerExample.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/RemoteGUIHelper.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/RemoteGUIHelperTCP.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsServerExample.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsServerExampleBullet2.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/SharedMemoryInProcessPhysicsC_API.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsServerSharedMemory.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsDirect.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsDirectC_API.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsServerCommandProcessor.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsClientSharedMemory.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsClientSharedMemory_C_API.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsClientC_API.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/Win32SharedMemory.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PosixSharedMemory.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/plugins/tinyRendererPlugin/TinyRendererVisualShapeConverter.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/plugins/tinyRendererPlugin/tinyRendererPlugin.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsClientUDP.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsClientUDP_C_API.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsClientTCP.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsClientTCP_C_API.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/b3PluginManager.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Utils/b3ResourcePath.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Utils/RobotLoggingUtil.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Utils/ChromeTraceUtil.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Utils/b3Clock.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Utils/b3Quickprof.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/stb_image/stb_image.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/stb_image/stb_image_write.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/minizip/ioapi.c"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/minizip/unzip.c"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/minizip/zip.c"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/zlib/adler32.c"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/zlib/compress.c"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/zlib/crc32.c"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/zlib/deflate.c"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/zlib/gzclose.c"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/zlib/gzlib.c"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/zlib/gzread.c"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/zlib/gzwrite.c"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/zlib/infback.c"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/zlib/inffast.c"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/zlib/inflate.c"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/zlib/inftrees.c"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/zlib/trees.c"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/zlib/uncompr.c"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/zlib/zutil.c"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Importers/ImportColladaDemo/LoadMeshFromCollada.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Importers/ImportObjDemo/LoadMeshFromObj.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Importers/ImportObjDemo/Wavefront2GLInstanceGraphicsShape.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Importers/ImportMJCFDemo/BulletMJCFImporter.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Importers/ImportURDFDemo/BulletUrdfImporter.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Importers/ImportURDFDemo/MyMultiBodyCreator.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Importers/ImportURDFDemo/URDF2Bullet.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Importers/ImportURDFDemo/UrdfParser.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Importers/ImportURDFDemo/urdfStringSplit.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Importers/ImportMeshUtility/b3ImportMeshUtility.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/MultiThreading/b3PosixThreadSupport.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/MultiThreading/b3Win32ThreadSupport.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/MultiThreading/b3ThreadSupportInterface.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/enet/callbacks.c"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/enet/compress.c"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/enet/host.c"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/enet/list.c"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/enet/packet.c"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/enet/peer.c"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/enet/protocol.c"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ExampleBrowser/OpenGLGuiHelper.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ExampleBrowser/OpenGLExampleBrowser.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ExampleBrowser/CollisionShape2TriangleMesh.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ExampleBrowser/GL_ShapeDrawer.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/SimpleOpenGL2Renderer.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/GLInstancingRenderer.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/SimpleOpenGL3App.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/GLPrimitiveRenderer.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/TwFonts.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/GLRenderToTexture.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/LoadShader.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/OpenSans.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/SimpleCamera.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/fontstash.cpp"
	# "${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/SimpleOpenGL2App.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/opengl_fontstashcallbacks.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ExampleBrowser/GwenGUISupport/GraphingTexture.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ExampleBrowser/GwenGUISupport/GwenProfileWindow.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ExampleBrowser/GwenGUISupport/gwenUserInterface.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ExampleBrowser/GwenGUISupport/GwenParameterInterface.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ExampleBrowser/GwenGUISupport/GwenTextureWindow.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/Bullet3Common/b3AlignedAllocator.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/Bullet3Common/b3Logging.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/Bullet3Common/b3Vector3.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/clsocket/src/ActiveSocket.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/clsocket/src/PassiveSocket.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/clsocket/src/SimpleSocket.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/Serialize/BulletFileLoader/bChunk.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/Serialize/BulletFileLoader/bDNA.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/Serialize/BulletFileLoader/bFile.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/Serialize/BulletFileLoader/btBulletFile.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/Serialize/BulletWorldImporter/btMultiBodyWorldImporter.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/Serialize/BulletWorldImporter/btBulletWorldImporter.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/Serialize/BulletWorldImporter/btWorldImporter.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/InverseDynamics/CloneTreeCreator.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/InverseDynamics/IDRandomUtil.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/InverseDynamics/MultiBodyTreeDebugGraph.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/InverseDynamics/User2InternalIndex.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/InverseDynamics/CoilCreator.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/InverseDynamics/MultiBodyNameMap.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/InverseDynamics/RandomTreeCreator.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/InverseDynamics/btMultiBodyTreeCreator.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/InverseDynamics/DillCreator.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/InverseDynamics/MultiBodyTreeCreator.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/InverseDynamics/SimpleTreeCreator.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/InverseDynamics/invdyn_bullet_comparison.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btDefaultSoftBodySolver.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btSoftBodyHelpers.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btSoftRigidCollisionAlgorithm.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btSoftBody.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btSoftRigidDynamicsWorld.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btSoftBodyConcaveCollisionAlgorithm.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btSoftMultiBodyDynamicsWorld.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btSoftSoftCollisionAlgorithm.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btDeformableBackwardEulerObjective.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btDeformableBodySolver.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btDeformableContactProjection.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btDeformableContactConstraint.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btDeformableMultiBodyConstraintSolver.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btDeformableMultiBodyDynamicsWorld.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/poly34.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletInverseDynamics/IDMath.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletInverseDynamics/MultiBodyTree.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletInverseDynamics/details/MultiBodyTreeImpl.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletInverseDynamics/details/MultiBodyTreeInitCache.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/BussIK/Jacobian.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/BussIK/LinearR2.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/BussIK/LinearR3.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/BussIK/LinearR4.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/BussIK/MatrixRmn.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/BussIK/Misc.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/BussIK/Node.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/BussIK/Tree.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/BussIK/VectorRn.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Anim.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/DragAndDrop.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Hook.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/ToolTip.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/events.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/BaseRender.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Gwen.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Skin.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Utility.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/inputhandler.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/Base.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/Button.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/Canvas.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/CheckBox.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/ColorControls.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/ColorPicker.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/ComboBox.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/CrossSplitter.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/DockBase.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/DockedTabControl.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/Dragger.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/GroupBox.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/HSVColorPicker.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/HorizontalScrollBar.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/ImagePanel.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/HorizontalSlider.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/Label.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/LabelClickable.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/ListBox.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/MenuItem.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/Menu.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/MenuStrip.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/NumericUpDown.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/PanelListPanel.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/ProgressBar.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/Properties.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/RadioButton.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/RadioButtonController.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/ResizableControl.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/Resizer.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/RichLabel.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/ScrollBar.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/ScrollBarBar.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/ScrollBarButton.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/ScrollControl.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/Slider.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/SplitterBar.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/TabButton.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/TabControl.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/TabStrip.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/Text.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/TextBox.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/TextBoxNumeric.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/TreeControl.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/TreeNode.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/VerticalScrollBar.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/VerticalSlider.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/WindowControl.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/Dialog/FileOpen.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/Dialog/FileSave.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Controls/Dialog/Query.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Platforms/Null.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Platforms/Windows.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Gwen/Renderers/OpenGL_DebugFont.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/VHACD/test/src/main_vhacd.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/VHACD/src/VHACD.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/VHACD/src/vhacdICHull.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/VHACD/src/vhacdManifoldMesh.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/VHACD/src/vhacdMesh.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/extras/VHACD/src/vhacdVolume.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/plugins/eglPlugin/eglRendererVisualShapeConverter.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/plugins/eglPlugin/eglRendererPlugin.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Importers/ImportColladaDemo/LoadMeshFromCollada.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Importers/ImportObjDemo/LoadMeshFromObj.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Importers/ImportMeshUtility/b3ImportMeshUtility.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Importers/ImportObjDemo/Wavefront2GLInstanceGraphicsShape.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/TinyRenderer/geometry.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/TinyRenderer/model.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/TinyRenderer/tgaimage.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/TinyRenderer/our_gl.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/TinyRenderer/TinyRenderer.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/stb_image/stb_image.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/stb_image/stb_image_write.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/tinyxml2/tinyxml2.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/SimpleCamera.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Utils/b3Clock.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/Utils/b3ResourcePath.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btShapeHull.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btConvexHullShape.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btBoxShape.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btSphereShape.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btPolyhedralConvexShape.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btConvexShape.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btCollisionShape.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btConvexPolyhedron.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btConvexInternalShape.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/Bullet3Common/b3Logging.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btAlignedAllocator.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btConvexHull.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btConvexHullComputer.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btGeometryUtil.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btQuickprof.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btThreads.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/Bullet3Common/b3AlignedAllocator.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad/gl.c"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/GLInstancingRenderer.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/GLRenderToTexture.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/LoadShader.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad/egl.c"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/EGLOpenGLWindow.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/Win32Window.cpp"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/OpenGLWindow/Win32OpenGLWindow.cpp"

	#[/IGE]
)

IF(BUILD_CLSOCKET)
	ADD_DEFINITIONS(-DBT_ENABLE_CLSOCKET)
ENDIF()

IF(NOT WIN32 AND NOT APPLE)
	ADD_DEFINITIONS(-DBT_USE_EGL)
ENDIF()

ADD_DEFINITIONS(-DPYBULLET_USE_NUMPY -DBT_NO_PROFILE -DGWEN_COMPILE_STATIC -DBT_ENABLE_ENET -DEGL_ADD_PYTHON_INIT -DB3_ENABLE_FILEIO_PLUGIN -DB3_USE_ZIPFILE_FILEIO -DBT_THREADSAFE=1 -DSTATIC_LINK_SPD_PLUGIN -DBT_ENABLE_VHACD )

ADD_DEFINITIONS("-DBT_USE_OPENMP=1")
IF (MSVC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /openmp")
ELSE (MSVC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
ENDIF (MSVC)

IF(WIN32)
	LINK_LIBRARIES(
		${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY}
	)
	IF(BUILD_ENET)
		ADD_DEFINITIONS(-DWIN32 -DBT_ENABLE_ENET)
	ENDIF()
	IF(BUILD_CLSOCKET)
		ADD_DEFINITIONS(-DWIN32)
	ENDIF()

ELSE(WIN32)
	IF(BUILD_ENET)
		ADD_DEFINITIONS(-DHAS_SOCKLEN_T -DBT_ENABLE_ENET)
	ENDIF()

	IF(BUILD_CLSOCKET)	
		ADD_DEFINITIONS(${OSDEF})
	ENDIF()
ENDIF(WIN32)



ADD_LIBRARY(pybullet STATIC ${pybullet_SRCS}) #[IGE]: force static

#[IGE]: rem below
# SET_TARGET_PROPERTIES(pybullet PROPERTIES PREFIX "")
# SET_TARGET_PROPERTIES(pybullet PROPERTIES POSTFIX "")

# SET_TARGET_PROPERTIES(pybullet PROPERTIES VERSION ${BULLET_VERSION})
# SET_TARGET_PROPERTIES(pybullet PROPERTIES SOVERSION ${BULLET_VERSION})
# SET_TARGET_PROPERTIES(pybullet PROPERTIES DEBUG_POSTFIX "_d")


# IF(WIN32)
	# IF(BUILD_ENET OR BUILD_CLSOCKET)
		# TARGET_LINK_LIBRARIES(pybullet ws2_32 )
	# ENDIF()

	# SET_TARGET_PROPERTIES(pybullet PROPERTIES SUFFIX ".pyd" )
# ENDIF(WIN32)

# IF (APPLE)
  # SET_TARGET_PROPERTIES(pybullet PROPERTIES SUFFIX ".so" )
# ENDIF()



# TARGET_LINK_LIBRARIES(pybullet BulletRoboticsGUI BulletExampleBrowserLib BulletRobotics BulletFileLoader BulletWorldImporter BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamicsUtils BulletInverseDynamics LinearMath OpenGLWindow gwen BussIK Bullet3Common)

# IF (WIN32)
  # TARGET_LINK_LIBRARIES(pybullet ${PYTHON_LIBRARIES})
# ELSEIF (APPLE)
  # SET_TARGET_PROPERTIES(pybullet PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
# ENDIF ()
# # else Linux: dont link

# IF(WIN32)
  # SET(PYTHON_SITE_PACKAGES Lib/site-packages CACHE PATH "Python install path")
# ELSE()
  # SET(PYTHON_SITE_PACKAGES lib/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/site-packages CACHE PATH "Python install path")
# ENDIF()

# INSTALL(TARGETS pybullet DESTINATION ${PYTHON_SITE_PACKAGES})
#[/IGE] Done

