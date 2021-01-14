#*****************************************************************************
# Copyright (c) 2016-2021, The Regents of the University of California (Regents).
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# The views and conclusions contained in the software and documentation are those
# of the authors and should not be interpreted as representing official policies,
# either expressed or implied, of the FreeBSD Project.
#
# REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
# THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS
# PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
# UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
#
#***************************************************************************

# Written by: Stevan Gavrilovic, Frank McKenna

QT += core gui charts concurrent network sql qml webenginewidgets webengine webchannel 3dcore 3drender 3dextras charts xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Information about the app
TARGET = R2D
TEMPLATE = app
VERSION=1.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# C++17 support
CONFIG += c++17

win32:DEFINES +=  CURL_STATICLIB
# win32::include($$PWD/ConanHelper.pri)
win32::LIBS+=Advapi32.lib

# Full optimization on release
QMAKE_CXXFLAGS_RELEASE += -O3

# Specify the path to the Simcenter common directory
PATH_TO_COMMON=../../SimCenterCommon

# Application Icons
win32 {
    RC_ICONS = icons/NHERI-R2D-Icon.ico
} else {
    mac {
    ICON = icons/NHERI-R2D-Icon.icns
    }
}

# GIS library
ARCGIS_RUNTIME_VERSION = 100.9
include($$PWD/arcgisruntime.pri)

# Simcenter dependencies
include($$PATH_TO_COMMON/Common/Common.pri)
include($$PATH_TO_COMMON/RandomVariables/RandomVariables.pri)
include(R2DCommon.pri)


# R2D files
INCLUDEPATH += $$PWD/Utils \
               $$PWD/styles \
               $$PWD/UIWidgets \
               $$PWD/EVENTS/UI \
               $$PWD/TOOLS \


SOURCES +=  EVENTS/UI/EarthquakeRuptureForecast.cpp \
            EVENTS/UI/EarthquakeRuptureForecastWidget.cpp \
            EVENTS/UI/GMPE.cpp \
            EVENTS/UI/GMPEWidget.cpp \
            EVENTS/UI/GMWidget.cpp \
            EVENTS/UI/GmAppConfig.cpp \
            EVENTS/UI/GmAppConfigWidget.cpp \
            EVENTS/UI/GmCommon.cpp \
            EVENTS/UI/GridDivision.cpp \
            EVENTS/UI/HBoxFormLayout.cpp \
            EVENTS/UI/IntensityMeasure.cpp \
            EVENTS/UI/IntensityMeasureWidget.cpp \
            EVENTS/UI/Location.cpp \
            EVENTS/UI/PeerLoginDialog.cpp \
            EVENTS/UI/PeerNGAWest2Client.cpp \
            EVENTS/UI/PointSourceRupture.cpp \
            EVENTS/UI/PointSourceRuptureWidget.cpp \
            EVENTS/UI/RecordSelectionConfig.cpp \
            EVENTS/UI/RecordSelectionWidget.cpp \
            EVENTS/UI/RuptureLocation.cpp \
            EVENTS/UI/RuptureWidget.cpp \
            EVENTS/UI/Site.cpp \
            EVENTS/UI/SiteConfig.cpp \
            EVENTS/UI/SiteConfigWidget.cpp \
            EVENTS/UI/SiteGrid.cpp \
            EVENTS/UI/SiteGridWidget.cpp \
            EVENTS/UI/SiteWidget.cpp \
            EVENTS/UI/SpatialCorrelationWidget.cpp \
            RunWidget.cpp \
            TOOLS/AssetInputDelegate.cpp \
            TOOLS/BuildingDatabase.cpp \
            TOOLS/CSVReaderWriter.cpp \
            TOOLS/CustomListWidget.cpp \
            TOOLS/NGAW2Converter.cpp \
            TOOLS/PelicunPostProcessor.cpp \
            TOOLS/REmpiricalProbabilityDistribution.cpp \
            TOOLS/TablePrinter.cpp \
            TOOLS/XMLAdaptor.cpp \
            TOOLS/shakeMapClient.cpp \
            UIWidgets/AnalysisWidget.cpp \
            UIWidgets/AssetsModelWidget.cpp \
            UIWidgets/AssetsWidget.cpp \
            UIWidgets/BuildingDMEQWidget.cpp \
            UIWidgets/BuildingDMWidget.cpp \
            UIWidgets/BuildingEDPEQWidget.cpp \
            UIWidgets/BuildingEDPWidget.cpp \
            UIWidgets/BuildingModelGeneratorWidget.cpp \
            UIWidgets/BuildingModelingWidget.cpp \
            UIWidgets/BuildingSimulationWidget.cpp \
            UIWidgets/CSVtoBIMModelingWidget.cpp \
            UIWidgets/ComponentInputWidget.cpp \
            UIWidgets/DLWidget.cpp \
            UIWidgets/DamageMeasureWidget.cpp \
            UIWidgets/DecisionVariableWidget.cpp \
            UIWidgets/EarthquakeInputWidget.cpp \
            UIWidgets/EngDemandParameterWidget.cpp \
            UIWidgets/GeneralInformationWidget.cpp \
            UIWidgets/GridNode.cpp \
            UIWidgets/GroundMotionStation.cpp \
            UIWidgets/GroundMotionTimeHistory.cpp \
            UIWidgets/HazardToAssetBuilding.cpp \
            UIWidgets/HazardToAssetWidget.cpp \
            UIWidgets/HazardsWidget.cpp \
            UIWidgets/InputWidgetOpenSeesPyAnalysis.cpp \
            UIWidgets/MDOF_LU.cpp \
            UIWidgets/MapViewSubWidget.cpp \
            UIWidgets/ModelWidget.cpp \
            UIWidgets/MultiComponentR2D.cpp \
            UIWidgets/NearestNeighbourMapping.cpp \
            UIWidgets/NodeHandle.cpp \
            UIWidgets/NoneWidget.cpp \
            UIWidgets/OpenSeesPyBuildingModel.cpp \
            UIWidgets/PelicunDLWidget.cpp \
            UIWidgets/PopUpWidget.cpp \
            UIWidgets/RectangleGrid.cpp \
            UIWidgets/ResultsMapViewWidget.cpp \
            UIWidgets/ResultsWidget.cpp \
            UIWidgets/SecondaryComponentSelection.cpp \
            UIWidgets/ShakeMapWidget.cpp \
            UIWidgets/SimCenterEventRegional.cpp \
            UIWidgets/SimCenterMapGraphicsView.cpp \
            UIWidgets/StructuralModelingWidget.cpp \
            UIWidgets/TreeItem.cpp \
            UIWidgets/LayerTreeItem.cpp \
            UIWidgets/TreeModel.cpp \
            UIWidgets/ListTreeModel.cpp \
            UIWidgets/LayerTreeView.cpp \
            UIWidgets/TreeViewStyle.cpp \
            UIWidgets/UQWidget.cpp \
            UIWidgets/UserDefinedEDPR.cpp \
            UIWidgets/UserInputGMWidget.cpp \
            UIWidgets/VisualizationWidget.cpp \
            WorkflowAppR2D.cpp \
            main.cpp \


HEADERS +=  EVENTS/UI/EarthquakeRuptureForecast.h \
            EVENTS/UI/EarthquakeRuptureForecastWidget.h \
            EVENTS/UI/GMPE.h \
            EVENTS/UI/GMPEWidget.h \
            EVENTS/UI/GMWidget.h \
            EVENTS/UI/GmAppConfig.h \
            EVENTS/UI/GmAppConfigWidget.h \
            EVENTS/UI/GmCommon.h \
            EVENTS/UI/GridDivision.h \
            EVENTS/UI/HBoxFormLayout.h \
            EVENTS/UI/IntensityMeasure.h \
            EVENTS/UI/IntensityMeasureWidget.h \
            EVENTS/UI/JsonSerializable.h \
            EVENTS/UI/Location.h \
            EVENTS/UI/PeerLoginDialog.h \
            EVENTS/UI/PeerNGAWest2Client.h \
            EVENTS/UI/PointSourceRupture.h \
            EVENTS/UI/PointSourceRuptureWidget.h \
            EVENTS/UI/RecordSelectionConfig.h \
            EVENTS/UI/RecordSelectionWidget.h \
            EVENTS/UI/RuptureLocation.h \
            EVENTS/UI/RuptureWidget.h \
            EVENTS/UI/Site.h \
            EVENTS/UI/SiteConfig.h \
            EVENTS/UI/SiteConfigWidget.h \
            EVENTS/UI/SiteGrid.h \
            EVENTS/UI/SiteGridWidget.h \
            EVENTS/UI/SiteWidget.h \
            EVENTS/UI/SpatialCorrelationWidget.h \
            R2DUserPass.h \
            RunWidget.h \
            TOOLS/AssetInputDelegate.h \
            TOOLS/BuildingDatabase.h \
            TOOLS/CSVReaderWriter.h \
            TOOLS/CustomListWidget.h \
            TOOLS/NGAW2Converter.h \
            TOOLS/PelicunPostProcessor.h \
            TOOLS/REmpiricalProbabilityDistribution.h \
            TOOLS/TablePrinter.h \
            TOOLS/XMLAdaptor.h \
            TOOLS/shakeMapClient.h \
            UIWidgets/AnalysisWidget.h \
            UIWidgets/AssetsModelWidget.h \
            UIWidgets/AssetsWidget.h \
            UIWidgets/BuildingDMEQWidget.h \
            UIWidgets/BuildingDMWidget.h \
            UIWidgets/BuildingEDPEQWidget.h \
            UIWidgets/BuildingEDPWidget.h \
            UIWidgets/BuildingModelGeneratorWidget.h \
            UIWidgets/BuildingModelingWidget.h \
            UIWidgets/BuildingSimulationWidget.h \
            UIWidgets/CSVtoBIMModelingWidget.h \
            UIWidgets/ComponentInputWidget.h \
            UIWidgets/DLWidget.h \
            UIWidgets/DamageMeasureWidget.h \
            UIWidgets/DecisionVariableWidget.h \
            UIWidgets/EarthquakeInputWidget.h \
            UIWidgets/EngDemandParameterWidget.h \
            UIWidgets/GeneralInformationWidget.h \
            UIWidgets/GridNode.h \
            UIWidgets/GroundMotionStation.h \
            UIWidgets/GroundMotionTimeHistory.h \
            UIWidgets/HazardToAssetBuilding.h \
            UIWidgets/HazardToAssetWidget.h \
            UIWidgets/HazardsWidget.h \
            UIWidgets/InputWidgetOpenSeesPyAnalysis.h \
            UIWidgets/MDOF_LU.h \
            UIWidgets/MapViewSubWidget.h \
            UIWidgets/ModelWidget.h \
            UIWidgets/MultiComponentR2D.h \             \
            UIWidgets/NearestNeighbourMapping.h \
            UIWidgets/NodeHandle.h \
            UIWidgets/NoneWidget.h \
            UIWidgets/OpenSeesPyBuildingModel.h \
            UIWidgets/PelicunDLWidget.h \
            UIWidgets/PopUpWidget.h \
            UIWidgets/RectangleGrid.h \
            UIWidgets/ResultsMapViewWidget.h \
            UIWidgets/ResultsWidget.h \
            UIWidgets/SecondaryComponentSelection.h \
            UIWidgets/ShakeMapWidget.h \
            UIWidgets/SimCenterEventRegional.h \
            UIWidgets/SimCenterMapGraphicsView.h \
            UIWidgets/StructuralModelingWidget.h \
            UIWidgets/TreeItem.h \
            UIWidgets/LayerTreeItem.h \
            UIWidgets/TreeModel.h \
            UIWidgets/ListTreeModel.h \
            UIWidgets/LayerTreeView.h \
            UIWidgets/TreeViewStyle.h \
            UIWidgets/UQWidget.h \
            UIWidgets/UserDefinedEDPR.h \
            UIWidgets/UserInputGMWidget.h \
            UIWidgets/VisualizationWidget.h \
            WorkflowAppR2D.h\


RESOURCES += \
    images.qrc \
    $$PWD/styles.qrc


DISTFILES += \
    resources/docs/textAboutR2DT.html

# External libraries
macos:LIBS += /usr/lib/libcurl.dylib -llapack -lblas
linux:LIBS += /usr/lib/x86_64-linux-gnu/libcurl.so

# Copies over the examples folder into the build directory
win32 {
PATH_TO_BINARY=$$DESTDIR/Examples
} else {
    mac {
    PATH_TO_BINARY=$$OUT_PWD/R2D.app/Contents/MacOS
    }
}

copydata.commands = $(COPY_DIR) \"$$shell_path($$PWD/Examples)\" \"$$shell_path($$PATH_TO_BINARY)\"
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

