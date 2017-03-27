#ifndef SVARCHSCUDVIEW_H
#define SVARCHSCUDVIEW_H

#include <QWidget>
#include <QMdiArea>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableView>
#include <QVBoxLayout>
#include <QModelIndex>

#define ARCHSCUD_SUBWINDOW_NAME "subw_archscud"

class SvArchSCUDView : public QWidget
{
    Q_OBJECT
  public:
    explicit SvArchSCUDView(QMdiArea* parent,
                             QString title);
    ~SvArchSCUDView();
    
  private:
    QSqlQueryModel *p_model;
    QTableView* table;
    
    int setTable();
    
  private slots:
    void slotTableDoubleClicked(QModelIndex);
    
  signals:
    
  public slots:
};

#endif // SVARCHSCUDVIEW_H
