
TEMPLATE = app
TARGET   = trounoir

HEADERS  = glm.h Vertex.h Viewer.h Particule.h
SOURCES  = glm.cpp Vertex.cpp Viewer.cpp Particule.cpp main.cpp


QT *= xml opengl widgets gui #openglwidgets

CONFIG += qt opengl warn_on thread rtti console embed_manifest_exe no_keywords

# Set path to include and lib files (see doc/compilation.html for details):
# Uncomment and tune these paths according to your configuration.

#INCLUDEPATH *= /home/barra/libQGLViewer-main
#LIBS *= -L/home/barra/libQGLViewer-main/QGLViewer

INCLUDEPATH *= /home/barra/libQGLViewer-main
LIBS *= -L/home/barra/libQGLViewer-main/QGLViewer

LIBS += -lGLU
# --------------------------------------------------------------------------------------

# The rest of this file sets these paths so that the examples
# can be compiled out of the box

ROOT_DIRECTORY = ../..

contains( _PRO_FILE_PWD_, ".*designerPlugin$" ) {
	ROOT_DIRECTORY = ..
}
contains( _PRO_FILE_PWD_, ".*/contribs/.+/.+" ) {
	ROOT_DIRECTORY = ../../../..
} else {
	contains( _PRO_FILE_PWD_, ".*/contribs/.+" ) {
		ROOT_DIRECTORY = ../../..
	}
}

INCLUDE_DIR = $${ROOT_DIRECTORY}
LIB_DIR = $${ROOT_DIRECTORY}/QGLViewer

# Include path, taking QGLViewer path prefix into account
INCLUDEPATH *= $${INCLUDE_DIR}
DEPENDPATH  *= $${INCLUDE_DIR}


unix {
	CONFIG -= debug debug_and_release
	CONFIG *= release

	isEmpty( QGLVIEWER_STATIC ) {
		# The absolute path where the library or framework was found
		LIB_DIR_ABSOLUTE_PATH = $$dirname(PWD)/QGLViewer

		macx|darwin-g++ {
			# Use install_name_tool to set the absolute path of the lib in the executable
			exists( $${LIB_DIR_ABSOLUTE_PATH}/QGLViewer.framework ) {
				!plugin:QMAKE_POST_LINK=install_name_tool -change QGLViewer.framework/Versions/2/QGLViewer $${LIB_DIR_ABSOLUTE_PATH}/QGLViewer.framework/Versions/2/QGLViewer $${TARGET}.app/Contents/MacOS/$${TARGET} #VERSION_MAJOR
				LIBS += -F$${LIB_DIR_ABSOLUTE_PATH} -framework QGLViewer
                        }
                        #else {
			#	!plugin:QMAKE_POST_LINK=install_name_tool -change libQGLViewer.2.dylib $${LIB_DIR_ABSOLUTE_PATH}/libQGLViewer.2.dylib $${TARGET}.app/Contents/MacOS/$${TARGET} #VERSION_MAJOR
			#	LIBS *= -L$${LIB_DIR} -lQGLViewer
			#}
		} else {
            isEmpty( NO_QT_VERSION_SUFFIX ) {
                equals (QT_MAJOR_VERSION, 4) {
                    LIB_NAME = QGLViewer-qt4
                }
                equals (QT_MAJOR_VERSION, 5) {
                    LIB_NAME = QGLViewer-qt5
                }
            }

			isEmpty(QMAKE_LFLAGS_RPATH) {
				!plugin:QMAKE_LFLAGS += -Wl,-rpath,$${LIB_DIR_ABSOLUTE_PATH}
			} else {
				!plugin:QMAKE_RPATHDIR *= $${LIB_DIR_ABSOLUTE_PATH}
			}
			LIBS *= -L$${LIB_DIR} -l$${LIB_NAME}
		}
	} else {
		LIBS *= $${LIB_DIR}/libQGLViewer.a
	}

	# Intermediate files are created in hidden folders
	MOC_DIR = .moc
	OBJECTS_DIR = .obj
}

macx|darwin-g++ {
    # Or whatever exists in /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/
    QMAKE_MAC_SDK = macosx12.3
}

win32 {
	# Seems to be needed for Visual Studio with Intel compiler
	DEFINES *= WIN32

	# Use native OpenGL drivers with Qt5.5
	# No longer implicit since the ANGLE driver is now an alternative
	LIBS += -lopengl32 -lglu32

	isEmpty( QGLVIEWER_STATIC ) {
		CONFIG(debug, debug|release) {
			LIBS *= -L$${LIB_DIR} -lQGLViewerd2
		} else {
			LIBS *= -L$${LIB_DIR} -lQGLViewer2
		}
	} else {
		DEFINES *= QGLVIEWER_STATIC
		CONFIG(debug, debug|release) {
			LIBS *= $${LIB_DIR}/libQGLViewerd2.a
		} else {
			LIBS *= $${LIB_DIR}/libQGLViewer2.a
		}
	}
}

