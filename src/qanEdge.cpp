/*
 Copyright (c) 2008-2017, Benoit AUTHEMAN All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the author or Destrat.io nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL AUTHOR BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

//-----------------------------------------------------------------------------
// This file is a part of the QuickQanava software library.
//
// \file	qanEdge.cpp
// \author	benoit@destrat.io
// \date	2004 February 15
//-----------------------------------------------------------------------------

// Qt headers
#include <QBrush>
#include <QPainter>

// QuickQanava headers
#include "./qanNode.h"
#include "./qanEdge.h"
#include "./qanEdgeItem.h"
#include "./qanGraph.h"

namespace qan { // ::qan

/* Edge Object Management *///-------------------------------------------------
Edge::Edge() :
    gtpo::GenEdge< qan::GraphConfig >{}
{
}

Edge::~Edge()
{
    if ( _item )
        _item->deleteLater();
}

qan::Graph* Edge::getGraph() noexcept {
    return qobject_cast< qan::Graph* >( gtpo::GenEdge< qan::GraphConfig >::getGraph() );
}

const qan::Graph* Edge::getGraph() const noexcept {
    return qobject_cast< const qan::Graph* >( gtpo::GenEdge< qan::GraphConfig >::getGraph() );
}

qan::EdgeItem*   Edge::getItem() noexcept { return _item.data(); }

void    Edge::setItem(qan::EdgeItem* edgeItem) noexcept
{
    if ( edgeItem != nullptr ) {
        _item = edgeItem;
        if ( edgeItem->getEdge() != this )
            edgeItem->setEdge(this);
    }
}
//-----------------------------------------------------------------------------

/* Node Static Factories *///--------------------------------------------------
static std::unique_ptr<QQmlComponent>   qan_Edge_delegate;
static std::unique_ptr<qan::EdgeStyle>  qan_Edge_style;

QQmlComponent*  Edge::delegate(QObject* caller) noexcept
{
    if ( !qan_Edge_delegate &&
         caller != nullptr ) {
        const auto engine = qmlEngine(caller);
        if ( engine != nullptr ) {
            qan_Edge_delegate = std::make_unique<QQmlComponent>(engine, "qrc:/QuickQanava/Edge.qml");
        }
    }
    return qan_Edge_delegate.get();
}

qan::EdgeStyle* Edge::style() noexcept
{
    if ( !qan_Edge_style )
        qan_Edge_style = std::make_unique<qan::EdgeStyle>();
    return qan_Edge_style.get();
}
//-----------------------------------------------------------------------------

/*! \name Edge Topology Management *///------------------------------------
qan::Node*  Edge::getSource() noexcept
{
    return qobject_cast<qan::Node*>(getSrc().lock().get());
}

qan::Node*  Edge::getDestination() noexcept
{
    return qobject_cast<qan::Node*>(getDst().lock().get());
}

qan::Edge*  Edge::getHDestination() noexcept
{
    return qobject_cast<qan::Edge*>(getHDst().lock().get());
}

QAbstractItemModel* Edge::getInHNodesModel() const { return const_cast<QAbstractItemModel*>( static_cast< const QAbstractItemModel* >( &getInHNodes() ) ); }
//-----------------------------------------------------------------------------

/* Edge Properties Management *///---------------------------------------------
void    Edge::setLabel( const QString& label )
{
    if ( label != _label ) {
        _label = label;
        emit labelChanged( );
    }
}

void     Edge::setWeight( qreal weight )
{
    if ( !qFuzzyCompare( 1.0 + weight, 1.0 + _weight ) ) {
        _weight = weight;
        emit weightChanged();
    }
}
//-----------------------------------------------------------------------------

} // ::qan
