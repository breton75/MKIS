#ifndef SVARCHVIDEOVIEW_H
#define SVARCHVIDEOVIEW_H

#include <QWidget>
#include <QMdiArea>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableView>
#include <QVBoxLayout>
#include <QModelIndex>

#define ARCHVIDEO_SUBWINDOW_NAME "subw_archvideo"

class SvArchVideoView : public QWidget
{
    Q_OBJECT
  public:
    explicit SvArchVideoView(QMdiArea* parent,
                             QString title);
    ~SvArchVideoView();
    
  private:
    QSqlQueryModel *p_model;
    QTableView* table;
    
    int setTable();
    
  private slots:
    void slotTableDoubleClicked(QModelIndex);
    
  signals:
    
  public slots:
};

#endif // SVARCHVIDEOVIEW_H
