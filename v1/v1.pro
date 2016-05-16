#-------------------------------------------------
#
# Project created by QtCreator 2016-02-25T19:48:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = v1
TEMPLATE = app

INCLUDEPATH += $$PWD/inc \
"C:/root_v5.34.34/include"

LIBS += -L"$$PWD/lib/Win32/Release/" -lCAENComm -lCAENDigitizer \
-L"C:/root_v5.34.34/lib"  \
"C:/root_v5.34.34/lib/complexDict.lib" \
"C:/root_v5.34.34/lib/dequeDict.lib" \
"C:/root_v5.34.34/lib/freetype.lib" \
"C:/root_v5.34.34/lib/libAfterImage.lib" \
"C:/root_v5.34.34/lib/libASImage.lib" \
"C:/root_v5.34.34/lib/libASImageGui.lib" \
"C:/root_v5.34.34/lib/libCint.lib" \
"C:/root_v5.34.34/lib/libCintex.lib" \
"C:/root_v5.34.34/lib/libCore.lib" \
"C:/root_v5.34.34/lib/libEG.lib" \
"C:/root_v5.34.34/lib/libEGPythia8.lib" \
"C:/root_v5.34.34/lib/libEve.lib" \
"C:/root_v5.34.34/lib/libFitPanel.lib" \
"C:/root_v5.34.34/lib/libFoam.lib" \
"C:/root_v5.34.34/lib/libFTGL.lib" \
"C:/root_v5.34.34/lib/libFumili.lib" \
"C:/root_v5.34.34/lib/libGdml.lib" \
"C:/root_v5.34.34/lib/libGed.lib" \
"C:/root_v5.34.34/lib/libGenetic.lib" \
"C:/root_v5.34.34/lib/libGenVector.lib" \
"C:/root_v5.34.34/lib/libGeom.lib" \
"C:/root_v5.34.34/lib/libGeomBuilder.lib" \
"C:/root_v5.34.34/lib/libGeomPainter.lib" \
"C:/root_v5.34.34/lib/libGLEW.lib" \
"C:/root_v5.34.34/lib/libGpad.lib" \
"C:/root_v5.34.34/lib/libGraf.lib" \
"C:/root_v5.34.34/lib/libGraf3d.lib" \
"C:/root_v5.34.34/lib/libGui.lib" \
"C:/root_v5.34.34/lib/libGuiBld.lib" \
"C:/root_v5.34.34/lib/libGuiHtml.lib" \
"C:/root_v5.34.34/lib/libGviz3d.lib" \
"C:/root_v5.34.34/lib/libHist.lib" \
"C:/root_v5.34.34/lib/libHistPainter.lib" \
"C:/root_v5.34.34/lib/libHtml.lib" \
"C:/root_v5.34.34/lib/libMathCore.lib" \
"C:/root_v5.34.34/lib/libMathMore.lib" \
"C:/root_v5.34.34/lib/libMatrix.lib" \
"C:/root_v5.34.34/lib/libMinuit.lib" \
"C:/root_v5.34.34/lib/libMinuit2.lib" \
"C:/root_v5.34.34/lib/libMLP.lib" \
"C:/root_v5.34.34/lib/libNet.lib" \
"C:/root_v5.34.34/lib/libPhysics.lib" \
"C:/root_v5.34.34/lib/libPostscript.lib" \
"C:/root_v5.34.34/lib/libProof.lib" \
"C:/root_v5.34.34/lib/libProofDraw.lib" \
"C:/root_v5.34.34/lib/libProofPlayer.lib" \
"C:/root_v5.34.34/lib/libPyROOT.lib" \
"C:/root_v5.34.34/lib/libQuadp.lib" \
"C:/root_v5.34.34/lib/libRecorder.lib" \
"C:/root_v5.34.34/lib/libReflex.lib" \
"C:/root_v5.34.34/lib/libReflexDict.lib" \
"C:/root_v5.34.34/lib/libRGL.lib" \
"C:/root_v5.34.34/lib/libRHTTP.lib" \
"C:/root_v5.34.34/lib/libRint.lib" \
"C:/root_v5.34.34/lib/libRIO.lib" \
"C:/root_v5.34.34/lib/libRODBC.lib" \
"C:/root_v5.34.34/lib/libRooFit.lib" \
"C:/root_v5.34.34/lib/libRooFitCore.lib" \
"C:/root_v5.34.34/lib/libRooStats.lib" \
"C:/root_v5.34.34/lib/libRootAuth.lib" \
"C:/root_v5.34.34/lib/libSessionViewer.lib" \
"C:/root_v5.34.34/lib/libSmatrix.lib" \
"C:/root_v5.34.34/lib/libSpectrum.lib" \
"C:/root_v5.34.34/lib/libSpectrumPainter.lib" \
"C:/root_v5.34.34/lib/libSPlot.lib" \
"C:/root_v5.34.34/lib/libSQLIO.lib" \
"C:/root_v5.34.34/lib/libTable.lib" \
"C:/root_v5.34.34/lib/libThread.lib" \
"C:/root_v5.34.34/lib/libTMVA.lib" \
"C:/root_v5.34.34/lib/libTree.lib" \
"C:/root_v5.34.34/lib/libTreePlayer.lib" \
"C:/root_v5.34.34/lib/libTreeViewer.lib" \
"C:/root_v5.34.34/lib/libUnuran.lib" \
"C:/root_v5.34.34/lib/libVMC.lib" \
"C:/root_v5.34.34/lib/libWin32gdk.lib" \
"C:/root_v5.34.34/lib/libXMLIO.lib" \
"C:/root_v5.34.34/lib/listDict.lib" \
"C:/root_v5.34.34/lib/map2Dict.lib" \
"C:/root_v5.34.34/lib/mapDict.lib" \
"C:/root_v5.34.34/lib/mathtext.lib" \
"C:/root_v5.34.34/lib/multimap2Dict.lib" \
"C:/root_v5.34.34/lib/multimapDict.lib" \
"C:/root_v5.34.34/lib/multisetDict.lib" \
"C:/root_v5.34.34/lib/setDict.lib" \
"C:/root_v5.34.34/lib/vectorDict.lib"


QMAKE_CXXFLAGS += -fpermissive

SOURCES += main.cpp\
        mainwindow.cpp \
    src/fft.cpp \
    src/keyb.cpp \
    src/WaveDump.cpp \
    src/WDconfig.cpp \
    src/WDplot.cpp \
    src/X742CorrectionRoutines.cpp \
    src/qcustomplot.cpp \
    myworker.cpp


HEADERS  += mainwindow.h \
    inc/CAENComm.h \
    inc/CAENDigitizer.h \
    inc/CAENDigitizerType.h \
    inc/fft.h \
    inc/keyb.h \
    inc/WaveDump.h \
    inc/WDconfig.h \
    inc/WDplot.h \
    inc/X742CorrectionRoutines.h \
    inc/qcustomplot.h \
    myworker.h



FORMS    += mainwindow.ui



