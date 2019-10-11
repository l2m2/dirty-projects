#ifndef MODEL_H
#define MODEL_H

#include <QAbstractItemModel>
#include "treeitem.h"

class Model : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = 0);
    ~Model();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    TreeItem *rootItem;
};

#endif // MODEL_H
