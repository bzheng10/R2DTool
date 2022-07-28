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
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
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

// Written by: Frank McKenna

#include "AnalysisWidget.h"
#include "ComponentInputWidget.h"
#include "InputWidgetOpenSeesAnalysis.h"
#include "InputWidgetOpenSeesPyAnalysis.h"
#include "NoArgSimCenterApp.h"
#include "NoneWidget.h"
#include "SecondaryComponentSelection.h"
#include "SimCenterAppSelection.h"
#include "VisualizationWidget.h"
#include "sectiontitle.h"

// Qt headers
#include <QCheckBox>
#include <QColorTransform>
#include <QDebug>
#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QJsonArray>
#include <QJsonObject>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPointer>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

AnalysisWidget::AnalysisWidget(QWidget *parent)
    : MultiComponentR2D(parent)
{

  buildingWidget = new SimCenterAppSelection(QString("Building Analysis Engine"), QString("Simulation"), this);

  SimCenterAppWidget *openSeesPy = new InputWidgetOpenSeesPyAnalysis(this);
  //SimCenterAppWidget *openSees = new InputWidgetOpenSeesAnalysis(theRVContainer,this);
  SimCenterAppWidget *openSees = new NoArgSimCenterApp(QString("OpenSees-Simulation_R"));
  SimCenterAppWidget *imAsEDP = new NoArgSimCenterApp(QString("IMasEDP"));

  buildingWidget->addComponent(QString("OpenSees"), QString("OpenSees-Simulation_R"), openSees);
  buildingWidget->addComponent(QString("OpenSeesPy"), QString("OpenSeesPy-Simulation"), openSeesPy);
  buildingWidget->addComponent(QString("IMasEDP"), QString("IMasEDP"), imAsEDP);
  //buildingWidget->addComponent(QString("None"), QString("None"), noneWidget);

  pipelineWidget = new SimCenterAppSelection(QString("Pipeline Analysis Engine"), QString("PipelineSimulation"), this);

  this->addComponent("Buildings", buildingWidget);
  this->addComponent("Gas Network",pipelineWidget);
  this->hideAll();
}


AnalysisWidget::~AnalysisWidget()
{

}


void AnalysisWidget::clear(void)
{
    buildingWidget->clear();
    pipelineWidget->clear();
}






