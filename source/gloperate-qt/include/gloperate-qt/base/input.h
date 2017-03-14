
#pragma once


#include <QMouseEvent>

#include <glm/fwd.hpp>

#include <gloperate/input/constants.h>

#include <gloperate-qt/gloperate-qt_api.h>


class QPoint;


namespace gloperate_qt
{


GLOPERATE_QT_API glm::ivec2 fromQPoint(const QPoint & point);
GLOPERATE_QT_API gloperate::MouseButton fromQtMouseButton(Qt::MouseButton button);
GLOPERATE_QT_API gloperate::Key fromQtKeyCode(int key, int mods);
GLOPERATE_QT_API gloperate::KeyModifier fromQtModifiers(int mods);


} // namespace gloperate_qt
