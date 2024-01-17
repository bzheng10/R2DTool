#ifndef GMWIDGET_H
#define GMWIDGET_H
/* *****************************************************************************
Copyright (c) 2016-2021, The Regents of the University of California (Regents).
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS
PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*************************************************************************** */

// Written by: Stevan Gavrilovic, Frank McKenna

#include "SimCenterAppWidget.h"
#include "GroundMotionStation.h"
#include "PeerNgaWest2Client.h"
#include "EventGMDirWidget.h"

#include <QProcess>
#include <QJsonObject>

class EventGMDirWidget;
class GMPE;
class GMPEWidget;
class GmAppConfig;
class RectangleGrid;
class IntensityMeasure;
class IntensityMeasureWidget;
class MapViewWindow;
class MapViewSubWidget;
class RecordSelectionConfig;
class RecordSelectionWidget;
class RuptureWidget;
class SiteConfig;
class SiteConfigWidget;
class SpatialCorrelationWidget;
class VisualizationWidget;
class Vs30; // vs30 info
class Vs30Widget; // vs30 setup widget

class QPushButton;
class QStatusBar;

class GMWidget : public SimCenterAppWidget
{
    Q_OBJECT

public:
    explicit GMWidget(VisualizationWidget* visWidget, QWidget *parent = nullptr);
    ~GMWidget();

    bool outputAppDataToJSON(QJsonObject &jsonObject);
    bool inputAppDataFromJSON(QJsonObject &jsonObj);
    bool outputToJSON(QJsonObject &jsonObject);
    bool inputFromJSON(QJsonObject &jsonObject);
    void saveAppSettings(void);
    void resetAppSettings(void);
    bool copyFiles(QString &destDir);
    bool getSimulationStatus(void);


    GmAppConfig *appConfig() const;

signals:
    void locationsChanged(void);
    void sceneViewChanged(void);
    void mapViewChanged(void);
    void outputDirectoryPathChanged(QString folderPath, QString gridFile);
    void useEventFileMotionDir(QString evtFile, QString gmDir);
    void configUpdated(void);
    void eventTypeChangedSignal(QString eventType);

public slots:
    void setAppConfig(void);
    void showGISWindow(void);
    void runHazardSimulation(void);

    // Handles the results when the user is finished
    void handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

    // Brings up the dialog and tells the user that the process has started
    void handleProcessStarted(void);

    // Displays the text output of the process in the dialog
    void handleProcessTextOutput(void);

    // Download records once selected
    int downloadRecords(void);

    // Download records once selected
    void downloadRecordBatch(void);

    // Process the outfile files once the hazard simulation is complete
    int parseDownloadedRecords(QString);

    // Send event file and motion dir
    void sendEventFileMotionDir(const QString &eventFile, const QString &motionDir);

    // Updating the simulaiton tag
    void updateSimulationTag(void);

private slots:

private:
    PeerNgaWest2Client peerClient;

    RuptureWidget* m_ruptureWidget;
    GMPE* m_gmpe;
    GMPEWidget* m_gmpeWidget;
    QProcess* process;
    IntensityMeasure* m_intensityMeasure;
    IntensityMeasureWidget* m_intensityMeasureWidget;
    SpatialCorrelationWidget* spatialCorrWidget;
    RecordSelectionConfig* m_selectionconfig;
    RecordSelectionWidget* m_selectionWidget;
    SiteConfig* m_siteConfig;
    SiteConfigWidget* m_siteConfigWidget;
    QPushButton* m_runButton;
    //QPushButton* m_settingButton;
    GmAppConfig* m_appConfig;
    Vs30* m_vs30;
    Vs30Widget* m_vs30Widget;
    EventGMDirWidget *m_eventGMDir;
    QString eventPath;
    QString motionFolder;

    VisualizationWidget* theVisualizationWidget;

    MapViewWindow* mapViewSubWidget;
    RectangleGrid* userGrid;

    void setupConnections();
    void initAppConfig();

    bool simulationComplete;
    QVector<GroundMotionStation> stationList;

    int processDownloadedRecords(QString& errorMessage);

    int numDownloaded;
    bool downloadComplete;
    QStringList recordsListToDownload;
    QJsonObject NGA2Results;
};

#endif // GMWIDGET_H
