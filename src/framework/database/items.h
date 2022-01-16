#ifndef ITEMS_H
#define ITEMS_H

#include <QVariantList>

// TODO: Should this file be moved to ``Pretzel/src/actions``?
namespace Pretzel::Actions
{
    void resetItemProperties(QVariantList args);
    void addItemProperty(QVariantList args);
    void updateItemProperty(QVariantList args);
} // namespace Pretzel::Actions

#endif // ITEMS_H
