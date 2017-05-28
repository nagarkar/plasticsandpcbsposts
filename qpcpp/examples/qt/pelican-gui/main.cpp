//****************************************************************************
// Product: QP/C++ example with Qt5
// Last Updated for Version: QP/C++ 5.5.0/Qt 5.x
// Last updated on  2015-09-25
//
//                    Q u a n t u m     L e a P s
//                    ---------------------------
//                    innovating embedded systems
//
// Copyright (C) Quantum Leaps, LLC. All rights reserved.
//
// This program is open source software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Alternatively, this program may be distributed and modified under the
// terms of Quantum Leaps commercial licenses, which expressly supersede
// the GNU General Public License and are specifically designed for
// licensees interested in retaining the proprietary status of their code.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
// Contact information:
// http://www.state-machine.com
// mailto:info@state-machine.com
//****************************************************************************
#include "gui.h"
//-----------------
#include "qpcpp.h"
#include "pelican.h"
#include "bsp.h"

//............................................................................
static QP::QSubscrList l_subscrSto[PELICAN::MAX_PUB_SIG];

static QF_MPOOL_EL(QP::QEvt) l_smlPoolSto[20]; // storage for small event pool

//............................................................................
int main(int argc, char *argv[]) {
    QP::GuiApp app(argc, argv);
    Gui gui;

    gui.show();

    QP::QF::init();  // initialize the framework
    BSP_init();      // initialize the Board Support Package

    // object dictionaries...
    QS_OBJ_DICTIONARY(l_smlPoolSto);

    // initialize publish-subscribe...
    QP::QF::psInit(l_subscrSto, Q_DIM(l_subscrSto));

    // initialize event pools...
    QP::QF::poolInit(l_smlPoolSto,
                sizeof(l_smlPoolSto), sizeof(l_smlPoolSto[0]));

    // start the active objects...
    PELICAN::AO_Pelican->start(1U,
                 (QP::QEvt const **)0, 0U, // no queue
                 (void *)0, 0U); // default stack size

    return QP::QF::run(); // calls qApp->exec()
}
