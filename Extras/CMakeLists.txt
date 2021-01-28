SUBDIRS( InverseDynamics BulletRoboticsGUI BulletRobotics Serialize ConvexDecomposition HACD GIMPACTUtils )

IF (MSVC)
    SUBDIRS( obj2sdf )
ENDIF ()


#Maya Dynamica plugin is moved to http://dynamica.googlecode.com

#IF (USE_GLUT AND GLUT_FOUND)
#	SUBDIRS (glui)
#ENDIF ()
