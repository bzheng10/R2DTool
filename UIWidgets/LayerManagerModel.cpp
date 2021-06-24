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

// Written by: Stevan Gavrilovic

#include "LayerManagerModel.h"
#include "GISObjectTypeMapping.h"

#include "SimpleMarkerSymbol.h"
#include "SimpleRenderer.h"
#include "SimpleFillSymbol.h"
#include "FeatureCollectionLayer.h"

#include <QBrush>

using namespace Esri::ArcGISRuntime;

LayerManagerModel::LayerManagerModel(QObject* parent) : QAbstractTableModel(parent)
{

}


void LayerManagerModel::setLayer(Esri::ArcGISRuntime::FeatureCollectionLayer *layer)
{
    beginResetModel();
    m_layer = layer;
    endResetModel();
}


int LayerManagerModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid() || !m_layer)
        return 0;

    return m_layer->featureCollection()->tables()->size();
}


int LayerManagerModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 4;
}


QVariant LayerManagerModel::data(const QModelIndex &index, int role) const
{

    if (!m_layer)
        return QVariant();

    auto renderer = m_layer->featureCollection()->tables()->at(index.row())->renderer();

    auto rendererType = renderer->rendererType();

    auto section = index.column();

    switch(section)
    {
    case 0:
    {
        if (role != Qt::DisplayRole)
            return QVariant();

        if(rendererType == RendererType::SimpleRenderer)
        {
            auto s_renderer = static_cast<SimpleRenderer*>(renderer);
            return s_renderer->label();
        }

        return QVariant();
    }
    case 1:
    {
        if (role != Qt::DisplayRole)
            return QVariant();

        if(rendererType == RendererType::SimpleRenderer)
        {
            auto s_renderer = static_cast<SimpleRenderer*>(renderer);

            auto symbol = s_renderer->symbol();

            auto s_symbolType = symbol->symbolType();

            if(s_symbolType == SymbolType::SimpleMarkerSymbol)
            {
                auto s_markerSymbol = static_cast<SimpleMarkerSymbol*>(symbol);

                auto s_markerSymbolStyle = s_markerSymbol->style();

                return getTextFromMarkerSymbolType(s_markerSymbolStyle);
            }
            else if(s_symbolType == SymbolType::SimpleLineSymbol)
            {
                auto s_markerSymbol = static_cast<SimpleLineSymbol*>(symbol);

                auto s_markerSymbolStyle = s_markerSymbol->style();

                return getTextFromLineSymbolType(s_markerSymbolStyle);
            }
            else if(s_symbolType == SymbolType::SimpleFillSymbol)
            {
                auto s_markerSymbol = static_cast<SimpleFillSymbol*>(symbol);

                auto s_markerSymbolStyle = s_markerSymbol->style();

                return getTextFromFillSymbolType(s_markerSymbolStyle);
            }
            else
            {
                return QVariant();
            }
        }

        return QVariant();
    }
    case 2:
    {
        if (role != Qt::DisplayRole)
            return QVariant();

        if(rendererType == RendererType::SimpleRenderer)
        {
            auto s_renderer = static_cast<SimpleRenderer*>(renderer);

            auto symbol = s_renderer->symbol();

            auto s_symbolType = symbol->symbolType();

            if(s_symbolType == SymbolType::SimpleMarkerSymbol)
            {
                auto s_markerSymbol = static_cast<SimpleMarkerSymbol*>(symbol);

                return s_markerSymbol->size();
            }
            else if(s_symbolType == SymbolType::SimpleLineSymbol)
            {
                auto s_markerSymbol = static_cast<SimpleLineSymbol*>(symbol);

                return s_markerSymbol->width();
            }
            else
            {
                return "N/A";
            }
        }

        return QVariant();
    }
    case 3:
    {
        if (role != Qt::BackgroundRole)
            return QVariant();

        if(rendererType == RendererType::SimpleRenderer)
        {
            auto s_renderer = static_cast<SimpleRenderer*>(renderer);

            auto renSym = s_renderer->symbol();

            auto symType = renSym->symbolType();

            if(symType == SymbolType::SimpleFillSymbol)
            {
                auto fillSym = static_cast<SimpleFillSymbol*>(renSym);

                auto currColor = fillSym->color();

                QBrush colBackground(currColor);

                return colBackground;
            }
            else if(symType == SymbolType::SimpleLineSymbol)
            {
                auto fillSym = static_cast<SimpleLineSymbol*>(renSym);

                auto currColor = fillSym->color();

                QBrush colBackground(currColor);

                return colBackground;
            }
            else if(symType == SymbolType::SimpleMarkerSymbol)
            {
                auto fillSym = static_cast<SimpleMarkerSymbol*>(renSym);

                auto currColor = fillSym->color();

                QBrush colBackground(currColor);

                return colBackground;
            }
        }


        return QVariant();
    }
    }

    return QVariant();
}


bool LayerManagerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if (!m_layer || role != Qt::EditRole)
        return false;

    auto renderer = m_layer->featureCollection()->tables()->at(index.row())->renderer();

    auto rendererType = renderer->rendererType();

    auto section = index.column();

    switch(section)
    {
    case 0:
    {
        // If we are in the first column then we need to set the name
        auto nameVal = value.toString();

        if(rendererType == RendererType::SimpleRenderer)
        {
            auto s_renderer = static_cast<SimpleRenderer*>(renderer);
            s_renderer->setLabel(nameVal);
        }

        break;
    }
    case 1:
    {
        // In the second column set the symbol type
        if(rendererType == RendererType::SimpleRenderer)
        {
            auto s_renderer = static_cast<SimpleRenderer*>(renderer);

            auto symbol = s_renderer->symbol();

            auto s_symbolType = symbol->symbolType();

            if(s_symbolType == SymbolType::SimpleMarkerSymbol)
            {
                auto symStyleInt = getMarkerSymbolTypeFromText(value.toString());
                if(symStyleInt == -1)
                    break;

                auto s_markerSymbol = static_cast<SimpleMarkerSymbol*>(symbol);

                auto symStyle = static_cast<Esri::ArcGISRuntime::SimpleMarkerSymbolStyle>(symStyleInt);

                s_markerSymbol->setStyle(symStyle);
            }
            else if(s_symbolType == SymbolType::SimpleLineSymbol)
            {
                auto symStyleInt = getLineSymbolTypeFromText(value.toString());
                if(symStyleInt == -1)
                    break;

                auto s_markerSymbol = static_cast<SimpleLineSymbol*>(symbol);

                auto symStyle = static_cast<Esri::ArcGISRuntime::SimpleLineSymbolStyle>(symStyleInt);

                s_markerSymbol->setStyle(symStyle);
            }
            else if(s_symbolType == SymbolType::SimpleFillSymbol)
            {
                auto symStyleInt = getFillSymbolTypeFromText(value.toString());
                if(symStyleInt == -1)
                    break;

                auto s_markerSymbol = static_cast<SimpleFillSymbol*>(symbol);

                auto symStyle = static_cast<Esri::ArcGISRuntime::SimpleFillSymbolStyle>(symStyleInt);

                s_markerSymbol->setStyle(symStyle);
            }
        }

        break;
    }
    case 2:
    {
        // Here we set the symbol size if applicable
        auto symSize = value.toFloat();

        if(rendererType == RendererType::SimpleRenderer)
        {
            auto s_renderer = static_cast<SimpleRenderer*>(renderer);

            auto symbol = s_renderer->symbol();

            auto s_symbolType = symbol->symbolType();

            if(s_symbolType == SymbolType::SimpleMarkerSymbol)
            {
                auto s_markerSymbol = static_cast<SimpleMarkerSymbol*>(symbol);
                s_markerSymbol->setSize(symSize);
            }
            else if(s_symbolType == SymbolType::SimpleLineSymbol)
            {
                auto s_markerSymbol = static_cast<SimpleLineSymbol*>(symbol);
                s_markerSymbol->setWidth(symSize);
            }
        }

        break;
    }
    case 3:
    {

        // Here we set the color

        auto symCol = value.value<QColor>();

        if(rendererType == RendererType::SimpleRenderer)
        {
            auto s_renderer = static_cast<SimpleRenderer*>(renderer);

            auto renSym = s_renderer->symbol();

            auto symType = renSym->symbolType();

            if(symType == SymbolType::SimpleFillSymbol)
            {
                auto fillSym = static_cast<SimpleFillSymbol*>(renSym);

                fillSym->setColor(symCol);
            }
            else if(symType == SymbolType::SimpleLineSymbol)
            {
                auto fillSym = static_cast<SimpleLineSymbol*>(renSym);

                fillSym->setColor(symCol);
            }
            else if(symType == SymbolType::SimpleMarkerSymbol)
            {
                auto fillSym = static_cast<SimpleMarkerSymbol*>(renSym);

                fillSym->setColor(symCol);
            }
        }

        break;
    }

    }

    emit dataChanged(index, index, {role});
    return true;
}


QVariant LayerManagerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};

    switch(section)
    {
    case 0: return "Name";
    case 1: return "Symbol";
    case 2: return "Size";
    case 3: return "Color";

    default: return {};
    }


}


Qt::ItemFlags LayerManagerModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
    {
        auto section = index.column();

        switch(section)
        {
        case 0: return QAbstractTableModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsEditable;
        case 1: return QAbstractTableModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsEditable;
        case 2: return QAbstractTableModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsEditable;
        case 3: return Qt::ItemIsEnabled;

        default: return QAbstractTableModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsEditable;
        }
    }

    return QAbstractTableModel::flags(index);
}







