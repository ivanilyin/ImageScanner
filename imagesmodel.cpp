#include "imagesmodel.h"
#include <QtGui>

ImagesModel::ImagesModel(QList<thumb> *pThumbList , QObject *parent) :
    QAbstractListModel(parent), thumbList(pThumbList)
{
}

void ImagesModel::addItem(thumb pThumb)
{
    beginInsertRows(QModelIndex(), thumbList->count(), thumbList->count());
    thumbList->append(pThumb);
    endInsertRows();
}

QVariant ImagesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    int objIndex = index.row();

    switch (role) {

    case Qt::DecorationRole:
        return thumbList->at(objIndex).pixmap;
        break;

    case Qt::DisplayRole:
        return thumbList->at(objIndex).name;
        break;
    }

    return QVariant();
}

int ImagesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (thumbList) {
        return thumbList->count();
    }

    return 0;
}

int ImagesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 1;
}
