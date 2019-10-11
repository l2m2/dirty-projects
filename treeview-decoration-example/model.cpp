#include "model.h"
#include <QIcon>
#include <QPixmap>
#include <QPainter>

QColor str2Color(const QString &str)
{
    QColor color;
    if (str.startsWith('#') && str.length() == 9) {
        color.setNamedColor(str.left(7));
        color.setAlpha(str.right(2).toInt(0, 16));
    } else {
        color.setNamedColor(str);
    }
    return color;
}

QPixmap composePixmap(const QPixmap &pixmap, const QString &color)
{
    QPixmap other(pixmap);
    QPainter painter(&other);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(other.rect(), str2Color(color));
    painter.end();
    return other;
}

QIcon makeIcon()
{
    QPixmap org(":/bold.svg");
    QIcon icon(composePixmap(org, "red"));
    icon.addPixmap(composePixmap(org, "green"), QIcon::Normal, QIcon::On);
    icon.addPixmap(composePixmap(org, "blue"), QIcon::Disabled, QIcon::On);
    icon.addPixmap(composePixmap(org, "blue"), QIcon::Disabled, QIcon::Off);
    return icon;
}

Model::Model(QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Name" << "Gender";
    rootItem = new TreeItem(rootData);

    // for testing
    {
        QList<QVariant> data;
        data << "Leon" << "Male";
        auto item = new TreeItem(data, rootItem);
        rootItem->appendChild(item);
        {
            QList<QVariant> data;
            data << "Leon Son" << "Male";
            item->appendChild(new TreeItem(data, item));
        }
    }
    {
        QList<QVariant> data;
        data << "Sarah" << "Female";
        rootItem->appendChild(new TreeItem(data, rootItem));
    }
}

Model::~Model()
{
    delete rootItem;
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex Model::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex Model::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int Model::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int Model::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        return item->data(index.column());
    } else if (role == Qt::DecorationRole) {
        return QVariant::fromValue(makeIcon());
    } else {
        return QVariant();
    }

}
