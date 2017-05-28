/// @file
/// @brief QP/C++ port to Qt
/// @cond
///***************************************************************************
/// Last Updated for Version: QP 5.4.0/Qt 5.x
/// Last updated on  2015-05-03
///
///                    Q u a n t u m     L e a P s
///                    ---------------------------
///                    innovating embedded systems
///
/// Copyright (C) Quantum Leaps, www.state-machine.com.
///
/// This program is open source software: you can redistribute it and/or
/// modify it under the terms of the GNU General Public License as published
/// by the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// Alternatively, this program may be distributed and modified under the
/// terms of Quantum Leaps commercial licenses, which expressly supersede
/// the GNU General Public License and are specifically designed for
/// licensees interested in retaining the proprietary status of their code.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program. If not, see <http://www.gnu.org/licenses/>.
///
/// Contact information:
/// Web:   www.state-machine.com
/// Email: info@state-machine.com
///***************************************************************************
/// @endcond

#ifndef aothread_h
#define aothread_h

#include <QThread>

namespace QP {

class AOThread : public QThread {
    Q_OBJECT

public:
    AOThread(void *act)
      : m_act(act),
        m_isRunning(false)
    {}
    virtual ~AOThread();
    virtual void run();

public:
    void *m_act;
    bool  m_isRunning;
};

} // namespace QP

#endif // aothread_h
