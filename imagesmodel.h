#ifndef IMAGESMODEL_H
#define IMAGESMODEL_H

#include <QAbstractListModel>
#include <QPixmap>

struct thumb
{
    thumb() {;}
    ~thumb() {;}



    QImage pixmap;
    QString name;
};
Q_DECLARE_METATYPE(thumb)

class ImagesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ImagesModel(QList<thumb> *pThumbList, QObject *parent = 0);

public slots:
    void addItem(thumb pThumb);
protected:
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    
signals:
    
public slots:

private:
    QList<thumb> *thumbList;
    
};

#endif // IMAGESMODEL_H
