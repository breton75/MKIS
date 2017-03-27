#ifndef SV_ZONE_H
#define SV_ZONE_H

#include "ui_sv_zone.h"
#include "ui_sv_new_zone.h"
#include "sv_zonedraw.h"
#include "sv_treeview.h"
#include "./COMMON/sv_zone_list.h"

#include <QDialog>
#include <QFileDialog>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>


namespace Ui {
  class SvZoneDialog;
}

namespace Ui_nz {
  class SvNewZoneDialog;
}
class SvZone : public QDialog
{
    Q_OBJECT
    
  public:
    explicit SvZone(QString zoneName,
                    bool allowEdit,
                    QWidget *parent = 0);
    ~SvZone();
    
    QList<QPointF>* p_list = new QList<QPointF>;
    
  private:
    Ui::SvZoneDialog *zui;
    GraphicsView *graphicsView;
    SvZoneDrawWidget* zdw;
    SvTreeView* dtv;
    
    void accept() Q_DECL_OVERRIDE;

};

class SvNewZone : public QDialog
{
    Q_OBJECT
    
  public:
    enum ShowMode { smNew = 0, smEdit = 1 };
    
    explicit SvNewZone(QWidget *parent = 0,
                       int showMode = smNew,
                       QString zoneName = "");
    ~SvNewZone();
    
    int t_id;
    QString t_zoneName = "";
    QString t_parentZoneName = "";
    QString t_imgPath = "";
    QString t_points = "";
    int t_sceneSize;
    QString t_description = "";
    int showMode;
    
  private:
    Ui_nz::SvNewZoneDialog *nzui;
    
    void accept() Q_DECL_OVERRIDE;
    
  private slots:
    void on_bnSelectParentZone_clicked();
    void on_ZONELIST_UI_closed();
    void on_gbChildable_clicked();
    void on_bnImgPath_clicked();

};

#endif // SV_ZONE_H
