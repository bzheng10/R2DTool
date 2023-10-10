#ifndef PELICUN3POSTPROCESSORTSPN_H
#define PELICUN3POSTPROCESSORTSPN_H
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

// Written by: Stevan Gavrilovic

#include "ComponentDatabase.h"

#include "SimCenterMapcanvasWidget.h"

#include <QString>
#include <QMainWindow>

#include <memory>
#include <set>

class REmpiricalProbabilityDistribution;
class VisualizationWidget;

class QDockWidget;
class QTableWidget;
class QGridLayout;
class QLabel;
class QComboBox;
class QGraphicsView;
class QVBoxLayout;

namespace QtCharts
{
class QChartView;
class QBarSet;
class QChart;
}

class Pelicun3PostProcessorTspn : public QMainWindow
{
    Q_OBJECT

public:

    Pelicun3PostProcessorTspn(QWidget *parent, VisualizationWidget* visWidget);

    void importResults(const QString& pathToResults);

    int printToPDF(const QString& outputPath);

    // Function to convert a QString and QVariant to double
    // Throws an error exception if conversion fails
    template <typename T>
    auto objectToDouble(T obj)
    {
        // Assume a zero value if the string is empty or null
        if(obj.isNull() || obj.isEmpty())
            return 0.0;

        bool OK;
        auto val = obj.toDouble(&OK);

        if(!OK)
            throw QString("Could not convert the object to a double");

        return val;
    }


    template <typename T>
    auto objectToInt(T obj)
    {
        // Assume a zero value if the string is empty or null
        if(obj.isNull() || obj.isEmpty())
            return 0;

        bool OK;
        auto val = obj.toInt(&OK);

        if(!OK)
            throw QString("Could not convert the object to an integer");

        return val;
    }

    void processResultsSubset(const std::set<int>& selectedComponentIDs);

    void setCurrentlyViewable(bool status);

    void clear(void);

    void setIsVisible(const bool value);

private slots:

    int assemblePDF(QImage screenShot);

    void sortTable(int index);

    void restoreUI(void);

protected:

    void showEvent(QShowEvent *e);

private:

    int processDVResults(const QVector<QStringList>& DVResults);

    QVector<QStringList> DMdata;
    QVector<QStringList> DVdata;
    QVector<QStringList> EDPdata;
    QVector<QStringList> IMdata;

    QString outputFilePath;

    QMenu* viewMenu;

    QLabel* totalCasLabelBridge;
    QLabel* totalLossLabelBridge;
    QLabel* totalRepairTimeLabelBridge;
    QLabel* totalFatalitiesLabelBridge;
    QLabel* structLossLabelBridge;
    QLabel* nonStructLossLabelBridge;
    QLabel* totalCasValueLabelBridge;
    QLabel* totalLossValueLabelBridge;
    QLabel* totalRepairTimeValueLabelBridge;
    QLabel* totalFatalitiesValueLabelBridge;
    QLabel* structLossValueLabelBridge;
    QLabel* nonStructLossValueLabelBridge;

    QLabel* totalCasLabelRoad;
    QLabel* totalLossLabelRoad;
    QLabel* totalRepairTimeLabelRoad;
    QLabel* totalFatalitiesLabelRoad;
    QLabel* structLossLabelRoad;
    QLabel* nonStructLossLabelRoad;
    QLabel* totalCasValueLabelRoad;
    QLabel* totalLossValueLabelRoad;
    QLabel* totalRepairTimeValueLabelRoad;
    QLabel* totalFatalitiesValueLabelRoad;
    QLabel* structLossValueLabelRoad;
    QLabel* nonStructLossValueLabelRoad;

    QLabel* totalCasLabelTunnel;
    QLabel* totalLossLabelTunnel;
    QLabel* totalRepairTimeLabelTunnel;
    QLabel* totalFatalitiesLabelTunnel;
    QLabel* structLossLabelTunnel;
    QLabel* nonStructLossLabelTunnel;
    QLabel* totalCasValueLabelTunnel;
    QLabel* totalLossValueLabelTunnel;
    QLabel* totalRepairTimeValueLabelTunnel;
    QLabel* totalFatalitiesValueLabelTunnel;
    QLabel* structLossValueLabelTunnel;
    QLabel* nonStructLossValueLabelTunnel;

    QWidget *tableWidget;

    QTableWidget* pelicunResultsTableWidget;

    QDockWidget* chartsDock1;
    QDockWidget* chartsDock2;
    QDockWidget* chartsDock3;

    VisualizationWidget* theVisualizationWidget;

    QComboBox* sortComboBox;

    std::unique_ptr<SimCenterMapcanvasWidget> mapViewSubWidget;

    QGraphicsView* mapViewMainWidget;

    QtCharts::QChart *RFDiagChartBridge;
    QtCharts::QChart *LosseschartBridge;
    QtCharts::QChart *RFDiagChartTunnel;
    QtCharts::QChart *LosseschartTunnel;
    QtCharts::QChart *RFDiagChartRoad;
    QtCharts::QChart *LosseschartRoad;

    QtCharts::QChart *Losseschart;
    QtCharts::QChartView *lossesChartView;

    QtCharts::QChart *casualtiesChart;
    QtCharts::QChart *RFDiagChart;
    QtCharts::QChartView *casualtiesChartView;
    QtCharts::QChartView *lossesRFDiagram;

    QtCharts::QChartView *lossesChartViewBridge;
    QtCharts::QChartView *lossesRFDiagramBridge;
    QtCharts::QChartView *lossesChartViewTunnel;
    QtCharts::QChartView *lossesRFDiagramTunnel;
    QtCharts::QChartView *lossesChartViewRoad;
    QtCharts::QChartView *lossesRFDiagramRoad;

    int createHistogramChart(REmpiricalProbabilityDistribution* probDist);

    int createLossesChart(QtCharts::QBarSet *LossSet1, QtCharts::QBarSet *LossSet2, QtCharts::QBarSet *LossSet3);

    int createCasualtiesChart(QtCharts::QBarSet *casualtiesSet);

    QByteArray uiState;

    // The number of header rows in the Pelicun results file
    int numHeaderRows;

    // kz: adding a dock layer under detailed results for different assets
    QDockWidget* tableDock;
    QDockWidget* tableDock2;

    // site response data table
    QTableWidget* siteResponseTableWidget;
    QWidget *tableWidget2;

    QTabWidget* resTabWidgetEcoLoss = nullptr;
    QTabWidget* resTabWidgetRelFreq = nullptr;
    // kz: adding site response result table
    void addSiteResponseTable(void);

    // processIMResults
    int processIMResults(const QVector<QStringList>& IMResults);

    // QGIS visualization
    QGISVisualizationWidget* QGISVisWidget;
};

#endif // PELICUN3POSTPROCESSORTSPN_H
